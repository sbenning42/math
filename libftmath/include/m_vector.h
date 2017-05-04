/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_vector.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:43:48 by                   #+#    #+#             */
/*   Updated: 2017/05/04 14:27:10 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_VECTOR_H
# define M_VECTOR_H

# include "m_vertex.h"
# include <math.h>

# define M_VCTSTR "Verctor( x = %.2f, y = %.2f, z = %.2f, w = %.2f )"

typedef struct s_vector	t_vector;

int						g_s_vector_verbose;

struct					s_vector
{
	double				v[4];
};

t_vector	*m_vector_new(t_vertex *dest, t_vertex *origin);
void		m_vector_del(t_vector **vct);
char		*m_vector_str(t_vector *vct, char *buf, size_t n);
t_vector	*m_vector_add(t_vector *vct1, t_vector *vct2);
t_vector	*m_vector_sub(t_vector *vct1, t_vector *vct2);
double		m_vector_dot(t_vector *vct1, t_vector *vct2);
double		m_vector_cos(t_vector *vct1, t_vector *vct2);
t_vector	*m_vector_cross(t_vector *vct1, t_vector *vct2);
t_vector	*m_vector_scalar(t_vector *vct1, double factor);
t_vector	*m_vector_opposite(t_vector *vct1);
t_vector	*m_vector_normalize(t_vector *vct1);
double		m_vector_magnitude(t_vector *vct);

#endif
