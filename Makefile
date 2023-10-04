# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 07:29:28 by ylabrahm          #+#    #+#              #
#    Updated: 2023/10/04 22:45:54 by ylabrahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## NAMES ##############
NAME	= cub3D
BONUS	= cub3D_bonus

INC		= inc 
IMLX	= -I $(HOME)/MLX42/include

########## COMMPILATION ##############
CC = cc
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
GLFW = -I include -lglfw -L"/goinfre/$(USER)/homebrew/opt/glfw/lib/"
ARCH = $(HOME)/MLX42/build/libmlx42.a
CFLAGS =  -Wall -Wextra -Werror 

######### SRCS & OBJS ###############
SRCDIR	 	=	src
OBJBON		=	objbonus
BONDIR		=	bonus
MANDIR		=	mandatory
PRSDIR		=	parser
OBJDIR		=	obj

SRCS		:=	main init draw_map draw_pixels draw_fov hooks draw_3d_walls \
				draw_3d_walls_tools move_player draw_map_tool draw_fov_tool
PARSERSRCS	:=	parser init_destroy_data_map check_errors utils utils_2 

SRC				:=      $(addprefix $(SRCDIR)/$(MANDIR)/, $(addsuffix .c, $(SRCS)))
OBJ             :=      $(addprefix $(OBJDIR)/$(MANDIR)/, $(addsuffix .o, $(SRCS)))
PARSEROBJ		:=		$(addprefix $(OBJDIR)/$(MANDIR)/$(PRSDIR)/, $(addsuffix .o, $(PARSERSRCS)))
PARSERSRC		:=		$(addprefix $(SRCDIR)/$(MANDIR)/$(PRSDIR)/, $(addsuffix .c, $(PARSERSRCS)))


SRCBONUS		:=      $(addprefix $(SRCDIR)/$(BONDIR)/, $(addsuffix .c, $(SRCS)))
OBJBONUS        :=      $(addprefix $(OBJBON)/$(BONDIR)/, $(addsuffix .o, $(SRCS)))
PARSEROBJBONUS	:=		$(addprefix $(OBJBON)/$(BONDIR)/$(PRSDIR)/, $(addsuffix .o, $(PARSERSRCS)))
PARSERSRCBONUS	:=		$(addprefix $(SRCDIR)/$(BONDIR)/$(PRSDIR)/, $(addsuffix .c, $(PARSERSRCS)))


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


AR_LIBFT        =       libft/libft.a
AR_GNL          =       gnl/get_next_line


#########	COMPILATION & FLAGS	##########e

all:	$(NAME)


$(OBJDIR)/%.o:	$(SRCDIR)/%.c 
	@printf "$(GREEN) compile >>>>> $(notdir $<) $(RESET)\n"
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(MANDIR)
	@mkdir -p $(OBJDIR)/$(MANDIR)/$(PRSDIR)
	@$(CC) $(CFLAGS) $< -c -I $(INC) $(IMLX) -o $@


$(OBJBON)/%.o:	$(SRCDIR)/%.c 
	@printf "$(GREEN) compile >>>>> $(notdir $<) $(RESET)\n"
	@mkdir -p $(OBJBON)
	@mkdir -p $(OBJBON)/$(BONDIR)
	@mkdir -p $(OBJBON)/$(BONDIR)/$(PRSDIR)
	@$(CC) $(CFLAGS) $< -c -I $(INC) $(IMLX) -o $@

$(NAME):	$(OBJ) $(PARSEROBJ)
	@$(C_LIBFT) -s
	@make -C libft bonus
	@echo "$(GREEN)$(BOLD)Creating >>>>>> $(AR_LIBFT)$(B_END)$(C_END)"
	@$(C_GNL) -s
	@echo "$(GREEN)$(BOLD)Creating >>>>>>>$(AR_GNL)$(B_END)$(C_END)"
	@$(C_MLX)
	@$(CC) $(CFLAGS) $(FRAMEWORKS) $(GLFW) $^ $(AR_LIBFT) $(AR_GNL) $(ARCH) -I $(INC) $(IMLX) -o $@
	@echo "  $(GREEN) $(BOLD) <<<<<< Done successful! >>>>>>$(B_END) $(C_END)"

bonus : $(BONUS)

$(BONUS):	$(OBJBONUS) $(PARSEROBJBONUS)
	@$(C_LIBFT) -s
	@make -C libft bonus
	@echo "$(GREEN)$(BOLD)Creating >>>>>> $(AR_LIBFT)$(B_END)$(C_END)"
	@$(C_GNL) -s
	@echo "$(GREEN)$(BOLD)Creating >>>>>>>$(AR_GNL)$(B_END)$(C_END)"
	@$(C_MLX)
	@$(CC) $(CFLAGS) $(FRAMEWORKS) $(GLFW) $^ $(AR_LIBFT) $(AR_GNL) $(ARCH) -I $(INC) $(IMLX) -o $@
	@echo "  $(GREEN) $(BOLD) <<<<<< Done successful! >>>>>>$(B_END) $(C_END)"

clean:
	@echo " $(RED)$(BOLD)REMOVED OBJECTS$(B_END)$(C_END)"
	@$(C_LIBFT) clean
	@$(C_GNL) clean
	@rm -rf $(OBJDIR)
	@rm -rf $(OBJBON)
	
fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS)
	@$(C_LIBFT) fclean
	@$(C_GNL) fclean
	@echo "$(RED)$(BOLD)removed $(AR_LIBFT)\nremoved $(NAME)$(B_END)$(C_END)"

re:	fclean all

.PHONY:	all clean fclean re
