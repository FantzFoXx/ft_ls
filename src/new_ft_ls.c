/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 13:30:59 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/16 13:46:25 by udelorme         ###   ########.fr       */
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

}


static int				open_dir(char *path, char *params)
{
	
}


static void				*open_dirs(char **paths, char *params)
{
	char			*cur_path;
	int				i;

	i = -1;
	if (paths)
		while (paths[++i])
		{
			if (i > 1)
			{
				ft_putstr(paths[i]);
				ft_putendl(":");
			}
			cur_path = ft_strjoin(paths[i], "/");
			open_dir(cur_path, params);
			free(cur_path);
			if (!paths[i + 1])
				ft_putchar('\n');
		}
	else
		open_dir(".", params);
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
