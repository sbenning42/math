/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 19:11:36 by                   #+#    #+#             */
/*   Updated: 2017/05/05 01:36:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

#define COMM 0
#define MESH 1
#define COL 2
#define VTX 3
#define FACE 4
#define INT 5
#define FLO 6

static char	*g_key[] = {\
	"Comment", \
	"Mesh", \
	"Color", \
	"Vertex", \
	"Face", \
	"Integer", \
	"Float"\
};

static char	*g_regex[] = {\
	"#.*", \
	"o [a-z]+", \
	"c ", \
	"v ", \
	"f ", \
	"[0-9]+", \
	"\\-?[0-9]+\\.[0-9]+"\
};

typedef struct s_select_lexem_handler	t_select_lexem_handler;

struct									s_select_lexem_handler
{
	int									id;
	int									(*handler)(t_data *, t_lexem *);
};

static t_select_lexem_handler	g_select_lexem_handler[] = {\
	{COMM, comment_lexem_hdl}, \
	{MESH, mesh_lexem_hdl}, \
	{COL, color_lexem_hdl}, \
	{VTX, vertex_lexem_hdl}, \
	{FACE, face_lexem_hdl}, \
	{-1, 0}\
};

static int	(*select_lexem_handler(int id))(t_data *, t_lexem *)
{
	int		i;

	i = -1;
	while (g_select_lexem_handler[++i].handler != 0)
	{
		if (g_select_lexem_handler[i].id == id)
			return (g_select_lexem_handler[i].handler);
	}
	return (uncatched_error);
}

static int	parse_line(t_data *data, char *line)
{
	t_lexem	*l;

	if (!*line)
		return (0);
	ft_lex_start_scan(line);
	while ((l = ft_lex()))
	{
		if (l->id < 0)
		{
			ft_fprintf(2, "%s: Syntax error: `%s`\n", progname(), line);
			return (-1);
		}
		if (select_lexem_handler(l->id)(data, l))
			return (-1);
		lexem_del(&l);
	}
	return (0);
}

static int	data_setup(t_data *data, char *filename)
{
	int		fd;
	int		ret;
	char	*line;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_fprintf(2, "%s: Error open `%s`\n", progname(), filename);
		return (-1);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (parse_line(data, line))
		{
			close(fd);
			return (-1);
		}
		ft_memdel((void **)&line);
	}
	if (ret < 0)
	{
		ft_fprintf(2, "%s: Error reading `%s`\n", progname(), filename);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	mlx_setup(t_data *data)
{
	if (!(data->mlx = mlx_init()))
	{
		ft_fprintf(2, "%s: Error mlx_init\n", progname());
		return (-1);
	}
	if (!(data->win = mlx_new_window(data->mlx, data->width, data->height, \
										"Ft Mlx")))
	{
		ft_fprintf(2, "%s: Error mlx_new_window\n", progname());
		return (-1);
	}
	if (!(data->img = mlx_new_image(data->mlx, data->width, data->height)))
	{
		ft_fprintf(2, "%s: Error mlx_new_image\n", progname());
		return (-1);
	}
	if (!(data->img_addr = mlx_get_data_addr(data->img, &data->bpp, \
												&data->sizel, &data->endian)))
	{
		ft_fprintf(2, "%s: Error mlx_get_data_addr\n", progname());
		return (-1);
	}
	mlx_expose_hook(data->win, expose_hook, data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	return (0);
}

int			setup(t_data *data, int ac, char **av)
{
	t_lexer	*lex;
	t_vertex	*vx;
	t_vector	*vc;

	if (!(lex = ft_gen_lex(g_regex, g_key, TABSIZE(g_key))))
	{
		ft_fprintf(2, "%s: Error ft_gen_lex\n", progname());
		return (-1);
	}
	ft_set_lex(lex);
	if (data_setup(data, av[1]))
		return (-1);
	ft_kill_lex();
	if (!(data->repere = make_repere()))
	{
		ft_fprintf(2, "%s: Error make_repere\n", progname());
		return (-1);
	}
	if (mlx_setup(data))
		return (-1);
	if (!(data->render = m_render_new(data->width, data->height, \
										data->img_addr, data->bpp, \
										data->sizel, data->endian)))
	{
		ft_fprintf(2, "%s: Error m_render_new\n", progname());
		return (-1);
	}
	if (!(vx = m_vertex_new(20.0, 20.0, 0.0, NULL)))
	{
		ft_fprintf(2, "%s: Error m_vertex_new\n", progname());
		return (-1);
	}
	if (!(vc = m_vector_new(vx, NULL)))
	{
		ft_fprintf(2, "%s: Error m_vector_new\n", progname());
		return (-1);
	}
	m_vertex_del(&vx);
	if (!(data->m[TRANSMAT] = m_matrix_new(M_TRANSLATION, vc)))
	{
		ft_fprintf(2, "%s: Error m_matrix_new\n", progname());
		return (-1);
	}
	m_vector_del(&vc);
	if (!(data->m[SCALEMAT] = m_matrix_new(M_SCALE, 10.0)))
	{
		ft_fprintf(2, "%s: Error m_matrix_new\n", progname());
		return (-1);
	}
	if (!(data->m[ROTXMAT] = m_matrix_new(M_RX, M_PI_4)))
	{
		ft_fprintf(2, "%s: Error m_matrix_new\n", progname());
		return (-1);
	}
	if (!(data->m[ROTYMAT] = m_matrix_new(M_RY, M_PI_4)))
	{
		ft_fprintf(2, "%s: Error m_matrix_new\n", progname());
		return (-1);
	}
	if (!(data->m[TRANSFMAT] = m_matrix_new(M_SCALE, 10.0)))
	{
		ft_fprintf(2, "%s: Error m_matrix_new\n", progname());
		return (-1);
	}
	return (0);
	(void)ac;
}
