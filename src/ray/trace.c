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
			res |= is_ray_hit_cylinder_topbottom((t_cylinder *)obj->property, ray);
		}
		cur = cur->next;
	}
	return (res);
}

int	is_pixel_visible(t_scene *s, double u, double v, t_ray *r)
{
	double	hori_r;
	double	vert_r;
	t_vec	point;

	vert_r = (0.5 / (double)s->camera.win.width) + u;
	vert_r *= s->camera.viewport_w;
	hori_r = (0.5 / (double)s->camera.win.height) + v;
	hori_r *= s->camera.viewport_h;

	point = vec3(s->camera.left_bottom.x + vert_r , s->camera.left_bottom.y + hori_r, s->camera.left_bottom.z);
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

void	shoot_ray(t_mlx *m, t_scene *scene)
{
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
			if (is_pixel_visible(scene, (double)i / (double)(scene->camera.win.width), (double)j / (double)(scene->camera.win.height), &ray))
			{
				if (is_light(scene->light, ray) && !is_pixel_in_shadow(scene->objects, &scene->light, &ray))
					my_mlx_pixel_put(&(m->data), i, scene->camera.win.height - 1 - j, to_rgb(vmulti_f(vmin(vec3(1, 1, 1), vplus(get_pixel_ambient_color(scene, ray.hit.color), get_pixel_diffuse_color(scene, &ray))), 255)));
				else
					my_mlx_pixel_put(&(m->data), i, scene->camera.win.height - 1 - j, to_rgb(vmulti_f(vmin(vec3(1, 1, 1), get_pixel_ambient_color(scene, ray.hit.color)), 255)));
			}
		}
	}
}
