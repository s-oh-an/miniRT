#include "../../includes/shadow.h"
#include "../../includes/vector.h"
#include <stdio.h>
#include <math.h>

int	is_pixel_in_shadow(t_object_list *objs, t_light *light, t_ray *ray)
{
	t_ray	tmp;
	t_vec	pl;
	double	len;
	t_vec	pp;

	pp = vmulti_f(ray->hit.normal, E);
	pl = vminus(light->coordinate, vplus(ray->hit.point, pp));
	len = vlen(pl);
	pl = vunit(pl);
	if (vdot(ray->hit.normal, pl) < E)
		return (0);
	tmp = init_ray(pl.x, pl.y, pl.z);
	tmp.hit.point = vplus(ray->hit.point, pp);
	tmp.origin = tmp.hit.point;
	if (is_ray_hit_object(objs, &tmp))
	{	
		if (tmp.hit.t > -E && tmp.hit.t < len - E)
			return (1);
	}
	return (0);
}
