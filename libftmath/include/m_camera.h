/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_camera.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 00:31:35 by                   #+#    #+#             */
/*   Updated: 2017/05/04 15:10:14 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_CAMERA_H
# define M_CAMERA_H

# include <math.h>

# define GLOBAL_WIDTH 640.0
# define GLOBAL_HEIGHT 480.0
# define GLOBAL_FOV 60.0
# define GLOBAL_RATIO (GLOBAL_WIDTH / GLOBAL_HEIGHT)
# define GLOBAL_NEAR 1.0
# define GLOBAL_FAR 100.0
# define GLOBAL_XCAM 15.0
# define GLOBAL_YCAM 15.0
# define GLOBAL_ZCAM 80.0
# define GLOBAL_YROT M_PI

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
t_triangle	*m_camera_watch_triangle(t_camera *cam, t_triangle *world_tri);
t_mesh		*m_camera_watch_mesh(t_camera *cam, t_mesh *world_mesh);

#endif
