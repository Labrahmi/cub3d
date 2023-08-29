# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 07:29:28 by ylabrahm          #+#    #+#              #
#    Updated: 2023/08/29 07:53:17 by ylabrahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = src/main.c
OBJS := $(SRCS:.c=.o)
OBJS := $(addprefix obj/, $(OBJS))

CC = cc
RM = rm -f
MLX = /Users/$(USER)/goinfre/MLX42/build/libmlx42.a
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
GLFW = -Iinclude -lglfw -L"/goinfre/$(USER)/homebrew/opt/glfw/lib/"
# -fsanitize=address
# CFLAGS = -Wall -Wextra -Werror

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(FRAMEWORKS) $(GLFW) -o $(NAME)

obj/%.o: %.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) -rf obj/

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re