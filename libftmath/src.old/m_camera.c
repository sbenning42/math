/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 02:15:35 by                   #+#    #+#             */
/*   Updated: 2017/05/03 13:38:13 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_camera	*m_camera_init_ap\
				(t_camera *self, t_vertex *position, \
				 t_matrix *rotation, va_list *ap)
{
	char		*verb;

	self->self = self;
	self->position = position;
	self->rotation = rotation;
	self->width = va_arg(*ap, double);
	self->height = va_arg(*ap, double);
	self->ratio = self->width / self->height;
	self->fov = va_arg(*ap, double);
	self->near = va_arg(*ap, double);
	self->far = va_arg(*ap, double);
	if (!(self->deplacement = m_vector_new(self->position, g_m_vtx_orig)))
		return (NULL);
	if (!(self->i_deplacement = m_vector_opposite(self->deplacement)))
		return (NULL);
	if (!(self->translation = m_matrix_new(M_TRANS_MTX, self->deplacement)))
		return (NULL);
	if (!(self->i_translation = m_matrix_new(M_TRANS_MTX, self->i_deplacement)))
		return (NULL);
	if (!(self->i_rotation = m_matrix_inv(self->rotation)))
		return (NULL);
	if (!(self->transform = m_matrix_mul(self->translation, self->rotation)))
		return (NULL);
	if (!(self->view = m_matrix_mul(self->i_rotation, self->i_translation)))
		return (NULL);
	if (!(self->projection = m_matrix_new(\
					M_PROJ_MTX, self->fov, self->ratio, self->near, self->far)))
		return (NULL);
	if (!(self->render = m_matrix_mul(self->view, self->projection)))
		return (NULL);
	if (g_s_camera_verbose && (verb = m_camera2str(self)))
	{
		ft_printf("Init %s ;\n", verb);
		free(verb);
	}
	return (self);
}

t_camera	*m_camera_init\
				(t_camera *self, t_vertex *position, \
				 t_matrix *rotation, ...)
{
	va_list		ap;
	
	va_start(ap, rotation);
	m_camera_init_ap(self, position, rotation, &ap);
	va_end(ap);
	return (self);
}

t_camera	*m_camera_new(t_vertex *position, t_matrix *rotation, ...)
{
	t_camera	*camera;
	va_list		ap;

	va_start(ap, rotation);
	if (!(camera = ft_memalloc(sizeof(t_camera))))
		return (NULL);
	m_camera_init_ap(camera, position, rotation, &ap);
	va_end(ap);
	return (camera);
}

t_camera	*m_camera_clear(t_camera *self)
{
	char		*verb;

	if (g_s_camera_verbose && (verb = m_camera2str(self)))
	{
		ft_printf("Clear %s ;\n", verb);
		free(verb);
	}
	m_vector_del(&self->deplacement);
	m_vector_del(&self->i_deplacement);
	m_matrix_del(&self->translation);
	m_matrix_del(&self->i_translation);
	m_matrix_del(&self->i_rotation);
	m_matrix_del(&self->view);
	m_matrix_del(&self->projection);
	m_matrix_del(&self->render);
	ft_bzero(self, sizeof(t_camera));
	self->self = self;
	return (self);
}

void		m_camera_del(t_camera **camera)
{
	m_camera_clear(*camera);
	free(*camera);
	*camera = NULL;
}

#include <stdio.h>

char		*m_camera2str(t_camera *self)
{
	char	buf[4096];
	char	*tostr[11];
	int		i;

	if (!(tostr[0] = m_vertex2str(self->position)) \
		|| !(tostr[1] = m_vector2str(self->deplacement)) \
		|| !(tostr[2] = m_vector2str(self->i_deplacement)) \
		|| !(tostr[3] = m_matrix2str(self->translation)) \
		|| !(tostr[4] = m_matrix2str(self->i_translation)) \
		|| !(tostr[5] = m_matrix2str(self->rotation)) \
		|| !(tostr[6] = m_matrix2str(self->i_rotation)) \
		|| !(tostr[7] = m_matrix2str(self->transform)) \
		|| !(tostr[8] = m_matrix2str(self->view)) \
		|| !(tostr[9] = m_matrix2str(self->projection)) \
		|| !(tostr[10] = m_matrix2str(self->render)))
		return (NULL);
	snprintf(buf, 4096, M_MTX_STR, \
			tostr[0], tostr[1], tostr[2], tostr[3], tostr[4], tostr[5], \
			tostr[6], tostr[7], tostr[8], tostr[9], tostr[10], self->fov, \
			self->width, self->height, self->ratio, self->near, self->far);
	i = -1;
	while (++i < 11)
		free(tostr[i]);
	return (ft_strdup(buf));
}

t_vertex	*m_camera_watch(t_camera *self, t_vertex *world_vtx)
{
	return (m_matrix_apply(self->render, world_vtx));
}
