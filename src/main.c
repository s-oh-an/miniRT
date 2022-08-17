#include "../includes/parse.h"
#include "../includes/scene.h"
#include "../lib/libft/libft.h"
#include "../lib/mlx/mlx.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "../includes/vector.h" //
#include "../includes/discriminant.h" //
#include "../includes/ray.h" //
#include "../includes/utils.h"
#include "../includes/transform.h"

void	print(t_scene *scene)
{
	printf("[Ambient]\n");
	printf("ambient light ratio	: %f\n", scene->ambient.ratio);
	printf("color			: %f %f %f\n", scene->ambient.color.x, scene->ambient.color.y,scene->ambient.color.z);
	printf("[Camera]\n");
	printf("xyz coordinate		: %f %f %f\n", scene->camera.orig.x, scene->camera.orig.y,scene->camera.orig.z);
	printf("normal vector		: %f %f %f\n", scene->camera.n_vector.x, scene->camera.n_vector.y,scene->camera.n_vector.z);
	printf("FOV		  	: %f\n", scene->camera.fov);
	printf("[Light]\n");
	printf("xyz coordinate		: %f %f %f\n", scene->light.coordinate.x, scene->light.coordinate.y,scene->light.coordinate.z);
	printf("light ratio		: %f\n", scene->light.ratio);
	t_object_list	*cur;
	t_object		*obj;
	t_sphere		*sp;
	t_plane			*pl;
	t_cylinder		*cy;
	int				cnt = 0;

	cur = scene->objects;
	while (cur)
	{
		printf("[Object %d]\n", ++cnt);
		obj = cur->content;
		printf("type %d ", obj->type);
		if (obj->type == T_SPHERE)
		{
			sp = obj->property;
			printf("*sp*\n");
			printf("xyz coordinate		: %f %f %f\n", sp->coordinate.x, sp->coordinate.y,sp->coordinate.z);
			printf("diameter		: %f\n", sp->diameter);
			printf("color			: %f %f %f\n", sp->color.x, sp->color.y,sp->color.z);
		}
		else if (obj->type == T_PLANE)
		{
			pl = obj->property;
			printf("*pl*\n");
			printf("xyz coordinate		: %f %f %f\n", pl->coordinate.x, pl->coordinate.y,pl->coordinate.z);
			printf("normal vector		: %f %f %f\n", pl->n_vector.x, pl->n_vector.y,pl->n_vector.z);
			printf("color			: %f %f %f\n", pl->color.x, pl->color.y,pl->color.z);
		}
		else if (obj->type == T_CYLINDER)
		{
			cy = obj->property;
			printf("*cy*\n");
			printf("xyz coordinate		: %f %f %f\n", cy->coordinate.x, cy->coordinate.y,cy->coordinate.z);
			printf("normal vector		: %f %f %f\n", cy->n_vector.x, cy->n_vector.y,cy->n_vector.z);
			printf("diameter		: %f\n", cy->diameter);
			printf("height			: %f\n", cy->height);
			printf("color			: %f %f %f\n", cy->color.x, cy->color.y,cy->color.z);
		}
		cur = cur->next;
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	t_scene scene;

	if (argc != 2 || !ft_strncmp(argv[1], "", ft_strlen(argv[1])))
	{	
		ft_putendl_fd("Error\nUsage:./miniRT <filename.rt>", 2);
		exit(1);
	}
	if (!is_rt_file(argv[1]))
	{
		ft_putendl_fd("Error\nNot .rt file", 2);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}
	read_rt_file(fd, &scene);
	print(&scene);
	world_to_camera(&scene);
	printf("\n\n");
	print(&scene);

	///////////////////////insert mlx print/////////////////////

	t_mlx		m;
	t_camera	cam;
	char		ratio[10];
	for (int i = 0; i < 10; i++)
		ratio[i] = 0;


	cam = scene.camera;
	init_mlx(&m, cam.win);
	m.data.img = mlx_new_image(m.mlx, cam.win.width, cam.win.height);
	m.data.addr = mlx_get_data_addr(m.data.img, &m.data.bits_per_pixel, &m.data.line_length, &m.data.endian);
	for (int i = 0; i < cam.win.width; i++)
		for (int j = 0; j < cam.win.height; j++)
			my_mlx_pixel_put(&m.data, i, j, to_rgb(vec3(255, 255, 255)));
	trace_objects(&m, &scene);
	mlx_put_image_to_window(m.mlx, m.win, m.data.img, 0, 0);
	mlx_string_put(m.mlx, m.win, 24, 36, 0x000000,gcvt(scene.ambient.ratio, 2, ratio));
	mlx_hook(m.win, X_EVENT_KEY_PRESS, 0, &press_key, &m);
	mlx_hook(m.win, X_EVENT_KEY_EXIT, 0, &exit_minirt, &m);
	mlx_loop(m.mlx);
	system("leaks miniRT");
	return (0);
}
