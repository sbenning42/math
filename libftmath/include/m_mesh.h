/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mesh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:22:25 by                   #+#    #+#             */
/*   Updated: 2017/05/04 13:55:34 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_MESH_H
# define M_MESH_H

# include "m_triangle.h"

typedef struct s_mesh	t_mesh;

int						g_s_mesh_verbose;

struct					s_mesh
{
	t_triangle			*tri;
	t_mesh				*next;
};

t_mesh					*m_mesh_newm(t_triangle *tri);
t_mesh					*m_mesh_new(t_triangle *tri);
void					m_mesh_add(t_mesh **mesh, t_mesh *ntri);
void					m_mesh_del(t_mesh **mesh);
char					*m_mesh_str(t_mesh *mesh);

#endif
