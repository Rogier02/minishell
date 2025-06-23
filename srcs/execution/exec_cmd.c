/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mahkilic <mahkilic@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/23 21:23:38 by mahkilic      #+#    #+#                 */
/*   Updated: 2025/06/23 21:23:38 by mahkilic      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**env_list_to_array(t_envp *envp)
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

static char	*find_cmd_path(char *cmd, t_envp *envp)
{
	char	**paths;
	char	*full;
	char	*tmp;
	int		i;

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
			return (ft_free_array(paths), full);
		free(full);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}

static char	*get_cmd_path(char *cmd, t_envp *envp)
{
	if (ft_strchr(cmd, '/'))
		return (cmd);
	return (find_cmd_path(cmd, envp));
}

int	exec_cmd(t_minishell *msh)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	char	**envp_arr;

	pid = fork();
	if (pid == 0)
	{
		cmd_path = get_cmd_path(msh->cmd_table->cmd[0], msh->envp);
		envp_arr = env_list_to_array(msh->envp);
		if (cmd_path)
			execve(cmd_path, msh->cmd_table->cmd, envp_arr);
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(msh->cmd_table->cmd[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (ft_putstr_fd("minishell: fork failed\n", 2), -1);
	return (0);
}
