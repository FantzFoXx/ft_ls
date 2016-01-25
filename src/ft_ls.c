/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:16:18 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/25 10:24:30 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
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
	int				cp_d;
	t_dir_content	*dirs;

	i = 0;
	cp_d = 0;
	cur_dir = NULL;
	nb_path = size_tab(path);
	dirs = NULL;
	while (i < nb_path)
	{
		cur_dir = opendir(path[i]);
		if (!cur_dir)
			catch_error(1, path[i]);
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

static void				check_params(char *params)
{
	char	*supported_params;
	int		i;

	i = 0;
	supported_params = ft_strdup("la");
	while (params[i] != 0)
	{
		if (!ft_strchr(supported_params, params[i]))
			error_params(supported_params, params[i]);
		i++;
	}
	free(supported_params);
}

int						ft_ls(char *params, char **path)
{
	t_dir_content	*dirs;
	DIR				*cur_dir;
	int				i;

	cur_dir = NULL;
	dirs = NULL;
	i = 0;
	if (params)
		check_params(params);
	if (!path)
	{
		path = (char **)malloc(sizeof(char *) * 2);
		path[1] = NULL;
		path[0] = ft_strdup(".");
	}
	dirs = open_dirs(path);
	get_dir_items(dirs);
	print_name_dir(dirs);
	return (1);
}
