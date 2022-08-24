#include "../../includes/shadow.h"
#include "../../includes/vector.h"
#include <stdio.h>
#include <math.h>

int	is_pixel_in_shadow(t_object_list *objs, t_light *light, t_ray *ray)
{
	//double	pl;
	t_ray	tmp;
	t_vec	pl;
	double	len;
	t_vec	pp;

	//tmp = *ray;
	pp = vmulti_f(ray->hit.hit_normal, E);

	//printf("norm: %f %f z:%f\n", ray->hit.hit_normal.x, ray->hit.hit_normal.y, ray->hit.hit_normal.z);

	// pl = vminus(light->coordinate, ray->hit.hit_point);
	
	pl = vminus(light->coordinate, vplus(ray->hit.hit_point, pp));
	len = vlen(pl);
	pl = vunit(pl);
	// printf("normal x: %f, y: %f, z: %f\n", ray->hit.hit_normal.x, ray->hit.hit_normal.y, ray->hit.hit_normal.z);
	if (vdot(ray->hit.hit_normal, pl) < E)
	{
		return (0);
	}
	tmp = init_ray(pl.x, pl.y, pl.z);
	tmp.hit.hit_point = vplus(ray->hit.hit_point, pp);
	if (is_ray_hit_object(objs, &tmp, tmp.hit.hit_point))
	{	
		// if (tmp.hit.t > -E && fabs(tmp.hit.t - len) < E)
		if (tmp.hit.t > -E && tmp.hit.t < len - E)
		{
//printf("in: %d t: %f x: %f y: %f z: %f\n", ray->hit.in_object, tmp.hit.t, ray->hit.hit_normal.x, ray->hit.hit_normal.y, ray->hit.hit_normal.z);			
			return (1);
		}
	}
	return (0);
}
