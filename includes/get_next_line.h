/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <sbenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 13:37:32 by sbenning          #+#    #+#             */
/*   Updated: 2015/11/30 18:05:02 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**		man 2 getrlimit
**		#include sys/ressource.h
**		And use :
**		int		getrlimit(int ressource, struct rlimit *rlp)
**		to get the RLIMIT_NOFILE (current, not max!) on this system!
*/

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <fcntl.h>

# define BUFF_S 32
# define MY_RLIMIT_NOFILE 256

int		get_next_line(int fd, char **line);

#endif
