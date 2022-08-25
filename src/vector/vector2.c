/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:28:48 by san               #+#    #+#             */
/*   Updated: 2022/08/25 15:28:49 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector.h"

t_vec	vminus(t_vec vec1, t_vec vec2)
{
	vec1.x = vec1.x - vec2.x;
	vec1.y = vec1.y - vec2.y;
	vec1.z = vec1.z - vec2.z;
	return (vec1);
}

t_vec	vminus_f(t_vec vec1, double x, double y, double z)
{
	vec1.x = vec1.x - x;
	vec1.y = vec1.y - y;
	vec1.z = vec1.z - z;
	return (vec1);
}

t_vec	vmulti_f(t_vec vec, double t)
{
	vec.x = vec.x * t;
	vec.y = vec.y * t;
	vec.z = vec.z * t;
	return (vec);
}

t_vec	vmulti(t_vec vec, t_vec vec2)
{
	vec.x *= vec2.x;
	vec.y *= vec2.y;
	vec.z *= vec2.z;
	return (vec);
}

t_vec	vdiv(t_vec vec, double t)
{
	vec.x = vec.x * (1 / t);
	vec.y = vec.y * (1 / t);
	vec.z = vec.z * (1 / t);
	return (vec);
}
