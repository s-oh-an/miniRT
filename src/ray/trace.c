#include "../../includes/ray.h"
#include "../../includes/discriminant.h"
#include "../../includes/utils.h"
#include "../../includes/vector.h"
#include "../../includes/ambient.h"

#include <stdio.h>

t_ray	init_ray(float x, float y, float z)
{
	t_ray	ray;
	t_vec	vec;

	vec = vec3(x, y, z);
	ray.vec = vunit(vec);
	ray.hit.t = 0;
	ray.hit.min = 0;
	ray.hit.ray_hit = 0;
	return (ray);
}

int	is_ray_hit_object(t_object_list *obs, t_ray *ray, t_color *color)
{
	t_object		*obj;
	t_object_list	*cur;
	// int			hit;

	// hit = 0;
	cur = obs;
	while (cur)
	{
		obj = cur->content;
		if (obj->type == T_SPHERE)
		{
			if (is_ray_hit_sphere((t_sphere *)obj->property, ray))
			*color = ((t_sphere *)obj->property)->color; //(color변수를 hit구조체 안으로 넣어도 괜찮을 지  물어보기 )
				// hit++;
		}
		else if (obj->type == T_PLANE)
		{
			if (is_ray_hit_plane((t_plane *)obj->property, ray))
			*color = ((t_plane *)obj->property)->color;
				// hit++;
		}	
		else if (obj->type == T_CYLINDER)
		{
			if (is_ray_hit_cylinder((t_cylinder *)obj->property, ray))
			(*color) = ((t_cylinder *)obj->property)->color;
				// hit++;
		}
		else
		{
			// 없는 물체 타입에 대한 에러 -> 근데 파싱에서 이런 경우를 다 걸러서 굳이 필요할까 싶음.
		}
		cur = cur->next;
	}
	return (ray->hit.ray_hit);
}

// int	is_ray_hit_object(t_object_list *obs, t_ray *ray, t_color *color)
// {
// 	t_object	*obj;
// 	int			hit;

// 	hit = 0;
// 	while (obs)
// 	{
// 		obj = obs->content;
// 		if (obj->type == T_SPHERE)
// 		{
// 			*color = ((t_sphere *)obj->property)->color; //(color변수를 hit구조체 안으로 넣어도 괜찮을 지  물어보기 )
// 			if (is_ray_hit_sphere((t_sphere *)obj->property, ray))
// 				hit++;
// 		}
// 		else if (obj->type == T_PLANE)
// 		{
// 			*color = ((t_plane *)obj->property)->color;
// 			if (is_ray_hit_plane((t_plane *)obj->property, ray))
// 				hit++;
// 		}	
// 		else if (obj->type == T_CYLINDER)
// 		{
// 			(*color) = ((t_cylinder *)obj->property)->color;
// 			if (is_ray_hit_cylinder((t_cylinder *)obj->property, ray))
// 				hit++;
// 		}
// 		else
// 		{
// 			// 없는 물체 타입에 대한 에러 -> 근데 파싱에서 이런 경우를 다 걸러서 굳이 필요할까 싶음.
// 		}
// 		obs = obs->next;
// 	}
// 	return (hit);
// }

int	is_object_visible(t_scene *s, float u, float v, t_color *color)
{
	t_ray	ray;
	float	hori_r;
	float	vert_r;

	vert_r = (0.5 / (float)s->camera.win.width) + u;
	vert_r *= s->camera.viewport_w;
	hori_r = (0.5 / (float)s->camera.win.height) + v;
	hori_r *= s->camera.viewport_h;

	//ray.vec = vunit(vplus(vplus(s->camera.left_bottom, vmulti_f(s->camera.ver, vert_r)), vmulti_f(s->camera.hor, hori_r)));
	ray = init_ray(s->camera.left_bottom.x + vert_r , s->camera.left_bottom.y + hori_r, s->camera.left_bottom.z);
	return (is_ray_hit_object(s->objects, &ray, color));
}

void	shoot_ray(t_mlx *m, t_scene *scene)
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
		while (i < scene->camera.win.width - 1)
		{
			// 이 픽셀에 해당하는 뷰포트의 픽셀을 지나가는 광선이 물체와 만나는지 확인
			u = (float)i / (float)(scene->camera.win.width);
			v = (float)j / (float)(scene->camera.win.height);
			if (is_object_visible(scene, u, v, &color))
				// my_mlx_pixel_put(&(m->data), i, scene->camera.win.height - 1 - j, 0x0000ff00);
				my_mlx_pixel_put(&(m->data), i, scene->camera.win.height - 1 - j, to_rgb(vmulti_f(get_pixel_ambient_color(scene, color), 255)));
			i++;
		}
		j++;
	}
	// printf("type : %d\n", scene->objects->content->type);
}

// void	trace_objects(t_mlx *m, t_scene *scene)
// {
// 	t_object		*obj;
// 	t_object_list	*cur;

// 	cur = scene->objects;
// 	while (cur)
// 	{
// 		obj = cur->content;
// 		shoot_ray(m, scene, obj);
// 		cur = cur->next;
// 	}
// 	m->scene = *scene;
// }
