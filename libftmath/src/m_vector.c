/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 19:35:33 by                   #+#    #+#             */
/*   Updated: 2017/05/04 00:29:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_vector.h"

t_vector		*m_vector_new(t_vertex *dest, t_vertex *origin)
{
	t_vector	*vct;
	char		buf[256 + 1];

	if (!(vct = ft_memalloc(sizeof(t_vector))))
		return (NULL);
	if (origin)
	{
		vct->v[0] = dest->v[0] - origin->v[0];
		vct->v[1] = dest->v[1] - origin->v[1];
		vct->v[2] = dest->v[2] - origin->v[2];
		vct->v[3] = dest->v[3] - origin->v[3];
	}
	else
	{
		vct->v[0] = dest->v[0];
		vct->v[1] = dest->v[1];
		vct->v[2] = dest->v[2];
		vct->v[3] = dest->v[3] - 1.0;
	}
	if (g_s_vector_verbose == 1)
	{
		m_vector_str(vct, buf, 256);
		ft_printf("New %s ;\n", buf);
	}
	return (vct);
}

void			m_vector_del(t_vector **vct)
{
	char		buf[256 + 1];

	if (*vct && g_s_vector_verbose == 1)
	{
		m_vector_str(*vct, buf, 256);
		ft_printf("Del %s ;\n", buf);
	}
	if (*vct)
	{
		free(*vct);
		*vct = NULL;
	}
}

char			*m_vector_str(t_vector *vct, char *buf, size_t n)
{
	char		lbuf[256 + 1];

	if (!buf)
	{
		buf = lbuf;
		n = 256;
	}
	if (vct)
		snprintf(buf, n, M_VCTSTR, vct->v[0], vct->v[1], vct->v[2], vct->v[3]);
	else
		snprintf(buf, n, "null");
	return ((buf == lbuf ? ft_strdup(buf) : buf));
}

double			m_vector_magnitude(t_vector *vct)
{
	return (sqrt(vct->v[0] * vct->v[0] \
				+ vct->v[1] * vct->v[1] \
				+ vct->v[2] * vct->v[2]));
}

t_vector		*m_vector_normalize(t_vector *vct1)
{
	double		magnitude;
	t_vertex	*vtx;
	t_vector	*vct;

	magnitude = m_vector_magnitude(vct1);
	magnitude = 1.0 / magnitude;
	if (!(vtx = m_vertex_new(\
					vct1->v[0] * magnitude, \
					vct1->v[1] * magnitude, \
					vct1->v[2] * magnitude, \
					NULL)))
		return (NULL);
	vct = m_vector_new(vtx, NULL);
	m_vertex_del(&vtx);
	return (vct);
}

t_vector		*m_vector_opposite(t_vector *vct1)
{
	t_vertex	*vtx;
	t_vector	*vct;

	if (!(vtx = m_vertex_new(-vct1->v[0], -vct1->v[1], -vct1->v[2], NULL)))
		return (NULL);
	vct = m_vector_new(vtx, NULL);
	m_vertex_del(&vtx);
	return (vct);

}

t_vector		*m_vector_scalar(t_vector *vct1, double factor)
{
	t_vertex	*vtx;
	t_vector	*vct;

	if (!(vtx = m_vertex_new(\
					vct1->v[0] * factor, \
					vct1->v[1] * factor, \
					vct1->v[2] * factor, \
					NULL)))
		return (NULL);
	vct = m_vector_new(vtx, NULL);
	m_vertex_del(&vtx);
	return (vct);
}

t_vector		*m_vector_add(t_vector *vct1, t_vector *vct2)
{
	t_vertex	*vtx;
	t_vector	*vct;

	if (!(vtx = m_vertex_new(\
					vct1->v[0] + vct2->v[0], \
					vct1->v[1] + vct2->v[1], \
					vct1->v[2] + vct2->v[2], \
					NULL)))
		return (NULL);
	vct = m_vector_new(vtx, NULL);
	m_vertex_del(&vtx);
	return (vct);
}

t_vector		*m_vector_sub(t_vector *vct1, t_vector *vct2)
{
	t_vertex	*vtx;
	t_vector	*vct;

	if (!(vtx = m_vertex_new(\
					vct1->v[0] - vct2->v[0], \
					vct1->v[1] - vct2->v[1], \
					vct1->v[2] - vct2->v[2], \
					NULL)))
		return (NULL);
	vct = m_vector_new(vtx, NULL);
	m_vertex_del(&vtx);
	return (vct);
}

double			m_vector_dot(t_vector *vct1, t_vector *vct2)
{
	return (vct1->v[0] * vct2->v[0] \
			+ vct1->v[1] * vct2->v[1] \
			+ vct1->v[2] * vct2->v[2]);
}

double			m_vector_cos(t_vector *vct1, t_vector *vct2)
{
	return (m_vector_dot(vct1, vct2) \
			/ abs(m_vector_magnitude(vct1) * m_vector_magnitude(vct2)));
}

t_vector		*m_vector_cross(t_vector *vct1, t_vector *vct2)
{
	t_vertex	*vtx;
	t_vector	*vct;

	if (!(vtx = m_vertex_new(\
					vct1->v[1] * vct2->v[2] - vct1->v[2] * vct2->v[1], \
					vct1->v[2] * vct2->v[0] - vct1->v[0] * vct2->v[2], \
					vct1->v[0] * vct2->v[1] - vct1->v[1] * vct2->v[0], \
					NULL)))
		return (NULL);
	vct = m_vector_new(vtx, NULL);
	m_vertex_del(&vtx);
	return (vct);
}
