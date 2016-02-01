/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 13:02:59 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/01 14:04:44 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "t_dir_content.h"

#ifndef CATCH_ERRORS_H
# define CATCH_ERRORS_H

void			error_params(char *supported, char param);
int				catch_error(int err_code, char *err_msg);
#endif
