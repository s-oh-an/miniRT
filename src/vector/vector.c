/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:28:42 by san               #+#    #+#             */
/*   Updated: 2022/08/25 15:28:43 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"
#include <math.h>

t_vec	vec3(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

double	vlen2(t_vec vec)
{
	long double	len;

	len = (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (len);
}

double	vlen(t_vec vec)
{
	double	len;

	len = sqrt(vlen2(vec));
	return (len);
}

t_vec	vplus(t_vec vec1, t_vec vec2)
{
	vec1.x = vec1.x + vec2.x;
	vec1.y = vec1.y + vec2.y;
	vec1.z = vec1.z + vec2.z;
	return (vec1);
}

t_vec	vplus_f(t_vec vec1, double x, double y, double z)
{
	vec1.x = vec1.x + x;
	vec1.y = vec1.y + y;
	vec1.z = vec1.z + z;
	return (vec1);
}
