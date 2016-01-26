/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 12:00:35 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/26 17:02:55 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir_content.h"
#include <stdlib.h>

void	sort_t_dir(t_dir_content *lst)
{
	t_dir_content	*index;
	t_dir_content	*first;

	index = lst;
	first = lst;
	if (lst)
		while (index->next)
		{
			if (ft_strcmp(index->dir_name,
						index->next->dir_name) > 0)
			{
				switch_items(index, index->next);
				index = first;
			}
			else
				index = index->next;
		}
}

void	switch_items(t_dir_content *first, t_dir_content *last)
{
	t_dir_content *tmp;

	tmp = t_dir_new(first->cur_dir, first->dir_name);
	free(tmp->items);
	tmp->items = first->items;
	first->cur_dir = last->cur_dir;
	first->items = last->items;
	first->dir_name = last->dir_name;
	last->cur_dir = tmp->cur_dir;
	last->items = tmp->items;
	last->dir_name = tmp->dir_name;
}
