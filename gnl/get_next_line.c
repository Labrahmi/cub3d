/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:45:40 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/09/13 10:27:30 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strfree(char *buffer, char *s)
{
	char	*tmp;

	tmp = ft_join(buffer, s);
	if (!tmp)
		return (NULL);
	free(buffer);
	return (tmp);
}

char	*fill_gnl(int fd, char *rest)
{
	int		ret;
	char	*buff;

	buff = ft_clloc(BUFFER_SIZE + 1, 1);
	if (!buff)
		return (0);
	ret = 1;
	while (ret > 0 && !ft_schr(buff, '\n'))
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0 || (ret == 0 && rest == NULL))
			return (free(buff), NULL);
		buff[ret] = '\0';
		rest = ft_strfree(rest, buff);
	}
	free(buff);
	return (rest);
}

char	*ft_line(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	line = ft_clloc(i + 2, 1);
	if (!line)
		return (0);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i])
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

void	ft_save(char *rest)
{
	char	*buff;
	int		i;
	int		j;

	buff = rest;
	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == 0 || (buff[i] == '\n' && buff[i + 1] == 0))
	{
		rest[0] = 0;
		return ;
	}
	j = 0;
	while (buff[++i])
	{
		rest[j++] = buff[i];
	}
	rest[j] = 0;
}

char	*get_next_line(int fd)
{
	char		*tmp;
	static char	rest[BUFFER_SIZE];
	char		*line;
	int			i;

	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (rest[0] = 0, NULL);
	tmp = ft_clloc(ft_strlenght(rest) + 1, 1);
	i = -1;
	while (rest[++i])
		tmp[i] = rest[i];
	if (!ft_schr(tmp, '\n'))
		tmp = fill_gnl(fd, tmp);
	if (!tmp[0])
		return (free(tmp), NULL);
	line = ft_line(tmp);
	ft_save(tmp);
	i = -1;
	while (tmp[++i])
		rest[i] = tmp[i];
	rest[i] = '\0';
	free(tmp);
	return (line);
}
