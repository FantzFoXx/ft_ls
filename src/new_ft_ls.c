/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 13:30:59 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/26 16:51:38 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "print_ls.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <t_dir_content.h>
#include <errno.h>

static void				get_dir_items(t_dir_content *first, char *params)
{
	struct dirent	*items;
	int 			a;
	int 			r;

	a = 0;
	r = 0;
	items = NULL;
	while (first && !first->cur_dir)
	{
		first = first->next;
	}
	if (first)
	{
		if (ft_strchr(params, 'a'))
			a = 1;
		if (ft_strchr(params, 'r'))
			r = 1;
		while ((items = readdir(first->cur_dir)) && items != NULL)
			if ((items->d_name[0] == '.' && a)
					|| items->d_name[0] != '.')
			{
				if (r)
					t_item_rev_place(&(first->items),
							t_item_new(items->d_name, first->dir_name));
				else
					t_item_place(&(first->items),
							t_item_new(items->d_name, first->dir_name));
			}
		print_ls(first->items, params);
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
		return (catch_error(1, item->item_name));
	}
	else
	{
		errno = 0;
		t_dir_place(&dirs, t_dir_new(cur_dir, ft_strdup(path), 0));
		get_dir_items(dirs, params);
	}
	if (ft_strchr(params, 'R') && dirs->items)
	{
		content = dirs->items;
		while (content && content->item)
		{
			if (S_ISDIR(content->prop.st_mode)
					&& !is_meta_dir(content->item_name))
			{
				if (!dirs->is_lfile)
					print_dir_name(ft_strjoin(path, content->item_name));
				rec_open_dir(ft_join_paths(path, content->item_name), params, content);
			}
			content = content->next;
		}
	}
	if (cur_dir)
		closedir(cur_dir);
	t_dir_free_all(&dirs);
	free(path);
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
					print_dir_name(ft_strjoin(items->path, items->item_name));
				rec_open_dir(ft_join_paths(items->path, items->item_name), params, items);
			}
			items = items->next;
		}
	}
	return (1);
}

static int			open_file(char *path, char *params)
{
	struct stat	file;
	t_dir_item		*prop;
	int				lstat_ret;

	lstat_ret = -1;
	prop = NULL;
	if ((lstat_ret = lstat(path, &file)) == 0)
	{
		t_item_push(&prop, t_file_new(path));
		print_ls(prop, params);
		return (1);
	}
	return (0);
}

static t_dir_content			*open_dirs(char **paths, char *params)
{
	DIR				*cur_dir;
	t_dir_content	*dirs;
	int				i;
	int				r;

	cur_dir = NULL;
	dirs = NULL;
	i = -1;
	r = 0;
	if (ft_strchr(params, 'r'))
		r = 1;
	while (paths[++i])
	{
		if ((cur_dir = opendir(paths[i])) && cur_dir)
		{
			if (r)
				t_dir_rev_place(&dirs, t_dir_new(cur_dir, paths[i], 0));
			else
				t_dir_place(&dirs, t_dir_new(cur_dir, paths[i], 0));
		}
		else if (open_file(paths[i], params))
		{}
		else
			catch_error(0, paths[i]);
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
	ft_freetab(path);
	free(params);
	while (1);
	return (1);
}
