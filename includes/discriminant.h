/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discriminant.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:53:59 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 18:54:00 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISCRIMINANT_H
# define DISCRIMINANT_H

# include "scene.h"
# include "ray.h"

int	is_ray_hit_sphere(t_sphere *sphere, t_ray *ray);
int	is_ray_hit_plane(t_plane *plane, t_ray *ray);
int	is_ray_hit_cylinder_cover(t_cylinder *cylinder, t_ray *ray);
int	is_ray_hit_cylinder(t_cylinder *cylinder, t_ray *ray);

#endif
