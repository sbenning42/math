/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 19:08:57 by                   #+#    #+#             */
/*   Updated: 2017/05/05 02:17:43 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

# define WIDTH 640
# define HEIGHT 480

# define TRANSMAT 0
# define SCALEMAT 1
# define ROTXMAT 2
# define ROTYMAT 3
# define TRANSFMAT 4

# include "libftmath.h"
# include "mlx.h"
# include "get_next_line.h"
# include <fcntl.h>

typedef struct s_data		t_data;
typedef struct s_select_key	t_select_key;

int							g_s_data_verbose;

struct						s_data
{
	char					*progname;
	char					*filename;
	int						width;
	int						height;
	void					*mlx;
	void					*win;
	int						event;
	void					*img;
	char					*img_addr;
	int						bpp;
	int						sizel;
	int						endian;
	t_render				*render;
	t_mesh					*repere;
	t_matrix				*m[5];
};

struct						s_select_key
{
	int						keycode;
	int						(*handler)(t_data *);
};

char	*progname(void);
int		setup(t_data *data, int ac, char **av);

int		uncatched_error(t_data *data, t_lexem *l);
int		comment_lexem_hdl(t_data *data, t_lexem *l);
int		mesh_lexem_hdl(t_data *data, t_lexem *l);
int		color_lexem_hdl(t_data *data, t_lexem *l);
int		vertex_lexem_hdl(t_data *data, t_lexem *l);
int		face_lexem_hdl(t_data *data, t_lexem *l);

int		esc_key(t_data *data);
int		right_key(t_data *data);
int		a_key(t_data *data);
int		(*select_key(int keycode))(t_data *);

void	refresh(t_data *data);

int		loop_hook(void *param);
int		expose_hook(void *param);
int		key_hook(int keycode, void *param);
int		mouse_hook(int button, int x, int y, void *param);

#endif
