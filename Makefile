# **************************************************************************** #
#									       #
#							  :::	   ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#						      +:+ +:+	      +:+      #
#    By: marcosv2 <marcosv2@student.42.rio>	    +#+  +:+	   +#+	       #
#						  +#+#+#+#+#+	+#+	       #
#    Created: 2024/01/20 00:36:02 by marcosv2	       #+#    #+#	       #
#    Updated: 2024/01/20 00:36:08 by marcosv2         ###   ########.fr        #
#									       #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -g

Y = \033[38;5;99m
R = \033[38;5;93m
G = \033[38;5;40m
B = \033[38;5;32m
X = \033[0m

CFILES = src/main.c src/utils/init.c src/utils/utils.c \
			src/utils/threads.c src/utils/actions.c \

OBJECTS = $(CFILES:.c=.o)

all: $(NAME)

%.o : %.c
	@printf "$(Y)Compiling [$<]...$(X)\r"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJECTS)
	@printf "$(Y)Compiling [$(CFILES)]...$(X)\n"
	@printf "$(Y)Compiling [$(NAME)]...$(X)\n"
	@$(CC) $(CFLAGS) $(LIBFT_LIB) $(PRINTF_LIB) $(OBJECTS) -o $(NAME)
	@printf "$(G)Finished [$(NAME)]$(X)\n"

clean:
	@rm -rf $(OBJECTS)
	@printf "$(R)Removed [$(OBJECTS)]$(X)\n"
	@printf "$(R)Removed libraries.o$(X)\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(R)Removed [$(NAME)]$(X)\n"

re: fclean all

norm:
	norminette ft_printf utils checker

#run:	all

.PHONY: all clean fclean re norm
