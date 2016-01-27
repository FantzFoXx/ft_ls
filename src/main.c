/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 10:13:32 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/27 17:57:53 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	char *params;
	char **params_d;

	params = NULL;
	params_d = NULL;
	if (argc < 2)
		ft_ls(NULL, NULL);
	else
	{
		get_args(argc, argv, &params, &params_d);
		if (params)
			check_params(params);
		ft_ls(params, params_d);
	}
	return (0);
}
