/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:45:47 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/21 18:49:29 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toolkit.h"
#include "ft_ls.h"

size_t	size_tab(char **tab)
{
	size_t size_tab;
	size_tab = 0;
	if (tab)
		while (tab[size_tab] != 0)
			size_tab++;
	return (size_tab);
}

void	realloc_tab(char ***tab, size_t size)
{
	char	**new;
	int		size_tab;
	int		i;

	size_tab = 0;
	if (*tab)
		while ((*tab)[size_tab] != 0)
			size_tab++;
	new = (char **)malloc(sizeof(char *) * (size_tab + size + 1));
	new[size_tab + size] = NULL;
	i = -1;
	while (++i < size_tab)
		new[i] = (*tab)[i];
	free(*tab);
	*tab = new;
}

void	realloc_dirent(struct dirent ***items, size_t size)
{
	struct dirent	**new;
	int				size_tab;
	int				i;

	size_tab = 0;
	if (*items)
		while ((*items)[size_tab] != 0)
			size_tab++;
	new = (char **)malloc(sizeof(char *) * (size_tab + size + 1));
	new[size_tab + size] = NULL;
	i = -1;
	while (++i < size_tab)
		new[i] = (*items)[i];
	free(*items);
	*items = new;
}
