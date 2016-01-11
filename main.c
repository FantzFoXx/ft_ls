#include "ft_ls.h"

int		main(int argc, char **argv)
{
	if (argc < 2)
		ft_ls(NULL);
	else
		ft_ls(get_params(argc, argv));
	return(0);
}
