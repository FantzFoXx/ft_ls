/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:16:18 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/13 11:27:17 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int		ft_ls(char **params)
{
	(void)params;
	DIR *curr_dir;
	struct dirent *items;

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
	return (1);
}
