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
	ray.direction = vunit(vec);
	ray.hit.t = 100000;
	ray.hit.ray_hit = 0;
	ray.hit.in_object = 0;
	return (ray);
}

int	is_ray_hit_object(t_object_list *obs, t_ray *ray)
{
	t_object		*obj;
	t_object_list	*cur;

	cur = obs;
	while (cur)
	{
		obj = cur->content;
		if (obj->type == T_SPHERE)
			is_ray_hit_sphere((t_sphere *)obj->property, ray);
		else if (obj->type == T_PLANE)
			is_ray_hit_plane((t_plane *)obj->property, ray);
		else if (obj->type == T_CYLINDER)
		{
			is_ray_hit_cylinder((t_cylinder *)obj->property, ray);
			is_ray_hit_cylinder_topbottom((t_cylinder *)obj->property, ray);
		}
		cur = cur->next;
	}
	return (ray->hit.ray_hit);
}

int	is_object_visible(t_scene *s, double u, double v, t_ray *ray)
{
	double	hori_r;
	double	vert_r;
	vert_r = (0.5 / (double)s->camera.win.width) + u;
	vert_r *= s->camera.viewport_w;
	hori_r = (0.5 / (double)s->camera.win.height) + v;
	hori_r *= s->camera.viewport_h;

	*ray = init_ray(s->camera.left_bottom.x + vert_r , s->camera.left_bottom.y + hori_r, s->camera.left_bottom.z);
	ray->origin = vec3(0, 0, 0);
	return (is_ray_hit_object(s->objects, ray));
}

int	is_light(t_light light, t_ray ray)
{
	int		light_in_obj;
	t_vec	light_vec;
	t_vec	obj_nvec;
	// t_vec	pp;

	// pp = vmulti_f(ray.hit.normal);
	// //printf("norm: %f %f z:%f\n", ray.hit.normal.x, ray.hit.normal.y, ray.hit.normal.z);

	// light_vec = vunit(vminus(vplus(ray.hit.point, pp), light.coordinate)); // LP
	light_vec = vunit(vminus(ray.hit.point, light.coordinate)); // LP


	if (ray.hit.in_object)
		obj_nvec = vmulti_f(ray.hit.normal, -1);
	else
		obj_nvec = ray.hit.normal;

	if (vdot(obj_nvec, light_vec) < E)
		light_in_obj = 0;
	else
		light_in_obj = 1;
	
	if (light_in_obj != ray.hit.in_object)
		return (0);
	else
		return (1);
}

void	shoot_ray(t_mlx *m, t_scene *scene)
{
	// double	u;
	// double	v;
	int		i;
	int		j;

	t_ray	ray;

	j = -1;
	while (++j < scene->camera.win.height - 1)
	{
		i = -1;
		while (++i < scene->camera.win.width - 1)
		{
			// u = (double)i / (double)(scene->camera.win.width);
			// v = (double)j / (double)(scene->camera.win.height);
			if (is_object_visible(scene, (double)i / (double)(scene->camera.win.width), (double)j / (double)(scene->camera.win.height), &ray))
			{
				if (is_light(scene->light, ray) && !is_pixel_in_shadow(scene->objects, &scene->light, &ray))
				{
					my_mlx_pixel_put(&(m->data), i, scene->camera.win.height - 1 - j, to_rgb(vmulti_f(vmin(vec3(1, 1, 1), vplus(get_pixel_ambient_color(scene, ray.hit.color), get_pixel_diffuse_color(scene, &ray))), 255)));
				}
				else
				{
					my_mlx_pixel_put(&(m->data), i, scene->camera.win.height - 1 - j, to_rgb(vmulti_f(vmin(vec3(1, 1, 1), get_pixel_ambient_color(scene, ray.hit.color)), 255)));
					//my_mlx_pixel_put(&m->data, i, scene->camera.win.height - 1 - j, to_rgb(vec3(0, 0, 0)));
				}
			}
		}
	}
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
