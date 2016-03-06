/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 12:00:35 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/06 00:38:42 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir_content.h"
#include <stdlib.h>
#include <errno.h>
#include "catch_errors.h"

static void	t_item_init_var(t_dir_item **new, char *d_name, char *join
		, struct stat *prop)
{
	(*new)->item_name = ft_strdup(d_name);
	(*new)->path = join;
	(*new)->next = NULL;
	(*new)->prop = *prop;
}

t_dir_item	*t_item_new(char *d_name, char *path)
{
	t_dir_item	*new;
	char		*join;
	char		*tmp;
	struct stat	prop;

	new = NULL;
	errno = 0;
	if (ft_strcmp(path, "/") != 0)
		join = ft_strjoin(path, "/");
	else
		join = ft_strdup(path);
	if (ft_strcmp(path, ".") == 0)
		tmp = ft_strdup(d_name);
	else
		tmp = ft_strjoin(join, d_name);
	lstat(tmp, &prop);
	free(tmp);
	if (errno)
		catch_error(0, ft_strdup(d_name));
	else
		new = (t_dir_item *)malloc(sizeof(t_dir_item));
	if (new)
		t_item_init_var(&new, d_name, join, &prop);
	return (new);
}

t_dir_item	*t_file_new(char *d_name)
{
	t_dir_item	*new;
	struct stat	prop;

	new = NULL;
	errno = 0;
	lstat(d_name, &prop);
	if (errno)
		catch_error(0, ft_strdup(d_name));
	else
		new = (t_dir_item *)malloc(sizeof(t_dir_item));
	if (new)
	{
		new->item_name = ft_strdup(d_name);
		new->path = NULL;
		new->next = NULL;
		new->prop = prop;
	}
	return (new);
}
