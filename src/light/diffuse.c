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
	// if (ray->hit.in_object) // 빛이 물체 안에 있는지 밖에 있는지 판별 필요 
	// 	ray->hit.hit_normal = vmulti_f(ray->hit.hit_normal, -1);
	
	
	
	diffuse = vmulti_f(diffuse, vdot(ray->hit.hit_normal, l) * -scene->light.ratio);
	return (vmax(vec3(0, 0, 0), diffuse));
}


