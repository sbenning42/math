/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_vertex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:43:48 by                   #+#    #+#             */
/*   Updated: 2017/05/03 19:23:02 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_VERTEX_H
# define M_VERTEX_H

# include "m_color.h"
# include <stdio.h>

# define M_VTXSTR "Vertex( x = %.2f, y = %.2f, z = %.2f, w = %.2f, c = %s )"
# define M_IX 0
# define M_IY 1
# define M_IZ 2
# define M_IW 3

typedef struct s_vertex		t_vertex;

int							g_s_vertex_verbose;

struct						s_vertex
{
	double					v[4];
	t_color					*c;
};

t_vertex	*m_vertex_new(double x, double y, double z, t_color *c);
void		m_vertex_del(t_vertex **vtx);
char		*m_vertex_str(t_vertex *vtx, char *buf, size_t n);
t_vertex	*m_vertex_add(t_vertex *vtx1, t_vertex *vtx2);
t_vertex	*m_vertex_sub(t_vertex *vtx1, t_vertex *vtx2);
t_vertex	*m_vertex_mult(t_vertex *vtx1, double factor);

#endif
