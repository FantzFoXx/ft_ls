/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:16:18 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/26 17:02:57 by udelorme         ###   ########.fr       */
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

static t_dir_content	*open_dirs(char **path)
{
	size_t			nb_path;
	DIR				*cur_dir;
	size_t			i;
	struct stat		file_props;
	t_dir_content	*dirs;

	i = 0;
	dirs = NULL;
	cur_dir = NULL;
	nb_path = ft_tab_size(path);
	while (i < nb_path)
	{
		cur_dir = opendir(path[i]);
		if (!cur_dir)
		{
			if (lstat(path[i], &file_props) == 0)
				t_dir_add_file(&dirs, file_props, path[i]);
			else
				catch_error(1, path[i]);
		}
		else
			t_dir_push(&dirs, t_dir_new(cur_dir, path[i]));
		i++;
	}
	return (dirs);
}

static void				get_dir_items(t_dir_content *first)
{
	struct dirent	*items;
	int				i;

	items = NULL;
	i = 0;
	while (first && !first->cur_dir)
		first = first->next;
	while (first)
	{
		while ((items = readdir(first->cur_dir)) && items != NULL)
		{
			realloc_dirent(&first->items, 1);
			first->items[i++] = items;
		}
		first = first->next;
		i = 0;
	}
}

int						ft_ls(char *params, char **path)
{
	t_dir_content	*dirs;
	DIR				*cur_dir;
	int				i;

	(void)params;
	cur_dir = NULL;
	dirs = NULL;
	i = 0;
	if (!path)
	{
		path = (char **)malloc(sizeof(char *) * 2);
		path[1] = NULL;
		path[0] = ft_strdup(".");
	}
	dirs = open_dirs(path);
	get_dir_items(dirs);
	sort_t_dir(dirs);
	print_items(dirs);
	return (1);
}
