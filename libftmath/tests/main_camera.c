/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vertex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 04:26:08 by                   #+#    #+#             */
/*   Updated: 2017/05/03 13:43:46 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdio.h>

int	main()
{
	t_camera	*camera;
	t_matrix	*m;
	t_vertex	*vtx;
	t_vertex	*pt;
	t_vertex	*img;
	double		coo[4] = {0.0, 0.0, 0.0, 1.0}; /*TODO: get valuable position.*/
	char		*str;

//	g_s_camera_verbose = 1;

	vtx = m_vertex_new(coo, g_m_black);
	m = m_matrix_new(M_RX_MTX, 0.0);	/*TODO: get valuable rotation matrix.*/

	camera = m_camera_new(vtx, m, 480.0, 360.0, 45.0, 50.0, 100.0);

	coo[M_X_VTX] = 1.0;
	coo[M_Y_VTX] = 1.0;
	coo[M_Z_VTX] = 1.0;
	coo[M_W_VTX] = 1.0;
	pt = m_vertex_new(coo, g_m_white);
	str = m_vertex2str(pt);
	printf("Pt VTX : %s ;\n", str);
	free(str);

	img = m_camera_watch(camera, pt);
	str = m_vertex2str(img);
	printf("Img VTX : %s ;\n", str);
	free(str);

	m_camera_del(&camera);
	m_matrix_del(&m);
	m_vertex_del(&vtx);
	m_vertex_del(&pt);

	return (0);
}
