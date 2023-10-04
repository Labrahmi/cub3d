# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 07:29:28 by ylabrahm          #+#    #+#              #
#    Updated: 2023/10/04 19:44:23 by ylabrahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## NAMES ##############
NAME	= cub3D
INC		= inc 
IMLX	= -I $(HOME)/MLX42/include

########## COMMPILATION ##############
CC = cc
MLX = $(HOME)/MLX42/build/libmlx42.a
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
GLFW = -I include -lglfw -L"/goinfre/$(USER)/homebrew/opt/glfw/lib/"
ARCH = $(HOME)/MLX42/build/libmlx42.a
CFLAGS =  -Wall -Wextra -Werror

######### SRCS & OBJS ###############
SRCDIR	 	=	src
PRSDIR		=	parser
OBJDIR		=	obj

SRCS		:=	main init draw_map draw_pixels draw_fov hooks draw_3d_walls \
				draw_3d_walls_tools move_player draw_map_tool draw_fov_tool
PARSERSRC	:=	parser init_destroy_data_map check_errors utils utils_2 

SRC				:=      $(addprefix $(SRCDIR)/, $(addsuffix .c, $(SRCS)))
OBJ             :=      $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))
PARSEROBJ		:=		$(addprefix $(OBJDIR)/$(PRSDIR)/, $(addsuffix .o, $(PARSERSRC)))
PARSERSRC		:=		$(addprefix $(SRCDIR)/$(PRSDIR)/, $(addsuffix .c, $(PARSERSRC)))

########### COLORS ################

RED = \033[1;31m
GREEN = \033[1;32m
SPLASH = \033[5m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RESET = \033[0m


#########	UTILES	###########

C_LIBFT         =       make -C libft
C_GNL           =       make -C gnl
C_MLX		=	#make -C mlx

AR_LIBFT        =       libft/libft.a
AR_GNL          =       gnl/get_next_line
AR_MLX		=#	mlx/libmlx.a

#########	COMPILATION & FLAGS	##########e

all:	$(NAME)


$(OBJDIR)/%.o:	$(SRCDIR)/%.c 
	@printf "$(GREEN) compile >>>>> $(notdir $<) $(RESET)\n"
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(PRSDIR)
	@$(CC) $(CFLAGS) $< -c -I $(INC) $(IMLX) -o $@


$(NAME):	$(OBJ) $(PARSEROBJ)
	@$(C_LIBFT) -s
	@make -C libft bonus
	@echo "$(GREEN)$(BOLD)Creating >>>>>> $(AR_LIBFT)$(B_END)$(C_END)"
	@$(C_GNL) -s
	@echo "$(GREEN)$(BOLD)Creating >>>>>>>$(AR_GNL)$(B_END)$(C_END)"
	@$(C_MLX)
	@$(CC) $(CFLAGS) $(MLX) $(FRAMEWORKS) $(GLFW) $^ $(AR_LIBFT) $(AR_GNL) $(ARCH) -I $(INC) $(IMLX) -o $@
	@echo "  $(GREEN) $(BOLD) <<<<<< Done successful! >>>>>>$(B_END) $(C_END)"

clean:
	@echo " $(RED)$(BOLD)REMOVED OBJECTS$(B_END)$(C_END)"
	@$(C_LIBFT) clean
	@$(C_GNL) clean
	@rm -rf $(OBJDIR)
	
fclean: clean
	@rm -rf $(NAME)
	@$(C_LIBFT) fclean
	@$(C_GNL) fclean
	@echo "$(RED)$(BOLD)removed $(AR_LIBFT)\nremoved $(NAME)$(B_END)$(C_END)"

re:	fclean all

.PHONY:	all clean fclean re
