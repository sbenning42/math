/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vertex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 04:26:08 by                   #+#    #+#             */
/*   Updated: 2017/05/02 16:07:06 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdio.h>

int	main()
{
	t_vertex	vtx;
	t_vector	vct;
	t_vector	*norm;
	double		coo[4] = {1.0, 2.0, 3.0, 1.0};

	g_s_vertex_verbose = 1;
	g_s_vector_verbose = 1;

	m_vertex_init(&vtx, coo, g_m_black);
	m_vector_init(&vct, &vtx, g_m_vtx_orig);
	printf("Magnitude : %.04f\n", m_vector_magnitude(&vct));
	norm = m_vector_normalize(&vct);
	printf("Magnitude : %.04f\n", m_vector_magnitude(norm));
	m_vector_del(&norm);

	return (0);
}
