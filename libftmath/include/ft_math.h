/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 22:27:44 by                   #+#    #+#             */
/*   Updated: 2017/05/02 06:21:50 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include "libft.h"

# include <math.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_colorv		t_colorv;
typedef struct s_color		t_color;
typedef struct s_vertex		t_vertex;
typedef struct s_vector		t_vector;

/*
********************************************************************************
*/

/*
**						rgb index
*/

# define M_RED_TC		0
# define M_GREEN_TC		1
# define M_BLUE_TC		2
# define M_NONE_TC		3


struct					s_colorv
{
	unsigned int		hex;
	unsigned char		rgb[4];
};

int						g_s_color_verbose;
char					*g_s_color_doc;
struct					s_color
{
	t_color				*self;
	t_colorv			v;
};

extern t_color			*g_m_black;
extern t_color			*g_m_red;
extern t_color			*g_m_green;
extern t_color			*g_m_blue;
extern t_color			*g_m_white;

/*
**						color_def_type
**
**						M_HEX_TC, unsigned int
**						M_RGB_TC, unsigned char, unsigned char, unsigned char
**
**						M_VAARG_TC is for intern purpose only!
**
*/

# define M_HEX_TC		1
# define M_RGB_TC		2
# define M_VAARG_TC		3

t_color					*m_color_new(int color_def_type, ...);
t_color					*m_color_init(t_color *c, int color_def_type, ...);
t_color					*m_color_clear(t_color *c);
void					m_color_del(t_color **c);
t_color					*m_color_add(t_color *self, t_color *c);
t_color					*m_color_sub(t_color *self, t_color *c);
t_color					*m_color_mul(t_color *self, unsigned char facteur);
char					*m_color2str(t_color *self);

void					m_reset(void);

/*
**						font/background mode pattern
*/

# define M_FTMODE_TC	(unsigned char *)"\x26\x2"
# define M_BGMODE_TC	(unsigned char *)"\x30\x2"

void					m_color_put(t_color *self, unsigned char *mode);

char					*m_color2ansi_esc\
							(t_color *self, char *buf, unsigned char *mode);

void					m_hex2rgb(unsigned int hex, unsigned char rgb[]);
void					m_rgb2hex(unsigned char rgb[], unsigned int *hex);

/*
********************************************************************************
*/

/*
**						vertex coordonate index
*/

# define M_X_VTX		0
# define M_Y_VTX		1
# define M_Z_VTX		2
# define M_W_VTX		3

int						g_s_vertex_verbose;
char					*g_s_vertex_doc;
struct					s_vertex
{
	t_vertex			*self;
	double				coo[4];
	t_color				*color;
};

extern t_vertex			*g_m_vtx_orig;

t_vertex				*m_vertex_init(t_vertex *self, double *coo, t_color *c);
t_vertex				*m_vertex_new(double *coo, t_color *c);
t_vertex				*m_vertex_clear(t_vertex *self);
void					m_vertex_del(t_vertex **vtx);
char					*m_vertex2str(t_vertex *self);

/*
********************************************************************************
*/

/*
**						vector magnitude index
*/

# define M_X_VCT		0
# define M_Y_VCT		1
# define M_Z_VCT		2
# define M_W_VCT		3

int						g_s_vector_verbose;
char					*g_s_vector_doc;
struct					s_vector
{
	t_vector			*self;
	double				magn[4];
};

extern t_vector			*g_m_vct_orig;

t_vector				*m_vector_init(t_vector *self, t_vertex *dest, t_vertex *orig);
t_vector				*m_vector_new(t_vertex *dest, t_vertex *orig);
t_vector				*m_vector_clear(t_vector *self);
void					m_vector_del(t_vector **vct);
char					*m_vector2str(t_vector *self);

/*
********************************************************************************
*/

double	m_powf_2(double n);

#endif
