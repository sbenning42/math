/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 22:28:48 by                   #+#    #+#             */
/*   Updated: 2017/05/05 02:20:05 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

int		esc_key(t_data *data)
{
	int	i;

	m_render_del(&data->render);
	m_mesh_del(&data->repere);
	i = -1;
	while (++i < 5)
		m_matrix_del(data->m + i);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int		right_key(t_data *data)
{
	(void)data;
	return (1);
}

int		a_key(t_data *data)
{
	(void)data;
	return (1);
}
