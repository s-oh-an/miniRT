#include "../../includes/light.h"
#include "../../includes/vector.h"
#include "../../includes/ray.h"
#include <math.h>

t_color	get_pixel_specular_color(t_scene *scene, t_ray *ray)
{
	t_color	specular;
	float	specular_ratio;
	float	alpha;
	t_vec	r;
	t_vec	v;
	t_vec	l;

	specular = vec3(1, 1, 1);
	specular_ratio = 0.6;
	alpha = 50;
	l = vunit(vminus(ray->hit.hit_point, scene->light.coordinate));
	r = vunit(vminus(l, vmulti_f(vmulti_f(ray->hit.hit_normal, vdot(l, ray->hit.hit_normal)), 2)));
	v = vunit(vmulti_f(ray->hit.hit_point, -1));
	specular = vmulti_f(specular, specular_ratio);
	specular = vmulti_f(specular, pow(vdot(r, v), alpha));
	return (specular);
}
