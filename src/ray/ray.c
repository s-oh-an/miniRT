

#include "../../includes/ray.h"
#include "../../includes/draw.h"

t_ray	init_ray(float x, float y, float z)
{
	t_ray	ray;
	t_vec	vec;

	vec = init_vec(x, y, z);
	ray.vec = vec_op_unit(vec);
	return (ray);	
}

int	ray_in_viewport(t_camera cam, t_window win, float u, float v, t_sphere *sphere)
{
	t_ray	ray;
	float	hori_r;
	float	vert_r;

	// 2.0 / 2 / win.width
	vert_r = 1.0 / (float)win.width;
	hori_r = 1.0 / (float)win.height;
	ray = init_ray((cam.left_bottom.x + vert_r + u ), (cam.left_bottom.y + hori_r + v), cam.left_bottom.z);
	
	// 물체 판별

	if (is_ray_hit_sphere(sphere, &ray))
		return (1);
	else 
		return (0);
}

// #include <fcntl.h>

void	shoot_ray(t_mlx *m, t_camera cam, t_window win, t_sphere *sphere)
{
	float	u;
	float	v;
	int		i;
	int		j;

	j = win.height - 1;
	//FILE *file = fopen("result.txt", "w");
	while (j >= 0)
	{
		i = 0;
		while (i < win.width)
		{
			// 이 픽셀에 해당하는 뷰포트의 픽셀을 지나가는 광선이 물체와 만나는지 확인
			u = (2.0 * win.ratio) * (float)i / (float)(win.width);
			v = 2.0 * (float)j / (float)(win.height);
			int k = ray_in_viewport(cam, win, u, v, sphere);
			//fprintf(file, "%d ", k);
			//if (ray_in_viewport(cam, win, u, v, sphere))		// if ray hit object, return 1
			if (k)													// 
			{
				//printf("i : %d j : %d\n", i, j);
				my_mlx_pixel_put(&(m->data), i, j, 0x0000FF00);
			}
			i++;
		}
		j--;
	}
	//fprintf(file, "\n");
}
