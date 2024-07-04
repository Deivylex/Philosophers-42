# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 14:49:23 by dzurita           #+#    #+#              #
#    Updated: 2024/07/03 14:59:44 by dzurita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------Archive--------------------------------------#
NAME = philo

#---------------------------------Flags----------------------------------------#
CC = @cc
CFLAGS = -Wall -Wextra -Werror
RM = @rm -rf

#---------------------------------Source Files---------------------------------#
SRC_FLS = init.c main.c times.c philo_utils.c philo_simulation.c \
	      simulation_utils.c \

#---------------------------------Colours--------------------------------------#
GREEN= \033[1;32m
CYAN= \033[1;36m
RED=\033[0;31m
END= \033[0m

#---------------------------------Rules----------------------------------------#
all: $(NAME)

OBJS = $(SRC_FLS:.c=.o)

$(NAME): $(OBJS)
	@echo "${RED}Compiling Philosophers${END}"
	$(CC) $(CFLAGS) $(OBJS) -o $@ 
	@echo "${GREEN}Philosophers Compiled Successfully${END}"

clean:
	$(RM) $(OBJS)
	@echo "${GREEN}Philosophers Cleaned${END}"

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re