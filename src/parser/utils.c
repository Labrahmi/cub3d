/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:37:51 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/09/14 20:47:29 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	free_2d_array(char **str)
{
	int i;
	
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

t_corMap	*init_corMap(char **map)
{
	t_corMap	*pos;
	char	*c;
	int		i;

	c = (char [4]) {'N', 'S', 'E', 'W'};
	pos = malloc(sizeof(t_corMap));
	pos->y = -1;
	while (map[++pos->y])
	{
		pos->x = -1;
		while (map[pos->y][++pos->x])
		{
			i = -1;
			while (++i < 4)
			{
				if (map[pos->y][pos->x] == c[i])
					return (pos);
			}
		}
	}
	return (FALSE);
}

int check_intruderInMap(char **map)
{
	int i;
	int j;
	int k;
	char	*c;

	c = (char [9]) {'N', 'S', 'E', 'W', ' ', '\n', '1', '0', '\t'};
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			k = -1;
			while (++k < 9)
			{
			   if (map[i][j] == c[k])
			   {
				   k = -1;
				   break;
			   }
			}
			if (k != -1)
				return (FALSE);
		}
	}
	return (TRUE);
}
