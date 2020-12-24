NAME = philo_one
SRCS = main.c\
       init.c\
       utils.c\
       philosopher.c

OBJS = $(SRCS:.c=.o)
CC = clang
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = philosophers.h
LDLIBS = -lpthread
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
