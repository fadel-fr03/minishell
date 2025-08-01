# Variables
NAME := minishell
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
SRC_DIR := srcs
OBJ_DIR := objs
INC_DIR := incs
CFLAGS := -Wall -Wextra -Werror -g3 -O0 -DDEBUG -I$(INC_DIR)
LDFLAGS := -lreadline -lncurses
CC := gcc

# Sources and objects
SRCS := $(addprefix srcs/, AST.c AST1.c AST2.c AST3.c builtin_cd_utils.c builtin_cd.c builtin_echo.c builtin_history.c \
				builtin_env.c builtin_exit.c builtin_export_utils.c builtin_export.c builtin_pwd.c builtin_unset.c \
				char_utils.c debugging.c env_utils.c env_utils2.c execution1.c execution2.c execution3.c execution_helpers.c \
				execution4.c execution5.c execution6.c expand_vars.c expand_vars2.c expand_vars3.c expand_vars4.c \
				find_command.c increment_lvl.c init_data.c main.c main_helper.c redirect_builtin.c sort_env.c str_utils.c \
				str_utils2.c tokenization.c tokenization1.c tokenization2.c tokenization3.c tokens_utils.c ft_realloc.c history.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Targets
all: $(LIBFT) $(NAME)

# Compile libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Compile the project
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Clean object files and binary
fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Recompile everything
re: fclean all

.PHONY: all clean fclean re
