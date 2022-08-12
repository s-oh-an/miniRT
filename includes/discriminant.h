


#ifndef DISCRIMINANT_H
# define DISCRIMINANT_H

# include "scene.h"
# include "vector.h"

typedef struct s_pixel
{
	t_coordinate	point;
	int				hit; 	// if hit == 1, else == 0
}	t_pixel;

typedef struct s_ray
{
	t_pixel			dir_pixel;
	t_coordinate	unit_vec;
} t_ray;

typedef struct s_window
{
	int		width;
	int		height;
	float	ratio;
}	t_window;


// t_ray	**find_view_pixel(float fov);
t_window	window(int width, int height);
t_camera	camera(t_coordinate point_w, float fov, t_window window);

#endif