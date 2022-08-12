



#ifndef RAY_H
# define RAY_H

# include "scene.h"
# include "vector.h"
# include "discriminant.h"
# include "my_mlx.h"

typedef struct s_ray
{
	// 정규화된 ray의 방향벡터
	t_vec	vec;
}	t_ray;

t_ray	init_ray(float x, float y, float z);
void	shoot_ray(t_mlx *m, t_camera cam, t_window win, t_sphere *sphere);

#endif
