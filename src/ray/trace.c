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

// distinguish object
//int	dist_object(t_object *object, t_ray *ray, t_color *color)
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

//int	ray_in_viewport(t_camera cam, float u, float v, t_object *object, t_color *color)
int	is_object_visible(t_camera cam, float u, float v, t_object *object, t_color *color)
{
	t_ray	ray;
	float	hori_r;
	float	vert_r;

	// 2.0 / 2 / win.width
	vert_r = 1.0 / (float)cam.win.width;
	hori_r = 1.0 / (float)cam.win.height;
	ray = init_ray((cam.left_bottom.x + vert_r + u ), (cam.left_bottom.y + hori_r + v), cam.left_bottom.z);
	return (is_ray_hit_object(object, &ray, color));
}

void	shoot_ray(t_mlx *m, t_camera cam, t_object *object)
{
	float	u;
	float	v;
	int		i;
	int		j;
	t_color	color;

	j = cam.win.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < cam.win.width)
		{
			// 이 픽셀에 해당하는 뷰포트의 픽셀을 지나가는 광선이 물체와 만나는지 확인
			u = (2.0  *cam.win.ratio) * (float)i / (float)(cam.win.width);
			v = 2.0 * (float)j / (float)(cam.win.height);
			if (is_object_visible(cam, u, v, object, &color))
				my_mlx_pixel_put(&(m->data), i, j, to_rgb(&color));
			i++;
		}
		j--;
	}
}

//void	check_ob_list(t_mlx *m, t_camera cam, t_object_list *cur)
void	trace_objects(t_mlx *m, t_camera cam, t_object_list *cur)
{
	t_object	*obj;

	while (cur)
	{
		obj = cur->content;
		shoot_ray(m, cam, obj);
		cur = cur->next;
	}
}
