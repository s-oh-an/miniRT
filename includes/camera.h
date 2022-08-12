#ifndef CAMERA_H
# define CAMERA_H

#include "scene.h"

void	set_camera_axis(t_camera *camera);
t_vec3	translate(t_vec3 *world, t_camera *camera);

#endif
