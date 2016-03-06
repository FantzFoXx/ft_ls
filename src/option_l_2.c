/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 21:12:48 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/06 00:16:24 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "option_l.h"
#include <sys/types.h>

char	*add_mode_to_right(char *rights, char *add)
{
	char	*tmp;

	tmp = ft_strdup(rights);
	free(rights);
	rights = ft_strjoin(tmp, add);
	free(tmp);
	return (rights);
}

char	*get_right_file_type(mode_t mode)
{
	char *rights;

	rights = NULL;
	if (S_ISDIR(mode))
		rights = ft_strdup("d");
	else if (S_ISCHR(mode))
		rights = ft_strdup("c");
	else if (S_ISFIFO(mode))
		rights = ft_strdup("p");
	else if (S_ISLNK(mode))
		rights = ft_strdup("l");
	else if (S_ISSOCK(mode))
		rights = ft_strdup("s");
	else if (S_ISBLK(mode))
		rights = ft_strdup("b");
	else if (S_ISREG(mode))
		rights = ft_strdup("-");
	return (rights);
}

t_litem	*get_rights(mode_t mode)
{
	char	*rights;

	rights = get_right_file_type(mode);
	rights = add_mode_to_right(rights, ((mode & S_IRUSR) ? "r" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IWUSR) ? "w" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IXUSR) ? "x" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IRGRP) ? "r" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IWGRP) ? "w" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IXGRP) ? "x" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IROTH) ? "r" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IWOTH) ? "w" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IXOTH) ? "x" : "-"));
	return (t_litem_new(rights));
}

void	free_ligtn(t_list **container)
{
	t_list	*bak;
	t_litem	*index;
	t_litem	*index_next;

	index = NULL;
	index_next = NULL;
	bak = (*container)->next;
	index = (*container)->content;
	while (index)
	{
		index_next = index->next;
		free(index->str);
		free(index);
		index = index_next;
	}
	free(*container);
	*container = bak;
}

char	*get_maj_min(dev_t st_rdev)
{
	char	*maj;
	char	*min;
	char	*tmp;
	char	*final;
	size_t	i;

	maj = ft_strdup(ft_itoa(major(st_rdev)));
	tmp = ft_strjoin(maj, ", ");
	min = ft_strdup(ft_itoa(minor(st_rdev)));
	i = -1;
	while (++i < (3 - ft_strlen(min)))
	{
		final = ft_strjoin(tmp, " ");
		free(tmp);
		tmp = final;
	}
	final = ft_strjoin(tmp, min);
	free(tmp);
	return (final);
}
