#ifndef RAY_H
# define RAY_H

# include "scene.h"
# include "my_mlx.h"

typedef struct s_hit
{
	t_coordinate	hit_point;
	float			t;
	t_vec			hit_normal;
	float			min;
	int				in_object;
}	t_hit;

typedef struct s_ray
{
	t_vec	vec;
	t_hit	hit;
}	t_ray;

t_ray	init_ray(float x, float y, float z);
void	shoot_ray(t_mlx *m, t_scene *scene);
// void	trace_objects(t_mlx *m, t_scene *scene);


#endif
