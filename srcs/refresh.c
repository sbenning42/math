/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 23:10:07 by                   #+#    #+#             */
/*   Updated: 2017/05/05 02:08:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

t_data			**sdata(t_data *data)
{
	static t_data	*d;

	if (data)
		d = data;
	return (&d);
}

void			clear(t_data *data)
{
	ft_bzero(data->img_addr, sizeof(int) * (data->height * data->width));
}

void			refresh(t_data *data)
{
	t_camera	*cam;
	t_mesh		*tmesh;
	t_mesh		*mesh;

	data->event = 0;
	cam = m_cam();
	tmesh = m_matrix_apply_mesh(data->m[TRANSFMAT], data->repere);
	mesh = m_camera_watch_mesh(cam, tmesh);
	m_mesh_del(&tmesh);
	m_camera_del(&cam);
	clear(data);
	mlx_clear_window(data->mlx, data->win);
	m_render_mesh(data->render, mesh, M_EDGE);
	m_mesh_del(&mesh);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
