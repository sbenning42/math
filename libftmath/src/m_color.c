/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:51:02 by                   #+#    #+#             */
/*   Updated: 2017/05/04 12:17:08 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_color.h"

void			m_color_hex_rgb(t_ui hex, t_uc *red, t_uc *green, t_uc *blue)
{
	*red = (hex >> 0x10) & 0xff;
	*green = (hex >> 0x8) & 0xff;
	*blue = hex & 0xff;
}

static t_color	*color_new(int red, int green, int blue)
{
	t_color		*c;

	if (!(c = ft_memalloc(sizeof(t_color))))
		return (NULL);
	c->red = red;
	c->green = green;
	c->blue = blue;
	return (c);
}

static t_color	*color_new_ap(int desc_type, va_list *ap)
{
	t_ui		hex;
	t_uc		red;
	t_uc		green;
	t_uc		blue;

	if (desc_type == M_HEX)
	{
		hex = va_arg(*ap, unsigned int);
		m_color_hex_rgb(hex, &red, &green, &blue);
	}
	else if (desc_type == M_RGB)
	{
		red = va_arg(*ap, unsigned int) & 0xff;
		green = va_arg(*ap, unsigned int) & 0xff;
		blue = va_arg(*ap, unsigned int) & 0xff;
	}
	else
		return (NULL);
	return (color_new(red, green, blue));
}

t_color			*m_color_new(int desc_type, ...)
{
	t_color		*c;
	va_list		ap;
	char		buf[256 + 1];

	va_start(ap, desc_type);
	c = color_new_ap(desc_type, &ap);
	va_end(ap);
	if (c && g_s_color_verbose == 1)
	{
		m_color_str(c, buf, 256);
		ft_printf("New %s ;\n", buf);
	}
	return (c);
}

void			m_color_del(t_color **color)
{
	char		buf[256 + 1];

	if (*color && g_s_color_verbose == 1)
	{
		m_color_str(*color, buf, 256);
		ft_printf("Del %s ;\n", buf);
	}
	free(*color);
	*color = NULL;
}

char			*m_color_str(t_color *c, char *buf, size_t n)
{
	char		lbuf[4096 + 1];

	if (!buf)
	{
		buf = lbuf;
		n = 4096;
	}
	if (c)
		ft_snprintf(buf, n, M_COLORSTR, c->red, c->green, c->blue);
	else
		ft_snprintf(buf, n, "null");
	return ((buf == lbuf ? ft_strdup(buf) : buf));
}

t_color			*m_color_add(t_color *c1, t_color *c2)
{
	return (m_color_new(M_RGB, \
				c1->red + c2->red, \
				c1->green + c2->green, \
				c1->blue + c2->blue));
}

t_color			*m_color_sub(t_color *c1, t_color *c2)
{
	return (m_color_new(M_RGB, \
				c1->red - c2->red, \
				c1->green - c2->green, \
				c1->blue - c2->blue));
}

t_color			*m_color_mult(t_color *c1, int factor)
{
	return (m_color_new(M_RGB, \
				c1->red * factor, \
				c1->green * factor, \
				c1->blue * factor));
}

t_color			*m_color_bifusion(t_color *a, t_color *b, int ar)
{
	t_color		*cols[2];
	t_color		*col;

	if (!(cols[0] = m_color_mult(a, 1 - ar)))
		return (NULL);
	if (!(cols[1] = m_color_mult(b, ar)))
		return (NULL);
	col = m_color_add(cols[0], cols[1]);
	m_color_del(cols + 0);
	m_color_del(cols + 1);
	return (col);
}

t_color			*m_color_trifusion(t_color *a, t_color *b, t_color *c, \
										int *ar)
{
	t_color		*cols[4];
	t_color		*col;

	if (!(cols[0] = m_color_mult(a, ar[0])))
		return (NULL);
	if (!(cols[1] = m_color_mult(b, ar[1])))
		return (NULL);
	if (!(cols[2] = m_color_mult(c, ar[2])))
		return (NULL);
	if (!(cols[3] = m_color_add(cols[0], cols[1])))
		return (NULL);
	col = m_color_add(cols[3], cols[2]);
	m_color_del(cols + 0);
	m_color_del(cols + 1);
	m_color_del(cols + 2);
	m_color_del(cols + 3);
	return (col);
}

void			m_color_term(t_color *c, char *mode, char *buf)
{
	ft_snprintf(buf, 256, M_ANSICOLOR, mode, c->red, c->green, c->blue);
}

void			m_color_xterm(t_ui hex, char *mode, char *buf)
{
	t_color		*c;

	c = m_color_new(M_HEX, hex);
	if (!c)
		return ;
	m_color_term(c, mode, buf);
	m_color_del(&c);
}

void			m_reset_xterm(char *buf)
{
	ft_sprintf(buf, M_ANSIRESET);
}
