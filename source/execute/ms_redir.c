/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:18:20 by enolbas           #+#    #+#             */
/*   Updated: 2023/01/31 14:53:45 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

static int	g_redir(t_redir *redir, int status)
{
	int	infile;

	infile = -1;
	if (status == 11)
		infile = open("/tmp/heredoc", O_RDONLY);
	else if (status == 1)
		infile = open(redir->file, O_RDONLY);
	return (infile);
}

static int	d_redir(char *file, int status)
{
	int	outfile;

	outfile = -1;
	if (status == 22)
		outfile = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (status == 2)
		outfile = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (outfile);
}

static int	ft_redirect_in(t_node *node)
{
	t_redir	*redir;
	t_list	*r;
	int		res;

	res = 0;
	r = node->redir;
	while (r)
	{
		redir = r->content;
		if (redir->type == 1 || redir->type == 11)
		{
			res = g_redir(redir, redir->type);
			if (res > 0 && dup2(res, STDIN_FILENO) != -1)
				close(res);
			else if (ret_er(redir, res))
				return (-1);
		}
		r = r->next;
	}
	return (0);
}

static int	ft_redirect_out(t_node *node)
{
	t_redir	*redir;
	t_list	*r;
	int		res;

	res = 0;
	r = node->redir;
	while (r)
	{
		redir = r->content;
		if (redir->type == 2 || redir->type == 22)
		{
			res = d_redir(redir->file, redir->type);
			if (res > 0 && dup2(res, STDOUT_FILENO) != -1)
				close(res);
			else if (ret_er(redir, res))
				return (-1);
		}
		r = r->next;
	}
	return (0);
}

int	ms_redir(t_node *node)
{
	int	res;

	res = 0;
	if (ft_redirect_in(node) < 0)
		return (-1);
	else
		res ++;
	if (ft_redirect_out(node) < 0)
		return (-1);
	else
		res += 2;
	return (res);
}
