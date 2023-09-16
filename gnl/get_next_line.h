/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:49:26 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/09/13 10:28:14 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*ft_line(char *rest);
void	ft_save(char *rest);
char	*ft_strfree(char *buff, char *str);
size_t	ft_strlenght(const char *str);
void	*ft_mset(void *s, int c, size_t n);
void	*ft_clloc(size_t num, size_t size);
char	*ft_join(char const *s1, char const *s2);
char	*ft_schr(const char *s, int c);

#endif
