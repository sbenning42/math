/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 04:00:18 by                   #+#    #+#             */
/*   Updated: 2017/05/02 16:06:22 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

int			m_equalszero(double d)
{
	return ((d > -M_DEPSILON) && (d < M_DEPSILON));
}

int			m_equals(double d1, double d2)
{
	double	eps;

	if (d1 > d2)
		eps = d1 - d2;
	else
		eps = d2 - d1;
	return (eps < M_DEPSILON);
}

t_vector	*m_vector_init(t_vector *self, t_vertex *dest, t_vertex *orig)
{
	char	*verb;

	self->self = self;
	self->magn[M_X_VCT] = dest->coo[M_X_VTX] - orig->coo[M_X_VTX];
	self->magn[M_Y_VCT] = dest->coo[M_Y_VTX] - orig->coo[M_Y_VTX];
	self->magn[M_Z_VCT] = dest->coo[M_Z_VTX] - orig->coo[M_Z_VTX];
	self->magn[M_W_VCT] = 1.0;
	if (g_s_vector_verbose && (verb = m_vector2str(self)))
	{
		ft_printf("Init %s ;\n", verb);
		free(verb);
	}
	return (self);
}

t_vector	*m_vector_clear(t_vector *self)
{	
	char	*verb;

	if (g_s_vector_verbose && (verb = m_vector2str(self)))
	{
		ft_printf("Clear %s ;\n", verb);
		free(verb);
	}
	ft_bzero(self, sizeof(t_vector));
	self->self = self;
	return (self);
}

t_vector	*m_vector_new(t_vertex *dest, t_vertex *orig)
{
	t_vector	*vct;

	if (!(vct = ft_memalloc(sizeof(t_vector))))
		return (NULL);
	m_vector_init(vct, dest, orig);
	return (vct);
}

void		m_vector_del(t_vector **vct)
{
	m_vector_clear(*vct);
	free(*vct);
	*vct = NULL;
}

t_vector	*m_vector_dup(t_vector *self)
{
	t_vector	*vct;

	if (!(vct = ft_memalloc(sizeof(t_vector))))
		return (NULL);
	vct->self = vct;
	vct->magn[M_X_VCT] = self->magn[M_X_VCT];
	vct->magn[M_Y_VCT] = self->magn[M_Y_VCT];
	vct->magn[M_Z_VCT] = self->magn[M_Z_VCT];
	vct->magn[M_W_VCT] = self->magn[M_W_VCT];
	return (vct);
}

int			m_vector_is_zero(t_vector *self)
{
	return (m_equalszero(self->magn[M_X_VCT]) \
			&& m_equalszero(self->magn[M_Y_VCT]) \
			&& m_equalszero(self->magn[M_Z_VCT]));
}

void		m_vector_make_zero(t_vector *self)
{
	self->magn[M_X_VCT] = 0.0;
	self->magn[M_Y_VCT] = 0.0;
	self->magn[M_Z_VCT] = 0.0;
}

int			m_vector_is_equals(t_vector *self, t_vector *rhs)
{
	return (m_equals(self->magn[M_X_VCT], rhs->magn[M_X_VCT]) \
			&& m_equals(self->magn[M_Y_VCT], rhs->magn[M_Y_VCT]) \
			&& m_equals(self->magn[M_Z_VCT], rhs->magn[M_Z_VCT]));
}

/*
**	is magnitude w dependant?
*/

double		m_vector_magnitude(t_vector *self)
{
	return (sqrt(\
				pow(self->magn[M_X_VCT], 2.0) \
				+ pow(self->magn[M_Y_VCT], 2.0) \
				+ pow(self->magn[M_Z_VCT], 2.0)));
}
#include <stdio.h>
t_vector	*m_vector_normalize(t_vector *self)
{
	t_vector	*vct;
	double		magn;

	if (!(vct = m_vector_dup(self)))
		return (NULL);
	if ((magn = m_vector_magnitude(self)))
	{
		magn = 1.0 / magn;
		vct->magn[M_X_VCT] *= magn;
		vct->magn[M_Y_VCT] *= magn;
		vct->magn[M_Z_VCT] *= magn;
	}
	return (vct);
}

