/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cmd_path.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/08 23:35:16 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/06/08 23:35:16 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(t_envp *envp)
{
	while (envp)
	{
		if (ft_strncmp(envp->value, "PATH=", 5) == 0)
			return (envp->value + 5);
		envp = envp->next;
	}
	return (NULL);
}

static char	*find_cmd_path(char *cmd, t_envp *envp)
{
	char	**paths;
	char	*full;
	char	*tmp;
	int		i;

	paths = ft_split(get_path(envp), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, 1) == 0)
			return (ft_free_array(paths), full);
		free(full);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_envp *envp)
{
	if (ft_strchr(cmd, '/'))
		return (cmd);
	return (find_cmd_path(cmd, envp));
}
