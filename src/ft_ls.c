/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:16:18 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/19 14:51:01 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
/*
static DIR	**open_dirs(char **path)
{
	char **files;
	size_t nb_path;
	DIR **dirs;
	DIR *cur_dir;
	size_t i;
	int cp_f;
	int cp_d;

	nb_path = 0;
	i = 0;
	cp_d = 0;
	cp_f = 0;
	cur_dir = NULL;
	nb_path = size_tab(path);
	dirs = (DIR **)malloc(sizeof(DIR *) * nb_path);
	files = (char **)malloc(sizeof(char *));
	while (i < nb_path)
	{
		cur_dir = opendir(path[i]);
		if (!cur_dir)
		{
			if (open(path[i], O_RDONLY))
			{
				realloc_tab(&files, 1);
				files[cp_f++] = ft_strdup(path[i]);
			}
			else
				catch_error(1, path[i]);
		}
		else
			dirs[cp_d++] = cur_dir;
		i++;
	}
	return (dirs);
}
*/
int			ft_ls(char *params, char **path)
{
	//struct	dirent *items;
	DIR		**cur_dir;
	char *buf = ft_strnew(1001);

	cur_dir = NULL;
	if (!path)
	{
		cur_dir = (DIR **)malloc(sizeof(DIR *));
		*cur_dir = opendir(".");
	}
	else
	{
		//cur_dir = open_dirs(path);
		stat
		ft_trace(buf);
	}
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
