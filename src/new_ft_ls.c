/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 13:30:59 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/16 16:25:50 by udelorme         ###   ########.fr       */
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
		{
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
		}
		print_ls(first->items, params);
	}
}

static int				open_dir(char *path, char *params)
{
	DIR				*cur_dir;
	t_dir_content	*dirs;

	dirs = NULL;
	cur_dir = opendir(path);
	if (!cur_dir)
	{
		return (catch_error(1, path));
	}
	else
	{
		t_dir_push(&dirs, t_dir_new(cur_dir, path));
		get_dir_items(dirs, params);
	}
	return (1);
}

static void				open_dirs(char **paths, char *params)
{
	char			*cur_path;
	int				i;
	size_t			size_tab;

	i = -1;
	size_tab = ft_tab_size(paths);
	if (paths && paths[0])
		while (paths[++i])
		{
			if (size_tab > 1)
			{
				ft_putstr(paths[i]);
				ft_putendl(":");
			}
			cur_path = ft_strjoin(paths[i], "/");
			open_dir(cur_path, params);
			free(cur_path);
			if (paths[i + 1])
				ft_putchar('\n');
		}
	else
		open_dir(".", params);
}

int						ft_ls(char *params, char **path)
{
	DIR				*cur_dir;
	int				i;

	cur_dir = NULL;
	i = 0;
	if (params)
		check_params(params);
	open_dirs(path, params);
	return (1);
}
