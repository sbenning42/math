/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_vertex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 04:00:18 by                   #+#    #+#             */
/*   Updated: 2017/05/02 06:22:00 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_vertex	*m_vertex_init(t_vertex *self, double *coo, t_color *c)
{
	char	*verb;

	self->self = self;
	self->color = c;
	self->coo[M_X_VTX] = coo[M_X_VTX];
	self->coo[M_Y_VTX] = coo[M_Y_VTX];
	self->coo[M_Z_VTX] = coo[M_Z_VTX];
	self->coo[M_W_VTX] = coo[M_W_VTX];
	if (g_s_vertex_verbose && (verb = m_vertex2str(self)))
	{
		ft_printf("Init %s ;\n", verb);
		free(verb);
	}
	return (self);
}

t_vertex	*m_vertex_clear(t_vertex *self)
{	
	char	*verb;

	if (g_s_vertex_verbose && (verb = m_vertex2str(self)))
	{
		ft_printf("Clear %s ;\n", verb);
		free(verb);
	}
	ft_bzero(self, sizeof(t_vertex));
	self->self = self;
	return (self);
}

t_vertex	*m_vertex_new(double *coo, t_color *c)
{
	t_vertex	*vtx;

	if (!(vtx = ft_memalloc(sizeof(t_vertex))))
		return (NULL);
	m_vertex_init(vtx, coo, c);
	return (vtx);
}

void		m_vertex_del(t_vertex **vtx)
{
	m_vertex_clear(*vtx);
	free(*vtx);
	*vtx = NULL;
}

char		*m_vertex2str(t_vertex *self)
{
	char	buf[1024];
	char	*strcolor;

	strcolor = m_color2str(self->color);
	ft_snprintf(buf, 1024, "Vertex( Coo[ %d.xx, %d.xx, %d.xx, %d.xx ], %s )", \
			(int)self->coo[M_X_VTX], \
			(int)self->coo[M_Y_VTX], \
			(int)self->coo[M_Z_VTX], \
			(int)self->coo[M_W_VTX], \
			strcolor);
	free(strcolor);
	return (ft_strdup(buf));
}

static t_vertex		g_m_vvtx_orig = {\
	&g_m_vvtx_orig, \
	{0.0, 0.0, 0.0, 1.0}, \
	NULL};

t_vertex			*g_m_vtx_orig = &g_m_vvtx_orig;
