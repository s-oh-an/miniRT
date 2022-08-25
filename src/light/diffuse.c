/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:42:16 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 19:26:03 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scene.h"
#include "../../includes/vector.h"
#include "../../includes/light.h"

t_color	get_pixel_diffuse_color(t_scene *scene, t_ray *ray)
{
	t_color	diffuse;
	t_color	color;
	t_vec	pl;
	double	d;
	double	attenuation;

	diffuse = vec3(1, 1, 1);
	pl = vminus(scene->light.coordinate, ray->hit.point);
	d = vlen(pl);
	pl = vunit(pl);
	diffuse = vmulti_f(diffuse, vdot(ray->hit.normal, pl) * scene->light.ratio);
	diffuse = vmax(vec3(0, 0, 0), diffuse);
	color = ray->hit.color;
	color.x /= 255;
	color.y /= 255;
	color.z /= 255;
	diffuse = vmulti(color, diffuse);
	attenuation = 1 / (1 + (0.0014 * d) + (0.000007 * d * d));
	diffuse = vmulti_f(diffuse, attenuation);
	return (vmin(vec3(1, 1, 1), diffuse));
}
