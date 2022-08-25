#include "../../includes/scene.h"
#include "../../includes/ray.h"
#include "../../includes/vector.h"
#include "../../includes/light.h"

t_color	get_pixel_diffuse_color(t_scene *scene, t_ray *ray)
{
	t_color	diffuse;
	t_color	color;
	t_vec	pl;

	diffuse = vec3(1, 1, 1);
	pl = vunit(vminus(scene->light.coordinate, ray->hit.point));
	diffuse = vmulti_f(diffuse, vdot(ray->hit.normal, pl) * scene->light.ratio);
	diffuse = vmax(vec3(0, 0, 0), diffuse);
	color = ray->hit.color;
	color.x /= 255;
	color.y /= 255;
	color.z /= 255;
	diffuse = vmulti(color, diffuse);
	return (vmin(vec3(1, 1, 1), diffuse));
}
