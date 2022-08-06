/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:13:41 by sohan             #+#    #+#             */
/*   Updated: 2022/08/06 17:36:06 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../includes/scene.h"

int		is_valid_identifier(char const *str);
int		is_valid_scene();
int		is_valid_color_range();
int		is_valid_vector_range();
int		is_valid_ratio_range(float ratio);
int		is_valid_fov_range();
void	read_rt_file(int fd, t_scene *scene);

#endif
