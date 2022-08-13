/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:45:40 by sohan             #+#    #+#             */
/*   Updated: 2022/08/13 20:07:27 by sohan            ###   ########.fr       */
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
	float	t[2];

	b = vec_op_dotproduct(ray->vec, vec_op_minus_vec(init_vec(0, 0, 0), sphere->coordinate));
	c = vec_len_squared(sphere->coordinate) - sphere->radius2;
	d = (b* b) - c;
	if (d < 0)
		return (0);
	t[0] = -b + sqrt(d);
	t[1] = -b - sqrt(d);
	if (t[0] * t[1] > 0)
	{
		if (t[0] < 0)
			return (0);
	}
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
