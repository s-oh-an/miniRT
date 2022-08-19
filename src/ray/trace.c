#include "../../includes/ray.h"
#include "../../includes/discriminant.h"
#include "../../includes/utils.h"
#include "../../includes/vector.h"
#include "../../includes/light.h"
#include "../../includes/shadow.h"

#include <stdio.h>

t_ray	init_ray(double x, double y, double z)
{
	t_ray	ray;
	t_vec	vec;

	vec = vec3(x, y, z);
	ray.vec = vunit(vec);
	ray.hit.t = 100000;
	ray.hit.min = 0;
	ray.hit.ray_hit = 0;
	return (ray);
}

// int	is_ray_hit_object(t_object_list *obs, t_ray *ray, t_color *color)
int	is_ray_hit_object(t_object_list *obs, t_ray *ray, t_coordinate e)
{
	t_object		*obj;
	t_object_list	*cur;

	cur = obs;
	while (cur)
	{
		obj = cur->content;
		if (obj->type == T_SPHERE)
		{
			is_ray_hit_sphere((t_sphere *)obj->property, ray, e);
			// if (is_ray_hit_sphere((t_sphere *)obj->property, ray))
			// *color = ((t_sphere *)obj->property)->color; //(color변수를 hit구조체 안으로 넣어도 괜찮을 지  물어보기 )
		}
		else if (obj->type == T_PLANE)
		{
			is_ray_hit_plane((t_plane *)obj->property, ray, e);
			// if (is_ray_hit_plane((t_plane *)obj->property, ray))
			// *color = ((t_plane *)obj->property)->color;
		}	
		else if (obj->type == T_CYLINDER)
		{
			is_ray_hit_cylinder((t_cylinder *)obj->property, ray, e);
			// if (is_ray_hit_cylinder((t_cylinder *)obj->property, ray))
			// (*color) = ((t_cylinder *)obj->property)->color;
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

int	is_object_visible(t_scene *s, double u, double v, t_ray *ray)
{
	// t_ray	ray;
	double	hori_r;
	double	vert_r;
	vert_r = (0.5 / (double)s->camera.win.width) + u;
	vert_r *= s->camera.viewport_w;
	hori_r = (0.5 / (double)s->camera.win.height) + v;
	hori_r *= s->camera.viewport_h;

	//ray.vec = vunit(vplus(vplus(s->camera.left_bottom, vmulti_f(s->camera.ver, vert_r)), vmulti_f(s->camera.hor, hori_r)));
	*ray = init_ray(s->camera.left_bottom.x + vert_r , s->camera.left_bottom.y + hori_r, s->camera.left_bottom.z);
	return (is_ray_hit_object(s->objects, ray, vec3(0, 0, 0)));
}

void	shoot_ray(t_mlx *m, t_scene *scene)
{
	double	u;
	double	v;
	int		i;
	int		j;

	t_ray	ray;

	j = 0;
	while (j < scene->camera.win.height - 1)
	{
		i = 0;
		while (i < scene->camera.win.width - 1)
		{
			// 이 픽셀에 해당하는 뷰포트의 픽셀을 지나가는 광선이 물체와 만나는지 확인
			u = (double)i / (double)(scene->camera.win.width);
			v = (double)j / (double)(scene->camera.win.height);
			if (is_object_visible(scene, u, v, &ray))
			{	
				if (!is_pixel_in_shadow(scene->objects, &scene->light, &ray))
					my_mlx_pixel_put(&(m->data), i, scene->camera.win.height - 1 - j, to_rgb(vmulti_f(vmin(vec3(1, 1, 1), vplus(get_pixel_ambient_color(scene, ray.hit.hit_color), get_pixel_diffuse_color(scene, &ray))), 255)));
				else
					my_mlx_pixel_put(&m->data, i, scene->camera.win.height - 1 - j, to_rgb(vec3(0, 0, 0)));
			}
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
