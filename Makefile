NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra -O2 -ggdb3

COMPILE = $(CC) $(CFLAGS)

LIB = ar -rcs $(NAME)

MAKE = make

RM_RF = rm -rf

LIBRARIES = -lft -L$(LIBFT_DIRECTORY) -lreadline -L/usr/local/opt/readline/lib/

LIBFT_DIRECTORY = ./libft/
LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

HEADERS_LIST = minishell.h
HEADERS_DIRECTORY = ./inc/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I/usr/local/opt/readline/include/

SOURCES_DIRECTORY = ./srcs/

SOURCES_LIST =	main.c signals.c parse.c parse_utils.c get_env.c free.c utils.c cmd.c 	\
				cmd_args.c redir_filepath.c utils_1.c utils_2.c utils_3.c	exec.c		\
				builtin_utils.c	exec_cmd.c	exec_utils.c	redir.c

OBJECTS_DIRECTORY = ./objs/

OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))

OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

CREATING = \033[90m[\033[0;33mCreating\033[90m]\033[0;33m
OK = \033[90m[\033[32mOK\033[90m]\033[34m
SUCCESS = \033[90m[\033[32mSuccess\033[90m]\033[0;32m
DELETE = \033[90m[\033[91mDeleting\033[90m]\033[31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@$(COMPILE) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)

$(OBJECTS_DIRECTORY):
	@echo "$(CREATING) $(NAME)...$(RESET)"
	@mkdir $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o: $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(COMPILE) -c $(INCLUDES) $< -o $@
	@echo "$(OK) $@$(RESET)"

$(LIBFT):
	@echo "$(CREATING) $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(RM_RF) $(OBJECTS_DIRECTORY)
	@echo "$(DELETE) $(OBJECTS_DIRECTORY)$(RESET)"
	@echo "$(DELETE) object files deleted$(RESET)"

fclean: clean
	@$(RM_RF) $(LIBFT)
	@echo "$(DELETE) $(LIBFT)$(RESET)"
	@$(RM_RF) $(NAME)
	@$(RM_RF) $(BONUS)
	@echo "$(DELETE) ./$(NAME)$(RESET)"
	@echo "$(DELETE) ./$(BONUS)$(RESET)"

re: fclean all

.PHONY: all clean fclean re