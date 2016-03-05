#include "option_l.h"
#include "stdlib.h"

t_litem	*t_litem_new(char *str)
{
	t_litem *new;

	new = (t_litem *)malloc(sizeof(t_litem));
	if (new)
	{
		new->str = str;
		new->next = NULL;
	}
	return (new);
}

void	t_litem_push(t_litem **first, t_litem *new)
{
	t_litem *index;

	index = *first;
	if (!index)
		*first = new;
	else
	{
		while (index->next)
			index = index->next;
		index->next = new;
	}
}
