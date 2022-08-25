#include "../../includes/scene.h"
#include "../../lib/mlx/mlx.h"
#include "../../includes/my_mlx.h"
#include "../../includes/ray.h"

int	exit_minirt(t_mlx *m)
{
	mlx_destroy_window(m->mlx, m->win);
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
	if (key_code == KEY_ESC)
		exit_minirt(m);
	return (0);
}
