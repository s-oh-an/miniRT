/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:43:52 by sohan             #+#    #+#             */
/*   Updated: 2022/08/07 14:48:32 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"
#include "../includes/scene.h"
#include "../lib/libft/libft.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

void	print(t_scene *scene)
{
	printf("[Ambient]\n");
	printf("ambient light ratio	: %f\n", scene->ambient.ratio);
	printf("color			: %f %f %f\n", scene->ambient.color.x, scene->ambient.color.y,scene->ambient.color.z);
	printf("[Camera]\n");
	printf("xyz coordinate		: %f %f %f\n", scene->camera.coordinate.x, scene->camera.coordinate.y,scene->camera.coordinate.z);
	printf("normal vector		: %f %f %f\n", scene->camera.n_vector.x, scene->camera.n_vector.y,scene->camera.n_vector.z);
	printf("FOV		  	: %d\n", scene->camera.fov);
	printf("[Light]\n");
	printf("xyz coordinate		: %f %f %f\n", scene->light.coordinate.x, scene->light.coordinate.y,scene->light.coordinate.z);
	printf("light ratio		: %f\n", scene->light.ratio);

	printf("[Object]\n");
}

int	main(int argc, char **argv)
{
	int		fd;
	t_scene scene;

	if (argc != 2)
	{	
		ft_putendl_fd("Error\nUsage:./miniRT <filename.rt>", 2);
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
	system("leaks miniRT");
	return (0);
}
