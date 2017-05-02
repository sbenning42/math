/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 04:00:18 by                   #+#    #+#             */
/*   Updated: 2017/05/02 06:31:36 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

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

double		m_vector_magnitude(t_vector *self)
{
	return (sqrt(\
				pow(self->magn[M_X_VCT], 2.0) \
				+ pow(self->magn[M_Y_VCT], 2.0) \
				+ pow(self->magn[M_Z_VCT], 2.0)));
}

t_vector	*m_vector_normalize(t_vector *self)
{
	return (self);
}

t_vector	*m_vector_add(t_vector *self, t_vector *rhs)
{
	return (self);
	(void)rhs;
}

t_vector	*m_vector_sub(t_vector *self, t_vector *rhs)
{
	return (self);
	(void)rhs;
}

t_vector	*m_vector_opposite(t_vector *self)
{
	return (self);
}

t_vector	*m_vector_scalar_product(t_vector *self, double factor)
{
	return (self);
	(void)factor;
}

t_vector	*m_vector_dot_product(t_vector *self, t_vector *rhs)
{
	return (self);
	(void)rhs;
}

double		m_vector_dot_product(t_vector *self, t_vector *rhs)
{
	return (self);
	(void)rhs;
}

t_vector	*m_vector_cross_product(t_vector *self, t_vector *rhs)
{
	return (self);
	(void)rhs;
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
