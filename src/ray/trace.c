#include "../../includes/ray.h"
#include "../../includes/discriminant.h"
#include "../../includes/utils.h"
#include "../../includes/vector.h"
#include "../../includes/ambient.h"

t_ray	init_ray(float x, float y, float z)
{
	t_ray	ray;
	t_vec	vec;

	vec = vec3(x, y, z);
	ray.vec = vunit(vec);
	return (ray);
}

int	is_ray_hit_object(t_object *object, t_ray *ray, t_color *color)
{
	if (object->type == T_SPHERE)
	{
		*color = ((t_sphere *)object->property)->color;
		return (is_ray_hit_sphere((t_sphere *)object->property, ray));
	}
	else if (object->type == T_PLANE)
	{
		*color = ((t_plane *)object->property)->color;
		return (is_ray_hit_plane((t_plane *)object->property, ray));
	}	
	else if (object->type == T_CYLINDER)
	{
		(*color) = ((t_cylinder *)object->property)->color;
		return (is_ray_hit_cylinder((t_cylinder *)object->property, ray));
	}
	else
		return (0);
}

int	is_object_visible(t_camera *cam, float u, float v, t_object *object, t_color *color)
{
	t_ray	ray;
	float	hori_r;
	float	vert_r;

	vert_r = (0.5 / (float)cam->win.width) + u;
	hori_r = (0.5 / (float)cam->win.height) + v;

	ray.vec = vunit(vplus(vplus(cam->left_bottom,
				vmulti_f(cam->ver, vert_r)), vmulti_f(cam->hor, hori_r)));
	return (is_ray_hit_object(object, &ray, color));
}

void	shoot_ray(t_mlx *m, t_scene *scene, t_object *object)
{
	float	u;
	float	v;
	int		i;
	int		j;
	t_color	color;

	j = 0;
	while (j < scene->camera.win.height - 1)
	{
		i = 0;
		while (i < scene->camera.win.width)
		{
			// 이 픽셀에 해당하는 뷰포트의 픽셀을 지나가는 광선이 물체와 만나는지 확인
			u = (2.0  * scene->camera.win.ratio) * (float)i / (float)(scene->camera.win.width);
			v = 2.0 * (float)j / (float)(scene->camera.win.height);
			if (is_object_visible(&scene->camera, u, v, object, &color))
				my_mlx_pixel_put(&(m->data), i, scene->camera.win.height - 1 - j, to_rgb(vmulti_f(get_pixel_ambient_color(scene, color), 255)));
			i++;
		}
		j++;
	}
}

void	trace_objects(t_mlx *m, t_scene *scene)
{
	t_object		*obj;
	t_object_list	*cur;

	cur = scene->objects;
	while (cur)
	{
		obj = cur->content;
		shoot_ray(m, scene, obj);
		cur = cur->next;
	}
	m->scene = *scene;
}
