/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:37:51 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/02 13:48:46 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d_array(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	set_dir_init(t_corMap *pos, char c)
{
	if (c == 'N')
		pos->dir = NORTH;
	if (c == 'S')
		pos->dir = SOUTH;
	if (c == 'E')
		pos->dir = EAST;
	if (c == 'W')
		pos->dir = WEST;
}

int	count_line_map(char *line, int fd)
{
	int		count;
	char	*tmp;

	count = 0;
	line = ft_strtrim(line, "\n");
	if (ft_strlen(line) > 0)
		count++;
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strtrim(line, "\n");
		if (ft_strlen(tmp) != 0 || (!ft_strlen(tmp) && count != 0))
			count++;
		free(line);
		free(tmp);
	}
	free(line);
	return (count);
}

t_corMap	*init_cor_map(char **map)
{
	t_corMap	*pos;
	char		*c;
	int			i;

	c = (char [4]){'N', 'S', 'E', 'W'};
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
				{
					map[pos->y][pos->x] = '0';
					set_dir_init(pos, c[i]);
					return (pos);
				}
			}
		}
	}
	return (FALSE);
}

int	check_intruder_map(char **map)
{
	int		i;
	int		j;
	int		k;
	char	*c;

	c = (char [4]){' ', '\n', '1', '0'};
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			k = -1;
			while (++k < 4)
			{
				if (map[i][j] == c[k])
					break ;
			}
			if (k >= 4)
				return (FALSE);
		}
	}
	return (TRUE);
}
