/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vertex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 04:26:08 by                   #+#    #+#             */
/*   Updated: 2017/05/03 01:31:00 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdio.h>

int	main()
{
	t_matrix	*m;
	t_vector	*vct;
	t_vertex	*vtx_pt;
	t_vertex	*vtx_pt_depl;
	t_vertex	*vtx_depl;
	double		coo_pt[4] = {1.0, 1.0, 1.0, 1.0};
	double		coo_depl[4] = {1.0, 2.0, 3.0, 1.0};
	char		*str;

	g_s_vertex_verbose = 1;
	g_s_vector_verbose = 1;
	g_s_matrix_verbose = 1;

	vtx_depl = m_vertex_new(coo_depl, g_m_black);
	vtx_pt = m_vertex_new(coo_pt, g_m_white);
	vct = m_vector_new(vtx_depl, g_m_vtx_orig);
	m = m_matrix_new(M_TRANS_MTX, vct);

	if ((str = m_vertex2str(vtx_pt)))
	{
		ft_printf("Old vertex : %s ;\n", str);
		free(str);
	}

	vtx_pt_depl = m_matrix_apply(m, vtx_pt);

	if ((str = m_vertex2str(vtx_pt_depl)))
	{
		ft_printf("New vertex : %s ;\n", str);
		free(str);
	}

	m_matrix_del(&m);
	m_vector_del(&vct);
	m_vertex_del(&vtx_pt);
	m_vertex_del(&vtx_pt_depl);
	m_vertex_del(&vtx_depl);

	return (0);
}
