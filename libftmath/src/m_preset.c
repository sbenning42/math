/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_preset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:44:00 by                   #+#    #+#             */
/*   Updated: 2017/05/04 17:06:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_preset.h"

t_mesh			*make_repere(void)
{
	t_color		*c[3];
	t_vertex	*v[6];
	t_triangle	*t[3];
	t_mesh		*mesh;
	t_mesh		*ntri;
	int			i;

	c[0] = m_color_new(M_HEX, 0xff0000);
	c[1] = m_color_new(M_HEX, 0xff00);
	c[2] = m_color_new(M_HEX, 0xff);
	v[0] = m_vertex_new(0.0, 0.0, 0.0, c[0]);
	v[1] = m_vertex_new(1.0, 0.0, 0.0, c[0]);
	v[2] = m_vertex_new(0.0, 0.0, 0.0, c[1]);
	v[3] = m_vertex_new(0.0, 1.0, 0.0, c[1]);
	v[4] = m_vertex_new(0.0, 0.0, 0.0, c[2]);
	v[5] = m_vertex_new(0.0, 0.0, 1.0, c[2]);
	i = -1;
	while (++i < 3)
		m_color_del(c + i);
	t[0] = m_triangle(v[0], v[0], v[1]);
	t[1] = m_triangle(v[2], v[2], v[3]);
	t[2] = m_triangle(v[4], v[4], v[5]);
	i = -1;
	while (++i < 6)
		m_vertex_del(v + i);
	mesh = NULL;
	i = -1;
	while (++i < 3)
	{
		ntri = m_mesh_new(t[i]);
		m_mesh_add(&mesh, ntri);
	}
	return (mesh);
}

t_mesh			*make_color_cube(double x, double y, double z, double l)
{
	t_color		*c[8];
	t_vertex	*v[8];
	t_triangle	*t[12];
	t_mesh		*mesh;
	t_mesh		*ntri;
	int			i;

	l = l / 2.0;
	c[0] = m_color_new(M_HEX, 0xff0000);
	c[1] = m_color_new(M_HEX, 0xff00);
	c[2] = m_color_new(M_HEX, 0xff);
	c[3] = m_color_new(M_HEX, 0xffff00);
	c[4] = m_color_new(M_HEX, 0xffff);
	c[5] = m_color_new(M_HEX, 0xff00ff);
	c[7] = m_color_new(M_HEX, 0x707070);
	c[6] = m_color_new(M_HEX, 0xffffff);
	v[0] = m_vertex_new(x - l, y + l, z + l, c[0]);
	v[1] = m_vertex_new(x + l, y + l, z + l, c[1]);
	v[2] = m_vertex_new(x + l, y + l, z - l, c[2]);
	v[3] = m_vertex_new(x - l, y + l, z - l, c[3]);
	v[4] = m_vertex_new(x - l, y - l, z + l, c[4]);
	v[5] = m_vertex_new(x + l, y - l, z + l, c[5]);
	v[6] = m_vertex_new(x + l, y - l, z - l, c[6]);
	v[7] = m_vertex_new(x - l, y - l, z - l, c[7]);
	i = -1;
	while (++i < 8)
		m_color_del(c + i);
	t[0] = m_triangle(v[0], v[2], v[1]);
	t[1] = m_triangle(v[0], v[3], v[2]);
	t[2] = m_triangle(v[4], v[6], v[7]);
	t[3] = m_triangle(v[4], v[5], v[6]);
	t[4] = m_triangle(v[4], v[1], v[5]);
	t[5] = m_triangle(v[0], v[1], v[4]);
	t[6] = m_triangle(v[3], v[6], v[2]);
	t[7] = m_triangle(v[3], v[7], v[6]);
	t[8] = m_triangle(v[0], v[4], v[7]);
	t[9] = m_triangle(v[0], v[7], v[3]);
	t[10] = m_triangle(v[5], v[2], v[6]);
	t[11] = m_triangle(v[5], v[1], v[2]);
	i = -1;
	while (++i < 8)
		m_vertex_del(v + i);
	mesh = NULL;
	i = -1;
	while (++i < 12)
	{
		ntri = m_mesh_new(t[i]);
		m_mesh_add(&mesh, ntri);
	}
	return (mesh);
}
