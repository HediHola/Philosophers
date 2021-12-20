# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htizi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/12 15:14:35 by htizi             #+#    #+#              #
#    Updated: 2021/12/20 14:22:40 by htizi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		philo
INC_DIR			=		./inc/
SRCS_DIR		=		./srcs/
SRCS			=		main.c			\
						init.c			\
						thread.c		\
						routine.c		\
						time.c

SRCS_BASENAME	=		$(addprefix $(SRCS_DIR), $(SRCS))
OBJS			=		$(SRCS_BASENAME:.c=.o)
CC				=		clang
FLAGS			=		-Werror -Wall -Wextra -I $(INC_DIR) 

.c.o			:
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all				:	$(NAME)

$(NAME)			:	$(OBJS)
				$(CC) $(FLAGS) -o $(NAME) $(OBJS)  -lpthread
				@echo [$(NAME)] : Created !

clean			:
				rm -rf $(OBJS)
				@echo "[OBJS] Deleted"

fclean			:	clean
				rm -f $(NAME)
				@echo "[$(NAME)]: Deleted"

re				:	fclean all
