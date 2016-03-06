/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 00:39:34 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/06 01:14:17 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "print_ls.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <t_dir_content.h>

void			get_dir_items(t_dir_content *first, char *params)
{
	struct dirent	*items;
	int				a;
	int				r;

	items = NULL;
	if (first)
	{
		r = (ft_strchr(params, 'r')) ? 1 : 0;
		a = (ft_strchr(params, 'a')) ? 1 : 0;
		while ((items = readdir(first->cur_dir)) && items != NULL)
		{
			if ((items->d_name[0] == '.' && a)
					|| items->d_name[0] != '.')
				t_item_sort(&(first->items),
						t_item_new(items->d_name, first->dir_name), params);
		}
		if (first->items && r)
			t_item_rev_sort(first->items, NULL, &(first->items));
		print_ls(first->items, params, 1, 1);
	}
}

int				open_dir(t_dir_content *dirs, char *params)
{
	t_dir_item *items;

	items = NULL;
	get_dir_items(dirs, params);
	if (ft_strchr(params, 'R'))
	{
		items = dirs->items;
		while (items)
		{
			if (S_ISDIR(items->prop.st_mode) && !is_meta_dir(items->item_name))
			{
				if (!dirs->is_lfile)
					rec_print_dir_name(
							ft_strjoin(items->path, items->item_name));
				rec_open_dir(ft_join_paths(items->path, items->item_name)
						, params, items);
			}
			items = items->next;
		}
	}
	return (1);
}

int				open_file(t_dir_item **files, char *path, char *params)
{
	struct stat	file;
	int			lstat_ret;

	lstat_ret = -1;
	if ((lstat_ret = lstat(path, &file)) == 0)
	{
		if ((S_ISLNK(file.st_mode) && ft_strchr(params, 'l'))
				|| (!S_ISDIR(file.st_mode) && !S_ISLNK(file.st_mode))
					|| (S_ISLNK(file.st_mode) && !ft_strchr(params, 'l')
						&& !opendir(path)))
			t_item_sort(files, t_file_new(path), params);
		else
			return (0);
		return (1);
	}
	return (0);
}
