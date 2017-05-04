/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_matrix.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:50:20 by                   #+#    #+#             */
/*   Updated: 2017/05/04 00:37:09 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_MATRIX_H
# define M_MATRIX_H

# define M_IDENTITY 1
# define M_SCALE 2
# define M_RX 3
# define M_RY 4
# define M_RZ 5
# define M_TRANSLATION 6
# define M_PROJECTION 7

# define FOV 0
# define RATIO 1
# define NEAR 2
# define FAR 3
# define CONFIGSIZE 4

# define RIGHT 0
# define LEFT 1
# define TOP 2
# define BOTTOM 3

# define M_MTXSTR "Matrix(\n\t ---------------------------------------\n"\
						   "\t| M | VtcX   | VctY   | VctZ   | VtxO   |\n"\
						   "\t|---|--------|--------|--------|--------|\n"\
				  		   "\t| x | %6.02f | %6.02f | %6.02f | %6.02f |\n"\
				  		   "\t| y | %6.02f | %6.02f | %6.02f | %6.02f |\n"\
				  		   "\t| z | %6.02f | %6.02f | %6.02f | %6.02f |\n"\
				  		   "\t| w | %6.02f | %6.02f | %6.02f | %6.02f |\n"\
						   "\t --------------------------------------- )"

# include "m_vector.h"

typedef struct s_matrix			t_matrix;
typedef struct s_select_preset	t_select_preset;

struct			s_select_preset
{
	int			preset;
	t_matrix	*(*make)(t_matrix *, va_list *);
};

int				g_s_matrix_verbose;

struct			s_matrix
{
	double		v[4][4];
};

t_matrix		*m_matrix_new(int type, ...);
void			m_matrix_del(t_matrix **m);
char			*m_matrix_str(t_matrix *m, char *buf, size_t n);
t_matrix		*m_matrix_mult(t_matrix *m1, t_matrix *m2);
t_matrix		*m_matrix_transp(t_matrix *m1);
t_vertex		*m_matrix_apply_vertex(t_matrix *m, t_vertex *vtx);

#endif
