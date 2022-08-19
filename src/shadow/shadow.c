#include "../../includes/shadow.h"
#include "../../includes/vector.h"
#include <stdio.h>

int	is_pixel_in_shadow(t_object_list *objs, t_light *light, t_ray *ray)
{
	//double	pl;
	t_ray	tmp;
	t_vec	pl;
	double	len;
	t_vec	pp;

	//tmp = *ray;
	pp = vmulti_f(ray->hit.hit_normal, 0.000001);

	//pl = vminus(light->coordinate, ray->hit.hit_point);
	pl = vminus(light->coordinate, vplus(ray->hit.hit_point, pp));
	len = vlen(pl);
	pl = vunit(pl);
	if (vdot(ray->hit.hit_normal, pl) < 0)
		return (0);
	tmp = init_ray(pl.x, pl.y, pl.z);
	tmp.hit.hit_point = vplus(ray->hit.hit_point, pp);
	if (is_ray_hit_object(objs, &tmp, tmp.hit.hit_point))
	{	
		if (tmp.hit.t > 0 && tmp.hit.t < len)
			return (1);
	}
	return (0);
}
