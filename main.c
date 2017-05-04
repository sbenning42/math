/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:41:41 by                   #+#    #+#             */
/*   Updated: 2017/05/04 15:55:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "m_camera.h"
# include "m_mesh.h"

enum	e_mtype
{
	trans,
	rotx,
	roty,
	scale
};

enum	e_ctype
{
	red,
	green,
	blue,
	yellow,
	cyan,
	magenta,
	white,
	grey
};

enum	e_vtype
{
	v_a,
	v_b,
	v_c,
	v_d,
	v_e,
	v_f,
	v_g,
	v_h
};

void	render_mlx(t_mesh *mesh)
{
}

int	main()
{
	t_camera	*cam;
	t_vertex	*vx;
	t_vector	*v;
	t_matrix	*m[4];
	t_matrix	*transform;
	t_matrix	*tmp;
	t_triangle	*tri[12];
	t_mesh		*mesh;
	t_mesh		*tmesh;
	t_mesh		*smesh;
	t_vertex	*vtx[8];
	t_color		*c[8];
	double		x;
	double		y;
	double		z;
	double		l;
	double		r;
	char		*str;

	g_s_color_verbose = 1;
	g_s_vertex_verbose = 1;
	g_s_vector_verbose = 1;
	g_s_triangle_verbose = 1;
	g_s_mesh_verbose = 1;
	g_s_matrix_verbose = 1;
	g_s_camera_verbose = 1;

	//	Set up

	c[red] = m_color_new(M_HEX, 0xff0000);
	c[green] = m_color_new(M_HEX, 0xff00);
	c[blue] = m_color_new(M_HEX, 0xff);
	c[yellow] = m_color_new(M_HEX, 0xffff00);
	c[cyan] = m_color_new(M_HEX, 0xffff);
	c[magenta] = m_color_new(M_HEX, 0xff00ff);
	c[white] = m_color_new(M_HEX, 0xffffff);
	c[grey] = m_color_new(M_HEX, 0x707070);

	x = 0.0;
	y = 0.0;
	z = 0.0;
	l = 1.0;
	r = l / 2.0;

	vtx[v_a] = m_vertex_new(x - r, y + r, z + r, c[red]);
	vtx[v_b] = m_vertex_new(x + r, y + r, z + r, c[green]);
	vtx[v_c] = m_vertex_new(x + r, y + r, z - r, c[blue]);
	vtx[v_d] = m_vertex_new(x - r, y + r, z - r, c[yellow]);
	vtx[v_e] = m_vertex_new(x - r, y - r, z + r, c[cyan]);
	vtx[v_f] = m_vertex_new(x + r, y - r, z + r, c[magenta]);
	vtx[v_g] = m_vertex_new(x + r, y - r, z - r, c[grey]);
	vtx[v_h] = m_vertex_new(x - r, y - r, z - r, c[white]);

	tri[0] = m_triangle(vtx[v_a], vtx[v_c], vtx[v_b]);
	tri[1] = m_triangle(vtx[v_a], vtx[v_d], vtx[v_c]);
	tri[2] = m_triangle(vtx[v_e], vtx[v_g], vtx[v_h]);
	tri[3] = m_triangle(vtx[v_e], vtx[v_f], vtx[v_g]);
	tri[4] = m_triangle(vtx[v_e], vtx[v_b], vtx[v_f]);
	tri[5] = m_triangle(vtx[v_a], vtx[v_b], vtx[v_e]);
	tri[6] = m_triangle(vtx[v_d], vtx[v_g], vtx[v_c]);
	tri[7] = m_triangle(vtx[v_d], vtx[v_h], vtx[v_g]);
	tri[8] = m_triangle(vtx[v_a], vtx[v_e], vtx[v_h]);
	tri[9] = m_triangle(vtx[v_a], vtx[v_h], vtx[v_d]);
	tri[10] = m_triangle(vtx[v_f], vtx[v_c], vtx[v_g]);
	tri[11] = m_triangle(vtx[v_f], vtx[v_b], vtx[v_c]);

	mesh = NULL;
	m_mesh_add(&mesh, m_mesh_newm(tri[0]));
	m_mesh_add(&mesh, m_mesh_newm(tri[1]));
	m_mesh_add(&mesh, m_mesh_newm(tri[2]));
	m_mesh_add(&mesh, m_mesh_newm(tri[3]));
	m_mesh_add(&mesh, m_mesh_newm(tri[4]));
	m_mesh_add(&mesh, m_mesh_newm(tri[5]));
	m_mesh_add(&mesh, m_mesh_newm(tri[6]));
	m_mesh_add(&mesh, m_mesh_newm(tri[7]));
	m_mesh_add(&mesh, m_mesh_newm(tri[8]));
	m_mesh_add(&mesh, m_mesh_newm(tri[9]));
	m_mesh_add(&mesh, m_mesh_newm(tri[10]));
	m_mesh_add(&mesh, m_mesh_newm(tri[11]));

	vx = m_vertex_new(20.0, 20.0, 0.0, NULL);
	v = m_vector_new(vx, NULL);
	m_vertex_del(&vx);

	m[trans] = m_matrix_new(M_TRANSLATION, v);
	m[scale] = m_matrix_new(M_SCALE, 10.0);
	m[roty] = m_matrix_new(M_RY, M_PI_4);
	m[rotx] = m_matrix_new(M_RX, M_PI_4);

	m_vector_del(&v);
	
	tmp = m_matrix_mult(m[trans], m[rotx]);
	transform = m_matrix_mult(tmp, m[roty]);
	m_matrix_del(&tmp);
	tmp = transform;
	transform = m_matrix_mult(tmp, m[scale]);
	m_matrix_del(&tmp);

	cam = m_cam();

/******************************************************************************/

	//	Do Job

	tmesh = m_matrix_apply_mesh(transform, mesh);
	smesh = m_camera_watch_mesh(cam, tmesh);

	render_mlx(smesh);

/******************************************************************************/

	//	Clean up

	m_camera_del(&cam);

	m_color_del(c + red);
	m_color_del(c + green);
	m_color_del(c + blue);
	m_color_del(c + yellow);
	m_color_del(c + cyan);
	m_color_del(c + magenta);
	m_color_del(c + grey);
	m_color_del(c + white);

	m_vertex_del(vtx + v_a);
	m_vertex_del(vtx + v_b);
	m_vertex_del(vtx + v_c);
	m_vertex_del(vtx + v_d);
	m_vertex_del(vtx + v_e);
	m_vertex_del(vtx + v_f);
	m_vertex_del(vtx + v_g);
	m_vertex_del(vtx + v_h);

	m_triangle_del(tri + 0);
	m_triangle_del(tri + 1);
	m_triangle_del(tri + 2);
	m_triangle_del(tri + 3);
	m_triangle_del(tri + 4);
	m_triangle_del(tri + 5);
	m_triangle_del(tri + 6);
	m_triangle_del(tri + 7);
	m_triangle_del(tri + 8);
	m_triangle_del(tri + 9);
	m_triangle_del(tri + 10);
	m_triangle_del(tri + 11);

	m_mesh_del(&mesh);
	m_mesh_del(&tmesh);
	m_mesh_del(&smesh);

	m_matrix_del(m + trans);
	m_matrix_del(m + rotx);
	m_matrix_del(m + roty);
	m_matrix_del(m + scale);

	return (0);
}
