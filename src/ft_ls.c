/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 15:53:34 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/05 21:06:35 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "print_ls.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <t_dir_content.h>
#include <errno.h>

static void				get_dir_items(t_dir_content *first, char *params)
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

static int				rec_open_dir(char *path, char *params, t_dir_item *item)
{
	DIR				*cur_dir;
	t_dir_content	*dirs;
	int				i;
	t_dir_item		*content;

	dirs = NULL;
	cur_dir = opendir(path);
	i = -1;
	if (!cur_dir)
	{
		free(path);
		return (catch_error(1, ft_strdup(item->item_name)));
	}
	else
	{
		errno = 0;
		t_dir_place(&dirs, t_dir_new(cur_dir, path, 0));
		get_dir_items(dirs, params);
	}
	if (ft_strchr(params, 'R') && dirs->items)
	{
		content = dirs->items;
		while (content)
		{
			if (S_ISDIR(content->prop.st_mode)
					&& !is_meta_dir(content->item_name))
			{
				if (!dirs->is_lfile)
					rec_print_dir_name(ft_strjoin(path, content->item_name));
				rec_open_dir(ft_join_paths(path, content->item_name)
						, params, content);
			}
			content = content->next;
		}
	}
	if (cur_dir)
		closedir(cur_dir);
	t_dir_free_all(&dirs);
	return (1);
}

static int				open_dir(t_dir_content *dirs, char *params)
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

static int				open_file(t_dir_item **files, char *path, char *params)
{
	struct stat	file;
	int			lstat_ret;

	lstat_ret = -1;
	if ((lstat_ret = lstat(path, &file)) == 0)
	{
		if ((S_ISLNK(file.st_mode) && ft_strchr(params, 'l'))
				|| (!S_ISDIR(file.st_mode) && !S_ISLNK(file.st_mode)))
			t_item_sort(files, t_file_new(path), params);
		else
			return (0);
		return (1);
	}
	return (0);
}

static t_dir_content	*open_dirs(char **paths, char *params)
{
	DIR				*cur_dir;
	t_dir_content	*dirs;
	t_dir_item		*files;
	int				i;
	int				r;

	dirs = NULL;
	files = NULL;
	i = -1;
	r = (ft_strchr(params, 'r') ? 1 : 0);
	while (paths[++i])
		if (!open_file(&files, paths[i], params))
		{
			if ((cur_dir = opendir(paths[i])) && cur_dir)
			{
				if (r)
					t_dir_rev_place(&dirs, t_dir_new(cur_dir, paths[i], 0));
				else
					t_dir_place(&dirs, t_dir_new(cur_dir, paths[i], 0));
			}
			else
				catch_error(0, ft_strdup(paths[i]));
		}
	if (files)
	{
		if (r)
			t_item_rev_sort(files, NULL, &files);
		print_ls(files, params, 0, (dirs) ? 0 : 1);
	}
	if (!paths[0])
		t_dir_place(&dirs, t_dir_new(opendir("."), ".", 0));
	return (dirs);
}

int						ft_ls(char *params, char **path)
{
	int				mult_dirs;
	DIR				*cur_dir;
	int				i;
	t_dir_content	*dirs;

	cur_dir = NULL;
	i = 0;
	mult_dirs = 0;
	if (params)
		check_params(params);
	dirs = open_dirs(path, params);
	if (ft_tab_size(path) > 1)
		mult_dirs = 1;
	while (dirs)
	{
		if (mult_dirs && !dirs->is_lfile)
			print_dir_name(ft_strdup(dirs->dir_name));
		open_dir(dirs, params);
		dirs = dirs->next;
		if (mult_dirs && dirs && !dirs->is_lfile)
			ft_putchar('\n');
	}
	free(params);
	ft_freetab(path);
	return (1);
}
