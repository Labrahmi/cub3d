/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:53:45 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/01 12:29:03 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_map(int fd, char *fileMap, t_data_maps *data)
{
	char	*line;
	int		pos;
	int		index;

	index = 0;
	pos = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (pos >= 6)
			break ;
		get_textures(line, data, &pos);
		if (get_color(line, data, &pos) == FALSE)
			return (FALSE);
		free(line);
		index++;
	}
	data->count = count_line_map(line, fd);
	free(line);
	close(fd);
	get_map(fileMap, data, index, data->count);
	return (TRUE);
}

void	get_textures(char *line, t_data_maps *data, int *pos)
{
	char	**tmp;

	line = ft_strtrim(line, " ");
	tmp = ft_split(line, ' ');
	if (!ft_strncmp(tmp[0], "NO", ft_strlen(tmp[0]))
		|| !ft_strncmp(tmp[0], "SO", ft_strlen(tmp[0]))
		|| !ft_strncmp(tmp[0], "WE", ft_strlen(tmp[0]))
		|| !ft_strncmp(tmp[0], "EA", ft_strlen(tmp[0])))
	{
		if (ft_strncmp(tmp[0], "NO", ft_strlen(tmp[0])) == 0)
			data->textures[0] = ft_strdup(line);
		else if (ft_strncmp(tmp[0], "SO", ft_strlen(tmp[0])) == 0)
			data->textures[1] = ft_strdup(line);
		else if (ft_strncmp(tmp[0], "WE", ft_strlen(tmp[0])) == 0)
			data->textures[2] = ft_strdup(line);
		else
			data->textures[3] = ft_strdup(line);
		(*pos)++;
	}
	free_2d_array(tmp);
	free(line);
}

int	get_color(char *line, t_data_maps *data, int *pos)
{
	char	**tmp;

	line = ft_strtrim(line, " ");
	tmp = ft_split(line, ' ');
	if (!ft_strncmp(tmp[0], "F", -1) || !ft_strncmp(tmp[0], "C", -1))
	{
		if (!ft_strncmp(tmp[0], "F", -1))
		{
			if (split_color(data, line, 'F') == FALSE)
				return (free(line), free_2d_array(tmp), FALSE);
		}
		else if (!ft_strncmp(tmp[0], "C", -1))
		{
			if (split_color(data, line, 'C') == FALSE)
				return (free(line), free_2d_array(tmp), FALSE);
		}
		(*pos)++;
	}
	return (free(line), free_2d_array(tmp), TRUE);
}

char	**fill_map(int fd, int count)
{
	char	*line;
	char	*tmp;
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (0);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strtrim(line, "\n");
		if (ft_strlen(tmp) || (!ft_strlen(tmp) && i != 0))
			map[i++] = ft_strdup(line);
		free(line);
		free(tmp);
	}
	free(line);
	map[i] = 0;
	return (map);
}

void	get_map(char *fileMap, t_data_maps *data, int pos, int count)
{
	int		i;
	char	*line;
	int		fd;

	fd = open(fileMap, O_RDONLY);
	i = -1;
	while (++i <= pos)
	{
		line = get_next_line(fd);
		free(line);
	}
	free(data->map);
	data->map = fill_map(fd, count);
	if (!data->map)
		destroy_data_map(data, FALSE);
}
