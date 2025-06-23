/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 19:05:44 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/06/23 19:05:44 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*find_env(t_envp *env, const char *key)
{
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->value, key, len) == 0 && env->value[len] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void	update_env_var(t_envp *env, const char *key, const char *newval)
{
	t_envp	*node;
	char	*tmp;

	node = find_env(env, key);
	if (!node)
		return ;
	tmp = ft_strjoin(key, "=");
	free(node->value);
	node->value = ft_strjoin(tmp, newval);
	free(tmp);
}

static void	update_pwd_oldpwd(t_envp *env, const char *oldpwd)
{
	char	cwd[4096];

	update_env_var(env, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(env, "PWD", cwd);
}

static int	cd_target(t_envp *env, char **args, char **target)
{
	t_envp	*home;
	t_envp	*oldpwd;

	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		home = find_env(env, "HOME");
		if (!home)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		*target = home->value + 5;
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		oldpwd = find_env(env, "OLDPWD");
		if (!oldpwd)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
		*target = oldpwd->value + 7;
		ft_putstr_fd(*target, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		*target = args[1];
	return (0);
}

int	ft_cd(t_minishell *minishell, char **args)
{
	char	cwd[4096];
	char	*target;
	t_envp	*env;

	target = NULL;
	env = minishell->envp;
	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	if (cd_target(env, args, &target))
		return (1);
	if (chdir(target) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	update_pwd_oldpwd(env, cwd);
	return (0);
}
