# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/09 14:39:04 by jhesso            #+#    #+#              #
#    Updated: 2023/06/09 18:05:58 by jhesso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex
CFLAGS			=	-Wall -Wextra -Werror
SRC_PATH		=	src/
BONUS_PATH		=	src/bonus/
OBJ_PATH		=	obj/
BONUS_OBJ_PATH	=	obj/bonus/
SRC				=	error.c file.c init.c pipex.c utils.c path.c
BONUS_SRC		=	error_bonus.c file_bonus.c init_bonus.c pipex_bonus.c\
					utils_bonus.c path_bonus.c
SRCS			=	$(addprefix $(SRC_PATH), $(SRC))
SRCS_BONUS		=	$(addprefix $(BONUS_PATH), $(BONUS_SRC))
OBJ				=	$(SRC:.c=.o)
BONUS_OBJ		=	$(BONUS_SRC:.c=.o)
OBJS			=	$(addprefix $(OBJ_PATH), $(OBJ))
OBJS_BONUS		=	$(addprefix $(BONUS_OBJ_PATH), $(BONUS_OBJ))
INCS			=	-I includes/

# Libft files and directories
LIBFT			=	libft.a
LIBFT_DIR		=	libft/

# pretty colors for the messages
GREEN			=	\033[0;32m
RED				=	\033[0;31m
BLUE			=	\033[0;34m
RESET			=	\033[0m

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@cc $(CFLAGS) -c $< -o $@ $(INCS)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft

$(LIBFT):
	make -C $(LIBFT_DIR)

$(BONUS_OBJ_PATH):
	@mkdir $(BONUS_OBJ_PATH)

$(BONUS_OBJ_PATH)%.o: $(BONUS_PATH)%.c
	@cc $(CFLAGS) -c $< -o $@ $(INCS)

bonus: libft $(OBJ_PATH) $(BONUS_OBJ_PATH)

bonus_done: $(OBJS_BONUS) libft .done
	@echo "$(BLUE)Compiling bonuses$(RESET)"
	@cc $(CFLAGS) $(OBJS_BONUS) -o $(NAME) -L$(LIBFT_DIR) -lft
	@touch $(BONUS_OBJ_PATH).done
	@echo "$(GREEN)done$(RESET)"

clean:
	@echo "$(RED)removing object files$(RESET)"
	@/bin/rm -rf $(OBJ_PATH)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)cleaning all compiled stuff.. :)$(RESET)"
	@/bin/rm $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)done$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
