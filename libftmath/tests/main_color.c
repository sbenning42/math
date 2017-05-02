/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 00:25:35 by                   #+#    #+#             */
/*   Updated: 2017/05/02 03:44:54 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdio.h>

void		putcc(char *str, t_color *ft, t_color *bg)
{
	m_color_put(ft, M_FTMODE_TC);
	m_color_put(bg, M_BGMODE_TC);
	ft_printf("%s", str);
	m_reset();
}

void		puthexc(char *str, unsigned int hex_ft, unsigned int hex_bg)
{
	t_color	ft;
	t_color	bg;

	m_color_init(&ft, M_HEX_TC, hex_ft);
	m_color_init(&bg, M_HEX_TC, hex_bg);
	putcc(str, &ft, &bg);
}

void	putrgbc(char *str, unsigned char *rgb_ft, unsigned char *rgb_bg)
{
	t_color	ft;
	t_color	bg;

	m_color_init(&ft, M_RGB_TC, \
			rgb_ft[M_RED_TC], rgb_ft[M_GREEN_TC], rgb_ft[M_BLUE_TC]);
	m_color_init(&bg, M_RGB_TC, \
			rgb_bg[M_RED_TC], rgb_bg[M_GREEN_TC], rgb_bg[M_BLUE_TC]);
	putcc(str, &ft, &bg);
}

int		main()
{
//	g_s_color_verbose = 1;
	puthexc("Hello World\n", 0xff00ff, 0xff00);
	puthexc("Hello World\n", 0xff00, 0xff00ff);
	return (0);
}
