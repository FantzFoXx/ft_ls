/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:16:18 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/04 17:29:34 by udelorme         ###   ########.fr       */
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

static void				get_dir_items(t_dir_content *first, char *params)
{
	struct dirent	*items;

	items = NULL;
	while (first && !first->cur_dir)
		first = first->next;
	if (first)
	{
		while ((items = readdir(first->cur_dir)) && items != NULL)
		{
			if (ft_strchr(params, 'r'))
				t_item_rev_place(&(first->items),
						t_item_new(items, first->dir_name));
			else
				t_item_place(&(first->items),
						t_item_new(items, first->dir_name));
		}
		if (ft_strchr(params, 'a'))
			print_ls(first->items);
		else
			print_all_ls(first->items);
		ft_putendl("");
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
		t_dir_push(&dirs, t_dir_new(cur_dir, path));
		get_dir_items(dirs, params);
	}
	if (ft_strchr(params, 'R') && dirs->items)
	{
		content = dirs->items;
		while (content && content->item)
		{
			if (S_ISDIR(content->prop.st_mode) && (ft_strcmp(content->item_name, ".")
						!= 0 && ft_strcmp(content->item_name, "..") != 0))
			{
				ft_putstr(path);
				ft_putstr(content->item_name);
				ft_putendl(":");
				open_dir(ft_strjoin(ft_strjoin(path, content->item_name), "/"), params);
			}
			content = content->next;
		}
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

	i = -1;
	size_tab = ft_tab_size(paths);
	if (size_tab == 0)
	{
		ft_realloc_tab(&paths, 1);
		paths[0] = ".";
	}
	dirs = NULL;
	while (paths[++i])
	{
		if (ft_strcmp(paths[i], "/") == 0)
			open_dir(paths[i], params);
		else
			open_dir(ft_strjoin(paths[i], "/"), params);
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
