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
