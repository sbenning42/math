/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_render.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 12:20:20 by                   #+#    #+#             */
/*   Updated: 2017/05/04 23:31:12 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_RENDER_H
# define M_RENDER_H

# define M_VERTEX 1
# define M_EDGE 2
# define M_RASTERIZE 3

# define M_RENDERSTR "Render( width = %.2f, height = %.2f, buf = %p, "\
							"bpp = %d, size line = %d, endian %d )"

# include "m_mesh.h"

typedef struct s_render	t_render;

int						g_s_render_verbose;

struct					s_render
{
	char				*buf;
	double				width;
	double				height;
	int					bpp;
	int					sizel;
	int					endian;
};

t_render			*m_render_new(double width, double height, char *buf, \
									int bpp, int sizel, int endian);
void				m_render_del(t_render **render);
char				*m_render_str(t_render *render, char *buf, size_t n);
void				m_render_vtx(t_render *render, t_vertex *vtx);
void				m_render_tri(t_render *render, t_triangle *tri, int mode);
void				m_render_mesh(t_render *render, t_mesh *mesh, int mode);

#endif
