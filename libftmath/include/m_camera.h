/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_camera.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 00:31:35 by                   #+#    #+#             */
/*   Updated: 2017/05/04 02:21:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_CAMERA_H
# define M_CAMERA_H

# define M_CAMERASTR "Camera(\n"\
						"\tfov = %.2f, width = %.2f, height = %.2f,\n"\
						"\tratio = %.2f\tnear = %.2f, far = %.2f,\n"\
						"Position = %s,\n"\
						"T translate = %s,\n"\
						"T rotate = %s,\n"\
						"View = %s,\n"\
						"Project = %s\n)"

# include "m_matrix.h"

typedef struct s_camera	t_camera;

int						g_s_camera_verbose;

struct					s_camera
{
	double				fov;
	double				width;
	double				height;
	double				ratio;
	double				near;
	double				far;
	t_vertex			*position;
	t_matrix			*t_translate;
	t_matrix			*t_rotate;
	t_matrix			*view;
	t_matrix			*project;
};

t_camera	*m_cam(void);
t_camera	*m_camera(t_vertex *position, t_matrix *rotation, double *conf);
void		m_camera_del(t_camera **cam);
char		*m_camera_str(t_camera *cam, char *buf, size_t n);
t_vertex	*m_camera_watch_vertex(t_camera *cam, t_vertex *vtx);

#endif
