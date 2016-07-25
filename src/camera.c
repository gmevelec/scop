/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:07:16 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/17 13:09:32 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"

void		increase_cam_position(t_camera *camera, GLfloat x, GLfloat y, GLfloat z)
{
	camera->position.x += x;
	camera->position.y += y;
	camera->position.z += z;
}
