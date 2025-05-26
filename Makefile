# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enzuguem <enzuguem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 15:56:03 by enzuguem          #+#    #+#              #
#    Updated: 2025/05/06 16:15:19 by enzuguem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f
SRCS_DIR = srcs
SRCS = actions.c init.c main.c simulation.c utils.c utils2.c args.c
SRC = $(addprefix srcs/, $(SRCS))
OBJS = $(SRC:.c=.o)

all: $(NAME)
	@clear
	@echo "Compilation terminée ✅"
	@echo "Exemple de test : ./philo 5 800 200 200"

${NAME}: $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@echo "🧹 Objets supprimés"

fclean: clean
	@$(RM) $(NAME)
	@clear
	@echo "🗑️  Exécutable supprimé"

re: fclean all

.PHONY: all clean fclean re
