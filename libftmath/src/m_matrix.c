/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_matrix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 22:11:37 by                   #+#    #+#             */
/*   Updated: 2017/05/04 14:29:02 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_matrix.h"

static t_matrix	*make_identity_preset(t_matrix *m, va_list *ap)
{
	m->v[0][0] = 1.0;
	m->v[1][1] = 1.0;
	m->v[2][2] = 1.0;
	m->v[3][3] = 1.0;
	return (m);
	(void)ap;
}

static t_matrix	*make_scale_preset(t_matrix *m, va_list *ap)
{
	double		scale;

	scale = va_arg(*ap, double);
	m = make_identity_preset(m, NULL);
	m->v[0][0] = scale;
	m->v[1][1] = scale;
	m->v[2][2] = scale;
	return (m);
}

static t_matrix	*make_rx_preset(t_matrix *m, va_list *ap)
{
	double		phi;

	phi = va_arg(*ap, double);
	m = make_identity_preset(m, NULL);
	m->v[1][1] = cos(phi);
	m->v[1][2] = -sin(phi);
	m->v[2][1] = sin(phi);
	m->v[2][2] = cos(phi);
	return (m);
}

static t_matrix	*make_ry_preset(t_matrix *m, va_list *ap)
{
	double		psi;

	psi = va_arg(*ap, double);
	m = make_identity_preset(m, NULL);
	m->v[0][0] = cos(psi);
	m->v[0][2] = sin(psi);
	m->v[2][0] = -sin(psi);
	m->v[2][2] = cos(psi);
	return (m);
}

static t_matrix	*make_rz_preset(t_matrix *m, va_list *ap)
{
	double		teta;

	teta = va_arg(*ap, double);
	m = make_identity_preset(m, NULL);
	m->v[0][0] = cos(teta);
	m->v[0][1] = -sin(teta);
	m->v[1][0] = sin(teta);
	m->v[1][1] = cos(teta);
	return (m);
}

static t_matrix	*make_translation_preset(t_matrix *m, va_list *ap)
{
	t_vector	*vct;

	vct = (t_vector *)va_arg(*ap, void *);
	m = make_identity_preset(m, NULL);
	m->v[0][3] += vct->v[0];
	m->v[1][3] += vct->v[1];
	m->v[2][3] += vct->v[2];
	return (m);
}

static t_matrix	*make_opengl_frustrum(t_matrix *m, double *conf, double *rltb)
{
	m->v[0][0] = (2.0 * conf[NEAR]) / (rltb[RIGHT] - rltb[LEFT]);
	m->v[0][1] = 0.0;
	m->v[0][2] = (rltb[RIGHT] + rltb[LEFT]) / (rltb[RIGHT] - rltb[LEFT]);
	m->v[0][3] = 0.0;
	m->v[1][0] = 0.0;
	m->v[1][1] = (2.0 * conf[NEAR]) / (rltb[TOP] - rltb[BOTTOM]);
	m->v[1][2] = (rltb[TOP] + rltb[BOTTOM]) / (rltb[TOP] - rltb[BOTTOM]);
	m->v[1][3] = 0.0;
	m->v[2][0] = 0.0;
	m->v[2][1] = 0.0;
	m->v[2][2] = -((conf[FAR] + conf[NEAR]) / (conf[FAR] - conf[NEAR]));
	m->v[2][3] = -((2.0 * conf[FAR] * conf[NEAR]) / (conf[FAR] - conf[NEAR]));
	m->v[3][0] = 0.0;
	m->v[3][1] = 0.0;
	m->v[3][2] = -1.0;
	m->v[3][3] = 0.0;
	return (m);
}

static double	deg2rad(double deg)
{
	return (deg * M_PI / 180.0);
}

static t_matrix	*make_opengl_projection_preset(t_matrix *m, double *conf)
{
	double		scale;
	double		rltb[4];

	scale = tan(deg2rad(conf[FOV] * 0.5)) * conf[NEAR];
	rltb[RIGHT] = conf[RATIO] * scale;
	rltb[LEFT] = -rltb[RIGHT];
	rltb[TOP] = scale;
	rltb[BOTTOM] = -rltb[TOP];
	return (make_opengl_frustrum(m, conf, rltb));
}

static t_matrix	*make_projection_preset(t_matrix *m, va_list *ap)
{
	double		conf[CONFIGSIZE];

	conf[FOV] = va_arg(*ap, double);
	conf[RATIO] = va_arg(*ap, double);
	conf[NEAR] = va_arg(*ap, double);
	conf[FAR] = va_arg(*ap, double);
	return (make_opengl_projection_preset(m, conf));
}

t_select_preset	g_select_preset[] = {\
	{M_IDENTITY, make_identity_preset}, \
	{M_SCALE, make_scale_preset}, \
	{M_RX, make_rx_preset}, \
	{M_RY, make_ry_preset}, \
	{M_RZ, make_rz_preset}, \
	{M_TRANSLATION, make_translation_preset}, \
	{M_PROJECTION, make_projection_preset}, \
	{0, 0}\
};

static t_matrix	*make_empty_preset(t_matrix *m, va_list *ap)
{
	return (m);
	(void)ap;
}

static t_matrix	*(*select_preset(int preset))(t_matrix *, va_list *)
{
	int			i;

	i = -1;
	while (g_select_preset[++i].preset > 0)
	{
		if (g_select_preset[i].preset == preset)
			return (g_select_preset[i].make);
	}
	return (make_empty_preset);
}

static t_matrix	*matrix_new_ap(int preset, va_list *ap)
{
	t_matrix	*m;

	if (!(m = ft_memalloc(sizeof(t_matrix))))
		return (NULL);
	return (select_preset(preset)(m, ap));
}

t_matrix		*m_matrix_new(int preset, ...)
{
	va_list		ap;
	t_matrix	*m;
	char		buf[1024 + 1];

	va_start(ap, preset);
	m = matrix_new_ap(preset, &ap);
	va_end(ap);
	if (m && g_s_matrix_verbose == 1)
	{
		m_matrix_str(m, buf, 1024);
		ft_printf("New %s ;\n", buf);
	}
	return (m);
}

void			m_matrix_del(t_matrix **m)
{
	char		buf[1024 + 1];

	if (*m && g_s_matrix_verbose == 1)
	{
		m_matrix_str(*m, buf, 1024);
		ft_printf("Del %s ;\n", buf);
	}
	if (*m)
	{
		free(*m);
		*m = NULL;
	}
}

char			*m_matrix_str(t_matrix *m, char *buf, size_t n)
{
	char		lbuf[1024 + 1];

	if (!buf)
	{
		buf = lbuf;
		n = 1024;
	}
	if (m)
		snprintf(buf, n, M_MTXSTR, \
				m->v[0][0], m->v[0][1], m->v[0][2], m->v[0][3], \
				m->v[1][0], m->v[1][1], m->v[1][2], m->v[1][3], \
				m->v[2][0], m->v[2][1], m->v[2][2], m->v[2][3], \
				m->v[3][0], m->v[3][1], m->v[3][2], m->v[3][3]);
	else
		snprintf(buf, n, "null");
	return ((buf == lbuf ? ft_strdup(buf) : buf));
}

t_matrix		*m_matrix_mult(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*m;
	int			i;
	int			j;

	if (!(m = m_matrix_new(M_IDENTITY)))
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			m->v[i][j] = m1->v[i][0] * m2->v[0][j] \
						 + m1->v[i][1] * m2->v[1][j] \
						 + m1->v[i][2] * m2->v[2][j] \
						 + m1->v[i][3] * m2->v[3][j];
	}
	return (m);
}

t_matrix		*m_matrix_transp(t_matrix *m1)
{
	t_matrix	*m;
	int			i;
	int			j;

	if (!(m = m_matrix_new(M_IDENTITY)))
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			m->v[i][j] = m1->v[j][i];
	}
	return (m);
}

t_vertex		*m_matrix_apply_vertex(t_matrix *m, t_vertex *vtx)
{
	double		x;
	double		y;
	double		z;
	double		w;

	x = vtx->v[0] * m->v[0][0] \
		+ vtx->v[1] * m->v[0][1] \
		+ vtx->v[2] * m->v[0][2] \
		+ m->v[0][3];
	y = vtx->v[0] * m->v[1][0] \
		+ vtx->v[1] * m->v[1][1] \
		+ vtx->v[2] * m->v[1][2] \
		+ m->v[1][3];
	z = vtx->v[0] * m->v[2][0] \
		+ vtx->v[1] * m->v[2][1] \
		+ vtx->v[2] * m->v[2][2] \
		+ m->v[2][3];
	w = vtx->v[0] * m->v[3][0] \
		+ vtx->v[1] * m->v[3][1] \
		+ vtx->v[2] * m->v[3][2] \
		+ m->v[3][3];
	return (m_vertex_new(x / w, y / w, z / w, vtx->c));
}

t_triangle		*m_matrix_apply_triangle(t_matrix *m, t_triangle *tri)
{
	t_triangle	*ntri;
	t_vertex	*vtxs[3];

	if (!(vtxs[0] = m_matrix_apply_vertex(m, tri->a)))
		return (NULL);
	if (!(vtxs[1] = m_matrix_apply_vertex(m, tri->b)))
		return (NULL);
	if (!(vtxs[2] = m_matrix_apply_vertex(m, tri->c)))
		return (NULL);
	ntri = m_triangle(vtxs[0], vtxs[1], vtxs[2]);
	m_vertex_del(vtxs + 0);
	m_vertex_del(vtxs + 1);
	m_vertex_del(vtxs + 2);
	return (ntri);
}

t_mesh			*m_matrix_apply_mesh(t_matrix *m, t_mesh *mesh)
{
	t_mesh		*nmesh;
	t_mesh		*ntri;
	t_triangle	*tri;

	nmesh = NULL;
	while (mesh)
	{
		if (!(tri = m_matrix_apply_triangle(m, mesh->tri)))
			return (NULL);
		if (!(ntri = m_mesh_new(tri)))
			return (NULL);
		m_mesh_add(&nmesh, ntri);
		mesh = mesh->next;
	}
	return (nmesh);
}
