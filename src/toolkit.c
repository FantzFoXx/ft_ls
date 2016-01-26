/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:45:47 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/26 12:01:17 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toolkit.h"
#include "ft_ls.h"
#include "libft.h"
#include "t_dir_content.h"

void	realloc_dirent(struct dirent ***items, size_t size)
{
	struct dirent	**new;
	int				size_tab;
	int				i;

	size_tab = 0;
	if (*items)
		while ((*items)[size_tab] != 0)
			size_tab++;
	new = (struct dirent **)malloc(sizeof(struct dirent *) *
			(size_tab + size + 1));
	new[size_tab + size] = NULL;
	i = -1;
	while (++i < size_tab)
		new[i] = (*items)[i];
	free(*items);
	*items = new;
}
