/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 12:00:26 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/06 00:22:01 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir_content.h"
#include <stdlib.h>
#include <errno.h>

t_dir_content	*t_dir_new(DIR *cur_dir, char *dir_name, int is_lfile)
{
	t_dir_content *new;

	new = NULL;
	new = (t_dir_content *)malloc(sizeof(t_dir_content));
	if (new)
	{
		new->items = NULL;
		new->cur_dir = cur_dir;
		new->dir_name = dir_name;
		new->is_lfile = is_lfile;
		new->next = NULL;
	}
	return (new);
}

t_dir_content	*t_dir_place(t_dir_content **first, t_dir_content *new)
{
	t_dir_content *index;

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
		else if (ft_strcmp(new->dir_name, index->dir_name) < 0)
		{
			new->next = index;
			*first = new;
			return (new);
		}
		else
			index->next = t_dir_place(&index->next, new);
	}
	return (index);
}

t_dir_content	*t_dir_rev_place(t_dir_content **first, t_dir_content *new)
{
	t_dir_content *index;

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
		else if (ft_strcmp(new->dir_name, index->dir_name) > 0)
		{
			new->next = index;
			*first = new;
			return (new);
		}
		else
			index->next = t_dir_rev_place(&index->next, new);
	}
	return (index);
}

void			t_dir_free_all(t_dir_content **cur)
{
	if ((*cur)->next)
	{
		t_dir_free_all(&((*cur)->next));
		free((*cur)->next);
		(*cur)->next = NULL;
	}
	if ((*cur)->dir_name)
		free((*cur)->dir_name);
	if ((*cur)->items)
		t_item_free_all(&((*cur)->items));
	free((*cur)->items);
	free(*cur);
}

void			t_item_free_all(t_dir_item **cur)
{
	if ((*cur)->next)
	{
		t_item_free_all(&((*cur)->next));
		free((*cur)->next);
		(*cur)->next = NULL;
	}
	free((*cur)->item_name);
	free((*cur)->path);
}
