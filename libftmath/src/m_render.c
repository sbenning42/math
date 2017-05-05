/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:56:28 by                   #+#    #+#             */
/*   Updated: 2017/05/05 02:10:45 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_render.h"

t_render		*m_render_new(double width, double height, char *buf, \
								int bpp, int sizel, int endian)
{
	char		lbuf[1024 + 1];
	t_render	*render;

	if (!(render = ft_memalloc(sizeof(t_render))))
		return (NULL);
	render->buf = buf;
	render->width = width;
	render->height = height;
	render->bpp = bpp;
	render->sizel = sizel;
	render->endian = endian;
	if (render && g_s_render_verbose)
	{
		m_render_str(render, lbuf, 1024);
		ft_printf("New %s ;\n", lbuf);
	}
	return (render);
}

void			m_render_del(t_render **render)
{
	char		buf[1024 + 1];

	if (*render && g_s_render_verbose)
	{
		m_render_str(*render, buf, 1024);
		ft_printf("Del %s ;\n", buf);
	}
	if (*render)
	{
		free(*render);
		*render = NULL;
	}
}

char			*m_render_str(t_render *render, char *buf, size_t n)
{
	char		lbuf[1024 + 1];

	if (!buf)
	{
		buf = lbuf;
		n = 1024;
	}
	if (render)
		snprintf(buf, n, M_RENDERSTR, \
				render->width, render->height, render->buf, \
				render->bpp, render->sizel, render->endian);
	else
		ft_sprintf(buf, "null");
	return ((buf == lbuf ? ft_strdup(buf) : buf));
}

void			m_render_vtx(t_render *render, t_vertex *vtx)
{
	int			*buf;
	
	buf = (int *)(render->buf \
			+ (int)((int)vtx->v[1] * render->sizel + (int)(vtx->v[0] * 4)));
	*buf = (vtx->c->red << 0x10) | (vtx->c->green << 0x8) | vtx->c->blue;
}

void			m_render_segment(t_render *render, t_vertex *vo, t_vertex *ve)
{
	int			xy[2][2];
	int			ds[2][2];
	int			err[2];
	double		size;
	double		current_size;
	t_vertex	*v;
	t_color		*c;

	xy[0][0] = round(vo->v[0]);
	xy[0][1] = round(vo->v[1]);
	xy[1][0] = round(ve->v[0]);
	xy[1][1] = round(ve->v[1]);
	size = sqrt(pow(xy[1][0] - xy[0][0], 2) + pow(xy[1][1] - xy[0][1], 2));
	ds[0][0] = round((xy[0][0] - xy[1][0] >= 0 \
						? xy[0][0] - xy[1][0] : xy[1][0] - xy[0][0]));
	ds[0][1] = round((xy[0][1] - xy[1][1] >= 0 \
						? xy[0][1] - xy[1][1] : xy[1][1] - xy[0][1]));
	ds[1][0] = round((xy[0][0] < xy[1][0] ? 1 : -1));
	ds[1][1] = round((xy[0][1] < xy[1][1] ? 1 : -1));
	err[0] = round((ds[0][0] > ds[0][1] ? ds[0][0] : -ds[0][1])) / 2;
	while (xy[0][0] != xy[1][0] || xy[0][1] != xy[1][1])
	{
		current_size = sqrt(pow(xy[1][0] - xy[0][0], 2) \
							+ pow(xy[1][1] - xy[0][1], 2));
		c = m_color_bifusion(vo->c, ve->c, 1 - (int)(current_size / size));
		v = m_vertex_new(xy[0][0], xy[0][1], 1, c);
		m_color_del(&c);
		m_render_vtx(render, v);
		m_vertex_del(&v);
		err[1] = err[0];
		if (err[1] > -ds[0][0])
		{
			err[0] -= ds[0][1];
			xy[0][0] += ds[1][0];
		}
		if (err[1] < ds[0][1])
		{
			err[0] += ds[0][0];
			xy[0][1] += ds[1][1];
		}
	}
	v = m_vertex_new(xy[0][0], xy[0][1], 1, ve->c);
	m_render_vtx(render, v);
	m_vertex_del(&v);
}

void			m_render_tri_rasterize(t_render *render, t_triangle *tri)
{
	(void)render;
	(void)tri;
}

void			m_render_tri(t_render *render, t_triangle *tri, int mode)
{
	if (mode == M_VERTEX)
	{
		m_render_vtx(render, tri->a);
		m_render_vtx(render, tri->b);
		m_render_vtx(render, tri->c);
	}
	else if (mode == M_EDGE)
	{
		m_render_segment(render, tri->b, tri->a);
		m_render_segment(render, tri->b, tri->c);
		m_render_segment(render, tri->a, tri->c);
	}
	else if (mode == M_RASTERIZE)
		m_render_tri_rasterize(render, tri);
}

void			m_render_mesh(t_render *render, t_mesh *mesh, int mode)
{
	while (mesh)
	{
		m_render_tri(render, mesh->tri, mode);
		mesh = mesh->next;
	}
}
