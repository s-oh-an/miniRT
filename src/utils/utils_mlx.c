#include "../../includes/scene.h"
#include "../../lib/mlx/mlx.h"
#include "../../includes/my_mlx.h"
#include "../../includes/ray.h"

//TODO
#include <stdio.h>

int	exit_minirt(t_mlx *m)
{
	mlx_destroy_window(m->mlx, m->win);
	// system("leaks miniRT");
	exit(0);
}

void	init_mlx(t_mlx *m, t_window w)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, w.w, w.h, "s(oh)an's MINIRT");
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	press_key(int key_code, t_mlx *m)
{
	char	ratio[10];

	//ratio = calloc(5, sizeof(char));
	for (int i = 0; i < 10; i++)
		ratio[i] = 0;
	if (key_code == KEY_ESC)
		exit_minirt(m);
	else if (key_code == KEY_RIGHT)
	{
		if (m->scene.ambient.ratio + 0.1 <= 1.1)
		{	
			m->scene.ambient.ratio += 0.1;
			shoot_ray(m, &m->scene);
			mlx_put_image_to_window(m->mlx, m->win, m->data.img, 0, 0);
			mlx_string_put(m->mlx, m->win, 24, 36, 0x000000,gcvt(m->scene.ambient.ratio, 2, ratio));
		}
	}
	else if (key_code == KEY_LEFT)
	{
		if (m->scene.ambient.ratio - 0.1 >= 0.0)
		{
			m->scene.ambient.ratio -= 0.1;
			shoot_ray(m, &m->scene);
			mlx_put_image_to_window(m->mlx, m->win, m->data.img, 0, 0);
			mlx_string_put(m->mlx, m->win, 24, 36, 0x000000,gcvt(m->scene.ambient.ratio, 2, ratio));
		}
	}
	return (0);
}
