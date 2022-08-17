#include "../../includes/scene.h"
#include "../../includes/vector.h"

t_color	get_pixel_ambient_color(t_scene *scene, t_color color)
{
	t_ambient	ambient;
	t_vec		light;

	ambient = scene->ambient;
	ambient.color.x /= 255;
	ambient.color.y /= 255;
	ambient.color.z /= 255;
	color.x /= 255;
	color.y /= 255;
	color.z /= 255;
	light = vmulti_f(ambient.color, ambient.ratio);
	return (vmin(vec3(1, 1, 1), vmulti(light, color)));
}
