/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 10:13:32 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/01 10:17:52 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	char *params;
	char **params_d;

	params = NULL;
	params_d = NULL;
	get_args(argc, argv, &params, &params_d);
	ft_ls(params, params_d);
	return (0);
}
