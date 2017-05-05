/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexem_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 21:32:00 by                   #+#    #+#             */
/*   Updated: 2017/05/04 22:37:01 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

int		uncatched_error(t_data *data, t_lexem *l)
{/*
	ft_fprintf(2, "%s: Unknow error on : %s\n", progname(), l->value);
	return (-1);
*/	return (0);
	(void)l;
	(void)data;
}

int		comment_lexem_hdl(t_data *data, t_lexem *l)
{
	return (0);
	(void)data;
	(void)l;
}

int		mesh_lexem_hdl(t_data *data, t_lexem *l)
{
	return (0);
	(void)data;
	(void)l;
}

int		color_lexem_hdl(t_data *data, t_lexem *l)
{
	return (0);
	(void)data;
	(void)l;
}

int		vertex_lexem_hdl(t_data *data, t_lexem *l)
{
	return (0);
	(void)data;
	(void)l;
}

int		face_lexem_hdl(t_data *data, t_lexem *l)
{
	return (0);
	(void)data;
	(void)l;
}
