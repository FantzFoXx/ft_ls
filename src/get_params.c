/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:26:49 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/20 18:37:15 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

static int	in_args(char *alrd_params, char *cur_params, char cmp)
{
	int i;

	i = -1;
	if (cmp == '-')
		return (0);
	while (alrd_params[++i] != 0)
		if (alrd_params[i] == cmp)
			return (1);
	i = -1;
	while (cur_params[++i] != 0)
		if (cur_params[i] == cmp)
			return (1);
	return (0);
}

static char	*get_params(char **params, char *cur_param)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_strnew(ft_strlen(cur_param) - 1);
	while (cur_param[++i] != 0)
		if (!in_args(*params, str, cur_param[i]))
			str[j++] = cur_param[i];
	*params = ft_strjoin(*params, str);
	return (*params);
}

static char	**get_entity(char ***params, char *cur_param)
{
	static int	i = -1;

	realloc_tab(params, 1);
	i++;
	params[0][i] = ft_strdup(cur_param);
	return (*params);
}

void		get_args(int ac, char **av, char **ret_params, char ***ret_paths)
{
	int		i;

	i = 0;
	*ret_params = ft_strnew(0);
	while (++i < ac && (av[i][0] == '-' && ft_strlen(av[i]) != 1)
			&& (ft_strcmp(av[i], "--") != 0))
		*ret_params = get_params(ret_params, av[i]);
	*ret_paths = (char **)malloc(sizeof(char *) * 1);
	*ret_paths[0] = NULL;
	while (i < ac)
		*ret_paths = get_entity(ret_paths, av[i++]);
}
