/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:56:28 by                   #+#    #+#             */
/*   Updated: 2017/05/04 14:40:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_render.h"

t_render		*m_render_new(double width, double height, \
								char **buf, char *filename)
{
	char		lbuf[1024 + 1];
	t_render	*render;

	if (!(render = ft_memalloc(sizeof(t_render))))
		return (NULL);
	render->filename = filename;
	render->buf = buf;
	render->width = width;
	render->height = height;
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
		if (*(*render)->buf)
		{
			free(*(*render)->buf);
			*(*render)->buf = NULL;
		}
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
				render->width, render->height, render->filename, *render->buf);
	else
		ft_sprintf(buf, "null");
	return ((buf == lbuf ? ft_strdup(buf) : buf));
}

void			m_render_vtx(t_render *render, t_vertex *vtx)
{
	(void)render;
	(void)vtx;
}

void			m_render_segment(t_render *render, t_vertex *f, t_vertex *e)
{
	(void)render;
	(void)f;
	(void)e;
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
