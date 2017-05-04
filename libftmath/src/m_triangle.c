/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_triangle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 11:22:08 by                   #+#    #+#             */
/*   Updated: 2017/05/04 15:37:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_triangle.h"

t_triangle		*m_triangle(t_vertex *a, t_vertex *b, t_vertex *c)
{
	t_triangle	*tri;
	char		buf[2048 + 1];

	if (!(tri = ft_memalloc(sizeof(t_triangle))))
		return (NULL);
	if (!(tri->a = m_vertex_new(a->v[0], a->v[1], a->v[2], a->c)))
		return (NULL);
	if (!(tri->b = m_vertex_new(b->v[0], b->v[1], b->v[2], b->c)))
		return (NULL);
	if (!(tri->c = m_vertex_new(c->v[0], c->v[1], c->v[2], c->c)))
		return (NULL);
	if (tri && g_s_triangle_verbose == 1)
	{
		m_triangle_str(tri, buf, 2048);
		ft_printf("New %s ;\n", buf);
	}
	return (tri);
}

void			m_triangle_del(t_triangle **tri)
{
	char		buf[2048 + 1];

	if (*tri && g_s_triangle_verbose == 1)
	{
		m_triangle_str(*tri, buf, 2048);
		ft_printf("New %s ;\n", buf);
	}
	if (*tri)
	{
		if ((*tri)->a)
			m_vertex_del(&(*tri)->a);
		if ((*tri)->b)
			m_vertex_del(&(*tri)->b);
		if ((*tri)->c)
			m_vertex_del(&(*tri)->c);
		free(*tri);
		*tri = NULL;
	}
}

char			*m_triangle_str(t_triangle *tri, char *buf, size_t n)
{
	char		lbuf[2048 + 1];
	char		bufs[3][512 + 1];

	if (!buf)
	{
		buf = lbuf;
		n = 2048;
	}
	if (tri)
	{
		m_vertex_str(tri->a, bufs[0], 512);
		m_vertex_str(tri->b, bufs[1], 512);
		m_vertex_str(tri->c, bufs[2], 512);
		ft_snprintf(buf, n, M_TRISTR, \
				bufs[0], bufs[1], bufs[2], tri->visible);
	}
	else
		ft_snprintf(buf, n, "null");
	return ((buf == lbuf ? ft_strdup(buf) : buf));
}

int				m_triangle_normal(t_triangle *tri, t_vector **normal)
{
	t_vector	*vct1;
	t_vector	*vct2;

	if (!(vct1 = m_vector_new(tri->b, tri->a)))
		return (-1);
	if (!(vct2 = m_vector_new(tri->c, tri->a)))
		return (-1);
	*normal = m_vector_cross(vct1, vct2);
	m_vector_del(&vct1);
	m_vector_del(&vct2);
	return (0);
}

t_vertex		*m_triangle_centroid(t_triangle *tri)
{
	double		x;
	double		y;
	double		z;

	x = (tri->a->v[0] + tri->b->v[0] + tri->c->v[0]) / 3.0;
	y = (tri->a->v[1] + tri->b->v[1] + tri->c->v[1]) / 3.0;
	z = (tri->a->v[2] + tri->b->v[2] + tri->c->v[2]) / 3.0;
	return (m_vertex_new(round(x), round(y), round(z), NULL));
}

double			m_triangle_area(t_triangle *tri)
{
	return (abs(\
				(tri->a->v[0] * (tri->b->v[1] - tri->c->v[1]) \
				 + tri->b->v[0] * (tri->c->v[1] - tri->a->v[1]) \
				 + tri->c->v[0] * (tri->a->v[1] - tri->b->v[1])) \
				/ 2.0));
}

t_color			*m_triangle_color(t_triangle *tri, t_vertex *vtx)
{
	t_triangle	*tris[3];
	double		area;
	int			areas[3];
	t_color		*c;

	if (!(tris[0] = m_triangle(tri->a, tri->b, vtx)))
		return (NULL);
	if (!(tris[1] = m_triangle(tri->a, tri->c, vtx)))
		return (NULL);
	if (!(tris[2] = m_triangle(tri->b, tri->c, vtx)))
		return (NULL);
	area = m_triangle_area(tri);
	areas[0] = (int)(m_triangle_area(tris[0]) / area);
	areas[1] = (int)(m_triangle_area(tris[1]) / area);
	areas[2] = (int)(m_triangle_area(tris[2]) / area);
	c = m_color_trifusion(tri->a->c, tri->b->c, tri->c->c, areas);
	m_triangle_del(tris + 0);
	m_triangle_del(tris + 1);
	m_triangle_del(tris + 2);
	return (c);
}
