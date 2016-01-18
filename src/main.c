/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 10:13:32 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/18 15:30:47 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	char *params = NULL;
	char **params_d = NULL;
	if (argc < 2)
		ft_ls(NULL, NULL);
	else
	{
		get_args(argc, argv, &params, &params_d);
		ft_ls(params, params_d);
	}
	return(0);
}
