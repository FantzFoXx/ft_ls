/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 10:13:32 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/14 14:36:11 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	char *params = ft_strnew(5);
	params[0] = 'l';
	params[1] = 'a';
	if (argc < 2)
		ft_ls(NULL, NULL);
	else
		ft_ls(params, &argv[1]);
	return(0);
}
