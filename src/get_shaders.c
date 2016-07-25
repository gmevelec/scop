/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shaders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 10:53:06 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/13 15:36:09 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"
#include "../libft/libft.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int			get_length_file(char *file)
{
	int		fd;
	char	*line;
	int		i;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_print(EXIT_ERROR, 0, "Couldn't open file: %s", file);
	i = 0;
	while (get_next_line(fd, &line))
	{
		i++;
	}
	return (i);
}

void		stock_shader(GLchar **shader, char *file)
{
	int				fd;
	char			*line;
	int				i;
	struct stat		buf;
	int				size;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_print(EXIT_ERROR, 0, "Couldn't open file: %s", file);
	i = 0;
	while (get_next_line(fd, &line))
	{
		shader[i] = ft_strdup(line);
		ft_strcat(shader[i], "\n");
		i++;
	}
	shader[i] = NULL;
	fstat(fd, &buf);
	size = buf.st_size;
}

void		get_shaders(t_env *env)
{
	int		n;

	n = get_length_file("./shaders/vertex_shader.txt");
	env->shader.vertex_shader.shader = malloc(sizeof(GLchar*) * (n + 1));
	stock_shader(env->shader.vertex_shader.shader,
			"./shaders/vertex_shader.txt");
	env->shader.vertex_shader.size = n;
	n = get_length_file("./shaders/fragment_shader.txt");
	env->shader.fragment_shader.shader = malloc(sizeof(GLchar*) * (n + 1));
	stock_shader(env->shader.fragment_shader.shader,
		"./shaders/fragment_shader.txt");
	env->shader.fragment_shader.size = n;
}
