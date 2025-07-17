/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/17 00:00:00 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/17 00:00:00 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_list_to_array(t_envp *envp)
{
	int		count;
	t_envp	*tmp;
	char	**arr;
	int		i;

	count = 0;
	tmp = envp;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	tmp = envp;
	i = 0;
	while (tmp)
	{
		arr[i++] = tmp->value;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

static char	*get_path_value(t_envp *envp)
{
	while (envp)
	{
		if (ft_strncmp(envp->value, "PATH=", 5) == 0)
			return (envp->value + 5);
		envp = envp->next;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, t_envp *envp)
{
	char	**paths;
	char	*full;
	char	*tmp;
	int		i;

	if (ft_strchr(cmd, '/'))  // Already a path
		return (ft_strdup(cmd));
	paths = ft_split(get_path_value(envp), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
		{
			ft_free_array(paths);
			return (full);
		}
		free(full);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}
