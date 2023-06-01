# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 16:36:04 by jhesso            #+#    #+#              #
#    Updated: 2023/06/01 15:38:08 by jhesso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CFLAGS		=	-Wall -Wextra -Werror
LIBFT		=	libft.a
LIBFT_DIR	=	libft/
SRC_PATH	=	src/
OBJ_PATH	=	obj/
SRC			=	error.c file.c init.c pipex.c utils.c path.c
SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))
INCS		=	-I includes/

# pretty colors for the messages
GREEN			=	\033[0;32m
RED				=	\033[0;31m
BLUE			=	\033[0;34m
RESET			=	\033[0m

all: libft $(OBJ_PATH) $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@cc $(CFLAGS) -c $< -o $@ $(INCS)

$(NAME): $(OBJS) libft
	@echo "$(BLUE)Compiling $(NAME)$(RESET)"
	@cc $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft
	@echo "$(GREEN)done$(RESET)"

clean:
	@echo "$(RED)removing object files$(RESET)"
	@/bin/rm $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)cleaning all compiled stuff.. :)$(RESET)"
	@/bin/rm $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@/bin/rm -rf $(OBJ_PATH)
	@echo "$(RED)done$(RESET)"

re: fclean all

.PHONY: all libft clean fclean re
