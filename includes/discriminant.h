


#ifndef DISCRIMINANT_H
# define DISCRIMINANT_H

# include "scene.h"
# include "vector.h"

typedef struct s_window
{
	int		width;
	int		height;
	float	ratio;
}	t_window;


t_window	window(int width, int height);
t_camera	camera(t_coordinate point_w, float fov, t_window window);

#endif
