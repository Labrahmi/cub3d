# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 07:29:28 by ylabrahm          #+#    #+#              #
#    Updated: 2023/09/01 15:24:04 by ayakoubi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
INC		=	inc 
IMLX	= -I /Users/$(USER)/goinfre/MLX42/include/MLX42
########## COMMPILATION ##############

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
MLX = /Users/$(USER)/goinfre/MLX42/build/libmlx42.a
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
GLFW = -I include -lglfw -L"/goinfre/$(USER)/homebrew/opt/glfw/lib/"
# -L"/usr/local/Cellar/glfw" 
# -L"/goinfre/$(USER)/homebrew/opt/glfw/lib/"
#CFLAGS = -fsanitize=address -g #-Wall -Wextra -Werror
# -fsanitize=address
ARCH = /Users/$(USER)/goinfre/MLX42/build/libmlx42.a

######### SRCS & OBJS ###############

SRCDIR	=	src
OBJDIR	=	obj

SRC		:= main drawing_tools draw_map hooks

OBJ		:= $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRC)))
SRC		:=	$(addprefix $(SRCDIR)/, $(addsuffix .c , $(SRC)))

########### COLORS ################

RED = \033[1;31m
GREEN = \033[1;32m
SPLASH = \033[5m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RESET = \033[0m


C_LIBFT		=	make -C libft
C_PRINTF	=	make -C ft_printf
C_GNL		=	make -C gnl
AR_LIBFT	=	libft/libft.a
AR_PRINTF	=	ft_printf/libftprintf.a
AR_GNL		=	gnl/get_next_line

$(OBJDIR)/%.o:	$(SRCDIR)/%.c 
#	@echo "compile >>>>> $^"
	@printf "$(GREEN) compile >>>>> $(notdir $<) $(RESET)\n"
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFALGS) $< -c -I $(INC) $(IMLX) -o $@

all:	$(NAME)

$(NAME):	$(OBJ)
	@$(CC) $(CFLAGS) $(MLX) $(FRAMEWORKS) $(GLFW) $^ $(ARCH) -I $(INC) $(IMLX) -o $@
	@printf "\n\n$(SPLASH) $(RED)              ------------- Cub3D Ready -------------$(RESET)\n\n\n"

clean:
	@rm -rf *.o
	@rm -rf $(OBJDIR)
	
fclean: clean
	@rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
