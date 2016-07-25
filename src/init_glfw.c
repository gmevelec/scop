/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_glfw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 10:48:53 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/14 14:05:33 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"

void		print_infos(void)
{
	const GLubyte	*render;
	const GLubyte	*version;

	render = glGetString(GL_RENDERER);
	version = glGetString(GL_VERSION);
	ft_print(FINE, 0, "Render: %s", render);
	ft_print(FINE, 0, "OpenGL version supported %s", version);
}

void		init_glfw(t_env *env)
{
	if (!glfwInit())
		exit(-1);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	env->window = glfwCreateWindow(WIDTH, HEIGHT, "SCOP", NULL, NULL);
	if (!env->window)
	{
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(env->window);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	print_infos();
	glClearColor(0, 0, 0, 1);
	glfwSetWindowUserPointer(env->window, env);
	glfwSetInputMode(env->window, GLFW_STICKY_KEYS, 1);
}
