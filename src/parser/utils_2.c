/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:04:38 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/04 09:45:58 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_input_colors(char	**str)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		j = -1;
		tmp = ft_strtrim(str[i], " ");
		while (tmp[++j])
		{
			if (tmp[0] == '\n')
				return (free(tmp), FALSE);
			if (tmp[j] != '\n' && (tmp[j] < '0' || tmp[j] > '9'))
				return (free(tmp), FALSE);
		}
		free(tmp);
	}
	return (TRUE);
}

int	split_color(t_data_maps *data, char *line, char c)
{
	int		i;
	char	**tmp;

	i = -1;
	line = ft_strdup(&line[1]);
	tmp = ft_split(line, ',');
	if (check_input_colors(tmp) == FALSE)
		return (free(line), free_2d_array(tmp), FALSE);
	while (++i < 3)
	{
		if ((i == 2 && tmp[i + 1]) || (i < 2 && !tmp[i]))
			return (free(line), free_2d_array(tmp), FALSE);
		if (tmp[i])
		{
			if (c == 'F')
				data->f[i] = ft_atoi(tmp[i]);
			else
				data->c[i] = ft_atoi(tmp[i]);
		}
	}
	return (free(line), free_2d_array(tmp), TRUE);
}

int	supp_check_path(char **textures, int start, int len, int i)
{
	char	*new;
	char	**tmp;

	if (textures[i][start] == '.')
	{
		new = ft_substr(textures[i], start, len - 1);
		if (ft_strncmp(new, ".png", 4) != 0)
			return (free(new), FALSE);
		tmp = ft_split(textures[i], ' ');
		free(textures[i]);
		free(new);
		textures[i] = ft_strtrim(tmp[1], "\n");
		free_2d_array(tmp);
		return (TRUE);
	}
	return (2);
}

int	loop_for_map(char **map, int count)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (aspects_zero(map, i, j, count) == FALSE)
				return (FALSE);
		}
	}
	return (TRUE);
}

int	aspects_zero(char **map, int i, int j, int count)
{
	if (map[i][j] == '0')
	{
		if (i == 0 || j == 0 || i == count - 1
			|| j == (int) ft_strlen(map[i]) - 2)
			return (FALSE);
		if (j > (int) ft_strlen(map[i + 1]) || j > (int) ft_strlen(map[i - 1]))
			return (FALSE);
		if (map[i + 1][j] != '0' && map[i + 1][j] != '1')
			return (FALSE);
		if (map[i - 1][j] != '0' && map[i - 1][j] != '1')
			return (FALSE);
		if (map[i][j + 1] != '0' && map[i][j + 1] != '1')
			return (FALSE);
		if (map[i][j - 1] != '0' && map[i][j - 1] != '1')
			return (FALSE);
	}
	return (TRUE);
}
