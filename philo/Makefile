# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkara2 <tkara2@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 11:36:41 by tkara2            #+#    #+#              #
#    Updated: 2024/09/15 13:19:14 by tkara2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCS_FILES	=	main.c \
				init_data.c \
				routine.c \
				monitor.c \
				print.c \
				check_philo.c \
				utils/ft_atoi.c \
				utils/check_arg.c \
				utils/free_utils.c \
				utils/ft_calloc.c \
				utils/time.c \

INC_FILE	=	philo.h

SRCS_PATH	=	srcs/
OBJS_PATH	=	.objs/
INC_PATH	=	include/

SRCS		=	$(addprefix $(SRCS_PATH), $(SRCS_FILES))
OBJS		=	$(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
INC			=	$(addprefix $(INC_PATH), $(INC_FILE))

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g3 -pthread -fsanitize=address -I$(INC_PATH)
RM			=	rm -rf

NORM_FLAG	=	-R CheckForbiddenSourceHeader -R CheckDefine

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_PATH)%.o:	%.c
	mkdir -p ${@D}
	$(CC) $(CFLAGS) -c $< -o $@

norm:
	@norminette $(NORM_FLAG) $(SRCS) $(INC)

clean:
	$(RM) $(OBJS_PATH)
	@echo "[DONE] Objects files deletion..."

fclean:	clean
	$(RM) $(NAME)
	@echo "[DONE] philo deletion..."

re:	fclean 
	make all
	@echo "[DONE] philo recompiled..."

.PHONY:	all clean fclean re norm