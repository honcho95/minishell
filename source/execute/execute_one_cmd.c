/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:00:55 by enolbas           #+#    #+#             */
/*   Updated: 2023/01/11 19:17:13 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

static void	exec_cmd(t_input *input, t_list *cmds, char *command);
static int	ft_execve(t_input *input, t_list *cmds, char *command);

void	check_cmd(t_input *input, t_list *cmds)
{
	char	*command;
	t_node	*node;

	command = NULL;
	node = cmds->content;
	if (builtin_chr(node, input))
		return ;
	if (node->args && node->args[0])
		command = cmd_path_chr(node->args[0], input);
	exec_cmd(input, cmds, command);
	if (!command)
	{
		if (node->args && node->args[0])
		{
			ft_putstr_fd(node->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		g_status = 127;
	}
	free(command);
}

static void	exec_cmd(t_input *input, t_list *cmds, char *command)
{
	int		pid;
	t_node	*node;

	node = cmds->content;
	pid = fork();
	if (pid < 0)
	{
		ft_cmd_error(NULL, "fork");
		free_all(input);
		free_input(input);
		return ;
	}
	if (pid == 0)
	{
		if (ms_redir(node) >= 0)
			ft_execve(input, cmds, command);
		free_all(input);
		free_input(input);
		free(command);
		exit(1);
	}
	wait_exec();
}

void	wait_exec(void)
{
	int	status;

	status = 0;
	wait(&status);
	if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
			ft_putstr_fd("Quit (core dumped)\n", 2);
		g_status = WTERMSIG(status) + 128;
	}
	if (WIFEXITED(status) == 1)
		g_status = WEXITSTATUS(status);
}

static int	ft_execve(t_input *input, t_list *cmds, char *command)
{
	t_node	*node;

	node = cmds->content;
	if (!node->args || !node->args[0])
		return (0);
	if (command && access(command, F_OK | X_OK) == 0)
	{
		if (execve(command, node->args, input->env) == -1)
		{
			return (ft_cmd_error(NULL, node->args[0]));
		}
	}
	return (1);
}
