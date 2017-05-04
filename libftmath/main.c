/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:41:41 by                   #+#    #+#             */
/*   Updated: 2017/05/04 02:24:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "m_camera.h"

int	main()
{
	t_camera	*cam;
	t_vertex	*origin;
	t_vertex	*vtx;
	t_vertex	*origin_screen;
	t_vertex	*vtx_screen;
	char		buf[256 + 1];

	g_s_color_verbose = 0;
	g_s_vertex_verbose = 0;
	g_s_vector_verbose = 0;
	g_s_matrix_verbose = 0;
	g_s_camera_verbose = 1;

	cam = m_cam();

	origin = m_vertex_new(0.0, 0.0, 0.0, NULL);
	m_vertex_str(origin, buf, 256);
	ft_printf("Origin : %s ;\n", buf);

	origin_screen = m_camera_watch_vertex(cam, origin);
	m_vertex_str(origin_screen, buf, 256);
	ft_printf("Origin Screen : %s ;\n", buf);

	vtx = m_vertex_new(42.0, 42.0, 42.0, NULL);
	m_vertex_str(vtx, buf, 256);
	ft_printf("Vtx : %s ;\n", buf);

	vtx_screen = m_camera_watch_vertex(cam, vtx);
	m_vertex_str(vtx_screen, buf, 256);
	ft_printf("Vtx Screen : %s ;\n", buf);

	m_camera_del(&cam);
	m_vertex_del(&vtx_screen);
	m_vertex_del(&vtx);
	m_vertex_del(&origin_screen);
	m_vertex_del(&origin);
	return (0);
}
