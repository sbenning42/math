/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_vertex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:56:57 by                   #+#    #+#             */
/*   Updated: 2017/05/04 00:28:50 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_vertex.h"

t_vertex		*m_vertex_new(double x, double y, double z, t_color *c)
{
	t_vertex	*vtx;
	char		buf[512 + 1];

	if (!(vtx = ft_memalloc(sizeof(t_vertex))))
		return (NULL);
	if (c)
	{
		if (!(vtx->c = m_color_new(M_RGB, c->red, c->green, c->blue)))
			return (NULL);
	}
	else
	{
		if (!(vtx->c = m_color_new(M_HEX, 0xffffff)))
			return (NULL);
	}
	vtx->v[0] = x;
	vtx->v[1] = y;
	vtx->v[2] = z;
	vtx->v[3] = 1.0;
	if (g_s_vertex_verbose == 1)
	{
		m_vertex_str(vtx, buf, 512);
		ft_printf("New %s ;\n", buf);
	}
	return (vtx);
}

void			m_vertex_del(t_vertex **vtx)
{
	char		buf[512 + 1];

	if (g_s_vertex_verbose == 1)
	{
		m_vertex_str(*vtx, buf, 512);
		ft_printf("Del %s ;\n", buf);
	}
	if (*vtx)
	{
		if ((*vtx)->c)
			m_color_del(&(*vtx)->c);
		free(*vtx);
		*vtx = NULL;
	}
}

char			*m_vertex_str(t_vertex *vtx, char *buf, size_t n)
{
	char		lbuf[512 + 1];
	char		lcbuf[256 + 1];

	if (!buf)
	{
		buf = lbuf;
		n = 512;
	}
	if (vtx)
	{
		m_color_str(vtx->c, lcbuf, 256);
		snprintf(buf, n, M_VTXSTR, \
				vtx->v[0], vtx->v[1], vtx->v[2], vtx->v[3], lcbuf);
	}
	else
		ft_snprintf(buf, n, "null");
	return ((buf == lbuf ? ft_strdup(buf) : buf));
}

t_vertex		*m_vertex_add(t_vertex *vtx1, t_vertex *vtx2)
{
	t_color		*tmp;
	t_vertex	*vtx;

	tmp = m_color_add(vtx1->c, vtx2->c);
	if (!tmp)
		return (NULL);
	vtx = m_vertex_new(\
			vtx1->v[0] + vtx2->v[0], \
			vtx1->v[1] + vtx2->v[1], \
			vtx1->v[2] + vtx2->v[2], \
			tmp);
	m_color_del(&tmp);
	return (vtx);
}

t_vertex		*m_vertex_sub(t_vertex *vtx1, t_vertex *vtx2)
{
	t_color		*tmp;
	t_vertex	*vtx;

	tmp = m_color_sub(vtx1->c, vtx2->c);
	if (!tmp)
		return (NULL);
	vtx = m_vertex_new(\
			vtx1->v[0] - vtx2->v[0], \
			vtx1->v[1] - vtx2->v[1], \
			vtx1->v[2] - vtx2->v[2], \
			tmp);
	m_color_del(&tmp);
	return (vtx);
}

t_vertex		*m_vertex_mult(t_vertex *vtx1, double factor)
{
	t_color		*tmp;
	t_vertex	*vtx;

	tmp = m_color_mult(vtx1->c, factor);
	if (!tmp)
		return (NULL);
	vtx = m_vertex_new(\
			vtx1->v[0] * factor, \
			vtx1->v[1] * factor, \
			vtx1->v[2] * factor, \
			tmp);
	m_color_del(&tmp);
	return (vtx);
}
