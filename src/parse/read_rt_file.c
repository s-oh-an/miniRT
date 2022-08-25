/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:46:47 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 18:46:48 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/utils.h"
#include "../../lib/libft/libft.h"
#include "../../includes/vector.h"
#include <math.h>

int	is_valid_scene(int identifier_flag, t_object_list *list)
{
	if (!list || identifier_flag != 7)
		return (0);
	return (1);
}

void	set_elements(t_scene *scene, char *line, int *identifier_flag)
{
	char	**data;

	data = ft_split_space(line);
	if (!data)
		error_exit("Error\nError While malloc");
	if (data[0])
	{
		if (!ft_strncmp(data[0], "A", ft_strlen(data[0])))
			set_ambient(scene, (char const **)data, identifier_flag);
		else if (!ft_strncmp(data[0], "C", ft_strlen(data[0])))
			set_camera(scene, (char const **)data, identifier_flag);
		else if (!ft_strncmp(data[0], "L", ft_strlen(data[0])))
			set_light(scene, (char const **)data, identifier_flag);
		else if (!ft_strncmp(data[0], "sp", ft_strlen(data[0])))
			set_sphere(scene, (char const **)data);
		else if (!ft_strncmp(data[0], "pl", ft_strlen(data[0])))
			set_plane(scene, (char const **)data);
		else if (!ft_strncmp(data[0], "cy", ft_strlen(data[0])))
			set_cylinder(scene, (char const **)data);
		else
			error_exit("Error\nInvalid Identifier");
	}
	free_array(data);
}

void	read_rt_file(int fd, t_scene *scene)
{
	char	*line;
	int		ret;
	int		identifier_flag;

	ret = 1;
	identifier_flag = 0;
	line = NULL;
	scene->objects = NULL;
	while (ret)
	{
		if (line)
			free(line);
		ret = get_next_line(fd, &line);
		if (!*line)
			continue ;
		set_elements(scene, line, &identifier_flag);
	}
	if (line)
		free(line);
	if (!is_valid_scene(identifier_flag, scene->objects))
		error_exit("Error\nNot enough Scene Arguments");
}
