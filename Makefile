# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 14:36:04 by dcastor           #+#    #+#              #
#    Updated: 2025/06/21 14:39:32 by dcastor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================== #
#                                 CONFIGURATION                                  #
# ============================================================================== #

# 📛 Nom du programme
NAME := minishell
LIB_NAME := libft

# 📂 Répertoires
SRCS_DIR := srcs/
BUILD_DIR := build/
LIB_DIR := $(LIB_NAME)/
INCLUDE_DIRS := -I$(LIB_DIR)includes -Iincludes

# 📦 Compiler & Flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3

# 🛠 Utilitaires
MAKE := make
RM := rm -rf

# 📁 Sources & Objets
SRCS := $(addprefix $(SRCS_DIR), \
		builtins/env.c \
		builtins/exit.c \
		builtins/export.c\
		\
		executor/child.c \
		executor/exec_prepare.c \
		executor/executor.c \
		executor/heredoc.c \
		executor/pipe_setup.c \
		executor/redirection.c \
		executor/sequence_exec.c \
		executor/simple_exec.c \
		executor/expansion.c \
		\
		init/init_env.c \
		init/init.c \
		\
		input/tokenizer/token_factory.c \
		input/tokenizer/token_operator.c \
		input/tokenizer/token_special.c \
		input/tokenizer/token_utils.c \
		input/tokenizer/token_word.c \
		input/tokenizer/tokenizer.c \
		\
		input/syntax/syntax_and_or_command.c \
		input/syntax/syntax_command.c \
		input/syntax/syntax_pipeline.c \
		input/syntax/syntax_redirection.c \
		input/syntax/syntax_simple_command.c \
		input/syntax/syntax_subshell.c \
		input/syntax/syntax_utils.c \
		input/syntax/syntax.c \
		\
		input/read_command.c \
		input/parse_tokens.c \
		input/parse_helpers.c \
		\
		memory/garbage.c \
		\
		signals/signals.c \
		\
		utils/env_utils.c \
		utils/error.c \
		utils/fd_utils.c \
		utils/print_utils.c \
		\
		main.c \
)
OBJS := $(patsubst %.c, $(BUILD_DIR)%.o, $(SRCS))

DEPS := $(OBJS:.o=.d)

# 📚 Libft
LIB_FILE := $(LIB_DIR)libft.a

# ============================================================================== #
#                               RULES - BUILD FLOW                               #
# ============================================================================== #

# 🎯 Règle principale
all: $(NAME)

# 🧱 Construction de l'exécutable
$(NAME): $(BUILD_DIR) $(LIB_FILE) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(LIB_FILE) $(OBJS) $(INCLUDE_DIRS) -lreadline -lft -L$(LIB_DIR)

# 🔨 Compilation des .c vers .o
$(BUILD_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -g -MMD $(INCLUDE_DIRS) -c $< -o $@


# ============================================================================== #
#                            DIRECTORY & LIBRARY SETUP                           #
# ============================================================================== #

# 📁 Création du dossier de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 📚 Build libft.a
$(LIB_FILE): $(LIB_DIR)
	$(MAKE) -sC $(LIB_DIR)


# ============================================================================== #
#                                   CLEAN RULES                                  #
# ============================================================================== #

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# ============================================================================== #
#                                    TEST RULES                                  #
# ============================================================================== #

test_leak: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --log-fd=1 --trace-children=yes .$(NAME)

# ============================================================================== #
#                                  PHONY & DEPS                                  #
# ============================================================================== #

# 📌 Cibles qui ne sont pas des fichiers
.PHONY: all clean fclean re

# 📎 Inclusion des dépendances générées automatiquement
-include $(DEPS) $(DEPS_BONUS)
