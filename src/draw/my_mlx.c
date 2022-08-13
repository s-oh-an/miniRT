

#include "../../includes/draw.h"

void	init_mlx(t_mlx *m, t_window w)
{

	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, w.width, w.height, "s(oh)an's MINIRT");

}

int	trans_trgb(t_color color)
{
	int	trgb;

	trgb = (int)color.x;
	trgb = trgb << 8;
	trgb = trgb | (int)color.y;
	trgb = trgb << 8;
	trgb = trgb | (int)color.z;
	return (trgb);
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
