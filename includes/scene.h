/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:55:12 by sohan             #+#    #+#             */
/*   Updated: 2022/08/07 17:34:24 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "../lib/libft/libft.h"

typedef struct s_ambient	t_ambient;
typedef struct s_light		t_light;
typedef struct s_camera		t_camera;
typedef struct s_object		t_object;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_vec3		t_coordinate;
typedef struct s_vec3		t_color;
typedef struct s_vec3		t_normal_vector;
typedef t_list				t_object_list;

struct s_vec3
{
	float	x;
	float	y;
	float	z;
};

struct s_ambient
{
	float	ratio;
	t_color	color;
};

struct s_camera
{
	t_coordinate	coordinate;
	t_normal_vector	n_vector;
	float			fov;
};

struct s_light
{
	t_coordinate	coordinate;
	float			ratio;
};

struct s_sphere
{
	t_coordinate	coordinate;
	float			diameter;
	t_color			color;
};

struct s_plane
{
	t_coordinate	coordinate;
	t_normal_vector	n_vector;
	t_color			color;
};

struct s_cylinder
{
	t_coordinate	coordinate;
	t_normal_vector	n_vector;
	float			diameter;
	float			height;
	t_color			color;
};

struct s_object
{
	int		type;
	void	*property;
};

typedef struct s_scene
{
	t_ambient		ambient;
	t_light			light;
	t_camera		camera;
	t_object_list	*objects;
}	t_scene;

enum e_object_type
{
	T_SPHERE,
	T_PLANE,
	T_CYLINDER,
};

#endif
