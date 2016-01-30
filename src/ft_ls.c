/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:16:18 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/28 16:24:00 by udelorme         ###   ########.fr       */
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
			realloc_dirent(&first->items, 1);
			first->items[i++] = items;
		}
		first = first->next;
		i = 0;
	}
	i = 0;
}

/*
 * Recursive :
 * J'ouvre mon repertoire
 * je read tout
 * tant que j'ai des dossiers a lire : recursive
 * je rouvre le nouveau dossier
 * je read tout
 * ...
 * une fois que fini, descente recursive, retour fonction.
 * a la suite on reboucle
 */
static t_dir_content	*open_dir(char *path, char *params)
{
	DIR				*cur_dir;
	struct stat		file_props;
	t_dir_content	*dirs;
	int 			i;

	ft_trace("pass", "pass");
	(void)params;
	dirs = NULL;
	cur_dir = NULL;
	cur_dir = opendir(path);
	i = 0;
	if (!cur_dir)
	{
		if (lstat(path, &file_props) == 0)
			t_dir_add_file(&dirs, file_props, path);
		else
			catch_error(1, path);
	}
	else
	{
		t_dir_push(&dirs, t_dir_new(cur_dir, path));
		get_dir_items(get_last_item(dirs));
	}
	if (ft_strchr(params, 'R') && dirs->items)
	{
		while (dirs->items[i] )
		{
			if (dirs->items[i]->d_type == DT_DIR && (ft_strcmp(".", dirs->items[i]->d_name) != 0
					&& ft_strcmp("..", dirs->items[i]->d_name) != 0))
			{
				ft_trace("dir->name", dirs->items[i]->d_name);
				t_dir_push(&dirs, open_dir(ft_strjoin(ft_strjoin(path, dirs->items[i]->d_name), "/"), params));
			}
			i++;
		}
	}
	return (dirs);
}

static t_dir_content	*open_dirs(char **paths, char *params)
{
	int				i;
	size_t			size_tab;
	t_dir_content	*dirs;

	i = 0;
	size_tab = ft_tab_size(paths);
	while (paths[i])
	{
		ft_nbrtrace("opendirs: pass ", i);
		sleep(1);
		t_dir_push(&dirs, open_dir(paths[i], params));
		ft_trace("end param dirs", "");
		//sort_t_dir(dirs);
		i++;
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
	dirs = open_dirs(path, params);
	ft_trace("opendirs", "ended");
	print_all_items(dirs);

	return (1);
}
