/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:45:47 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/01 16:18:18 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toolkit.h"
#include "ft_ls.h"
#include "libft.h"
#include "t_dir_content.h"
#include <unistd.h>

void	realloc_dirent(struct dirent ***props, size_t size)
{
	struct dirent	**new;
	int				size_tab;
	int				i;

	//ft_trace("pass", "#################################");
	new = NULL;
	size_tab = 0;
	if (*props)
		while ((*props)[size_tab] != 0)
		{
			//usleep(1000);
			//ft_trace("prop", (*props)[size_tab]->d_name);
			size_tab++;
		}
	//ft_nbrtrace("size_tab", size_tab);
	new = (struct dirent **)malloc(sizeof(struct dirent *) *
			(size_tab + size + 1));
	if (!new)
	{
		sleep(10);
	}
	new[size_tab + size] = NULL;
	i = -1;
	while (++i < size_tab)
		new[i] = (*props)[i];
	free(*props);
	*props = new;
}
/*
void	realloc_props(struct stat **props, size_t size)
{
	struct stat		*new;
	int				size_tab;
	int				i;

	new = NULL;
	size_tab = 0;
	if (*props)
		while ((*props)[size_tab] != 0)
			size_tab++;
	new = (struct stat **)malloc(sizeof(struct stat *) *
			(size_tab + size + 1));
	new[size_tab + size] = NULL;
	i = -1;
	while (++i < size_tab)
		new[i] = (*props)[i];
	free(*props);
	*props = new;
}*/

