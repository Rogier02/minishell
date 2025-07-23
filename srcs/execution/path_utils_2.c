/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_utils_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/23 18:26:02 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/23 18:26:10 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_vars(t_envp *envp)
{
    int	count;

    count = 0;
    while (envp)
    {
        count++;
        envp = envp->next;
    }
    return (count);
}

static char	*create_env_string(t_envp *envp_node)
{
    char	*temp;
    char	*result;

    temp = ft_strjoin(envp_node->key, "=");
    if (!temp)
        return (NULL);
    result = ft_strjoin(temp, envp_node->value);
    free(temp);
    return (result);
}

static int	populate_env_array(char **arr, t_envp *envp)
{
    int	i;

    i = 0;
    while (envp)
    {
        arr[i] = create_env_string(envp);
        if (!arr[i])
        {
            ft_free_array(arr);
            return (-1);
        }
        envp = envp->next;
        i++;
    }
    arr[i] = NULL;
    return (0);
}

char	**env_list_to_array(t_envp *envp)
{
    int		count;
    char	**arr;

    count = count_env_vars(envp);
    arr = malloc(sizeof(char *) * (count + 1));
    if (!arr)
        return (NULL);
    if (populate_env_array(arr, envp) == -1)
        return (NULL);
    return (arr);
}