/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <sbenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 15:55:13 by sbenning          #+#    #+#             */
/*   Updated: 2015/12/14 10:24:41 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		get_mem(char **tab, char **mem)
{
	char		*find;

	if (!*tab)
	{
		if (!(*tab = ft_strnew(BUFF_S)))
			return (-1);
		if (!(*mem = ft_strnew(BUFF_S)))
			return (-1);
		return (0);
	}
	if (!(*mem = ft_strnew(BUFF_S)))
	{
		ft_memdel((void **)tab);
		return (-1);
	}
	if (!(find = ft_strchr(*tab, '\n')))
	{
		ft_strncpy(*mem, *tab, BUFF_S);
		ft_bzero(*tab, BUFF_S);
		return (0);
	}
	*find = '\0';
	ft_strncpy(*mem, *tab, BUFF_S);
	ft_strncpy(*tab, &(find[1]), BUFF_S);
	return (1);
}

static char		get_line(int fd, char **line, char **tab)
{
	char		*find;
	int			ret;
	int			t_ret;

	t_ret = 0;
	find = NULL;
	if (!(*line = ft_strnew(BUFF_S)))
		return (-1);
	while (!find)
	{
		if (!(*line = ft_strexp(*line, BUFF_S + t_ret)))
			return (-1);
		if ((ret = read(fd, *line + t_ret, BUFF_S)) < 0)
			return (-1);
		if (!ret)
			return (0);
		(*line)[t_ret + ret] = '\0';
		find = ft_strchr(*line + t_ret, '\n');
		t_ret += ret;
	}
	find[0] = '\0';
	ft_strncpy(*tab, &(find[1]), BUFF_S);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char	*tab[MY_RLIMIT_NOFILE];
	char		ret;
	char		*mem;
	char		*line_tmp;

	if (!line || (fd < 0))
		return (-1);
	if ((ret = get_mem(&(tab[fd]), &mem)) < 0)
		return (-1);
	if (ret)
	{
		*line = mem;
		return (1);
	}
	if ((ret = get_line(fd, &line_tmp, &(tab[fd]))) < 0)
	{
		ft_memdel((void **)&mem);
		return (-1);
	}
	*line = ft_strjoin(mem, line_tmp);
	ft_strdel(&line_tmp);
	ft_strdel(&mem);
	if (!ret)
		return (0);
	return (1);
}
