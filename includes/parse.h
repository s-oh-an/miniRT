/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:54:33 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 18:54:34 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "scene.h"

void	read_rt_file(int fd, t_scene *scene);

void	set_sphere(t_scene *scene, char const **data);
void	set_plane(t_scene *scene, char const **data);
void	set_cylinder(t_scene *scene, char const **data);
void	set_ambient(t_scene *scene, char const **data, int *identifier_flag);
void	set_camera(t_scene *scene, char const **data, int *identifier_flag);
void	set_light(t_scene *scene, char const **data, int *identifier_flag);

#endif
