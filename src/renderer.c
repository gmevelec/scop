/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 19:43:36 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/17 14:53:45 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"
#include <math.h>

void		prepare(void)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void		render(t_env *env)
{
	glBindVertexArray(env->entity.texture.model.vaoid);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	create_transformation_matrix(env->transf_mat, env->entity.position,
		env->entity.rot, env->entity.scale);
	load_transformation_matrix(env->transf_mat_id, env->transf_mat);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, env->entity.texture.texture_id);
	glDrawElements(env->draw_type, env->entity.texture.model.vertex_count,
		GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

void		create_projection_matrix(t_env *env)
{
	GLfloat		aspect_ratio;
	GLfloat		y_scale;
	GLfloat		x_scale;
	GLfloat		frustum_lenght;

	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	y_scale = (float)((1.0 / tan(convert_to_rad(FOV / 2.0))) * aspect_ratio);
	x_scale = y_scale / aspect_ratio;
	frustum_lenght = FAR_PLANE - NEAR_PLANE;
	env->proj_mat[0] = x_scale;
	env->proj_mat[1] = 0.0f;
	env->proj_mat[2] = 0.0f;
	env->proj_mat[3] = 0.0f;
	env->proj_mat[4] = 0.0f;
	env->proj_mat[5] = y_scale;
	env->proj_mat[6] = 0.0f;
	env->proj_mat[7] = 0.0f;
	env->proj_mat[8] = 0.0f;
	env->proj_mat[9] = 0.0f;
	env->proj_mat[10] = -((FAR_PLANE + NEAR_PLANE) / frustum_lenght);
	env->proj_mat[11] = -1;
	env->proj_mat[12] = 0.0f;
	env->proj_mat[13] = 0.0f;
	env->proj_mat[14] = -((2 * NEAR_PLANE * FAR_PLANE) / frustum_lenght);
	env->proj_mat[15] = 0;
}

void		renderer(t_env *env)
{
	create_projection_matrix(env);
	start(env->shader.program_id);
	load_projection_matrix(env->proj_mat_id, env->proj_mat);
	stop();
}
