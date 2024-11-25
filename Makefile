# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 14:32:32 by tda-silv          #+#    #+#              #
#    Updated: 2022/12/17 04:44:06 by tda-silv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC_DIR		= source/
OBJ_DIR		= object/
INC_DIR		= include/
LIB_DIR		= libft/

CC			= cc

CFLAGS		= -Wall -Wextra -Werror
LDFLAGS_1	= -fsanitize=address -g
LDFLAGS_2	= -fsanitize=address -g -static-libasan -fsanitize=leak

# **************************************************************************** #
# -I | Chemin du dossier où trouver un .h									   #
# -L | Chemin du dossier où trouver un .a									   #
# -l | Nom du .a sans le préfixe "lib"										   #
# **************************************************************************** #

I_HEADERS	= -I $(INC_DIR) -I $(LIB_DIR) -I /opt/homebrew/opt/readline/include
L_LIB		= -L $(LIB_DIR) -l ft -l readline -L /opt/homebrew/opt/readline/lib

################################################################################

HEADERS		= ./include/header.h \
			  ./include/struct.h \

NAME_FILE	= $(addprefix builtin/,												\
					$(addprefix	  ms_export/,									\
			  								ms_export							\
											wrong_name_var						\
											get_export							\
											show_export							\
											update_var							\
					)															\
					$(addprefix	  ms_unset/,									\
			  								ms_unset							\
											ls_clear_one_export					\
											del_one_env							\
					)															\
								  ms_echo										\
								  ms_env										\
								  ms_pwd										\
								  builtin_chr									\
								  ms_exit										\
								  ft_cd											\
								  ft_clone_redir								\
								  ft_replace_varenv								\
																				\
			  )																	\
			  $(addprefix utils/,												\
			  					map_utils										\
			  					ast_utils										\
			  					str_utils										\
			  )																	\
			  $(addprefix parser/,												\
			  					 parser											\
								 check_syntax									\
								 syntax_error									\
								 expand											\
								 lexer											\
								 splits											\
								 unquote										\
			  )																	\
			  $(addprefix execute/,												\
			  					  cmd_path_chr									\
								  ft_cmd_error									\
								  ms_redir										\
								  ms_pipe										\
								  execute_cmd									\
								  execute_one_cmd								\
								  ret_er										\
			  )																	\
			  $(addprefix start_main/,											\
			  						 copy_env_in_export							\
									 copy_env									\
									 init_input									\
									 shlvl										\
			  )																	\
			  $(addprefix signal/,												\
			  					 handler_on										\
								 handler_off									\
								 handler_herdoc									\
			  )																	\
			  minishell															\
			  free_input														\
			  ms_get_env														\
			  ms_get_env_start													\
			  free_all															\
			  str_chr_start_str													\

SRC			= $(addsuffix .c, $(addprefix $(SRC_DIR), $(NAME_FILE)))
OBJ			= $(addsuffix .o, $(addprefix $(OBJ_DIR), $(NAME_FILE)))

################################################################################

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(I_HEADERS) -c $< -o $@

all: $(NAME) $(HEADERS)

$(NAME): $(OBJ)
	@cd libft; make bonus; cd ..
	$(CC) $(OBJ) $(I_HEADERS) $(L_LIB) -o $(NAME)

################################################################################

valgrind: $(OBJ)
	valgrind --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all --suppressions=readline_leaks --track-fds=yes ./$(NAME)

fsanitize1: $(OBJ)
	@cd libft; make bonus; cd ..
	$(CC) $(LDFLAGS_1) $(OBJ) $(I_HEADERS) $(L_LIB) -o $(NAME)

fsanitize2: $(OBJ)
	@cd libft; make bonus; cd ..
	$(CC) $(LDFLAGS_2) $(OBJ) $(I_HEADERS) $(L_LIB) -o $(NAME)

################################################################################

clean:
	cd libft; make clean
	rm -rf $(OBJ_DIR)

fclean: clean
	cd libft; make fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all valgrind fsanitize1 fsanitize2 clean fclean re
