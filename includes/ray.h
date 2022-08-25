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
	int				in_object;	// 0이면 물체 밖에 카메라, 1이면 물체 안에 카메라
	int				ray_hit;	// 0이면 이 ray는 hit이 없음. 1이면 이 ray는 hit한 ray
}	t_hit;

typedef struct s_ray
{
	t_vec			direction;
	t_coordinate	origin;
	t_hit			hit;
}	t_ray;

t_ray	ray(t_vec direction, t_coordinate origin);
void	shoot_ray(t_mlx *m, t_scene *scene);
int		is_ray_hit_object(t_object_list *objs, t_ray *ray);

#endif
