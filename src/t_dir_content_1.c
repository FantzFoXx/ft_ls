/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 12:00:26 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/26 12:01:58 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir_content.h"
#include <stdlib.h>

t_dir_content	*t_dir_new(DIR *cur_dir, char *dir_name)
{
	t_dir_content *new;

	new = (t_dir_content *)malloc(sizeof(t_dir_content));
	if (new)
	{
		new->items = (struct dirent **)malloc(sizeof(struct dirent*));
		new->items[0] = NULL;
		new->cur_dir = cur_dir;
		new->dir_name = dir_name;
		new->next = NULL;
	}
	return (new);
}

void			t_dir_push(t_dir_content **first, t_dir_content *new)
{
	t_dir_content *index;

	index = *first;
	if (!index)
		*first = new;
	else
	{
		while (index->next)
			index = index->next;
		index->next = new;
	}
}

t_dir_content	*get_last_item(t_dir_content *first)
{
	while (first->next)
		first = first->next;
	return (first);
}

void			print_name_dir(t_dir_content *first)
{
	int i;

	i = 0;
	while (first)
	{
		ft_putstr(first->dir_name);
		ft_putendl(" : ");
		while (first->items[i])
		{
			ft_putendl(first->items[i]->d_name);
			i++;
		}
		i = 0;
		first = first->next;
		ft_putchar('\n');
	}
}

void			switch_items(t_dir_content *first, t_dir_content *last)
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
