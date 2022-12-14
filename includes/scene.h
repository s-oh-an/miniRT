/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:54:47 by sohan             #+#    #+#             */
/*   Updated: 2022/08/26 10:21:17 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "../lib/libft/libft.h"

# define KEY_ESC				53

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_EXIT		17
# define E 1e-6
# define INF 99999999999999

typedef struct s_scene		t_scene;
typedef struct s_ambient	t_ambient;
typedef struct s_light		t_light;
typedef struct s_camera		t_camera;
typedef struct s_object		t_object;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_cy_calc	t_cy_calc;
typedef struct s_vec3		t_vec;

typedef t_vec				t_coordinate;
typedef t_vec				t_color;
typedef t_vec				t_normal_vector;
typedef t_list				t_object_list;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct s_ambient
{
	double	ratio;
	t_color	color;
};

typedef struct s_window
{
	double	w;
	double	h;
	double	ratio;
}	t_window;

struct s_camera
{
	t_coordinate	orig;
	t_normal_vector	n_vector;
	t_vec			x;
	t_vec			y;
	t_vec			z;
	double			fov;
	double			viewport_h;
	double			viewport_w;
	t_vec			hori_vec;
	t_vec			vert_vec;
	double			focal_len;
	t_vec			ver;
	t_vec			hor;
	t_coordinate	left_bottom;
	double			t;
};

struct s_light
{
	t_coordinate	coordinate;
	double			ratio;
};

struct s_sphere
{
	t_coordinate	coordinate;
	double			diameter;
	double			radius2;
	t_color			color;
};

struct s_plane
{
	t_coordinate	coordinate;
	t_normal_vector	n_vector;
	t_color			color;
};

struct s_cy_calc
{
	t_vec	v;
	double	top_t;
	double	bottom_t;
	double	d_dot_v;
	double	c_dot_v;
	t_vec	ce;
	double	t[2];
};

struct s_cylinder
{
	t_coordinate	coordinate;
	t_normal_vector	n_vector;
	double			diameter;
	double			radius2;
	double			height;
	int				top;
	int				bottom;
	t_color			color;
	t_cy_calc		tcc;
};

struct s_object
{
	int		type;
	void	*property;
};

struct s_scene
{
	t_ambient		ambient;
	t_light			light;
	t_camera		camera;
	t_object_list	*objects;
	t_window		win;
};

enum e_object_type
{
	T_SPHERE,
	T_PLANE,
	T_CYLINDER,
};

#endif
