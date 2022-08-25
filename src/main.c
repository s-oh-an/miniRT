#include "../includes/scene.h"
#include "../includes/parse.h"
#include "../includes/ray.h"
#include "../includes/utils.h"
#include "../includes/transform.h"
#include "../lib/libft/libft.h"
#include "../lib/mlx/mlx.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	int		fd;
	t_mlx	m;
	t_scene scene;

	if (argc != 2 || !ft_strncmp(argv[1], "", ft_strlen(argv[1])))
		error_exit("Error\nUsage:./miniRT <filename.rt>");
	if (!is_rt_file(argv[1]))
		error_exit("Error\nNot .rt file");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}
	read_rt_file(fd, &scene);
	world_to_camera(&scene);
	init_mlx(&m, scene.win);
	m.data.img = mlx_new_image(m.mlx, scene.win.w, scene.win.h);
	m.data.addr = mlx_get_data_addr(m.data.img, &m.data.bits_per_pixel, &m.data.line_length, &m.data.endian);
	shoot_ray(&m, &scene);
	mlx_put_image_to_window(m.mlx, m.win, m.data.img, 0, 0);
	mlx_hook(m.win, X_EVENT_KEY_PRESS, 0, &press_key, &m);
	mlx_hook(m.win, X_EVENT_KEY_EXIT, 0, &exit_minirt, &m);
	mlx_loop(m.mlx);
	return (0);
}
