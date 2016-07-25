/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 17:26:00 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/13 13:50:10 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"
#include <math.h>

float	convert_to_rad(float angle)
{
	return (angle / 180 * 3.141592654);
}

void	scale_mat(GLfloat mat[16], t_vec3f vect)
{
	mat[0] = mat[0] * vect.x;
	mat[1] = mat[1] * vect.x;
	mat[2] = mat[2] * vect.x;
	mat[3] = mat[3] * vect.x;
	mat[4] = mat[4] * vect.y;
	mat[5] = mat[5] * vect.y;
	mat[6] = mat[6] * vect.y;
	mat[7] = mat[7] * vect.y;
	mat[8] = mat[8] * vect.z;
	mat[9] = mat[9] * vect.z;
	mat[10] = mat[10] * vect.z;
	mat[11] = mat[11] * vect.z;
}

void	create_transformation_matrix(GLfloat mat[16], t_vec3f trans,
									t_vec3f rot, GLfloat scale)
{
	t_vec3f	vect;

	set_identity(mat);
	translate_mat(mat, trans);
	vect.x = 1;
	vect.y = 0;
	vect.z = 0;
	rotate_mat(mat, vect, convert_to_rad(rot.x));
	vect.x = 0;
	vect.y = 1;
	vect.z = 0;
	rotate_mat(mat, vect, convert_to_rad(rot.y));
	vect.x = 0;
	vect.y = 0;
	vect.z = 1;
	rotate_mat(mat, vect, convert_to_rad(rot.z));
	vect.x = scale;
	vect.y = scale;
	vect.z = scale;
	scale_mat(mat, vect);
}

void	create_view_matrix(GLfloat mat[16], t_camera camera)
{
	t_vec3f	vect;

	set_identity(mat);
	vect.x = 0;
	vect.y = 0;
	vect.z = 1;
	rotate_mat(mat, vect, convert_to_rad(camera.pitch));
	vect.x = 0;
	vect.y = 1;
	vect.z = 0;
	rotate_mat(mat, vect, convert_to_rad(camera.yaw));
	vect.x = -camera.position.x;
	vect.y = -camera.position.y;
	vect.z = -camera.position.z;
	translate_mat(mat, vect);
}
