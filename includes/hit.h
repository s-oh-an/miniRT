
#ifndef HIT_H
# define HIT_H

# include "scene.h"
# include "ray.h"

int	update_hit(t_ray *old, t_hit new);

t_hit	make_hit_sphere(t_sphere *sphere, double *t, t_ray *ray);
t_hit	make_hit_plane(t_plane *plane, double t, t_ray *ray);
t_hit	make_hit_cylinder(t_cylinder *cylinder, double t, t_ray *ray);
t_hit	make_hit_cylinder_topbottom(t_cylinder *cylinder, double t, t_ray *ray);



#endif







