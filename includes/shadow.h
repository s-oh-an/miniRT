/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:55:09 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 18:55:33 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADOW_H
# define SHADOW_H

# include "scene.h"
# include "ray.h"

int	is_pixel_in_shadow(t_object_list *objs, t_light *light, t_ray *ray);

#endif
