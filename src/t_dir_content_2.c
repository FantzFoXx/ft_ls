/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 12:00:35 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/02 17:41:14 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir_content.h"
#include <stdlib.h>
#include "print_ls.h"

t_dir_item	*t_item_new(struct dirent *item)
{
	t_dir_item *new;

	new = (t_dir_item *)malloc(sizeof(t_dir_item));
	if (new)
	{
		new->item_name = ft_strdup(item->d_name);
		new->item = item;
		//new->prop = prop;
		new->next = NULL;
	}
	return (new);
}

int			t_item_place(t_dir_item **first, t_dir_item *new)
{
	t_dir_item *index;
	t_dir_item *bak;

		//	ft_trace("__pass________", "place");
	bak = *first;
	index = *first;
	if (!index)
		*first = new;
	else
		while (index)
		{
			if (ft_strcmp(new->item_name, index->item_name) < 0)
			{
				new->next = bak->next;	
				bak->next = new;
				return (0);
			}
			if (!index->next)
			{
				index->next = new;
				break ;
			}
			bak = index;
			index = index->next;
		}
	return (0);
}
