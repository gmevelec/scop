/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_model.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:01:25 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/13 15:35:59 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"

void		test_file(const char *filename)
{
	char	*type;

	type = strrchr(filename, '.');
	if (!type || type == filename)
		ft_print(EXIT_ERROR, 0, "File: \"%s\" is not a correct file", filename);
	ft_print(DEBUG, 0, "%s", type);
	if (strcmp(type, ".obj"))
		ft_print(EXIT_ERROR, 0, "File: \"%s\" is not a correct file", filename);
}

void		init_model(const char **argv, t_env *env)
{
	env->obj_model = (t_obj_model*)malloc(sizeof(t_obj_model));
	test_file(argv[1]);
	env->entity.texture.model = load_obj_model(argv[1], env);
}
