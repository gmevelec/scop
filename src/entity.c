/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 17:42:10 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/13 15:33:04 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"

void		increase_position(t_entity *entity, GLfloat x, GLfloat y, GLfloat z)
{
	entity->position.x += x;
	entity->position.y += y;
	entity->position.z += z;
}

void		increase_rotation(t_entity *entity, GLfloat x, GLfloat y, GLfloat z)
{
	entity->rot.x += x;
	entity->rot.y += y;
	entity->rot.z += z;
}
