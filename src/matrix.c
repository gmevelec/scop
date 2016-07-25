/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 18:18:44 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/13 13:49:34 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"
#include <math.h>

void	set_identity(GLfloat mat[16])
{
	mat[0] = 1.0;
	mat[1] = 0.0;
	mat[2] = 0.0;
	mat[3] = 0.0;
	mat[4] = 0.0;
	mat[5] = 1.0;
	mat[6] = 0.0;
	mat[7] = 0.0;
	mat[8] = 0.0;
	mat[9] = 0.0;
	mat[10] = 1.0;
	mat[11] = 0.0;
	mat[12] = 0.0;
	mat[13] = 0.0;
	mat[14] = 0.0;
	mat[15] = 1.0;
}

void	translate_mat(GLfloat mat[16], t_vec3f vect)
{
	mat[12] += mat[0] * vect.x + mat[4] * vect.y + mat[8] * vect.z;
	mat[13] += mat[1] * vect.x + mat[5] * vect.y + mat[9] * vect.z;
	mat[14] += mat[2] * vect.x + mat[6] * vect.y + mat[10] * vect.z;
	mat[15] += mat[3] * vect.x + mat[7] * vect.y + mat[11] * vect.z;
}

void	init_tab_rot_mat(GLfloat tab[26], t_vec3f vect, float angle)
{
	tab[0] = (float)cos(angle);
	tab[1] = (float)sin(angle);
	tab[2] = 1.0f - tab[0];
	tab[3] = vect.x * vect.y;
	tab[4] = vect.y * vect.z;
	tab[5] = vect.x * vect.z;
	tab[6] = vect.x * tab[1];
	tab[7] = vect.y * tab[1];
	tab[8] = vect.z * tab[1];
	tab[9] = vect.x * vect.x * tab[2] + tab[0];
	tab[10] = tab[3] * tab[2] + tab[8];
	tab[11] = tab[5] * tab[2] - tab[7];
	tab[12] = tab[3] * tab[2] - tab[8];
	tab[13] = vect.y * vect.y * tab[2] + tab[0];
	tab[14] = tab[4] * tab[2] + tab[6];
	tab[15] = tab[5] * tab[2] + tab[7];
	tab[16] = tab[4] * tab[2] - tab[6];
	tab[17] = vect.z * vect.z * tab[2] + tab[0];
}

void	rotate_mat(GLfloat mat[16], t_vec3f vect, float angle)
{
	GLfloat		tab[26];

	init_tab_rot_mat(tab, vect, angle);
	tab[18] = mat[0] * tab[9] + mat[4] * tab[10] + mat[8] * tab[11];
	tab[19] = mat[1] * tab[9] + mat[5] * tab[10] + mat[9] * tab[11];
	tab[20] = mat[2] * tab[9] + mat[6] * tab[10] + mat[10] * tab[11];
	tab[21] = mat[3] * tab[9] + mat[7] * tab[10] + mat[11] * tab[11];
	tab[22] = mat[0] * tab[12] + mat[4] * tab[13] + mat[8] * tab[14];
	tab[23] = mat[1] * tab[12] + mat[5] * tab[13] + mat[9] * tab[14];
	tab[24] = mat[2] * tab[12] + mat[6] * tab[13] + mat[10] * tab[14];
	tab[25] = mat[3] * tab[12] + mat[7] * tab[13] + mat[11] * tab[14];
	mat[8] = mat[0] * tab[15] + mat[4] * tab[16] + mat[8] * tab[17];
	mat[9] = mat[1] * tab[15] + mat[5] * tab[16] + mat[9] * tab[17];
	mat[10] = mat[2] * tab[15] + mat[6] * tab[16] + mat[10] * tab[17];
	mat[11] = mat[3] * tab[15] + mat[7] * tab[16] + mat[11] * tab[17];
	mat[0] = tab[18];
	mat[1] = tab[19];
	mat[2] = tab[20];
	mat[3] = tab[21];
	mat[4] = tab[22];
	mat[5] = tab[23];
	mat[6] = tab[24];
	mat[7] = tab[25];
}
