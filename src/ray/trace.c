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
		}
		else if (obj->type == T_PLANE)
		{
			is_ray_hit_plane((t_plane *)obj->property, ray, e);
		}	
		else if (obj->type == T_CYLINDER)
		{
			is_ray_hit_cylinder((t_cylinder *)obj->property, ray, e);
		}
		else
		{
			// 없는 물체 타입에 대한 에러 -> 근데 파싱에서 이런 경우를 다 걸러서 굳이 필요할까 싶음.
		}
		cur = cur->next;
	}
	return (ray->hit.ray_hit);
}

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

int	is_light(t_light light, t_ray ray)
{
	int		light_in_obj;
	t_vec	light_vec;
	t_vec	obj_nvec;

	light_vec = vunit(vminus(ray.hit.hit_point, light.coordinate)); // LP

	if (ray.hit.in_object) // 빛이 물체 안에 있으면 바꿨던 방향벡터를 다시 돌려놓고 LP와 방향비교 
		obj_nvec = vmulti_f(ray.hit.hit_normal, -1);
	else
		obj_nvec = ray.hit.hit_normal;

	if (vdot(obj_nvec, light_vec) < 0)
		light_in_obj = 0; // 물체 밖에 있다 
	else
		light_in_obj = 1;
	
	if (light_in_obj != ray.hit.in_object)
	// 이전 버전으로 했을떄 (in_object조건 추가했을 때) botton2.rt에서 빨간 구외의 물체 안에 빛을 넣으면 빛이 새서 이렇게 바꿨어요!! - san
		return (0);
	else
		return (1);
}

// int	is_light(t_light light, t_ray ray)
// {
// 	int		light_in_obj;
// 	t_vec	light_vec;
// 	t_vec	obj_nvec;
// 	t_vec	cp;

// 	cp = ray.hit.hit_point;
// 	light_vec = vunit(vminus(light.coordinate, ray.hit.hit_point)); // LP
// 	//if (ray.hit.in_object) // 빛이 물체 안에 있는지 밖에 있는지 판별 필요 
// 	//	obj_nvec = vmulti_f(ray.hit.hit_normal, -1);
// 	//else
// 	obj_nvec = ray.hit.hit_normal;
// 	if (vdot(obj_nvec, light_vec) < 0)
// 		light_in_obj = 0;
// 	else
// 		light_in_obj = 1;
	
// 	if (ray.hit.in_object && light_in_obj != ray.hit.in_object)
// 	// if (light_in_obj != ray.hit.in_object)
// 		return (0);
// 	//else if (ray.hit.in_object && vdot(cp, light_vec) < 0)
// 	//	return (0);
// 	else
// 		return (1);
// }

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
			u = (double)i / (double)(scene->camera.win.width);
			v = (double)j / (double)(scene->camera.win.height);
			if (is_object_visible(scene, u, v, &ray))
			{
				if (is_light(scene->light, ray) && !is_pixel_in_shadow(scene->objects, &scene->light, &ray))
				{
					my_mlx_pixel_put(&(m->data), i, scene->camera.win.height - 1 - j, to_rgb(vmulti_f(vmin(vec3(1, 1, 1), vplus(get_pixel_ambient_color(scene, ray.hit.hit_color), get_pixel_diffuse_color(scene, &ray))), 255)));
				}
				else
				{
					my_mlx_pixel_put(&(m->data), i, scene->camera.win.height - 1 - j, to_rgb(vmulti_f(vmin(vec3(1, 1, 1), get_pixel_ambient_color(scene, ray.hit.hit_color)), 255)));
					//my_mlx_pixel_put(&m->data, i, scene->camera.win.height - 1 - j, to_rgb(vec3(0, 0, 0)));
				}
			}
			i++;
		}
		j++;
	}
	// printf("type : %d\n", scene->objects->content->type);
}


// void	shoot_ray(t_mlx *m, t_scene *scene)
// {
// 	double	u;
// 	double	v;
// 	int		i;
// 	int		j;

// 	t_ray	ray;

// 	j = 0;
// 	while (j < scene->camera.win.height - 1)
// 	{
// 		i = 0;
// 		while (i < scene->camera.win.width - 1)
// 		{
// 			u = (double)i / (double)(scene->camera.win.width);
// 			v = (double)j / (double)(scene->camera.win.height);
// 			if (is_object_visible(scene, u, v, &ray))
// 				my_mlx_pixel_put(&(m->data), i, scene->camera.win.height - 1 - j, to_rgb(vmulti_f(vmin(vec3(1, 1, 1), vplus(get_pixel_ambient_color(scene, ray.hit.hit_color), get_pixel_diffuse_color(scene, &ray))), 255)));
// 			i++;
// 		}
// 		j++;
// 	}
// 	// printf("type : %d\n", scene->objects->content->type);
// }

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
