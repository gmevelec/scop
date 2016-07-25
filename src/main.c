/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:59:10 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/17 17:11:05 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"
#include "/nfs/2013/g/gmevelec/lib/mlx/mlx.h"
#include "../libft/libft.h"
#include "/nfs/2013/g/gmevelec/perso/libs/libprint/inc/libprint.h"
#include <time.h>

void			do_pause(t_env *env)
{
	if (env->pause == 0)
		env->pause = 1;
	else
		env->pause = 0;
}

void			move_camera(int key, t_camera *camera)
{
	if (key == GLFW_KEY_S)
		increase_cam_position(camera, 0, 0, 0.2);
	if (key == GLFW_KEY_W)
		increase_cam_position(camera, 0, 0, -0.2);
	if (key == GLFW_KEY_A)
		increase_cam_position(camera, -0.2, 0, 0);
	if (key == GLFW_KEY_D)
		increase_cam_position(camera, 0.2, 0, 0);
}

void			rot_entity(int key, t_entity *entity)
{
	if (key == GLFW_KEY_DOWN)
		increase_rotation(entity, 4, 0, 0);
	if (key == GLFW_KEY_UP)
		increase_rotation(entity, -4, 0, 0);
	if (key == GLFW_KEY_LEFT)
		increase_rotation(entity, 0, 4, 0);
	if (key == GLFW_KEY_RIGHT)
		increase_rotation(entity, 0, -4, 0);
}

void			move_entity(int key, t_entity *entity)
{
	if (key == GLFW_KEY_K)
		increase_position(entity, 0, -0.2, 0);
	if (key == GLFW_KEY_I)
		increase_position(entity, 0, 0.2, 0);
	if (key == GLFW_KEY_J)
		increase_position(entity, -0.2, 0, 0);
	if (key == GLFW_KEY_L)
		increase_position(entity, 0.2, 0, 0);
}

static void		key_callback(GLFWwindow *window, int key,
						int scancode, int action, int mods)
{
	t_env *env;

	env = glfwGetWindowUserPointer(window);
	(void)mods;
	(void)scancode;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		do_pause(env);
	move_camera(key, &env->camera);
	move_entity(key, &env->entity);
	rot_entity(key, &env->entity);
}

void			update_fps(GLFWwindow *window)
{
	static double	previous_seconds = 0;
	static int		frame_count;
	double			current_seconds;
	double			elapsed_seconds;
	double			fps;
	char			tmp[24];

	current_seconds = glfwGetTime();
	elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25)
	{
		previous_seconds = current_seconds;
		fps = (double)frame_count / elapsed_seconds;
		sprintf(tmp, "%.2f FPS", fps);
		glfwSetWindowTitle(window, tmp);
		frame_count = 0;
	}
	frame_count++;
}

void			loop(t_env *env)
{
	if (!env->pause)
		increase_rotation(&(env->entity), 0, 1, 0);
	prepare();
	start(env->shader.program_id);
	render(env);
	load_view_matrix(env->view_mat_id, env->view_mat, env->camera);
	stop();
	update_fps(env->window);
	glfwPollEvents();
	glfwSwapBuffers(env->window);
}

int				main(int argc, char const *argv[])
{
	t_env	env;

	if (argc < 2)
		ft_print(EXIT_ERROR, 0, "Program must have 2 arguments");
	init_env(&env);
	init_glfw(&env);
	init_model(argv, &env);
	ft_print(FINE, 0, "Initialization done.");
//	env.entity.texture.texture_id = load_texture("texture/cat.png");
//	env.entity.texture.texture_id = load_texture("texture/wall.xpm");
	env.entity.texture.texture_id = load_texture("models/katarina/katarinabasediffuse.png");
//	env.entity.texture.texture_id = load_texture("models/stall/stall.png");
//	env.entity.texture.texture_id = load_texture("models/urfthenamitee/urfthenamitee.png");
	get_shaders(&env);
	shader_program(&env);
	renderer(&env);
	ft_print(FINE, 0, "Starting to render !");
	glfwSetKeyCallback(env.window, key_callback);
	while (!glfwWindowShouldClose(env.window))
		loop(&env);
	glfwDestroyWindow(env.window);
	glfwTerminate();
	return (0);
}
