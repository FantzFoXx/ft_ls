/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:26:49 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/14 16:52:07 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

static char **realloc_tab(char ***tab, size_t size)
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
	i = 0;

	while (i < size_tab)
	{
		new[i] = (*tab)[i];
		i++;
	}
	free(*tab);
	return (new);
}

static int	in_args(char **exist_params, char *new_params, char cmp)
{
	int i;
	int j;

	j = 0;
	i = -1;
	if (cmp == '-')
		return (0);
	while (new_params[++i] != 0)
		if (new_params[i] == cmp)
			return (1);
	i = 0;
	while (exist_params[i])
	{
		j = 0;
		while (exist_params[i][j])
		{
			if (exist_params[i][j] == cmp)
				return (1);
			j++;	
		}
		i++;
	}
	return (0);
}

static char	*get_params(char **params, char *cur_param)
{
	char *str;

	str = ft_strnew(ft_strlen(cur_param) - 1);
	*params = ft_strjoin(*params, &cur_param[1]);
	/*
	while (cur_param[++j] != 0)
		if (!in_args(*params, str, cur_param[j]))
			str[++i] = cur_param[j];
	size_param = ft_strlen(str) - 1;
	(*params) = realloc_tab(params, size_param);
	i = 1;
	while (str[i])
	{
		(*params)[*index] = ft_strnew(2);
		(*params)[*index][0] = '-';
		(*params)[*index][0] = str[i];
		i++;
		(*index)++;
	}*/
	return (*params);
}

static char	**get_entity(char ***params, char *cur_param, int *index)
{
	*params = realloc_tab(params, 1);
	(*params)[*index] = ft_strdup(cur_param);
	(*index)++;
	return (*params);
}

void		get_args(int ac, char **av, char *ret_params, char **ret_paths)
{
	int		i;
	(void)ret_paths;

	ret_params = ft_strnew(0);
	i = 0;
	// condition boucle a revoir
	while (++i < ac && (ft_strcmp(av[i], "--") != 0 && av[i][0] == '-'))
		ret_params = get_params(&ret_params, av[i]);
	i--;
	/*
	while (++i < ac)
		params = get_entity(&params, av[i], &index);
	t = -1;
	while (params[++t])
		ft_trace(params[t]);
		*/
}
