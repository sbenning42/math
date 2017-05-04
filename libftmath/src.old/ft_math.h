/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 22:27:44 by                   #+#    #+#             */
/*   Updated: 2017/05/03 13:35:08 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# define M_DEPSILON	0.0001

# include "libft.h"

# include <math.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_colorv		t_colorv;
typedef struct s_color		t_color;
typedef struct s_vertex		t_vertex;
typedef struct s_vector		t_vector;
typedef struct s_matrix		t_matrix;
typedef struct s_camera		t_camera;

/*
********************************************************************************
**						COLOR
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
**						VERTEX
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
**						VECTOR
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

t_vector				*m_vector_init\
							(t_vector *self, t_vertex *dest, t_vertex *orig);
t_vector				*m_vector_new(t_vertex *dest, t_vertex *orig);
t_vector				*m_vector_clear(t_vector *self);
void					m_vector_del(t_vector **vct);
char					*m_vector2str(t_vector *self);

int						m_vector_is_zero(t_vector *self);
void					m_vector_make_zero(t_vector *self);
int						m_vector_is_equals(t_vector *self, t_vector *rhs);
double					m_vector_magnitude(t_vector *self);
t_vector				*m_vector_normalize(t_vector *self);
t_vector				*m_vector_add(t_vector *self, t_vector *rhs);
t_vector				*m_vector_sub(t_vector *self, t_vector *rhs);
t_vector				*m_vector_mul(t_vector *self, t_vector *rhs);
t_vector				*m_vector_opposite(t_vector *self);
t_vector				*m_vector_scalar_product(t_vector *self, double factor);
double					m_vector_dot_product(t_vector *self, t_vector *rhs);
double					m_vector_cos(t_vector *self, t_vector *rhs);
t_vector				*m_vector_cross_product(t_vector *self, t_vector *rhs);
double					m_vector_distance(t_vector *self, t_vector *rhs);

/*
********************************************************************************
**						MATRIX
********************************************************************************
*/

# define M_MTX_STR \
	"Camera(\n"\
	"\tPosition = %s,\n\tDeplacement = %s,\n\tI Deplacement = %s,\n"\
	"\tTranslation = %s,\n\tI Translation = %s,\n\tRotation = %s,\n"\
	"\tI Rotation = %s,\n\tTransform = %s,\n\tView = %s,\n"\
	"\tProjection = %s,\n\tRender = %s,\n\tFoV = %.3f, Width = %.1f, "\
	"Height = %.1f,\n\tRatio = %.3f, Near = %.3f, Far = %.3f )"

/*
**		Matrix type constant
*/

# define M_IDENT_MTX	1
# define M_SCALE_MTX	2
# define M_RX_MTX		3
# define M_RY_MTX		4
# define M_RZ_MTX		5
# define M_TRANS_MTX	6
# define M_PROJ_MTX		7

/*
**		Matrix desc arguments
*/

# define M_SCALEV_MTX		/*	double, Needed if preset is M_SCALE_MTX	*/
# define M_ANGLE_MTX		/*	double, Needed if preset is M_R(X|Y|Z)_MTX	*/
# define M_VTC_MTX			/*	t_vector *, Needed if preset is M_TRANS_MTX	*/
# define M_FOV_MTX			/*	double, Needed if preset is M_PROJ_MTX	*/
# define M_RATIO_MTX		/*	double, Needed if preset is M_PROJ_MTX	*/
# define M_NEAR_MTX			/*	double, Needed if preset is M_PROJ_MTX	*/
# define M_FAR_MTX			/*	double, Needed if preset is M_PROJ_MTX	*/

/*
**		Matrix v index
*/

# define M_VCTX_MTX		0
# define M_VCTY_MTX		1
# define M_VCTZ_MTX		2
# define M_VTXO_MTX		3

# define M_X_MTX		0
# define M_Y_MTX		1
# define M_Z_MTX		2
# define M_W_MTX		3

int						g_s_matrix_verbose;
char					*g_s_matrix_doc;
struct					s_matrix
{
	t_matrix			*self;
	int					type;
	double				v[4][4];
};

t_matrix				*m_matrix_new(int type, ...);
t_matrix				*m_matrix_init(t_matrix *self, \
							int type, ...);
t_matrix				*m_matrix_clear(t_matrix *self);
void					m_matrix_del(t_matrix **mtx);
char					*m_matrix2str(t_matrix *self);
t_matrix				*m_matrix_mul(t_matrix *self, t_matrix *rhs);
t_matrix				*m_matrix_inv(t_matrix *self);
t_vertex				*m_matrix_apply(t_matrix *self, t_vertex *vtx);

/*
********************************************************************************
**						CAMERA
********************************************************************************
*/

int						g_s_camera_verbose;
char					*g_s_camera_doc;
struct					s_camera
{
	t_camera			*self;
	double				fov;
	double				width;
	double				height;
	double				ratio;
	double				near;
	double				far;
	t_vertex			*position;
	t_vector			*deplacement;
	t_vector			*i_deplacement;
	t_matrix			*translation;
	t_matrix			*i_translation;
	t_matrix			*rotation;
	t_matrix			*i_rotation;
	t_matrix			*transform;
	t_matrix			*view;
	t_matrix			*projection;
	t_matrix			*render;
};

/*
**		For 42 norme. Must call with:
**	... = (double width, double height, double fov, double near, double far)
*/

t_camera				*m_camera_init\
							(t_camera *self, \
							 t_vertex *position, \
							 t_matrix *rotation, \
							 ...);
t_camera				*m_camera_new\
							(t_vertex *position, t_matrix *rotation, ...);
t_camera				*m_camera_clear(t_camera *self);
void					m_camera_del(t_camera **camera);
char					*m_camera2str(t_camera *self);
t_vertex				*m_camera_watch(t_camera *self, t_vertex *world_vtx);

/*
********************************************************************************
*/

int						m_equalszero(double d);
int						m_equals(double d1, double d2);

#endif
