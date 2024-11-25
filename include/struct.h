/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:11:18 by enolbas           #+#    #+#             */
/*   Updated: 2023/01/31 17:33:37 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_type {
	WORD,
	SQUOTE,
	DQUOTE,
	DOLLAR,
	PIPE,
	ESPACE,
	DREDIR,
	DRREDIR,
	GREDIR,
	GRREDIR
}	t_type;

typedef struct s_redir {
	int				type;
	char			*file;
}	t_redir;

typedef struct s_map {
	int				key;
	char			*content;
	t_type			type;
	struct s_map	*next;
}	t_map;

typedef struct s_node {
	char			**args;
	t_list			*redir;
}	t_node;

typedef struct s_input {
	char				**env;
	t_ls				*export;
	char				*raw;
	int					*pids;
	int					fdin;
	int					fdout;
	t_map				*lexer;
	t_map				*parser;
	t_list				*ast;
	struct sigaction	*ssa;
}	t_input;

extern int	g_status;

#endif
