/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:19:12 by enolbas           #+#    #+#             */
/*   Updated: 2023/01/31 17:00:58 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	error_msg(char *target, int nb_args);

static int	ft_cderror(void)
{
	perror("cd");
	return (1);
}

static char	*ft_chr_env(char **env, char *var)
{
	size_t	count;
	size_t	len;

	count = 0;
	if (!env)
		return (NULL);
	len = ft_strlen(var);
	while (env[count])
	{
		if (!ft_strncmp(var, env[count], len) && env[count][len] == '=')
		{
			return (env[count] + len + 1);
		}
		count ++;
	}
	return (NULL);
}

static char	*get_target(t_input *input, char **args, int nb_args)
{
	char	*target;

	target = NULL;
	if (nb_args == 1)
		target = ft_chr_env(input->env, "HOME");
	else if (nb_args == 2)
	{
		if (!my_strcmp(args[1], "-"))
		{
			target = ft_chr_env(input->env, "OLDPWD");
			if (target)
				ft_printf("%s\n", target);
		}
		else
			target = args[1];
	}
	else
	{
		ft_cderror();
		return (NULL);
	}
	error_msg(target, nb_args);
	return (target);
}

static void	error_msg(char *target, int nb_args)
{
	if (!target && nb_args == 1)
		ft_putstr_fd("cd: HOME not set\n", 2);
	else if (!target)
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
}

int	ft_cd(t_input *input, char **args, int nb_arg)
{
	char	cdd[PATH_MAX];
	char	*target;

	target = get_target(input, args, nb_arg);
	if (!target)
		return (1);
	getcwd(cdd, PATH_MAX);
	if (chdir(target) != 0)
		return (ft_cderror());
	ft_replace_varenv(input->env, "OLDPWD", cdd);
	ft_replace_varenv(input->env, "PWD", getcwd(cdd, PATH_MAX));
	return (0);
}
