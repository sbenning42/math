/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_matrix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:07:42 by                   #+#    #+#             */
/*   Updated: 2017/05/03 12:45:50 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdio.h>

static double		m_matrix_apply_step(int step, double m1[4][4], double coo[])
{
	return (m1[M_VCTX_MTX][step] * coo[M_X_VTX] \
			+ m1[M_VCTY_MTX][step] * coo[M_Y_VTX] \
			+ m1[M_VCTZ_MTX][step] * coo[M_Z_VTX] \
			+ m1[M_VTXO_MTX][step] * coo[M_W_VTX]);
}

t_vertex			*m_matrix_apply(t_matrix *self, t_vertex *vtx)
{
	double			coo[4];

	coo[M_X_VTX] = m_matrix_apply_step(0, self->v, vtx->coo);
	coo[M_Y_VTX] = m_matrix_apply_step(1, self->v, vtx->coo);
	coo[M_Z_VTX] = m_matrix_apply_step(2, self->v, vtx->coo);
	coo[M_W_VTX] = m_matrix_apply_step(3, self->v, vtx->coo);
	return (m_vertex_new(coo, vtx->color));
}

static double		m_matrix_mul_step(int step, double m1[4][4], double m2[4][4])
{
	int				i;
	int				j;

	i = step / 4;
	j = step % 4;
	return (m1[M_VCTX_MTX][j] * m2[i][M_X_MTX] \
			+ m1[M_VCTY_MTX][j] * m2[i][M_Y_MTX] \
			+ m1[M_VCTZ_MTX][j] * m2[i][M_Z_MTX] \
			+ m1[M_VTXO_MTX][j] * m2[i][M_W_MTX]);
}

t_matrix			*m_matrix_mul(t_matrix *self, t_matrix *rhs)
{
	t_matrix		*mtx;

	if (!(mtx = ft_memalloc(sizeof(t_matrix))))
		return (NULL);
	mtx->self = mtx;
	mtx->v[M_VCTX_MTX][M_X_MTX] = m_matrix_mul_step(0, self->v, rhs->v);
	mtx->v[M_VCTX_MTX][M_Y_MTX] = m_matrix_mul_step(1, self->v, rhs->v);
	mtx->v[M_VCTX_MTX][M_Z_MTX] = m_matrix_mul_step(2, self->v, rhs->v);
	mtx->v[M_VCTX_MTX][M_W_MTX] = m_matrix_mul_step(3, self->v, rhs->v);
	mtx->v[M_VCTY_MTX][M_X_MTX] = m_matrix_mul_step(4, self->v, rhs->v);
	mtx->v[M_VCTY_MTX][M_Y_MTX] = m_matrix_mul_step(5, self->v, rhs->v);
	mtx->v[M_VCTY_MTX][M_Z_MTX] = m_matrix_mul_step(6, self->v, rhs->v);
	mtx->v[M_VCTY_MTX][M_W_MTX] = m_matrix_mul_step(7, self->v, rhs->v);
	mtx->v[M_VCTZ_MTX][M_X_MTX] = m_matrix_mul_step(8, self->v, rhs->v);
	mtx->v[M_VCTZ_MTX][M_Y_MTX] = m_matrix_mul_step(9, self->v, rhs->v);
	mtx->v[M_VCTZ_MTX][M_Z_MTX] = m_matrix_mul_step(10, self->v, rhs->v);
	mtx->v[M_VCTZ_MTX][M_W_MTX] = m_matrix_mul_step(11, self->v, rhs->v);
	mtx->v[M_VTXO_MTX][M_X_MTX] = m_matrix_mul_step(12, self->v, rhs->v);
	mtx->v[M_VTXO_MTX][M_Y_MTX] = m_matrix_mul_step(13, self->v, rhs->v);
	mtx->v[M_VTXO_MTX][M_Z_MTX] = m_matrix_mul_step(14, self->v, rhs->v);
	mtx->v[M_VTXO_MTX][M_W_MTX] = m_matrix_mul_step(15, self->v, rhs->v);
	return (mtx);
}

t_matrix			*m_matrix_inv(t_matrix *self)
{
	t_matrix		*mtx;

	if (!(mtx = ft_memalloc(sizeof(t_matrix))))
		return (NULL);
	mtx->self = mtx;
	mtx->type = self->type;
	mtx->v[M_VCTX_MTX][M_X_MTX] = self->v[M_VCTX_MTX][M_X_MTX];
	mtx->v[M_VCTX_MTX][M_Y_MTX] = self->v[M_VCTY_MTX][M_X_MTX];
	mtx->v[M_VCTX_MTX][M_Z_MTX] = self->v[M_VCTZ_MTX][M_X_MTX];
	mtx->v[M_VCTX_MTX][M_W_MTX] = self->v[M_VTXO_MTX][M_X_MTX];
	mtx->v[M_VCTY_MTX][M_X_MTX] = self->v[M_VCTX_MTX][M_Y_MTX];
	mtx->v[M_VCTY_MTX][M_Y_MTX] = self->v[M_VCTY_MTX][M_Y_MTX];
	mtx->v[M_VCTY_MTX][M_Z_MTX] = self->v[M_VCTZ_MTX][M_Y_MTX];
	mtx->v[M_VCTY_MTX][M_W_MTX] = self->v[M_VTXO_MTX][M_Y_MTX];
	mtx->v[M_VCTZ_MTX][M_X_MTX] = self->v[M_VCTX_MTX][M_Z_MTX];
	mtx->v[M_VCTZ_MTX][M_Y_MTX] = self->v[M_VCTY_MTX][M_Z_MTX];
	mtx->v[M_VCTZ_MTX][M_Z_MTX] = self->v[M_VCTZ_MTX][M_Z_MTX];
	mtx->v[M_VCTZ_MTX][M_W_MTX] = self->v[M_VTXO_MTX][M_Z_MTX];
	mtx->v[M_VTXO_MTX][M_X_MTX] = self->v[M_VCTX_MTX][M_W_MTX];
	mtx->v[M_VTXO_MTX][M_Y_MTX] = self->v[M_VCTY_MTX][M_W_MTX];
	mtx->v[M_VTXO_MTX][M_Z_MTX] = self->v[M_VCTZ_MTX][M_W_MTX];
	mtx->v[M_VTXO_MTX][M_W_MTX] = self->v[M_VTXO_MTX][M_W_MTX];
	return (mtx);
}

void				m_matrix_ident_preset(t_matrix *self, va_list *ap)
{
	self->v[M_VCTX_MTX][M_X_MTX] = 1.0;
	self->v[M_VCTY_MTX][M_Y_MTX] = 1.0;
	self->v[M_VCTZ_MTX][M_Z_MTX] = 1.0;
	self->v[M_VTXO_MTX][M_W_MTX] = 1.0;
	(void)ap;
}

void				m_matrix_scale_preset(t_matrix *self, va_list *ap)
{
	double			scale;

	scale = va_arg(*ap, double);
	m_matrix_ident_preset(self, NULL);
	self->v[M_VCTX_MTX][M_X_MTX] = scale;
	self->v[M_VCTY_MTX][M_Y_MTX] = scale;
	self->v[M_VCTZ_MTX][M_Z_MTX] = scale;
}

void				m_matrix_rx_preset(t_matrix *self, va_list *ap)
{
	double			rad_phi;

	rad_phi = va_arg(*ap, double);
	m_matrix_ident_preset(self, NULL);
	self->v[M_VCTY_MTX][M_Y_MTX] = cos(rad_phi);
	self->v[M_VCTY_MTX][M_Z_MTX] = sin(rad_phi);
	self->v[M_VCTZ_MTX][M_Y_MTX] = -sin(rad_phi);
	self->v[M_VCTZ_MTX][M_Z_MTX] = cos(rad_phi);
}

void				m_matrix_ry_preset(t_matrix *self, va_list *ap)
{
	double			rad_psi;

	rad_psi = va_arg(*ap, double);
	m_matrix_ident_preset(self, NULL);
	self->v[M_VCTX_MTX][M_X_MTX] = cos(rad_psi);
	self->v[M_VCTX_MTX][M_Z_MTX] = -sin(rad_psi);
	self->v[M_VCTZ_MTX][M_X_MTX] = sin(rad_psi);
	self->v[M_VCTZ_MTX][M_Z_MTX] = cos(rad_psi);
}

void				m_matrix_rz_preset(t_matrix *self, va_list *ap)
{
	double			rad_teta;

	rad_teta = va_arg(*ap, double);
	m_matrix_ident_preset(self, NULL);
	self->v[M_VCTX_MTX][M_X_MTX] = cos(rad_teta);
	self->v[M_VCTX_MTX][M_Y_MTX] = sin(rad_teta);
	self->v[M_VCTY_MTX][M_X_MTX] = -sin(rad_teta);
	self->v[M_VCTY_MTX][M_Y_MTX] = cos(rad_teta);
}

void				m_matrix_trans_preset(t_matrix *self, va_list *ap)
{
	t_vector		*trans;

	trans = (t_vector *)va_arg(*ap, void *);
	if (!trans)
		return ;
	m_matrix_ident_preset(self, NULL);
	self->v[M_VTXO_MTX][M_X_MTX] = trans->magn[M_X_VCT];
	self->v[M_VTXO_MTX][M_Y_MTX] = trans->magn[M_Y_VCT];
	self->v[M_VTXO_MTX][M_Z_MTX] = trans->magn[M_Z_VCT];
}

void				m_matrix_proj_preset(t_matrix *self, va_list *ap)
{
	double			fov;
	double			ratio;
	double			near;
	double			far;

	fov = va_arg(*ap, double);
	ratio = va_arg(*ap, double);
	near = va_arg(*ap, double);
	far = va_arg(*ap, double);
	fov = tan(fov / 2.0);
	self->v[M_VCTX_MTX][M_X_MTX] = 1.0 / (ratio * fov);
	self->v[M_VCTY_MTX][M_Y_MTX] = 1.0 / fov;
	self->v[M_VCTZ_MTX][M_Z_MTX] = -(far + near) / (far - near);
	self->v[M_VCTZ_MTX][M_W_MTX] = -1.0;
	self->v[M_VTXO_MTX][M_Z_MTX] = -(2.0 * far * near) / (far - near);
}

typedef struct		s_preset_select
{
	int				type;
	void			(*function)(t_matrix *, va_list *);
}					t_preset_select;

t_preset_select		g_preset_select[] = {\
	{M_IDENT_MTX, m_matrix_ident_preset},\
	{M_SCALE_MTX, m_matrix_scale_preset},\
	{M_RX_MTX, m_matrix_rx_preset},\
	{M_RY_MTX, m_matrix_ry_preset},\
	{M_RZ_MTX, m_matrix_rz_preset},\
	{M_TRANS_MTX, m_matrix_trans_preset},\
	{M_PROJ_MTX, m_matrix_proj_preset},\
	{0, 0}\
};

static void			unknow_type(t_matrix *self, va_list *ap)
{
	self->type = -1;
	(void)ap;
}

void		(*preset_select(int type))(t_matrix *, va_list *)
{
	int		i;

	i = -1;
	while (g_preset_select[++i].type > 0)
	{
		if (g_preset_select[i].type == type)
			return (g_preset_select[i].function);
	}
	return (unknow_type);
}

t_matrix	*m_matrix_init_ap(t_matrix *self, int type, va_list *ap)
{
	char	*verb;

	self->self = self;
	self->type = type;
	ft_bzero(self->v, sizeof(self->v));
	preset_select(type)(self, ap);
	if (g_s_matrix_verbose == 1 && (verb = m_matrix2str(self)))
	{
		ft_printf("Init %s ;\n", verb);
		free(verb);
	}
	return (self);
}

t_matrix	*m_matrix_init(t_matrix *self, int type, ...)
{
	va_list	ap;

	va_start(ap, type);
	m_matrix_init_ap(self, type, &ap);
	va_end(ap);
	return (self);
}

t_matrix	*m_matrix_new(int type, ...)
{
	t_matrix	*mtx;
	va_list		ap;

	va_start(ap, type);
	if (!(mtx = ft_memalloc(sizeof(t_matrix))))
		return (NULL);
	m_matrix_init_ap(mtx, type, &ap);
	va_end(ap);
	return (mtx);
}

t_matrix	*m_matrix_clear(t_matrix *self)
{
	char	*verb;

	if (g_s_matrix_verbose == 1 && (verb = m_matrix2str(self)))
	{
		ft_printf("Clear %s ;\n", verb);
		free(verb);
	}
	ft_bzero(self, sizeof(t_matrix));
	self->self = self;
	return (self);
}

void		m_matrix_del(t_matrix **mtx)
{
	m_matrix_clear(*mtx);
	free(*mtx);
	*mtx = NULL;
}

typedef struct		s_typestr_select
{
	int				type;
	char			*str;
}					t_typestr_select;

t_typestr_select	g_typestr_select[] = {\
	{M_IDENT_MTX, "'Identity'"},\
	{M_SCALE_MTX, "'Scale'"},\
	{M_RX_MTX, "'X Rotation'"},\
	{M_RY_MTX, "'Y Rotation'"},\
	{M_RZ_MTX, "'Z Rotation'"},\
	{M_TRANS_MTX, "'Translation'"},\
	{M_PROJ_MTX, "'Projection'"},\
	{0, 0}\
};

char		*typestr_select(int type)
{
	int		i;

	i = -1;
	while (g_typestr_select[++i].type > 0)
	{
		if (g_typestr_select[i].type == type)
			return (g_typestr_select[i].str);
	}
	return ("'Not a valid Matrix preset type'");
}

char		*m_matrix_typestr(t_matrix *self)
{
	return (typestr_select(self->type));
}

char		*m_matrix2str(t_matrix *self)
{
	char	buf[1024];

	snprintf(buf, 1024, \
		"Matrix( Type = %s, v = {\n"
				"\t  VtcX, VctY, VctZ, VtxO\n"
				"\tx %4.02f, %4.02f, %4.02f, %4.02f\n"
				"\ty %4.02f, %4.02f, %4.02f, %4.02f\n"
				"\tz %4.02f, %4.02f, %4.02f, %4.02f\n"
				"\tw %4.02f, %4.02f, %4.02f, %4.02f } )", \
			m_matrix_typestr(self), \
			self->v[M_VCTX_MTX][M_X_MTX], self->v[M_VCTY_MTX][M_X_MTX], \
			self->v[M_VCTZ_MTX][M_X_MTX], self->v[M_VTXO_MTX][M_X_MTX], \
			self->v[M_VCTX_MTX][M_Y_MTX], self->v[M_VCTY_MTX][M_Y_MTX], \
			self->v[M_VCTZ_MTX][M_Y_MTX], self->v[M_VTXO_MTX][M_Y_MTX], \
			self->v[M_VCTX_MTX][M_Z_MTX], self->v[M_VCTY_MTX][M_Z_MTX], \
			self->v[M_VCTZ_MTX][M_Z_MTX], self->v[M_VTXO_MTX][M_Z_MTX], \
			self->v[M_VCTX_MTX][M_W_MTX], self->v[M_VCTY_MTX][M_W_MTX], \
			self->v[M_VCTZ_MTX][M_W_MTX], self->v[M_VTXO_MTX][M_W_MTX]);
	return (ft_strdup(buf));
}

