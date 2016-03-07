/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 15:53:34 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/07 08:04:23 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>
#include "print_ls.h"

static void		recurse_call(t_dir_item *content, t_dir_content *dirs
		, char *path, char *params)
{
	content = dirs->items;
	while (content)
	{
		if (S_ISDIR(content->prop.st_mode)
				&& !is_meta_dir(content->item_name))
		{
			if (!dirs->is_lfile)
				rec_print_dir_name(ft_strjoin(path, content->item_name));
			rec_open_dir(ft_join_paths(path, content->item_name)
					, params, content);
		}
		content = content->next;
	}
}

int				rec_open_dir(char *path, char *params, t_dir_item *item)
{
	DIR				*cur_dir;
	t_dir_content	*dirs;
	t_dir_item		*content;

	dirs = NULL;
	cur_dir = opendir(path);
	content = NULL;
	if (!cur_dir)
	{
		free(path);
		return (catch_error(1, ft_strdup(item->item_name)));
	}
	else
	{
		errno = 0;
		t_dir_place(&dirs, t_dir_new(cur_dir, path, 0));
		get_dir_items(dirs, params);
	}
	if (ft_strchr(params, 'R') && dirs->items)
		recurse_call(content, dirs, path, params);
	if (cur_dir)
		closedir(cur_dir);
	t_dir_free_all(&dirs);
	return (1);
}

static void		print_files(t_dir_item **files, char **paths
		, t_dir_content **dirs, char *params)
{
	static int r;

	r = (ft_strchr(params, 'r') ? 1 : 0);
	if (*files)
	{
		if (r)
			t_item_rev_sort(*files, NULL, files);
		print_ls(*files, params, 0, (dirs) ? 0 : 1);
	}
	if (!paths[0])
		t_dir_place(dirs, t_dir_new(opendir("."), ".", 0));
}

t_dir_content	*open_dirs(char **paths, char *params)
{
	DIR				*cur_dir;
	t_dir_content	*dirs;
	t_dir_item		*files;
	int				i;
	int				r;

	dirs = NULL;
	files = NULL;
	i = -1;
	r = (ft_strchr(params, 'r') ? 1 : 0);
	while (paths[++i])
		if (!open_file(&files, paths[i], params))
		{
			if ((cur_dir = opendir(paths[i])) && cur_dir)
			{
				if (r)
					t_dir_rev_place(&dirs, t_dir_new(cur_dir, paths[i], 0));
				else
					t_dir_place(&dirs, t_dir_new(cur_dir, paths[i], 0));
			}
			else
				catch_error(0, ft_strdup(paths[i]));
		}
	print_files(&files, paths, &dirs, params);
	return (dirs);
}

int				ft_ls(char *params, char **path)
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
		if (mult_dirs && !dirs->is_lfile)
			print_dir_name(ft_strdup(dirs->dir_name));
		open_dir(dirs, params);
		dirs = dirs->next;
		if (mult_dirs && dirs && !dirs->is_lfile)
			ft_putchar('\n');
	}
	free(params);
	ft_freetab(path);
	return (1);
}