t_vector	*m_vector_add(t_vector *self, t_vector *rhs)
{
	t_vector	*vct;

	if (!(vct = m_vector_dup(self)))
		return (NULL);
	vct->magn[M_X_VCT] += rhs->magn[M_X_VCT];
	vct->magn[M_Y_VCT] += rhs->magn[M_Y_VCT];
	vct->magn[M_Z_VCT] += rhs->magn[M_Z_VCT];
	return (vct);
}

t_vector	*m_vector_sub(t_vector *self, t_vector *rhs)
{
	t_vector	*vct;

	if (!(vct = m_vector_dup(self)))
		return (NULL);
	vct->magn[M_X_VCT] -= rhs->magn[M_X_VCT];
	vct->magn[M_Y_VCT] -= rhs->magn[M_Y_VCT];
	vct->magn[M_Z_VCT] -= rhs->magn[M_Z_VCT];
	return (vct);
}

t_vector	*m_vector_mul(t_vector *self, t_vector *rhs)
{
	t_vector	*vct;

	if (!(vct = m_vector_dup(self)))
		return (NULL);
	vct->magn[M_X_VCT] *= rhs->magn[M_X_VCT];
	vct->magn[M_Y_VCT] *= rhs->magn[M_Y_VCT];
	vct->magn[M_Z_VCT] *= rhs->magn[M_Z_VCT];
	return (vct);
}

t_vector	*m_vector_opposite(t_vector *self)
{
	return (m_vector_scalar_product(self, -1.0));
}

t_vector	*m_vector_scalar_product(t_vector *self, double factor)
{
	t_vector	*vct;

	if (!(vct = m_vector_dup(self)))
		return (NULL);
	vct->magn[M_X_VCT] *= factor;
	vct->magn[M_Y_VCT] *= factor;
	vct->magn[M_Z_VCT] *= factor;
	return (vct);
}

double		m_vector_dot_product(t_vector *self, t_vector *rhs)
{
	return ((self->magn[M_X_VCT] * rhs->magn[M_X_VCT]) \
			+ (self->magn[M_Y_VCT] * rhs->magn[M_Y_VCT]) \
			+ (self->magn[M_Z_VCT] * rhs->magn[M_Z_VCT]));
}

double		m_vector_cos(t_vector *self, t_vector *rhs)
{
	return (m_vector_dot_product(self, rhs) \
			/ (m_vector_magnitude(self) * m_vector_magnitude(rhs)));
}

t_vector	*m_vector_cross_product(t_vector *self, t_vector *rhs)
{
	t_vector	*vct;

	if (!(vct = ft_memalloc(sizeof(t_vector))))
		return (NULL);
	vct->self = vct;
	vct->magn[M_X_VCT] = \
						self->magn[M_Y_VCT] * rhs->magn[M_Z_VCT] \
				   		- self->magn[M_Z_VCT] * rhs->magn[M_Y_VCT];
	vct->magn[M_Y_VCT] = \
						self->magn[M_Z_VCT] * rhs->magn[M_X_VCT] \
				   		- self->magn[M_X_VCT] * rhs->magn[M_Z_VCT];
	vct->magn[M_Z_VCT] = \
						self->magn[M_X_VCT] * rhs->magn[M_Y_VCT] \
				   		- self->magn[M_Y_VCT] * rhs->magn[M_X_VCT];
	vct->magn[M_W_VCT] = 1.0;
	return (vct);
}

double		m_vector_distance(t_vector *self, t_vector *rhs)
{
	t_vector	*d;
	double		dist;

	if (!(d == m_vector_sub(self, rhs)))
		return (0.0);
	dist = m_vector_magnitude(d);
	m_vector_del(&d);
	return (dist);
}

char		*m_vector2str(t_vector *self)
{
	char	buf[1024];

	ft_snprintf(buf, 1024, "Vector( Magn[ %d.xx, %d.xx, %d.xx, %d.xx ] )", \
			(int)self->magn[M_X_VCT], \
			(int)self->magn[M_Y_VCT], \
			(int)self->magn[M_Z_VCT], \
			(int)self->magn[M_W_VCT]);
	return (ft_strdup(buf));
}

static t_vector		g_m_vvct_orig = {\
	&g_m_vvct_orig, \
	{0.0, 0.0, 0.0, 1.0}\
};

t_vector			*g_m_vct_orig = &g_m_vvct_orig;
