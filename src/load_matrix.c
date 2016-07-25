/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 17:09:44 by gmevelec          #+#    #+#             */
/*   Updated: 2015/06/03 17:09:44 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"

void	load_matrix(GLuint location, GLfloat mat[16])
{
	glUniformMatrix4fv(location, 1, GL_FALSE, mat);
}

void	load_transformation_matrix(GLuint transf_matrix, GLfloat mat[16])
{
	load_matrix(transf_matrix, mat);
}

void	load_projection_matrix(GLuint projection_matrix, GLfloat mat[16])
{
	load_matrix(projection_matrix, mat);
}

void	load_view_matrix(GLuint view_matrix, GLfloat mat[16], t_camera camera)
{
	create_view_matrix(mat, camera);
	load_matrix(view_matrix, mat);
}
