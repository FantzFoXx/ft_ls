/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:26:49 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/12 17:12:58 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

static char **realloc_tab(char **tab, size_t size)
{
	char	**new;
	int		i;

	i = 0;
	while (tab[i] != 0)
		i++;
	new = (char **)malloc(sizeof(char *) * i + size);
	if (!new)
		return (NULL);
	new[size] = 0;
	i = 0;
	while (tab[i] != 0)
	{
		new[i] = tab[i];
		i++;
	}
	free(tab);
	return (new);
}

static char	**get_params(char **params, char *cur_param, int *index)
{
	size_t size_param;
	int i;

	size_param = ((ft_strlen(cur_param) - 1));
	params = realloc_tab(params, size_param);
	params[size_param] = 0;
	i = 1;
	while (cur_param[i] != 0)
	{
		params[*index] = ft_strnew(2);
		params[*index][0] = '-';
		params[*index][1] = cur_param[i];
		i++;
		*index += 1;
	}
	return (params);
}
/*
   static char	**get_entity(char **params, char *cur_param, int index)
   {

   }
   */
char		**get_args(int ac, char **av)
{
	int		i;
	int		index;
	char	**params;

	params = (char **)malloc(sizeof(char *) * 1);
	params[0] = NULL;
	i = 1;
	index = 0;
	while (i < ac)
	{
		if (av[i][0] != '-')
			break;
		params = get_params(params, av[i], &index);
		i++;
	}
	while (i < ac)
	{
	}
		
	}
	//ft_trace(params[0]);
	//ft_trace(params[1]);
	return (params);
}
