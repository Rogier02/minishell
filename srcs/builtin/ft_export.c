/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 19:16:56 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/07/06 11:23:08 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_print(t_envp *env)
{
	t_envp	*current;
	
	current = env;
	while (current)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(current->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(current->value, 1);
		ft_putstr_fd("\"\n", 1);
		current = current->next;
	}
}

static int	is_valid_key(const char *key)
{
	int	i;

	i = 0;
	if (!key || !(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	export_update(t_envp *env, char *key, char *value)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->value, key, len) == 0 && env->value[len] == '=')
		{
			free(env->value);
			env->value = ft_strjoin(key, "=");
			tmp = ft_strjoin(env->value, value);
			free(env->value);
			env->value = tmp;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static void	export_add(t_envp **env, char *key, char *value)
{
	char	*tmp;
	char	*full;
	t_envp	*new;
	t_envp	*last;

	tmp = ft_strjoin(key, "=");
	full = ft_strjoin(tmp, value);
	new = malloc(sizeof(t_envp));
	last = *env;
	free(tmp);
	new->value = full;
	new->next = NULL;
	if (!last)
		*env = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

int	ft_export(t_minishell *minishell, char **args)
{
	int		i;
	char	*eq;
	t_envp	*env;

	i = 1;
	env = minishell->envp;
	if (!args[1])
		return (export_print(env), 0);
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (!is_valid_key(args[i]))
		{
			minishell->exit_code = 1;
			ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
		}
		else if (eq)
		{
			*eq = '\0';
			if (!export_update(env, args[i], eq + 1))
				export_add(&env, args[i], eq + 1);
			*eq = '=';
		}
		i++;
	}
	return (0);
}
