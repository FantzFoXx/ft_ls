/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 12:00:26 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/26 15:10:17 by udelorme         ###   ########.fr       */
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
		new->props = (struct stat *)malloc(sizeof(struct stat));
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
	if (first && !first->cur_dir)
		while (first && !first->cur_dir)
		{
			ft_putendl(first->dir_name);
			first = first->next;
		}
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

void			t_dir_add_file(t_dir_content **first,
		struct stat file, char *dir_name)
{
	t_dir_content *new;

	new = (t_dir_content *)malloc(sizeof(t_dir_content));
	if (new)
	{
		new->items = NULL;
		new->items = NULL;
		new->cur_dir = NULL;
		new->props = &file;
		new->dir_name = dir_name;
		new->next = *first;
	}
	*first = new;
}
