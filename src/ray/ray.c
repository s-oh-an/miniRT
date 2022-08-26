/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:46:56 by sohan             #+#    #+#             */
/*   Updated: 2022/08/26 09:56:11 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ray.h"
#include "../../includes/vector.h"
#include "../../includes/discriminant.h"

t_ray	ray(t_vec direction, t_coordinate origin)
{
	t_ray	ray;

	ray.direction = vunit(direction);
	ray.origin = origin;
	ray.hit.t = INF;
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
