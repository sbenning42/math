/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:41:41 by                   #+#    #+#             */
/*   Updated: 2017/05/05 02:09:54 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_mlx.h"

static char	*g_progname;

char		*progname(void)
{
	return (g_progname);
}

int			main(int ac, char **av)
{
	t_data	data;

	if (ac < 2)
	{
		ft_fprintf(2, "%s: %s <filename.obj>\n", av[0], av[0]);
		return (1);
	}
	g_progname = av[0];
	ft_bzero(&data, sizeof(t_data));
	data.width = WIDTH;
	data.height = HEIGHT;
	if (setup(&data, ac, av))
		return (1);
	mlx_loop(data.mlx);
	return (0);
}
