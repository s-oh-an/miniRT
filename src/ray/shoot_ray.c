/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:28:18 by san               #+#    #+#             */
/*   Updated: 2022/08/25 15:28:20 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray.h"
#include "../../includes/discriminant.h"
#include "../../includes/utils.h"
#include "../../includes/vector.h"
#include "../../includes/light.h"
#include "../../includes/shadow.h"

t_ray	ray(t_vec direction, t_coordinate origin)
{
	t_ray	ray;

	ray.direction = vunit(direction);
	ray.origin = origin;
	ray.hit.t = 100000;
	ray.hit.in_object = 0;
	return (ray);
}

int	is_ray_hit_object(t_object_list *obs, t_ray *ray)
{
	t_object		*obj;
	t_object_list	*cur;
	int				res;

	cur = obs;
	res = 0;
	while (cur)
	{
		obj = cur->content;
		if (obj->type == T_SPHERE)
			res |= is_ray_hit_sphere((t_sphere *)obj->property, ray);
		else if (obj->type == T_PLANE)
			res |= is_ray_hit_plane((t_plane *)obj->property, ray);
		else if (obj->type == T_CYLINDER)
		{
			res |= is_ray_hit_cylinder((t_cylinder *)obj->property, ray);
			res |= is_ray_hit_cylinder_cover((t_cylinder *)obj->property, ray);
		}
		cur = cur->next;
	}
	return (res);
}

int	is_pixel(t_scene *s, double u, double v, t_ray *r)
{
	double	hori_r;
	double	vert_r;
	t_vec	point;

	vert_r = (0.5 / s->camera.win.w) + u;
	vert_r *= s->camera.viewport_w;
	hori_r = (0.5 / s->camera.win.h) + v;
	hori_r *= s->camera.viewport_h;
	point = vec3(s->camera.left_bottom.x + vert_r, s->camera.left_bottom.y
			+ hori_r, s->camera.left_bottom.z);
	*r = ray(point, vec3(0, 0, 0));
	return (is_ray_hit_object(s->objects, r));
}

int	is_light(t_light light, t_ray ray)
{
	int		light_in_obj;
	t_vec	light_vec;
	t_vec	obj_nvec;

	light_vec = vunit(vminus(ray.hit.point, light.coordinate));
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

void	shoot_ray(t_mlx *m, t_scene *s)
{
	double	i;
	double	j;
	t_ray	ray;

	j = -1;
	while (++j < s->camera.win.h - 1)
	{
		i = -1;
		while (++i < s->camera.win.w - 1)
		{
			if (is_pixel(s, i / s->camera.win.w, j / s->camera.win.h, &ray))
			{
				if (is_light(s->light, ray) && !is_pixel_in_shadow
					(s->objects, &s->light, &ray))
					my_mlx_pixel_put(&(m->data), i, s->camera.win.h - 1 - j,
						to_rgb(vmulti_f(vmin(vec3(1, 1, 1), \
						vplus(get_pixel_ambient_color(s, ray.hit.color), \
						get_pixel_diffuse_color(s, &ray))), 255)));
				else
					my_mlx_pixel_put(&(m->data), i, s->camera.win.h - 1 - j,
						to_rgb(vmulti_f(vmin(vec3(1, 1, 1), \
						get_pixel_ambient_color(s, ray.hit.color)), 255)));
			}
		}
	}
}
