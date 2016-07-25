/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 10:53:06 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/13 12:36:12 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"

void		bind_attributes(GLuint program_id)
{
	glBindAttribLocation(program_id, 0, "position");
	glBindAttribLocation(program_id, 1, "textureCoords");
}

void		get_all_uniform_location(GLuint program_id, t_env *env)
{
	env->transf_mat_id = glGetUniformLocation(program_id, "tMatrix");
	env->proj_mat_id = glGetUniformLocation(program_id, "pMatrix");
	env->view_mat_id = glGetUniformLocation(program_id, "vMatrix");
}

void		start(GLuint program_id)
{
	glUseProgram(program_id);
}

void		stop(void)
{
	glUseProgram(0);
}

void		shader_error(GLuint shader_id)
{
	int			info_log_length;
	int			chars_written;
	char		*info_log;

	ft_print(ERROR, 0, "Unable to compile");
	info_log_length = 0;
	chars_written = 0;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0)
	{
		info_log = (char *)malloc(info_log_length);
		glGetShaderInfoLog(shader_id, info_log_length,
			&chars_written, info_log);
		printf("%s\n", info_log);
	}
	glDeleteShader(shader_id);
}

GLuint		load_shader(GLuint type, t_env *env)
{
	GLuint		shader_id;
	int			compile_status;

	shader_id = glCreateShader(type);
	if (type == GL_VERTEX_SHADER)
		glShaderSource(shader_id,
			env->shader.vertex_shader.size,
			(const GLchar **)env->shader.vertex_shader.shader, NULL);
	else
		glShaderSource(shader_id,
			env->shader.fragment_shader.size,
			(const GLchar **)env->shader.fragment_shader.shader, NULL);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
	if (compile_status != GL_TRUE)
	{
		shader_error(shader_id);
		return (shader_id);
	}
	return (shader_id);
}

void		shader_program(t_env *env)
{
	env->shader.vertex_shader_id = load_shader(GL_VERTEX_SHADER, env);
	env->shader.fragment_shader_id = load_shader(GL_FRAGMENT_SHADER, env);
	env->shader.program_id = glCreateProgram();
	glAttachShader(env->shader.program_id, env->shader.vertex_shader_id);
	glAttachShader(env->shader.program_id, env->shader.fragment_shader_id);
	bind_attributes(env->shader.program_id);
	glLinkProgram(env->shader.program_id);
	glValidateProgram(env->shader.program_id);
	get_all_uniform_location(env->shader.program_id, env);
}
