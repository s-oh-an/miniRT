/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:54:13 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 18:54:14 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "scene.h"
# include "ray.h"

t_color	get_pixel_ambient_color(t_scene *scene, t_color color);
t_color	get_pixel_diffuse_color(t_scene *scene, t_ray *ray);

#endif
