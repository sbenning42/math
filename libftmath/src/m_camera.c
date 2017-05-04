/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 00:44:20 by                   #+#    #+#             */
/*   Updated: 2017/05/04 14:34:36 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_camera.h"

static t_matrix	*camera_transp_translation(t_vertex *position)
{
	t_vector	*vct;
	t_vector	*oppvct;
	t_matrix	*t_translate;

	if (!(vct = m_vector_new(position, NULL)))
		return (NULL);
	if (!(oppvct = m_vector_opposite(vct)))
		return (NULL);
	if (!(t_translate = m_matrix_new(M_TRANSLATION, oppvct)))
		return (NULL);
	m_vector_del(&oppvct);
	m_vector_del(&vct);
	return (t_translate);
}

static void		dump_conf(t_camera *cam, double *conf)
{
	cam->fov = conf[FOV];
	cam->ratio = conf[RATIO];
	cam->near = conf[NEAR];
	cam->far = conf[FAR];
	cam->width = cam->ratio * 480;
	cam->height = 480;
}

t_camera		*m_camera(t_vertex *position, t_matrix *rotation, double *conf)
{
	t_camera	*cam;
	char		buf[4096 + 1];

	if (!(cam = ft_memalloc(sizeof(t_camera))))
		return (NULL);
	dump_conf(cam, conf);
	if (!(cam->position = m_vertex_new(\
					position->v[0], position->v[1], \
					position->v[2], position->c)))
		return (NULL);
	if (!(cam->t_translate = camera_transp_translation(position)))
		return (NULL);
	if (!(cam->t_rotate = m_matrix_transp(rotation)))
		return (NULL);
	if (!(cam->view = m_matrix_mult(cam->t_rotate, cam->t_translate)))
		return (NULL);
	if (!(cam->project = m_matrix_new(M_PROJECTION, \
					cam->fov, cam->ratio, cam->near, cam->far)))
		return (NULL);
	if (g_s_camera_verbose == 1)
	{
		m_camera_str(cam, buf, 4096);
		ft_printf("New %s ;\n", buf);
	}
	return (cam);
}

void			m_camera_del(t_camera **cam)
{
	char		buf[4096 + 1];

	if (*cam)
	{
		if (g_s_camera_verbose == 1)
		{
			m_camera_str(*cam, buf, 4096);
			ft_printf("Del %s ;\n", buf);
		}
		m_matrix_del(&(*cam)->project);
		m_matrix_del(&(*cam)->view);
		m_matrix_del(&(*cam)->t_rotate);
		m_matrix_del(&(*cam)->t_translate);
		m_vertex_del(&(*cam)->position);
		free(*cam);
		*cam = NULL;
	}
}

char			*m_camera_str(t_camera *cam, char *buf, size_t n)
{
	char		lbuf[4096 + 1];
	char		bufs[5][1024 + 1];

	if (!buf)
	{
		buf = lbuf;
		n = 4096;
	}
	if (cam)
	{
		m_vertex_str(cam->position, bufs[0], 1024);
		m_matrix_str(cam->t_translate, bufs[1], 1024);
		m_matrix_str(cam->t_rotate, bufs[2], 1024);
		m_matrix_str(cam->view, bufs[3], 1024);
		m_matrix_str(cam->project, bufs[4], 1024);
		snprintf(buf, 4096, M_CAMERASTR, \
				cam->fov, cam->width, cam->height, cam->ratio, cam->near, \
				cam->far, bufs[0], bufs[1], bufs[2], bufs[3], bufs[4]);
	}
	else
		ft_snprintf(buf, n, "null");
	return ((buf == lbuf ? ft_strdup(buf) : buf));
}

t_vertex		*m_camera_watch_vertex(t_camera *cam, t_vertex *world_vtx)
{
	t_vertex	*view_vtx;
	t_vertex	*ndc_vtx;
	t_vertex	*vtx;

	if (!(view_vtx = m_matrix_apply_vertex(cam->view, world_vtx)))
		return (NULL);
	if (!(ndc_vtx = m_matrix_apply_vertex(cam->project, view_vtx)))
		return (NULL);
	m_vertex_del(&view_vtx);
	if (!(vtx = m_vertex_new(\
					(1.0 + ndc_vtx->v[0]) * cam->width / 2.0, \
					(1.0 + ndc_vtx->v[1]) * cam->height / 2.0, \
					ndc_vtx->v[2], ndc_vtx->c)))
		return (NULL);
	m_vertex_del(&ndc_vtx);
	return (vtx);
}

static int		camera_setvisible(t_camera *cam, t_triangle *tri)
{
	t_vertex	*centroid;
	t_vector	*view_vct;
	t_vector	*normal;
	double		visible;

	if (m_triangle_normal(tri, &normal))
		return (-1);
	if (!(centroid = m_triangle_centroid(tri)))
		return (-1);
	if (!(view_vct = m_vector_new(centroid, cam->position)))
		return (-1);
	m_vertex_del(&centroid);
	visible = -m_vector_dot(view_vct, normal);
	m_vector_del(&view_vct);
	if (visible >= 0.0)
		tri->visible = 0;
	else
		tri->visible = 1;
	return (0);
}

t_triangle		*m_camera_watch_triangle(t_camera *cam, t_triangle *world_tri)
{
	t_triangle	*tri;
	t_vertex	*vtxs[3];

	if (!(vtxs[0] = m_camera_watch_vertex(cam, world_tri->a)))
		return (NULL);
	if (!(vtxs[1] = m_camera_watch_vertex(cam, world_tri->b)))
		return (NULL);
	if (!(vtxs[2] = m_camera_watch_vertex(cam, world_tri->c)))
		return (NULL);
	if (!(tri = m_triangle(vtxs[0], vtxs[1], vtxs[2])))
		return (NULL);
	if (camera_setvisible(cam, tri))
		return (NULL);
	m_vertex_del(vtxs + 0);
	m_vertex_del(vtxs + 1);
	m_vertex_del(vtxs + 2);
	return (tri);
}

t_mesh			*m_camera_watch_mesh(t_camera *cam, t_mesh *world_mesh)
{
	t_mesh		*mesh;
	t_mesh		*ntri;
	t_triangle	*tri;

	mesh = NULL;
	while (world_mesh)
	{
		if (!(tri = m_camera_watch_triangle(cam, world_mesh->tri)))
			return (NULL);
		if (!(ntri = m_mesh_new(tri)))
			return (NULL);
		m_mesh_add(&mesh, ntri);
		world_mesh = world_mesh->next;
	}
	return (mesh);
}

t_camera		*m_cam(void)
{
	t_vertex	*position;
	t_matrix	*rotation;
	t_camera	*camera;
	double		conf[CONFIGSIZE];

	conf[FOV] = GLOBAL_FOV;
	conf[RATIO] = GLOBAL_RATIO;
	conf[NEAR] = GLOBAL_NEAR;
	conf[FAR] = GLOBAL_FAR;
	if (!(position = m_vertex_new(GLOBAL_XCAM, GLOBAL_YCAM, GLOBAL_ZCAM, NULL)))
		return (NULL);
	if (!(rotation = m_matrix_new(M_RY, GLOBAL_YROT)))
		return (NULL);
	if (!(camera = m_camera(position, rotation, conf)))
		return (NULL);
	m_matrix_del(&rotation);
	m_vertex_del(&position);
	return (camera);
}
