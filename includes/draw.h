/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:43:23 by sohan             #+#    #+#             */
/*   Updated: 2022/08/12 17:25:32 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "scene.h"
# include "ray.h"

int	is_ray_hit_sphere(t_sphere *sphere, t_ray *ray);

#endif
