/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_triangle.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 11:14:24 by                   #+#    #+#             */
/*   Updated: 2017/05/04 15:37:29 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_TRIANGLE_H
# define M_TRIANGLE_H

# define M_TRISTR "Triangle(\n"\
					"\tA = %s,\n"\
					"\tB = %s,\n"\
					"\tC = %s,\n"\
					"\tVisible = %d )"

# include "m_vector.h"

typedef struct s_triangle	t_triangle;

int							g_s_triangle_verbose;

struct						s_triangle
{
	t_vertex				*a;
	t_vertex				*b;
	t_vertex				*c;
	int						visible;
};

t_triangle	*m_triangle(t_vertex *a, t_vertex *b, t_vertex *c);
void		m_triangle_del(t_triangle **tri);
char		*m_triangle_str(t_triangle *tri, char *buf, size_t n);
int			m_triangle_normal(t_triangle *tri, t_vector **normal);
t_vertex	*m_triangle_centroid(t_triangle *tri);
double		m_triangle_area(t_triangle *tri);
t_color		*m_triangle_color(t_triangle *tri, t_vertex *vtx);

#endif
