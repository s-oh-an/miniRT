/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:15:59 by sohan             #+#    #+#             */
/*   Updated: 2022/08/06 18:41:38 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/ft_string.h"
#include "../../lib/libft/libft.h"

/*void	check_file()
{

}*/

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}

int	is_duplicate_identifier(int identifier_flag)
{
	if (identifier_flag != 0)
		return (1);
	return (0);
}

int	is_valid_ratio_range(float ratio)
{
	if (ratio < 0.0 || ratio > 1.0)
		return (0);
	return (1);
}

void	set_light_ratio(float *ratio, char const *str)
{
	*ratio = ft_stof(str);
	if (!is_valid_ratio_range(*ratio))
	{
		ft_putendl_fd("Error\nInvalid Lightning Ratio", 2);
		exit(1);
	}
}

void	set_color(t_color *color, char const *str)
{
	char	**rgb;
	int		i;

	i = 0;
	rgb = ft_split(str, ',');
	if (!rgb)
	{
		ft_putendl_fd("Error\nError While malloc", 2);
		exit(1);
	}
	while (rgb[i])
		++i;
	if (i != 3)
	{
		ft_putendl_fd("Error\nInvalid Color", 2);
		exit(1);
	}
	color->x = ft_atoi(rgb[0]);
	if (color->x == 0 && rgb[0][0] != '0')
	{
		ft_putendl_fd("Error\nInvalid Color", 2);
		exit(1);
	}
	color->y = ft_atoi(rgb[1]);
	if (color->y == 0 && rgb[1][0] != '0')
	{
		ft_putendl_fd("Error\nInvalid Color", 2);
		exit(1);
	}
	color->z = ft_atoi(rgb[2]);
	if (color->z == 0 && rgb[2][0] != '0')
	{
		ft_putendl_fd("Error\nInvalid Color", 2);
		exit(1);
	}
	free_array(rgb);
}

void	set_ambient(t_scene *scene, char const **data, int *identifier_flag)
{
	if (is_duplicate_identifier(*identifier_flag & 1))
	{
		ft_putendl_fd("Error\nDuplicate Identifier", 2);
		exit(1);
	}
	*identifier_flag |= 1;
	set_light_ratio(&scene->ambient.ratio, data[1]);
	set_color(&scene->ambient.color, data[2]);
}

void	set_camera(t_scene *scene, char const **data, int *identifier_flag)
{
	(void)scene;
	(void)data;
	(void)identifier_flag;
}

void	set_light(t_scene *scene, char const **data, int *identifier_flag)
{
	(void)scene;
	(void)data;
	(void)identifier_flag;
}

void	set_object(t_scene *scene, char const **data, int type)
{
	(void)scene;
	(void)data;
	(void)type;
}

void	read_rt_file(int fd, t_scene *scene)
{
	char	*line;
	char	**data;
	int		ret;
	int		identifier_flag;
	
	ret = 1;
	identifier_flag = 0;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (!*line)
			continue ;
		data = ft_split_space(line);
		if (!ft_strncmp(data[0], "A", ft_strlen(data[0])))
			set_ambient(scene, (char const **)data, &identifier_flag);
		else if (!ft_strncmp(data[0], "C", ft_strlen(data[0])))
			set_camera(scene, (char const **)data, &identifier_flag);
		else if (!ft_strncmp(data[0], "L", ft_strlen(data[0])))
			set_light(scene, (char const **)data, &identifier_flag);
		else if (!ft_strncmp(data[0], "sp", ft_strlen(data[0])))
			set_object(scene, (char const **)data, T_SPHERE);
		else if (!ft_strncmp(data[0], "pl", ft_strlen(data[0])))
			set_object(scene, (char const **)data, T_PLANE);
		else if (!ft_strncmp(data[0], "cy", ft_strlen(data[0])))
			set_object(scene, (char const **)data, T_CYLINDER);
		else
		{
			ft_putendl_fd("Error\nInvalid Identifier", 2);
			exit(1);
		}
		free_array(data);
	}
}
