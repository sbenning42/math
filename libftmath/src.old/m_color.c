/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 23:23:39 by                   #+#    #+#             */
/*   Updated: 2017/05/02 04:55:14 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

void				m_hex2rgb(unsigned int hex, unsigned char rgb[])
{
	rgb[M_RED_TC] = (hex & 0xff0000) >> 16;
	rgb[M_GREEN_TC] = (hex & 0xff00) >> 8;
	rgb[M_BLUE_TC] = hex & 0xff;
	rgb[M_NONE_TC] = 0;
}

void				m_rgb2hex(unsigned char rgb[], unsigned int *hex)
{
	*hex = 0;
	*hex = (rgb[M_RED_TC] << 16) \
		   | (rgb[M_GREEN_TC] << 8) \
		   | rgb[M_BLUE_TC];
}

typedef struct		s_color_select
{
	int				type;
	void			(*function)(t_color *, va_list *);
}					t_color_select;

void				m_color_init_hex(t_color *c, va_list *ap);
void				m_color_init_rgb(t_color *c, va_list *ap);
void				m_color_init_ap(t_color *c, va_list *ap);

static t_color_select	g_color_select[] = {\
	{M_HEX_TC, m_color_init_hex},\
	{M_RGB_TC, m_color_init_rgb},\
	{M_VAARG_TC, m_color_init_ap},\
	{0, 0}\
};

static void			wrong_color_def_type(t_color *c, va_list *ap)
{
	c->v.hex = 0;
	if (g_s_color_verbose)
		write(2, "wrong_color_def_type\n", 21);
	(void)ap;
}

static void			(*color_select(int color_def_type))(t_color *, va_list *)
{
	int				i;

	i = -1;
	while (g_color_select[++i].type > 0)
	{
		if (g_color_select[i].type == color_def_type)
			return (g_color_select[i].function);
	}
	return (wrong_color_def_type);
}

void				m_color_init_hex(t_color *c, va_list *ap)
{
	c->v.hex = (va_arg(*ap, unsigned int) & 0xffffff);
	m_hex2rgb(c->v.hex, c->v.rgb);
}

void				m_color_init_rgb(t_color *c, va_list *ap)
{
	c->v.rgb[M_RED_TC] = (unsigned char)va_arg(*ap, unsigned int);
	c->v.rgb[M_GREEN_TC] = (unsigned char)va_arg(*ap, unsigned int);
	c->v.rgb[M_BLUE_TC] = (unsigned char)va_arg(*ap, unsigned int);
	c->v.rgb[M_NONE_TC] = 0;
	m_rgb2hex(c->v.rgb, &c->v.hex);
}

void				m_color_init_ap(t_color *c, va_list *ap)
{
	int				color_def_type;
	va_list			*ap_new;

	color_def_type = va_arg(*ap, int);
	ap_new = (va_list *)va_arg(*ap, void *); 
	color_select(color_def_type)(c, ap_new);
}

t_color				*m_color_init(t_color *c, int color_def_type, ...)
{
	va_list			ap;
	char			*verb;

	va_start(ap, color_def_type);
	c->self = c;
	color_select(color_def_type)(c, &ap);
	va_end(ap);
	if (g_s_color_verbose && (verb = m_color2str(c)))
	{
		ft_printf("Init %s ;\n", verb);
		free(verb);
	}
	return (c);
}

t_color				*m_color_clear(t_color *c)
{
	char			*verb;

	if (g_s_color_verbose && (verb = m_color2str(c)))
	{
		ft_printf("Init %s ;\n", verb);
		free(verb);
	}
	c->self = NULL;
	c->v.hex = 0;
	c->v.rgb[M_RED_TC] = 0;
	c->v.rgb[M_GREEN_TC] = 0;
	c->v.rgb[M_BLUE_TC] = 0;
	c->v.rgb[M_NONE_TC] = 0;
	return (c);
}

t_color				*m_color_new(int color_def_type, ...)
{
	va_list			ap;
	t_color			*c;

	va_start(ap, color_def_type);
	c = malloc(sizeof(t_color));
	if (!c)
		return (NULL);
	m_color_init(c, M_VAARG_TC, color_def_type, &ap);
	va_end(ap);
	return (c);
}

void				m_color_del(t_color **c)
{
	m_color_clear(*c);
	free(*c);
	*c = NULL;
}

t_color				*m_color_add(t_color *self, t_color *c)
{
	self->v.rgb[M_RED_TC] += c->v.rgb[M_RED_TC];
	self->v.rgb[M_GREEN_TC] += c->v.rgb[M_GREEN_TC];
	self->v.rgb[M_BLUE_TC] += c->v.rgb[M_BLUE_TC];
	m_rgb2hex(self->v.rgb, &self->v.hex);
	return (self);
}

t_color				*m_color_sub(t_color *self, t_color *c)
{
	self->v.rgb[M_RED_TC] -= c->v.rgb[M_RED_TC];
	self->v.rgb[M_GREEN_TC] -= c->v.rgb[M_GREEN_TC];
	self->v.rgb[M_BLUE_TC] -= c->v.rgb[M_BLUE_TC];
	m_rgb2hex(self->v.rgb, &self->v.hex);
	return (self);
}

t_color				*m_color_mul(t_color *self, unsigned char facteur)
{
	self->v.rgb[M_RED_TC] *= facteur;
	self->v.rgb[M_GREEN_TC] *= facteur;
	self->v.rgb[M_BLUE_TC] *= facteur;
	m_rgb2hex(self->v.rgb, &self->v.hex);
	return (self);
}

char				*m_color2str(t_color *self)
{
	char			buf[512];

	ft_snprintf(buf, 512, "Color( Hex = %06x, Rgb[ %hhu, %hhu, %hhu ] )", \
			self->v.hex, \
			self->v.rgb[M_RED_TC], \
			self->v.rgb[M_GREEN_TC], \
			self->v.rgb[M_BLUE_TC]);
	return (ft_strdup(buf));
}

char				*m_color2ansi_esc\
						(t_color *self, char *buf, unsigned char *mode)
{
	ft_sprintf(buf, "\x1b[%hhu;%hhu;%hhu;%hhu;%hhum", \
			mode[0], mode[1], \
			self->v.rgb[M_RED_TC], \
			self->v.rgb[M_GREEN_TC], \
			self->v.rgb[M_BLUE_TC]);
	return (buf);
}

void				m_color_put(t_color *self, unsigned char *mode)
{
	ft_printf("\x1b[%hhu;%hhu;%hhu;%hhu;%hhum", \
			mode[0], mode[1], \
			self->v.rgb[M_RED_TC], \
			self->v.rgb[M_GREEN_TC], \
			self->v.rgb[M_BLUE_TC]);
}

void				m_reset(void)
{
	ft_printf("\x1b[0m");
}

static t_color		g_vcblack = {&g_vcblack, {0, {0, 0, 0}}};
static t_color		g_vcred = {&g_vcred, {0xff0000, {255, 0, 0}}};
static t_color		g_vcgreen = {&g_vcgreen, {0xff00, {0, 255, 0}}};
static t_color		g_vcblue = {&g_vcblue, {0xff, {0, 0, 255}}};
static t_color		g_vcwhite = {&g_vcwhite, {0xffffff, {255, 255, 255}}};

t_color				*g_m_black = &g_vcblack;
t_color				*g_m_red = &g_vcred;
t_color				*g_m_blue = &g_vcblue;
t_color				*g_m_green = &g_vcgreen;
t_color				*g_m_white = &g_vcwhite;
