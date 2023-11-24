/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:44:59 by ecaliska          #+#    #+#             */
/*   Updated: 2023/11/24 16:35:33 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *neu)
{
	t_list	*temp;

	if (*lst == NULL)
		*lst = neu;
	else
	{
		temp = *lst;
		while (temp -> next != NULL)
		{
			temp = temp -> next;
		}
		temp -> next = neu;
	}
}
