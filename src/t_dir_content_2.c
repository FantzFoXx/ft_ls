/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 12:00:35 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/18 18:32:04 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir_content.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "catch_errors.h"

t_dir_item	*t_item_new(struct dirent *item, char *path)
{
	t_dir_item	*new;
	char		*join;
	struct stat	prop;

	join = ft_strjoin(path, "/");
	new = NULL;
	if (ft_strcmp(path, ".") == 0)
		lstat(ft_strjoin("", item->d_name), &prop);
	else
		lstat(ft_strjoin(join, item->d_name), &prop);
	free(join);
	if (errno)
		catch_error(0, item->d_name);
	else
		new = (t_dir_item *)malloc(sizeof(t_dir_item));
	if (new)
	{
		new->item_name = ft_strdup(item->d_name);
		ft_memcpy((void *)&(new->item_type),
				(void *)&(item->d_type), sizeof(__uint8_t));
		new->item = item;
		new->path = path;
		new->next = NULL;
	}
	return (new);
}

/*
   int			t_item_place(t_dir_item **first, t_dir_item *new)
   {
   t_dir_item *index;
   t_dir_item *bak;

   bak = *first;
   index = *first;
   if (!index)
 *first = new;
 else if (ft_strcmp(new->item_name, (*first)->item_name) < 0)
 {
 new->next = *first;
 *first = new;
 }
 else
 while (index)
 {
 if (ft_strcmp(new->item_name, index->item_name) < 0)
 {
 new->next = bak->next;
 bak->next = new;
 return (0);
 }
 if (!index->next)
 {
 index->next = new;
 break ;
 }
 bak = index;
 index = index->next;
 }
 return (0);
 }
 */

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

t_dir_item	*t_item_rev_place(t_dir_item **first, t_dir_item *new)
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
		else if (ft_strcmp(new->item_name, index->item_name) > 0)
		{
			new->next = index;
			*first = new;
			return (new);
		}
		else
			index->next = t_item_rev_place(&index->next, new);
	}
	return (index);
}

void		t_item_push(t_dir_item **first, t_dir_item *new)
{
	t_dir_item *index;

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
