/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:47:19 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 19:04:10 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scene.h"
#include "../../includes/transform.h"
#include "../../includes/vector.h"

t_vec	rotate(t_vec *world, t_camera *camera)
{
	t_vec	new;

	new.x = vdot(*world, camera->x);
	new.y = vdot(*world, camera->y);
	new.z = vdot(*world, camera->z);
	return (new);
}

t_vec	translate(t_vec *world, t_camera *camera)
{
	t_vec	new;

	new = vminus(*world, camera->orig);
	return (new);
}
