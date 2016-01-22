/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:16:18 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/22 13:08:46 by udelorme         ###   ########.fr       */
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
/*
static DIR				**open_dirs(char **path)
{
	size_t nb_path;
	DIR **dirs;
	DIR *cur_dir;
	size_t i;
	int cp_d;

	nb_path = 0;
	i = 0;
	cp_d = 0;
	cur_dir = NULL;
	nb_path = size_tab(path);
	dirs = (DIR **)malloc(sizeof(DIR *) * nb_path);
	while (i < nb_path)
	{
		cur_dir = opendir(path[i]);
		if (!cur_dir)
			catch_error(1, path[i]);
		else
			dirs[cp_d++] = cur_dir;
		i++;
	}
	return (dirs);
}
*/
static t_dir_content	*open_dirs(char **path)
{
	size_t nb_path;
	DIR *cur_dir;
	size_t i;
	int cp_d;
	t_dir_content *dirs;

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
		{
			t_dir_push(&dirs, t_dir_new(cur_dir));
			//dirs[cp_d++] = cur_dir;
		}
		i++;
	}
	return (dirs);
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

//static struct dirent	**list_dir()

int						ft_ls(char *params, char **path)
{
	struct	dirent **items;
	t_dir_content *dirs;
	DIR				*cur_dir;
	//struct stat *ret;
	int		i;

	cur_dir = NULL;
	dirs = NULL;
	items = NULL;
	i = 0;
	if (params)
		check_params(params);
	if (!path)
	{
		cur_dir = opendir(".");
		t_dir_push(&dirs, t_dir_new(cur_dir));
		while ((*items = readdir(*cur_dir)) && *items != NULL)
		{
			printf("%s\n", (*items)->d_name);
		}
	}
	else
	{
		dirs = open_dirs(path);
	}
	return (1);

}
