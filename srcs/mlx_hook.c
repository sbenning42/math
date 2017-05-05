/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 20:48:25 by                   #+#    #+#             */
/*   Updated: 2017/05/05 01:33:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

int			loop_hook(void *param)
{
	if (((t_data *)param)->event)
		refresh(param);
	return (0);
}

int		expose_hook(void *param)
{
	refresh(param);
	(void)param;
	return (0);
}

int		key_hook(int keycode, void *param)
{
	((t_data *)param)->event = select_key(keycode)(param);
	return (0);
}

int		mouse_hook(int button, int x, int y, void *param)
{
	(void)param;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}
