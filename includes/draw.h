#ifndef DRAW_H
# define DRAW_H

# include "scene.h"
# include "ray.h"
# include "../lib/mlx/mlx.h" //
// # include "discriminant.h"



int	is_ray_hit_sphere(t_sphere *sphere, t_ray *ray);
int	is_ray_hit_plane(t_plane *plane, t_ray *ray);
int	is_ray_hit_cylinder(t_cylinder *cylinder, t_ray *ray);

#endif
