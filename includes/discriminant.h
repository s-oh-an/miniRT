#ifndef DISCRIMINANT_H
# define DISCRIMINANT_H

# include "scene.h"
# include "ray.h"

int	is_ray_hit_sphere(t_sphere *sphere, t_ray *ray, t_coordinate e);
int	is_ray_hit_plane(t_plane *plane, t_ray *ray, t_coordinate e);
int	is_ray_hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_coordinate e);

#endif
