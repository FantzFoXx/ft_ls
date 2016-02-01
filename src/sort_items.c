/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 17:31:23 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/01 09:25:45 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir_content.h"
#include <stdlib.h>
#include "print_ls.h"

void	sort_t_dir(t_dir_content *lst)
{
	int				i;
	t_dir_content	*index;
	t_dir_content	*first;

	first = lst;
	index = lst;
	i = 0;
	if (lst)
		while (index->next)
		{
			if (ft_strcmp(index->dir_name,
						index->next->dir_name) > 0)
			{
				switch_dirs(index, index->next);
				index = first;
			}
			else
				index = index->next;
		}
	while (first)
	{
		sort_t_dir_elems(index);
		first = first->next;
	}
}

void	sort_t_dir_elems(t_dir_content *lst)
{
	int i;

	// a reprendre, segfault
	i = 0;
	while (lst->items[i + 1])
	{
		if (ft_strcmp(lst->items[i]->d_name,
					lst->items[i + 1]->d_name) > 0)
		{
			switch_items(&lst->items[i], &lst->items[i + 1]);
			//switch_props(&lst->props[i], &lst->props[i + 1]);
			i = -1;
		}
		i++;
	}
}

void	switch_items(struct dirent **d1, struct dirent **d2)
{
	struct dirent *tmp;

	tmp = *d1;
	*d1 = *d2;
	*d2 = tmp;
}

void	switch_props(struct stat *s1, struct stat *s2)
{
	struct stat tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	switch_dirs(t_dir_content *first, t_dir_content *last)
{
	t_dir_content *tmp;

	tmp = t_dir_new(first->cur_dir, first->dir_name);
	//free(tmp->items);
	tmp->items = first->items;
	first->cur_dir = last->cur_dir;
	first->items = last->items;
	first->dir_name = last->dir_name;
	last->cur_dir = tmp->cur_dir;
	last->items = tmp->items;
	last->dir_name = tmp->dir_name;
}
