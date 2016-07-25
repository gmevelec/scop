/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 19:32:00 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/17 15:35:35 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"

t_raw_model		load_to_vao(t_env *env, t_indice indices)
{
	int			vaoid;
	t_raw_model	raw_model;

	vaoid = create_vao();
	bind_indices_buffer(indices.array, indices.count);
	store_data_in_attribute_list(0, 3, 0, env);
	store_data_in_attribute_list(1, 2, 1, env);
	unbind_vao();
	raw_model.vaoid = vaoid;
	raw_model.vertex_count = indices.count;
	return (raw_model);
}

int				create_vao(void)
{
	GLuint		vaoid;

	glGenVertexArrays(1, &vaoid);
	glBindVertexArray(vaoid);
	return (vaoid);
}

void			store_data_in_attribute_list(int attribute_number,
					int coord_size, int n, t_env *env)
{
	GLuint		vboid;

	glGenBuffers(1, &vboid);
	glBindBuffer(GL_ARRAY_BUFFER, vboid);
	if (n == 0)
		glBufferData(GL_ARRAY_BUFFER, env->vertices.count * sizeof(GLfloat),
			env->vertices.array, GL_STATIC_DRAW);
	else if (n == 1)
		glBufferData(GL_ARRAY_BUFFER, env->texture_array.count *
			sizeof(GLfloat), env->texture_array.array, GL_STATIC_DRAW);
	glVertexAttribPointer(attribute_number, coord_size,
		GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void			unbind_vao(void)
{
	glBindVertexArray(0);
}

void			bind_indices_buffer(GLuint *indices, int length)
{
	GLuint		vboid;

	glGenBuffers(1, &vboid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(GLuint),
				indices, GL_STATIC_DRAW);
	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(65535);
}
