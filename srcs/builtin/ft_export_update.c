/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export_update.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rgoossen <rgoossen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/29 12:15:24 by rgoossen      #+#    #+#                 */
/*   Updated: 2025/07/29 12:15:48 by rgoossen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_update(t_envp *env, char *key, char *value)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
        {
            free(env->value);
            if (value)
                env->value = ft_strdup(value);
            else
                env->value = NULL;
            return (1);
        }
        env = env->next;
    }
    return (0);
}
