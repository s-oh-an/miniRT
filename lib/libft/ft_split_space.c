/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:34:37 by sohan             #+#    #+#             */
/*   Updated: 2022/08/06 15:44:03 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *str)
{
	int	word_count;

	word_count = 0;
	while (*str)
	{
		while (!ft_isspace(*str) && *str)
			str++;
		if (!ft_isspace(*(str - 1)))
		{
			word_count++;
		}
		if (*str == '\0')
			break ;
		str++;
	}
	return (word_count);
}

static int	count_word_len(const char *str)
{
	int	word_len;

	word_len = 0;
	while (!ft_isspace(*str) && *str)
	{
		str++;
		word_len++;
	}
	return (word_len);
}

static const char	*put_words(char **strs, const char *str, int i)
{
	int	j;

	j = 0;
	while (!ft_isspace(*str) && *str)
	{
		strs[i][j] = *str;
		j++;
		str++;
	}
	strs[i][j] = '\0';
	while (ft_isspace(*str))
		str++;
	return (str);
}

static void	free_memory(char **strs, int i)
{
	int	index;

	index = 0;
	while (index <= i)
	{
		free(strs[index]);
		index++;
	}
	free(strs);
}

char	**ft_split_space(const char *str)
{
	char	**strs;
	int		i;
	int		num_word;

	strs = 0;
	i = 0;
	while (ft_isspace(*str) && *str)
		str++;
	num_word = count_word(str);
	strs = (char **)ft_calloc(num_word + 1, sizeof(char *));
	if (strs == 0)
		return (0);
	while (i < num_word)
	{
		strs[i] = (char *)ft_calloc(count_word_len(str) + 1, sizeof(char));
		if (strs[i] == 0)
		{
			free_memory(strs, i);
			return (0);
		}
		str = put_words(strs, str, i);
		i++;
	}
	return (strs);
}
