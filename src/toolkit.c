/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:45:47 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/14 11:49:07 by udelorme         ###   ########.fr       */
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
