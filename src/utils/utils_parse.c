/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:49:44 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 19:00:36 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scene.h"
#include "../../includes/utils.h"
#include "../../lib/libft/libft.h"

void	set_vec3(struct s_vec3 *vec, char const *str)
{
	char	**xyz;
	int		i;

	i = 0;
	xyz = ft_split(str, ',');
	if (!xyz)
		error_exit("Error\nError While malloc");
	while (xyz[i])
		++i;
	if (i != 3)
		error_exit("Error\nInvalid vec");
	vec->x = ft_stof(xyz[0]);
	vec->y = ft_stof(xyz[1]);
	vec->z = ft_stof(xyz[2]);
	free_array(xyz);
}

void	set_light_ratio(double *ratio, char const *str)
{
	*ratio = ft_stof(str);
	if (!is_valid_ratio_range(*ratio))
		error_exit("Error\nInvalid Lightning Ratio");
}

int	get_field_count(char const **data)
{
	int	i;

	i = 0;
	while (data[i])
		++i;
	return (i);
}

int	is_rt_file(char const *str)
{
	char	*file;

	file = ft_strchr(str, '.');
	if (!file || ft_strncmp(file, ".rt", ft_strlen(file)) != 0)
		return (0);
	return (1);
}
