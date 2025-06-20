/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgoossen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:05:34 by rgoossen          #+#    #+#             */
/*   Updated: 2023/10/27 13:05:41 by rgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// int main()
// {
//     int data = 42;
//     t_list *new_node = ft_lstnew(&data);

//     if (new_node != NULL)
//     {
//         printf("New node content: %d\n", *(int *)new_node->content);
//         printf("New node next: %p\n", (void *)new_node->next);
//         free(new_node);
//     }
//     else
//     {
//         printf("ft_lstnew returned NULL, allocation failed.\n");
//     }

//     return 0;
// }
