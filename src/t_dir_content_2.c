/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 12:00:35 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/03 17:56:06 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir_content.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "catch_errors.h"

#include <stdio.h>

t_dir_item	*t_item_new(char *d_name, char *path)
{
	t_dir_item	*new;
	char		*join;
	char 		*tmp;
	struct stat	prop;

	new = NULL;
	errno = 0;
	if (ft_strcmp(path, "/") != 0)
		join = ft_strjoin(path, "/");
	else
		join = ft_strdup(path);
	if (ft_strcmp(path, ".") == 0)
		tmp = ft_strdup(d_name);
	else
		tmp = ft_strjoin(join, d_name);
	lstat(tmp, &prop);
	free(tmp);
	if (errno)
		catch_error(0, ft_strdup(d_name));
	else
		new = (t_dir_item *)malloc(sizeof(t_dir_item));
	if (new)
	{
		new->item_name = ft_strdup(d_name);
		new->path = join;
		new->next = NULL;
		new->prop = prop;
	}
	return (new);
}

t_dir_item	*t_file_new(char *d_name)
{
	t_dir_item	*new;
	struct stat	prop;

	new = NULL;
	errno = 0;
	lstat(d_name, &prop);
	if (errno)
		catch_error(0, ft_strdup(d_name));
	else
		new = (t_dir_item *)malloc(sizeof(t_dir_item));
	if (new)
	{
		new->item_name = ft_strdup(d_name);
		new->path = NULL;;
		new->next = NULL;
		new->prop = prop;
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

static void			t_item_swap(t_dir_item *index)
{
	t_dir_item *bak;

	bak = index->next;
	index->next = index->next->next;
	bak->next = index->next->next;
	index->next->next = bak;
}

static t_dir_item	*t_item_time_ascii_swap(t_dir_item **item)
{
	// a revoir, ne gere pas le swap avec le premier elem de la liste
	t_dir_item *index;
	t_dir_item *begin;

	index = *item;
	begin = *item;
	while (index && index->next && index->next->next)
	{
		if ((index->next->prop.st_mtimespec.tv_sec
					- index->next->next->prop.st_mtimespec.tv_sec) == 0)
		{
			if ((index->next->prop.st_mtimespec.tv_nsec
						- index->next->next->prop.st_mtimespec.tv_nsec) == 0)
			{
				if (ft_strcmp(index->next->item_name, index->next->next->item_name) > 0)
				{
					t_item_swap(index);
					return(t_item_time_ascii_swap(&begin));
				}
			}
			else if ((index->next->prop.st_mtimespec.tv_nsec
						- index->next->next->prop.st_mtimespec.tv_nsec) < 0)
			{
				t_item_swap(index);
				return(t_item_time_ascii_swap(&begin));
			}
		}
		index = index->next;
	}
	return (*item);
}

t_dir_item	*t_item_sort(t_dir_item **item, t_dir_item *new, char *params)
{
	static int bool_pass = 0;
	static int t = 0;

	if (!bool_pass)
	{
		t = (ft_strchr(params, 't')) ? 1 : 0;
		bool_pass = 1;
	}
	if (t)
	{
		t_item_time_place(item, new);
		t_item_time_ascii_swap(item);
	}
	else
		t_item_place(item,
				new);
	return (*item);
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
		else if ((new->prop.st_mtimespec.tv_sec - index->prop.st_mtimespec.tv_sec) > 0)
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
