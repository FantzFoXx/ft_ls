#include "option_g.h"
#include "colors.h"
#include "t_dir_content.h"
#include "unistd.h"

static char *colorize_item(t_dir_item *item, char *color_fg)
{
	char *tmp;
	char *filename;

	tmp = ft_strjoin(color_fg, item->item_name);
	filename = ft_strjoin(tmp, DEFAULT_COLOR);
	free(tmp);
	return (filename);
}

static char *colorize_item_hl(t_dir_item *item, char *color_fg, char *color_bg)
{
	char *filename;
	char *tmp;

	filename = ft_strjoin(color_fg, color_bg);
	tmp = ft_strjoin(filename, item->item_name);
	free(filename);
	filename = ft_strjoin(tmp, DEFAULT_COLOR);
	free(tmp);
	return (filename);
}

static char	*apply_option_g(t_dir_item *item)
{
	char *filename;

	if (S_ISDIR(item->prop.st_mode))
		if ((S_IWOTH & item->prop.st_mode))
			filename = colorize_item_hl(item, DARK_BLACK, HLIGHT_YELLOW);
		else
			filename = colorize_item(item, CYAN);
	else if (S_ISCHR(item->prop.st_mode))
		filename = colorize_item_hl(item, DARK_BLUE, HLIGHT_YELLOW);
	else if (is_archive_file(item->item_name))
		filename = colorize_item(item, GREEN);
	else if (S_ISBLK(item->prop.st_mode))
		filename = colorize_item_hl(item, DARK_BLUE, HLIGHT_CYAN);
	else if (S_ISFIFO(item->prop.st_mode))
		filename = colorize_item(item, DARK_YELLOW);
	else if (S_ISLNK(item->prop.st_mode))
		filename = colorize_item(item, DARK_PURPLE);
	else if (is_exec_file(item->prop.st_mode))
		filename = colorize_item(item, DARK_RED);
	else
		filename = ft_strdup(item->item_name);
	return (filename);
}

static char *get_link_pointer(t_dir_item *item, char *filename)
{
	char	*tmp;
	char	buf[1024];
	ssize_t	read;

	read = 0;
	tmp = ft_strjoin(filename, " -> ");
	free(filename);
	if (item->path)
		filename = ft_strjoin(item->path, item->item_name);
	else
		filename = ft_strdup(item->item_name);
	read = readlink(filename, buf, sizeof(buf));
	buf[read] = 0;
	free(filename);
	filename = ft_strjoin(tmp, buf);
	free(tmp);
	return (filename);
}

char		*get_item_name(t_dir_item *item, char *params)
{
	static int	option_g = -1;
	char		*filename;
	char		*tmp;

	tmp = NULL;
	filename = NULL;
	if (option_g == -1)
		option_g = (ft_strchr(params, 'G')) ? 1 : 0;
	if (option_g)
		filename = apply_option_g(item);
	else
		filename = ft_strdup(item->item_name);
	if (ft_strchr(params, 'l') && S_ISLNK(item->prop.st_mode))
		filename = get_link_pointer(item, filename);
	return (filename);
}
