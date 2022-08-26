/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:54:38 by sohan             #+#    #+#             */
/*   Updated: 2022/08/26 10:21:31 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "scene.h"
# include "my_mlx.h"

typedef struct s_hit
{
	double			t;
	t_coordinate	point;
	t_color			color;
	t_vec			normal;
	int				in_object;
}	t_hit;

typedef struct s_ray
{
	t_vec			direction;
	t_coordinate	origin;
	t_hit			hit;
}	t_ray;

t_ray	ray(t_vec direction, t_coordinate origin);
int		is_ray_hit_object(t_object_list *objs, t_ray *ray);
void	shoot_ray(t_mlx *m, t_scene *scene);

#endif
