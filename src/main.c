/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:43:52 by sohan             #+#    #+#             */
/*   Updated: 2022/08/07 19:01:33 by sohan            ###   ########.fr       */
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
	system("leaks miniRT");
	return (0);
}
