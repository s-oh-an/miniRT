#include "../includes/parse.h"
#include "../includes/scene.h"
#include "../includes/my_mlx.h"
#include "../lib/libft/libft.h"
#include "../lib/mlx/mlx.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "../includes/vector.h" //
#include "../includes/discriminant.h" //
#include "../includes/ray.h" //

///////////// add mlx func /////////////////

int	exit_minirt(t_mlx *m)
{
	mlx_destroy_window(m->mlx, m->win);
	free(m);
	exit(0);
}

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



/////////////////////////////////////////////

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

int	is_rt_file(char const *str)
{
	char	*file;

	file = ft_strchr(str, '.');
	if (!file || ft_strncmp(file, ".rt", ft_strlen(file)) != 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_scene scene;
	//t_image	img;
	//t_mlx	mlx;

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

	t_mlx	*m;
	// t_window	win;
	t_camera	cam;

	// win = window(1280, 1280); // 1:1
	// win = window(1280, 720); // 16 : 9
	// win = window(960, 720); // 4:3
	//cam = camera(init_point(0,0,0), 45, win);
	//cam = camera();
	cam = scene.camera;
	m = malloc(sizeof(t_mlx));
	init_mlx(m, cam.win);

	m->data.img = mlx_new_image(m->mlx, cam.win.width, cam.win.height);
	m->data.addr = mlx_get_data_addr(m->data.img, &m->data.bits_per_pixel, &m->data.line_length, &m->data.endian);

	// t_object_list *cur;

	// cur = scene.objects;
	// t_object	*obj;
	// obj = cur->content;
	// t_sphere	*sp = obj->property;
	// shoot_ray(m, cam, obj);

	// obj = cur->content;

	check_ob_list(m, cam, scene.objects);

	mlx_put_image_to_window(m->mlx, m->win, m->data.img, 0, 0);

	mlx_hook(m->win, X_EVENT_KEY_PRESS, 0, &press_key, m);
	mlx_hook(m->win, X_EVENT_KEY_EXIT, 0, &exit_minirt, m);
	mlx_loop(m->mlx);

	///////////////////////////////////////////////////////////

		//mlx.mlx_ptr = mlx_init();
	//mlx.img.img = mlx_new_image(mlx.mlx_ptr, 500, 500);
	//mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bits_per_pixel, &mlx.img.line_length, &mlx.img.endian);
	//mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 500, 500, "test");
	//mlx_loop(mlx.mlx_ptr);
	system("leaks miniRT");
	return (0);
}
