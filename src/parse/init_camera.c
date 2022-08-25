/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:29:05 by san               #+#    #+#             */
/*   Updated: 2022/08/25 15:29:07 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/camera.h"
#include "../../includes/vector.h"
#include <math.h>

void	camera(t_camera *camera)
{
	camera->win.w = 1280;
	camera->win.h = 720;
	camera->win.ratio = (double)camera->win.w / (double)camera->win.h;
	camera->viewport_h = 2.0;
	camera->viewport_w = camera->viewport_h * (camera->win.ratio);
	camera->focal_len = 1.0 / tan((camera->fov / 2) * (M_PI / 180));
	camera->left_bottom = vec3(-camera->viewport_w / 2,
			-camera->viewport_h / 2, -camera->focal_len);
}
