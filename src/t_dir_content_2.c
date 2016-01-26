/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 12:00:35 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/26 12:01:59 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir_content.h"

void	sort_t_dir(t_dir_content *lst)
{
	t_dir_content	*index;
	t_dir_content	*first;

	index = lst;
	first = lst;
	while (index->next)
		if (ft_strcmp(index->dir_name,
					index->next->dir_name) > 0)
		{
			switch_items(index, index->next);
			index = first;
		}
		else
			index = index->next;
}
