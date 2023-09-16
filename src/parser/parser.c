/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:53:45 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/09/14 11:14:29 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_map(int fd, char *fileMap, t_data_maps *data)
{
	char *line;
	int pos;
	int count;

	pos = 0;
	count = 0;
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			break;
			free(line);
		}
		if (pos >= 6)
		{
			count = count_line_map(line, fd);
			break;
		}
		get_textures(line, data, &pos);
		if (get_color(line, data, &pos) == FALSE)
			return (FALSE);
		free(line);
	}
	close(fd);
	if (pos >= 6)
		get_map(fileMap, data, pos, count);
	return (TRUE);
}

void	get_textures(char *line, t_data_maps *data, int *pos)
{
	char	**tmp;
	int i;

	line = ft_strtrim(line, " ");
	tmp = ft_split(line, ' ');
	if (!ft_strncmp(tmp[0], "NO", ft_strlen(tmp[0])) || !ft_strncmp(tmp[0], "SO", ft_strlen(tmp[0]))
	   	|| !ft_strncmp(tmp[0], "WE", ft_strlen(tmp[0])) || !ft_strncmp(tmp[0], "EA", ft_strlen(tmp[0])))
	{
		i = (ft_strncmp(tmp[0], "NO", ft_strlen(tmp[0])) == 0) ? 0 : 
			(ft_strncmp(tmp[0], "SO", ft_strlen(tmp[0])) == 0) ? 1 : 
			(ft_strncmp(tmp[0], "WE", ft_strlen(tmp[0])) == 0) ? 2 : 3;
		data->textures[i] = ft_strdup(line);
		(*pos)++;
	}
	free(tmp);
	free(line);
}


int	check_input(char	**str)
{
	int	i;
	int j;

	i = -1;
	while (str[++i])
	{
		//str[i] = ft_strtrim(str[i], "\n");
		j = -1;
		while (str[i][++j])
		{
			if (str[i][0] == '\n')
				return (FALSE);
			if (str[i][j] != '\n' && (str[i][j] < '0' || str[i][j] > '9'))
				return (FALSE);
		}
	}
	return (TRUE);
}	

int	get_color(char *line, t_data_maps *data, int *pos)
{
	int i;
	char **tmp;
	
	line = ft_strtrim(line, " ");
	tmp = ft_split(line, ' ');
	if (!ft_strncmp(tmp[0], "F", -1) || !ft_strncmp(tmp[0], "C", -1))
	{
		if (!ft_strncmp(tmp[0], "F", -1))
		{
			i = -1;	
			line = ft_strtrim(line, "F ");
			tmp = ft_split(line, ',');
			if (check_input(tmp) == FALSE)
				return (FALSE);
			while (++i < 3)
			{
				if ((i == 2 && tmp[i + 1]) || (i < 2 && !tmp[i])) 
					return (FALSE);
				if (tmp[i])
					data->F[i] = ft_atoi(tmp[i]);
			}
		}
		else if (!ft_strncmp(tmp[0], "C", -1))
		{
			i = -1;
			line = ft_strtrim(line, "C ");
			tmp = ft_split(line, ',');
			if (check_input(tmp) == FALSE)
				return (FALSE);
			while (++i < 3)
			{
				if ((i == 2 && tmp[i + 1]) || (i < 2 && !tmp[i]))
						return (FALSE);
				if (tmp[i])
					data->C[i] = ft_atoi(tmp[i]);
			}
		}
		(*pos)++;
		free(tmp);
	}
	return (TRUE);
}

int	count_line_map(char *line, int fd)
{
	int count;
	char *tmp;

	count = 0;
	line = ft_strtrim(line, "\n");
	if (ft_strlen(line) > 0)
		count++;
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		tmp = ft_strtrim(line, "\n");
		if (ft_strlen(tmp) != 0 || (!ft_strlen(tmp) && count != 0))
			count++;
		free(line);
		free(tmp);
	}
	free(line);
	return (count);
	
}


void	get_map(char *fileMap, t_data_maps *data, int pos, int count)
{
	int i;
	char	*tmp;
	char	*line;
	int	fd;

	fd = open(fileMap, O_RDONLY);
	i = -1;
	while (++i <= pos)
	{
		line = get_next_line(fd);
		free(line);
	}
	data->map = malloc(sizeof(char *) * (count + 1));
	if (!data->map)
		exit(1);
	line = get_next_line(fd);
	free(line);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		tmp = ft_strtrim(line, "\n");
		if (ft_strlen(tmp) || (!ft_strlen(line) && i != 0))
			data->map[i++] = ft_strdup(line);
		free(line);
		free(tmp);
	}
	data->map[i] = 0;
	free(line);
}

