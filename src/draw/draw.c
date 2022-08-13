/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:45:40 by sohan             #+#    #+#             */
/*   Updated: 2022/08/12 19:54:04 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/draw.h"
#include "../../includes/vector.h"
#include "../../includes/ray.h"

int	is_ray_hit_sphere(t_sphere *sphere, t_ray *ray)
{
	float	b;
	float	c;
	float	d;

	b = vec_op_dotproduct(ray->vec, sphere->coordinate);
	b *= b;
	c = vec_len(sphere->coordinate) * vec_len(sphere->coordinate) - sphere->radius2;
	d = b - c;
	if (d < 0)
		return (0);
	return (1);
}

int	is_ray_hit_plane(t_plane *plane, t_ray *ray)
{
	float	c_dot_n;
	float	d_dot_n;
	float	d;

	c_dot_n = vec_op_dotproduct(plane->n_vector, plane->coordinate);
	d_dot_n = vec_op_dotproduct(plane->n_vector, ray->vec);
	if (d_dot_n == 0)
		return (0);
	d = c_dot_n / d_dot_n;
	if (d < 0)
		return (0);
	return (1);
}