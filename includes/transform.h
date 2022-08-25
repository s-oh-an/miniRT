/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:55:50 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 18:55:51 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "scene.h"

void	world_to_camera(t_scene *scene);
t_vec	rotate(t_vec *world, t_camera *camera);
t_vec	translate(t_vec *world, t_camera *camera);

#endif
