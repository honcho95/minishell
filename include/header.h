/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:29:18 by enolbas           #+#    #+#             */
/*   Updated: 2023/01/31 15:49:46 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <termios.h>
# include <limits.h>

# include <stdbool.h>

# include <libft.h>
# include "./struct.h"

/* ************************************************************************** */
/*																			  */
/*   ../source/                    											  */
/*																			  */
/* ************************************************************************** */

void	free_input(t_input *input);
char	*ms_get_env(char *strchr, t_input *input);
char	**ms_get_env_start(char *strchr, t_input *input);
int		free_all(t_input *input);
int		str_chr_start_str(char *str, char *strchr);

/* ************************************************************************** */
/*																			  */
/*   ../source/start_main/            	                 					  */
/*																			  */
/* ************************************************************************** */

int		copy_env(char **strd, t_input *input);
int		copy_env_in_export(t_input *input);
void	init_input(t_input *input, char *line);
int		shlvl(t_input *input);

/* ************************************************************************** */
/*																			  */
/*   ../source/utils/                            							  */
/*																			  */
/* ************************************************************************** */

t_map	*map_last(t_map *lst);
t_map	*map_new(char *content, t_type type);
void	map_add(t_map **lst, t_map *new);
void	map_delone(t_map *lst, void (*del)(void*));
void	map_clear(t_map **lst, void (*del)(void *));

size_t	ft_strdlen(char **strd);
void	ft_strdfree(char **strd);
char	**ft_strdjoin(char **strd, char *s);
char	*ft_streplace(char *oldstr, char *newstr);
char	*ft_strjoin_free(char *s1, char *s2);

t_redir	*new_redir(int status, char *file);
t_node	*new_node(void);

/* ************************************************************************** */
/*																			  */
/*   ../source/execute/                             						  */
/*																			  */
/* ************************************************************************** */

char	*cmd_path_chr(char *cmd, t_input *input);
int		ft_cmd_error(t_list *cmd, char *message);
int		ms_redir(t_node *node);
void	ft_heredoc(char *file, char *limit);
void	exec_pipe(t_input *input, t_list *cmds, size_t size);
void	pipe_child(t_input *input, t_list *cmds, int fd[2]);
void	ft_close_pipes(int fd[2]);
void	execute(t_input *input);
void	check_cmd(t_input *input, t_list *cmds);
void	wait_pipes(int *pids, size_t size);
void	wait_exec(void);
int		ret_er(t_redir *redir, int res);

/* ************************************************************************** */
/*																			  */
/*   ../source/parser/            	                 						  */
/*																			  */
/* ************************************************************************** */

t_type	switch_type(char c);
void	split_delim(t_input *input, int *start, int index, t_type type);
int		split_redir(t_input *input, char *line, int index, t_type type);
int		split_quote(char *line, int index);
int		split_dollar(t_input *input, int index);
int		lexer_char_error(char content);
int		lexer_str_error(char *content);
int		lexer(t_input *input, char *line);

int		is_break(t_type type);

void	parser(t_input *input);
int		check_syntax(t_input *input);
void	ft_replace_quote(t_input *input);
char	*unquoted(t_input *input, char *word, int status);
char	*remove_quote_in_word(t_input *input,
			char *line, t_type type, int *start);
char	*replace_dollar(t_input *input, char *word, int *start, t_type type);
char	*find_in_env(char **env, char *var);

/* ************************************************************************** */
/*																			  */
/*   ../source/signal/                            							  */
/*																			  */
/* ************************************************************************** */

void	handler_on(int sig);
void	handler_off(int sig);
void	handler_herdoc(int sig);

/* ************************************************************************** */
/*																			  */
/*   ../source/builtin/                            							  */
/*																			  */
/* ************************************************************************** */

int		builtin_chr(t_node *node, t_input *input);
int		save_redir(t_node *node, t_input *input);
void	restore_redir(t_input *input, int redir);
int		ms_env(t_input *input);
int		ms_pwd(void);
int		ms_echo(char **str);
void	ms_exit(t_input *input, int exit_status);
int		ft_cd(t_input *input, char **args, int nb_arg);
void	ft_replace_varenv(char **env, char *var, char *newvar);

/*   EXPORT   *************************************************************** */
int		ms_export(char *var, t_input *input);
int		wrong_name_var(char *var);
char	*get_export(char *strchr, t_input *input);
int		show_export(t_input *input);
int		update_var(char *var, t_input *input);

/*   UNSET   **************************************************************** */
int		ms_unset(const char *var, t_input *input);
void	ls_clear_one_export(t_ls **lst, char *content);
char	**del_one_env(char *var, t_input *input);

#endif
