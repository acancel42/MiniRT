#include "miniRT.h"

static int	select_parser(char **line_parsed, t_minirt *minirt)
{
	if (ft_strncmp(line_parsed[0], "A", ft_strlen(line_parsed[0])) == 0)
		return (parse_ambient_light(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "C", ft_strlen(line_parsed[0])) == 0)
		return (parse_camera(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "L", ft_strlen(line_parsed[0])) == 0)
		return (parse_light(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "pl", ft_strlen(line_parsed[0])) == 0)
		return (parse_plane(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "sp", ft_strlen(line_parsed[0])) == 0)
		return (parse_sphere(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "cy", ft_strlen(line_parsed[0])) == 0)
		return (parse_cylinder(line_parsed, minirt));
	else if (ft_strncmp(line_parsed[0], "#", ft_strlen(line_parsed[0])) == 0)
		return (0);
	return (-1);
}

int	prasing_map(t_minirt *minirt, char *file)
{
	int		map_file;
	char	*line;

	map_file = open(file, O_RDONLY);
	if (map_file == -1)
	{
		printf("Failed to open the map\n");
		return (-1);
	}
	line = get_next_line(map_file);
	while (line)
	{
		parse_line(line, minirt);
		free(line);
		line = get_next_line(map_file);
	}
	free(line);
	close(map_file);
	return (0);
}

void	parse_line(char *line, t_minirt *minirt)
{
	char	**line_parsed;

	line_parsed = ft_split_whitespace(line);
	if (!line_parsed)
		ft_free_exit(minirt, line, line_parsed, -1);
	if (!arr_len(line_parsed))
	{
		ft_free_arr(line_parsed);
		return ;
	}
	if (select_parser(line_parsed, minirt))
	{
		printf("Error map, on line : %s\n", line);
		ft_free_exit(minirt, line, line_parsed, 2);
	}
	ft_free_arr(line_parsed);
	return ;
}