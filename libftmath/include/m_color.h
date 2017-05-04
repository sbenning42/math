/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_color.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:38:21 by                   #+#    #+#             */
/*   Updated: 2017/05/04 12:17:07 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_COLOR_H
# define M_COLOR_H

# include				"libft.h"

# define M_COLORSTR		"Color( 'red' = %hhu, 'green' = %hhu, 'blue' = %hhu )"
# define M_HEX			1
# define M_RGB			2
# define M_ANSICOLOR	"\x1b[%hhu;%hhu;%hhu;%hhu;%hhum"
# define M_ANSIRESET	"\x1b[0m"
# define M_FTMODE		"\x26\x2"
# define M_BGMODE		"\x30\x2"

typedef unsigned char	t_uc;
typedef unsigned int	t_ui;

typedef struct s_color	t_color;

int						g_s_color_verbose;

struct					s_color
{
	t_uc				red;
	t_uc				green;
	t_uc				blue;
};

t_color		*m_color_new(int desc_type, ...);
void		m_color_del(t_color **color);
char		*m_color_str(t_color *c, char *buf, size_t n);
t_color		*m_color_add(t_color *c1, t_color *c2);
t_color		*m_color_sub(t_color *c1, t_color *c2);
t_color		*m_color_mult(t_color *c1, int factor);
t_color		*m_color_bifusion(t_color *a, t_color *b, int ar);
t_color		*m_color_trifusion(t_color *a, t_color *b, t_color *c, int *ar);
void		m_color_hex_rgb(t_ui hex, t_uc *red, t_uc *green, t_uc *blue);
void		m_color_term(t_color *c, char *mode, char *buf);
void		m_color_xterm(t_ui hex, char *mode, char *buf);
void		m_reset_xterm(char *buf);

#endif
