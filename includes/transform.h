#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "scene.h"

void	world_to_camera(t_scene *scene);
t_vec	rotate(t_vec *world, t_camera *camera);
t_vec	translate(t_vec *world, t_camera *camera);

#endif
