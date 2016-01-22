/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 17:28:13 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/22 11:51:40 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir_content.h"
#include <stdlib.h>

t_dir_content	*t_dir_new(void)
{
	t_dir_content *new;
	new = (t_dir_content *)malloc(sizeof(t_dir_content));
	new->items = (struct dirent **)malloc(sizeof(struct dirent*));
	new-> dir_name = NULL;
	new-> next = NULL;
	return (new);
}

void			t_dir_push(t_dir_content **first, t_dir_content *new)
{
	t_dir_content *index;

	index = *first;
	while (index->next)
		index = index->next;
	index->next = new;
}
