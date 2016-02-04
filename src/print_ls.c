/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 15:17:19 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/04 16:03:02 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_ls.h"

void				print_ls(t_dir_item *items)
{
	while (items)
	{
		ft_putendl(items->item_name);
		items = items->next;
	}
}

void				print_all_ls(t_dir_item *items)
{
	while (items)
	{
		if (items->item_name[0] != '.')
			ft_putendl(items->item_name);
		items = items->next;
	}
}
