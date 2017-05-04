/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mesh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:26:09 by                   #+#    #+#             */
/*   Updated: 2017/05/04 15:46:41 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_mesh.h"

t_mesh		*m_mesh_newm(t_triangle *tri)
{
	char	*buf;
	t_mesh	*ntri;

	if (!(ntri = ft_memalloc(sizeof(t_mesh))))
		return (NULL);
	if (!(ntri->tri = m_triangle(tri->a, tri->b, tri->c)))
		return (NULL);
	if (g_s_mesh_verbose == 1 && ntri && (buf = m_mesh_str(ntri)))
	{
		ft_printf("New %s ;\n", buf);
		free(buf);
	}
	return (ntri);
}

t_mesh		*m_mesh_new(t_triangle *tri)
{
	char	*buf;
	t_mesh	*ntri;

	if (!(ntri = ft_memalloc(sizeof(t_mesh))))
		return (NULL);
	ntri->tri = tri;
	if (g_s_mesh_verbose == 1 && ntri && (buf = m_mesh_str(ntri)))
	{
		ft_printf("New %s ;\n", buf);
		free(buf);
	}
	return (ntri);
}

void		m_mesh_add(t_mesh **mesh, t_mesh *ntri)
{
	t_mesh	*drive;

	drive = *mesh;
	if (!drive)
	{
		*mesh = ntri;
		return ;
	}
	while (drive->next)
		drive = drive->next;
	drive->next = ntri;
}

static void	ntri_del(t_mesh **ntri)
{
	if ((*ntri)->tri)
		m_triangle_del(&(*ntri)->tri);
	free(*ntri);
	*ntri = NULL;
}

void		m_mesh_del(t_mesh **mesh)
{
	t_mesh	*next;
	char	*buf;

	if (g_s_mesh_verbose == 1 && *mesh && (buf = m_mesh_str(*mesh)))
	{
		ft_printf("Del %s ;\n", buf);
		free(buf);
	}
	while (*mesh)
	{
		next = (*mesh)->next;
		ntri_del(mesh);
		*mesh = next;
	}
}

static void	del_str(void *c, size_t n)
{
	free(c);
	(void)n;
}

char		*m_mesh_str(t_mesh *mesh)
{
	t_list	*meshstr;
	t_list	*ntristr;
	char	buf[1024 + 1];
	int		i;
	size_t	size;
	char	*tmp;
	char	*str;

	i = 0;
	meshstr = NULL;
	size = 0;
	while (mesh)
	{
		m_triangle_str(mesh->tri, buf, 1024);
		size += ft_strlen(buf);
		if (!(ntristr = ft_lstnew(buf, size + 1)))
			return (NULL);
		ft_lstadd_back(&meshstr, ntristr);
		mesh = mesh->next;
		++i;
	}
	if (!(str = ft_strnew(size + 1 + 2048)))
		return (NULL);
	if (!(tmp = ft_strnew(size + 1 + 2048)))
		return (NULL);
	ft_sprintf(str, "Mesh( %d triangles:\n\t", i);
	ft_strcpy(tmp, str);
	ntristr = meshstr;
	while (ntristr)
	{
		ft_sprintf(str, "%s%s,\n\t", tmp, ntristr->content);
		ft_strcpy(tmp, str);
		ntristr = ntristr->next;
	}
	ft_sprintf(str, "%s)", tmp);
	ft_lstdel(&meshstr, del_str);
	free(tmp);
	return (str);
}
