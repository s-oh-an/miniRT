#ifndef LIGHT_H
# define LIGHT_H

# include "scene.h"
# include "ray.h"

t_color	get_pixel_ambient_color(t_scene *scene, t_color color);
t_color	get_pixel_diffuse_color(t_scene *scene, t_ray *ray);

#endif
