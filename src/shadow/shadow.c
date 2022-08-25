/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:51:45 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 19:04:56 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shadow.h"
#include "../../includes/vector.h"

int	is_pixel_in_shadow(t_object_list *objs, t_light *light, t_ray *primary)
{
	t_ray	shadow;
	t_vec	pl;
	double	len;
	t_vec	pp;

	pp = vmulti_f(primary->hit.normal, E);
	pl = vminus(light->coordinate, vplus(primary->hit.point, pp));
	len = vlen(pl);
	pl = vunit(pl);
	if (vdot(primary->hit.normal, pl) < E)
		return (0);
	shadow = ray(vec3(pl.x, pl.y, pl.z), vplus(primary->hit.point, pp));
	if (is_ray_hit_object(objs, &shadow))
	{
		if (shadow.hit.t > -E && shadow.hit.t < len - E)
			return (1);
	}
	return (0);
}
