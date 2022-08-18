
#ifndef HIT_H
# define HIT_H

# include "scene.h"
# include "ray.h"

int	update_hit(t_ray *ray, t_ray new);

t_ray	make_hit_sphere(t_sphere *sphere, float *t, t_ray *ray);
t_ray	make_hit_plane(t_plane *plane, float t, t_ray *ray);
t_ray	make_hit_cylinder(t_cylinder *cylinder, float *t, t_ray *ray);



#endif







