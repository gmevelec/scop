/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 10:39:38 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/17 14:33:21 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"

void		init_entity(t_env *env)
{
	env->entity.position.x = 0;
	env->entity.position.y = 0;
	env->entity.position.z = -10;
	env->entity.rot.x = 0;
	env->entity.rot.y = 0;
	env->entity.rot.z = 0;
//	env->entity.texture.texture_id = load_bmp("./texture/wall.bmp", env);
	env->entity.scale = 1;
}

void		init_camera(t_env *env)
{
	env->camera.position.x = 0;
	env->camera.position.y = 0;
	env->camera.position.z = -1;
}

void		init_options(t_env *env)
{
	env->pause = 0;
	env->draw_type = GL_TRIANGLE_FAN;
}

void		init_env(t_env *env)
{
	init_entity(env);
	init_camera(env);
	init_options(env);
}
