#ifndef SHADOW_H
# define SHADOW_H

# include "ray.h"

int	is_pixel_in_shadow(t_object_list *objs, t_light *light, t_ray *ray);

#endif
