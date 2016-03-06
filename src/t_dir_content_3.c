/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 00:16:44 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/06 00:26:58 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir_content.h"

static int	t_item_time_nsec_sort(t_dir_item *item, t_dir_item *new)
{
	if ((item->prop.st_mtimespec.tv_sec
				- new->prop.st_mtimespec.tv_sec) == 0)
	{
		if ((item->prop.st_mtimespec.tv_nsec
					- new->prop.st_mtimespec.tv_nsec) == 0)
		{
			if (ft_strcmp(item->item_name, new->item_name) > 0)
				return (1);
		}
		else if ((item->prop.st_mtimespec.tv_nsec
					- new->prop.st_mtimespec.tv_nsec) < 0)
			return (1);
	}
	return (0);
}

t_dir_item	*t_item_sort(t_dir_item **item, t_dir_item *new, char *params)
{
	static int bool_pass = 0;
	static int t = 0;
	static int r = 0;

	if (!bool_pass)
	{
		t = (ft_strchr(params, 't')) ? 1 : 0;
		r = (ft_strchr(params, 'r')) ? 1 : 0;
		bool_pass = 1;
	}
	if (t)
		t_item_time_place(item, new);
	else
		t_item_place(item,
				new);
	return (*item);
}

void		t_item_rev_sort(t_dir_item *first, t_dir_item *new_next,
		t_dir_item **new_first)
{
	if (first->next)
		t_item_rev_sort(first->next, first, new_first);
	else
		*new_first = first;
	first->next = new_next;
}

t_dir_item	*t_item_place(t_dir_item **first, t_dir_item *new)
{
	t_dir_item *index;

	index = NULL;
	if (new)
	{
		if (*first)
			index = *first;
		if (!index)
		{
			*first = new;
			return (*first);
		}
		else if (ft_strcmp(new->item_name, index->item_name) < 0)
		{
			new->next = index;
			*first = new;
			return (new);
		}
		else
			index->next = t_item_place(&index->next, new);
	}
	return (index);
}

t_dir_item	*t_item_time_place(t_dir_item **first, t_dir_item *new)
{
	t_dir_item *index;

	index = NULL;
	if (new)
	{
		if (*first)
			index = *first;
		if (!index)
		{
			*first = new;
			return (*first);
		}
		else if (((new->prop.st_mtimespec.tv_sec
						- index->prop.st_mtimespec.tv_sec) > 0)
				|| (t_item_time_nsec_sort(index, new)))
		{
			new->next = index;
			*first = new;
			return (new);
		}
		else
			index->next = t_item_time_place(&index->next, new);
	}
	return (index);
}
