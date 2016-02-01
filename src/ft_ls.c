/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:16:18 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/01 11:59:06 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "print_ls.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <t_dir_content.h>

static void				get_dir_items(t_dir_content *first)
{
	struct dirent	*items;
	int				i;

	items = NULL;
	i = 0;
	while (first && !first->cur_dir)
		first = first->next;
	if (first)
	{
		while ((items = readdir(first->cur_dir)) && items != NULL)
		{
			ft_putendl(items->d_name);
			realloc_dirent(&first->items, 1);
			first->items[i++] = items;
			sort_t_dir_elems(first);
		}
	}
}

static t_dir_content	*open_dir(char *path, char *params)
{
	DIR				*cur_dir;
	//struct stat		file_props;
	t_dir_content	*dirs;
	int 			i;

	dirs = NULL;
	cur_dir = opendir(path);
	i = -1;
	if (!cur_dir)
	{
		/*
		if (lstat(path, &file_props) == 0)
		{
			ft_trace("unique file", "pass");
			t_dir_add_file(&dirs, file_props, path);
		}
		else
		{
		*/
			return (catch_error(1, path));
	}
	else
	{
		t_dir_push(&dirs, t_dir_new(cur_dir, path));
		get_dir_items(dirs);
		sort_t_dir_elems(dirs);
	}
	if (ft_strchr(params, 'R') && dirs->items)
	{
		while (dirs->items[++i])
		{
			if (dirs->items[i]->d_type == DT_DIR && (ft_strcmp(dirs->items[i]->d_name, ".")
						!= 0 && ft_strcmp(dirs->items[i]->d_name, "..") != 0))
			{
				t_dir_push(&dirs, open_dir(ft_strjoin(ft_strjoin(path, dirs->items[i]->d_name), "/"), params));
				
			}
		}
	}

	return (dirs);
}

static t_dir_content	*open_dirs(char **paths, char *params)
{
	int				i;
	size_t			size_tab;
	t_dir_content	*dirs;
	t_dir_content	*check;

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
		check = open_dir(ft_strjoin(paths[i], "/"), params);
		if (check)
			t_dir_push(&dirs, check);
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
	/*else
		params = ft_strnew(0);
	if (!path)
	{
		path = ft_create_tab(1);
		path[0] = ".";
	}*/
	dirs = open_dirs(path, params);
	print_items(dirs);
	//print_all_items(dirs);

	return (1);
}
