/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ft_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 13:30:59 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/22 10:30:18 by udelorme         ###   ########.fr       */
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

/*


   static int				open_dir(char *path, char *params, size_t size_tab)
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
   get_dir_items(dirs, params, size_tab);
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
   cur_path = ft_strjoin(paths[i], ((ft_strcmp(paths[i], "/") == 0) ? "" : "/"));
//cur_path = ft_strjoin(paths[i], "/");
open_dir(cur_path, params, size_tab);
free(cur_path);
if (paths[i + 1])
ft_putchar('\n');
}
else
open_dir(".", params, size_tab);
}

static char				**check_dirs(char **paths)
{
DIR		*cur_dir;
int		st_paths;
int		fn_paths;
char	**clear_paths;

st_paths = -1;
fn_paths = 0;
cur_dir = NULL;
clear_paths = NULL;
if (paths)
{
ft_realloc_tab(&clear_paths, 0);
while (paths[++st_paths])
if ((cur_dir = opendir(paths[st_paths])) && cur_dir != NULL)
{
ft_realloc_tab(&clear_paths, 1);
clear_paths[fn_paths] = paths[st_paths];
closedir(cur_dir);
fn_paths++;
}
else
perror("ft_ls");
ft_freetab(paths);
}
else
return (paths);
return (clear_paths);
}

static void				get_dir_items(t_dir_content *first, char *params)
{
	(void)first;
	(void)params;
}

*/

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
			if ((items->d_name[0] == '.' && a)
					|| items->d_name[0] != '.')
			{
				if (r)
					t_item_rev_place(&(first->items),
							t_item_new(items, first->dir_name));
				else
					t_item_place(&(first->items),
							t_item_new(items, first->dir_name));
			}
		print_ls(first->items, params);
	}
}

static int				open_dir(t_dir_content *dirs, char *params)
{

	get_dir_items(dirs, params);
	return (1);
}

static t_dir_content			*open_dirs(char **paths, char *params)
{
	DIR				*cur_dir;
	t_dir_content	*dirs;
	int				i;
	int				r;

	cur_dir = NULL;
	dirs = NULL;
	i = -1;
	r = 0;
	if (ft_strchr(params, 'r'))
		r = 1;
	while (paths[++i])
		if ((cur_dir = opendir(paths[i])) && cur_dir)
		{
			if (r)
				t_dir_rev_place(&dirs, t_dir_new(cur_dir, paths[i]));
			else
				t_dir_place(&dirs, t_dir_new(cur_dir, paths[i]));
		}
		else
			catch_error(0, paths[i]);
	if (!paths[0])
		t_dir_place(&dirs, t_dir_new(opendir("."), "."));
	return (dirs);
}

int						ft_ls(char *params, char **path)
{
	int				mult_dirs;
	DIR				*cur_dir;
	int				i;
	t_dir_content	*dirs;

	cur_dir = NULL;
	i = 0;
	mult_dirs = 0;
	if (params)
		check_params(params);
	dirs = open_dirs(path, params);
	if (ft_tab_size(path) > 1)
		mult_dirs = 1;
	while (dirs)
	{
		if (mult_dirs)
			print_dir_name(dirs->dir_name);
		open_dir(dirs, params);
		dirs = dirs->next;
		if (mult_dirs && dirs)
			ft_putchar('\n');
	}
	return (1);
}
