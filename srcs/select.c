/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 22:13:47 by                   #+#    #+#             */
/*   Updated: 2017/05/05 02:12:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

static t_select_key	g_select_key[] = {\
	{65307, esc_key}, \
	{65363, right_key}, \
	{97, a_key}, \
	{0, 0}\
};

static int			unhandled_key(t_data *data)
{
	return (0);
	(void)data;
}

int					(*select_key(int keycode))(t_data *)
{
	int				i;

	i = -1;
	while (g_select_key[++i].keycode > 0)
	{
		if (g_select_key[i].keycode == keycode)
			return (g_select_key[i].handler);
	}
	ft_printf("Here in key_hook: keycode = %d\n", keycode);
	return (unhandled_key);
}
