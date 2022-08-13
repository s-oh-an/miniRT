/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:45:40 by sohan             #+#    #+#             */
/*   Updated: 2022/08/13 17:40:27 by sohan            ###   ########.fr       */
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

int	is_ray_hit_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	float	d_dot_n;
	float	c_dot_n;
	float	c_dot_d;
	float	c_dot_c;
	float	cp_dot_n;
	float	d;
	float	a;
	float	b;
	float	c;
	float	t[2];
	t_vec3	cp;

	d_dot_n = vec_op_dotproduct(ray->vec, cylinder->n_vector);
	c_dot_n = vec_op_dotproduct(cylinder->coordinate, cylinder->n_vector);
	c_dot_d = vec_op_dotproduct(cylinder->coordinate, ray->vec);
	c_dot_c = vec_op_dotproduct(cylinder->coordinate, cylinder->coordinate);
	a = d_dot_n * d_dot_n - 1;
	b = d_dot_n * c_dot_n - c_dot_d;
	c =	(cylinder->radius2 * cylinder->radius2) - c_dot_c + (c_dot_n * c_dot_n);
	d = (b * b) - (a * c);
	if (d > 0)
	{
		t[0] = (-b - sqrt(d)) / a;
		t[1] = (-b + sqrt(d)) / a;
		if (t[0] > 0)
			cp = vec_op_plus_vec(cylinder->coordinate, vec_op_multi_float(ray->vec, t[0]));
		else
			cp = vec_op_plus_vec(cylinder->coordinate, vec_op_multi_float(ray->vec, t[1]));
	}
	else if (d == 0)
		cp = vec_op_plus_vec(cylinder->coordinate, vec_op_multi_float(ray->vec, (-b / a)));
	else
		return (0);
	cp_dot_n = vec_op_dotproduct(cp, ray->vec);
	if (cp_dot_n >= 0 && cp_dot_n <= cylinder->height)
		return (1);
	return (0);
}
