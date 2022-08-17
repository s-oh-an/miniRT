#include "../../includes/ray.h"
#include "../../includes/discriminant.h"
#include "../../includes/utils.h"
#include "../../includes/vector.h"

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

void	shoot_ray(t_mlx *m, t_camera *cam, t_object *object)
{
	float	u;
	float	v;
	int		i;
	int		j;
	t_color	color;

	j = 0;
	while (j < cam->win.height - 1)
	{
		i = 0;
		while (i < cam->win.width - 1)
		{
			u = (float)i / (float)(cam->win.width);
			v = (float)j / (float)(cam->win.height);
			if (is_object_visible(cam, u, v, object, &color))
				my_mlx_pixel_put(&(m->data), i, (cam->win.height - 1) - j, to_rgb(&color));
			i++;
		}
		j++;
	}
}

void	trace_objects(t_mlx *m, t_camera *cam, t_object_list *cur)
{
	t_object	*obj;

	while (cur)
	{
		obj = cur->content;
		shoot_ray(m, cam, obj);
		cur = cur->next;
	}
}
