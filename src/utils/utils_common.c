/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:49:02 by sohan             #+#    #+#             */
/*   Updated: 2022/08/26 11:33:10 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
#include <stdio.h>

int	to_rgb(t_color color)
{
	int	trgb;

	trgb = (int)color.x;
	trgb = trgb << 8;
	trgb = trgb | (int)color.y;
	trgb = trgb << 8;
	trgb = trgb | (int)color.z;
	return (trgb);
}

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

void	error_exit(char const *msg)
{
	ft_putendl_fd((char *)msg, 2);
	exit(1);
}

void	perror_exit(void)
{
	perror("Error");
	exit(1);
}
