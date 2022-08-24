#ifndef RAY_H
# define RAY_H

# include "scene.h"
# include "my_mlx.h"

typedef struct s_hit
{
	double			t;
	t_coordinate	hit_point;
	t_color			hit_color;
	t_vec			hit_normal;
	int				in_object;	// 0이면 물체 밖에 카메라, 1이면 물체 안에 카메라
	int				ray_hit;	// 0이면 이 ray는 hit이 없음. 1이면 이 ray는 hit한 ray
	int				in_shadow;
}	t_hit;

typedef struct s_ray
{
	t_vec	vec;
	t_hit	hit;
}	t_ray;

t_ray	init_ray(double x, double y, double z);
void	shoot_ray(t_mlx *m, t_scene *scene);
int		is_ray_hit_object(t_object_list *objs, t_ray *ray, t_coordinate e);
// void	trace_objects(t_mlx *m, t_scene *scene);


#endif
