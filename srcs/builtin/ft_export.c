/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 19:16:56 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/07/29 13:26:19 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	export_add(t_envp **env, char *key, char *value)
{
    t_envp	*new;
    t_envp	*last;

    new = malloc(sizeof(t_envp));
    if (!new)
        return;
    new->key = ft_strdup(key);
    new->value = value ? ft_strdup(value) : NULL;
    new->next = NULL;
    last = *env;
    if (!last)
        *env = new;
    else
    {
        while (last->next)
            last = last->next;
        last->next = new;
    }
}

static void	handle_export_assignment(t_envp *env, char *arg)
{
    char	*eq;

    eq = ft_strchr(arg, '=');
    if (eq)
    {
        *eq = '\0';
        if (!export_update(env, arg, eq + 1))
            export_add(&env, arg, eq + 1);
        *eq = '=';
    }
    else
    {
        if (!export_update(env, arg, NULL))
            export_add(&env, arg, NULL);
    }
}

static void	handle_export_argument(t_minishell *minishell, t_envp *env, char *arg)
{
    if (!is_valid_key(arg))
    {
        minishell->exit_code = 1;
        ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
    }
    else
    {
        handle_export_assignment(env, arg);
    }
}

int	ft_export(t_minishell *minishell, char **args)
{
    int		i;
    t_envp	*env;

    i = 1;
	minishell->exit_code = 0;
    env = minishell->envp;
    if (!args[1])
    {
        ft_export_print(env);
        return (0);
    }
    while (args[i])
    {
        handle_export_argument(minishell, env, args[i]);
        i++;
    }
    return (0);
}
