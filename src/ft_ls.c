/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:16:18 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/26 15:44:39 by udelorme         ###   ########.fr       */
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
		first = first->next;
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
							t_item_new(items, first->dir_name));
				else if (!r)
					t_item_place(&(first->items),
							t_item_new(items, first->dir_name));
				if (errno)
					catch_error(0, first->dir_name);
			}
		print_ls(first->items, params);
	}
}

static int				open_dir(char *path, char *params)
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
		return (catch_error(1, path));
	}
	else
	{
		errno = 0;
		t_dir_push(&dirs, t_dir_new(cur_dir, path));
		get_dir_items(dirs, params);
	}
	if (ft_strchr(params, 'R') && dirs->items)
	{
		content = dirs->items;
		while (content && content->item)
		{
			if (S_ISDIR(content->prop.st_mode)
					&& (ft_strcmp(content->item_name, ".") != 0
						&& ft_strcmp(content->item_name, "..") != 0)
					&& ((content->item_name[0] == '.'
							&& ft_strchr(params, 'a'))
						|| content->item_name[0] != '.'))
			{
				ft_putendl("");
				ft_putstr(path);
				ft_putstr(content->item_name);
				ft_putendl(":");
				open_dir(ft_strjoin(ft_strjoin(path,
								content->item_name), "/"), params);
			}

			content = content->next;
		}
		//ft_trace(NULL, "pass");
	}
	closedir(cur_dir);
	t_dir_free_all(&dirs);
	return (1);
}

static t_dir_content	*open_dirs(char **paths, char *params)
{
	int				i;
	size_t			size_tab;
	t_dir_content	*dirs;
	char			*cur_path;

	i = -1;
	size_tab = ft_tab_size(paths);
	cur_path = NULL;
	dirs = NULL;
	if (size_tab == 0)
	{
		ft_realloc_tab(&paths, 1);
		paths[0] = ".";
	}
	while (paths[++i])
	{
		if (size_tab > 1)
		{
			ft_putstr(paths[i]);
			ft_putendl(":");
		}
		if (ft_strcmp(paths[i], "/") == 0)
			cur_path = ft_strdup(paths[i]);
		else
			cur_path = ft_strjoin(paths[i], "/");
		open_dir(cur_path, params);
		if (paths[i + 1] != 0)
			ft_putendl("");
	}
	return (dirs);
}

int						ft_ls(char *params, char **path)
{
	t_dir_content	*dirs;
	DIR				*cur_dir;
	int				i;

	dirs = NULL;
	cur_dir = NULL;
	i = 0;
	if (params)
		check_params(params);
	dirs = open_dirs(path, params);
	return (1);
}
