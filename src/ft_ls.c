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

static DIR				open_dirs(char **paths, char *params)
{
	size_t			size_tab;
	t_dir_content	*dirs;

	size_tab = ft_tab_size(paths);
	while (path[i])
		dirs = t_dir_push(dirs, opendir(path[i]));
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
static t_dir_content	open_dir(char *path, char *params)
{
	DIR				*cur_dir;
	struct stat		file_props;
	t_dir_content	*dirs;

	dirs = NULL;
	cur_dir = NULL;
	cur_dir = opendir(path);
	if (!cur_dir)
	{
		if (lstat(path, &file_props) == 0)
			t_dir_add_file(&dirs, file_props, path);
		else
			catch_error(1, path);
	}
	else
		t_dir_push(&dirs, t_dir_new(cur_dir, path));
	return (dirs);
}

int						ft_ls(char *params, char **path)
{
	t_dir_content	*dirs;
	DIR				*cur_dir;
	int				i;


	open_dirs(path, params);
	dirs = NULL;
	cur_dir = NULL;
	i = 0;

	return (1);
}
