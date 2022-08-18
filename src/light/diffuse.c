#include "../../includes/scene.h"
#include "../../includes/ray.h"
#include "../../includes/vector.h"
#include "../../includes/light.h"

t_color	get_pixel_diffuse_color(t_scene *scene, t_ray *ray)
{
	t_color	diffuse;
	t_vec	l;

	diffuse = vec3(1, 1, 1);
	l = vunit(vminus(ray->hit.hit_point, scene->light.coordinate));
	diffuse = vmulti_f(diffuse, vdot(ray->hit.hit_normal, l) * -scene->light.ratio);
	return (vmax(vec3(0, 0, 0), diffuse));
}


