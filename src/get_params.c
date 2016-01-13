/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:26:49 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/13 11:27:15 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

static char **realloc_tab(char **tab, size_t size)
{
	char	**new;
	int		size_tab;
	int		i;

	size_tab = 0;
	if (tab)
		while (tab[size_tab] != 0)
			size_tab++;

	new = (char **)malloc(sizeof(char *) * size_tab + size + 1);
	new[size_tab + size] = NULL;
	ft_trace("malloc pass");
	i = 0;
	while (i < size_tab)
	{
		ft_trace("while pass");
		new[i] = tab[i];
		i++;
	}
	free(tab);
	return (new);
}

static char	**get_params(char **params, char *cur_param, int *index)
{
	size_t size_param;
	char *str;
	int i;

	size_param = ft_strlen(cur_param);
	ft_nbrtrace(size_param);
	params = realloc_tab(params, size_param);
	str = NULL;
	i = 1;
	while (cur_param[i] != 0)
	{
	ft_nbrtrace(*index);
		str = ft_strnew(2);
		str[0] = '-';
		str[1] = cur_param[i];
		params[*index] = str;
		i++;
	ft_trace("pass1");
		*index += 1;
		//ft_trace(params[*index]);
	}
	ft_trace("out while");
	return (params);
}
/*
static char	**get_entity(char **params, char *cur_param, int *index)
{
	params = realloc_tab(params, 1);
	params[*index] = ft_strdup(cur_param);
	*index += 1;
	return (params);
}
*/
char		**get_args(int ac, char **av)
{
	int		i;
	int		t;
	int		index;
	char	**params;

	//params = (char **)malloc(sizeof(char *) * 1);
	//params[0] = NULL;
	params = NULL;
	i = 1;
	index = 0;
	while (i < ac && av[i][0] == '-')
	{
		ft_nbrtrace(i);
		params = get_params(params, av[i], &index);
		i++;
	}
	/*
	while (i < ac)
	{
		params = get_entity(params, av[i], &index);
		i++;
	}
	*/
t = 0;
	while (params[t])
	{
		ft_trace(params[t]);
		t++;
	}
	//ft_trace(params[1]);
	return (params);
}
