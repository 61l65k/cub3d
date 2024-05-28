/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:17:19 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/28 10:17:42 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_null(char	**ptr_to_ptr)
{
	if (*ptr_to_ptr)
	{
		free(*ptr_to_ptr);
		*ptr_to_ptr = NULL;
	}
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_null_2d_array(char ***ptr_to_ptrarray)
{
	if (*ptr_to_ptrarray)
	{
		free_2d_array(*ptr_to_ptrarray);
		*ptr_to_ptrarray = NULL;
	}
}

int	ft_2d_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
