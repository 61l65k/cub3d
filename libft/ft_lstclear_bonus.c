/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 23:18:49 by apyykone          #+#    #+#             */
/*   Updated: 2024/04/30 14:28:24 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;

	if (lst)
	{
		while (*lst)
		{
			current = *lst;
			*lst = (*lst)->next;
			if (*del)
				(*del)(current->content);
			current->content = NULL;
			free(current);
			current = NULL;
		}
	}
}
