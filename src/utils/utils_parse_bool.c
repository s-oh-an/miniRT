/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_bool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:50:11 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 18:50:13 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scene.h"
#include "../../includes/utils.h"

int	is_duplicate_identifier(int identifier_flag)
{
	if (identifier_flag != 0)
		return (1);
	return (0);
}

int	is_valid_ratio_range(double ratio)
{
	if (ratio < 0.0 || ratio > 1.0)
		return (0);
	return (1);
}

int	is_valid_color_range(t_color *color)
{
	if (color->x < 0.0 || color->x > 255.0 || color->y < 0.0 || \
		color->y > 255.0 || color->z < 0.0 || color->z > 255.0)
		return (0);
	return (1);
}

int	is_valid_vector_range(t_normal_vector *vec)
{
	if (vec->x < -1.0 || vec->x > 1.0 || vec->y < -1.0 || vec->y > 1.0 || \
		vec->z < -1.0 || vec->z > 1.0)
		return (0);
	return (1);
}

int	is_valid_property(double value)
{
	if (value < 0.0)
		return (0);
	return (1);
}
