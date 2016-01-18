/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:16:18 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/18 15:32:56 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>
#include <stdio.h>

static DIR	**open_dirs(char **path)
{
	size_t nb_path;
	DIR **cur_dir;
	size_t i;

	nb_path = 0;
	i = 0;
	nb_path = size_tab(path);
	cur_dir = (DIR **)malloc(sizeof(DIR *) * nb_path);
	while (i < nb_path)
	{
		cur_dir[i] = opendir(path[i]);
		if (!cur_dir[i])
			catch_error(1, path[i]);
		i++;
	}
	return (cur_dir);
}

int			ft_ls(char *params, char **path)
{
	//struct	dirent *items;
	DIR		**cur_dir;

	cur_dir = NULL;
	if (!path)
	{
		cur_dir = (DIR **)malloc(sizeof(DIR *));
		*cur_dir = opendir(".");
	}
	else
		cur_dir = open_dirs(path);
	if (params)
		ft_trace("params OK");

	/*
	   curr_dir = opendir(".");
	   if (!curr_dir)
	   ft_trace("opendir: failed.");
	   else
	   {
	   items = readdir(curr_dir);
	   if (!items)
	   ft_trace("readdir: failed.");
	   else
	   {
	   printf("%hhu\n", items->d_type);
	   items = readdir(curr_dir);
	   printf("%hhu\n", items->d_type);
	   items = readdir(curr_dir);
	   printf("%hhu\n", items->d_type);
	   items = readdir(curr_dir);
	   printf("%hhu\n", items->d_type);
	   items = readdir(curr_dir);
	   printf("%hhu\n", items->d_type);
	   items = readdir(curr_dir);
	   printf("%hhu\n", items->d_type);
	   items = readdir(curr_dir);
	   printf("%hhu\n", items->d_type);
	   items = readdir(curr_dir);
	   printf("%hhu\n", items->d_type);
	   items = readdir(curr_dir);
	   printf("%hhu\n", items->d_type);
	   items = readdir(curr_dir);
	   closedir(curr_dir);
	   }
	   }
	   */
	return (1);
}
