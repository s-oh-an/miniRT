/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:28:55 by san               #+#    #+#             */
/*   Updated: 2022/08/25 18:51:20 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"
#include "../../includes/utils.h"

double	vdot(t_vec vec1, t_vec vec2)
{
	double	res;

	res = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
	return (res);
}

t_vec	vcross(t_vec vec1, t_vec vec2)
{
	t_vec	res;

	res.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
	res.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
	res.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
	return (res);
}

t_vec	vunit(t_vec vec)
{
	t_vec	unit;
	double	len;

	len = vlen(vec);
	if (len == 0)
		error_exit("Error\ninvalid location\nexiting...");
	unit.x = vec.x / len;
	unit.y = vec.y / len;
	unit.z = vec.z / len;
	return (unit);
}

t_vec	vmin(t_vec vec1, t_vec vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}

t_vec	vmax(t_vec vec1, t_vec vec2)
{
	if (vec1.x < vec2.x)
		vec1.x = vec2.x;
	if (vec1.y < vec2.y)
		vec1.y = vec2.y;
	if (vec1.z < vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}
