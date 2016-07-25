/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 19:43:36 by gmevelec          #+#    #+#             */
/*   Updated: 2016/03/17 17:08:40 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/scop.h"
#include "../libft/libft.h"
#include <fcntl.h>

void			print_vertex(t_vec3f *vertex, int nb_vertex)
{
	ft_print(DEBUG, 0, "Print vertex");
	for (int i = 0; i < nb_vertex; ++i)
	{
		ft_print(DEBUG, 1, "%f %f %f", vertex[i].x, vertex[i].y, vertex[i].z);
	}
}

void			print_textures(t_vec2f *textures, int nb_textures)
{
	ft_print(DEBUG, 0, "Print textures");
	for (int i = 0; i < nb_textures; ++i)
	{
		ft_print(DEBUG, 1, "%f %f", textures[i].x, textures[i].y);
	}
}

void			print_normals(t_vec3f *normals, int nb_normals)
{
	ft_print(DEBUG, 0, "Print normals");
	for (int i = 0; i < nb_normals; ++i)
	{
		ft_print(DEBUG, 1, "%f %f %f", normals[i].x, normals[i].y, normals[i].z);
	}
}

void			print_faces(t_face *faces, int nb_faces)
{
	ft_print(DEBUG, 0, "Print faces");
	for (int i = 0; i < nb_faces; ++i)
	{
		for (int j = 0; j < faces[i].num_elems; ++j)
		{
			ft_print(DEBUG, 1, "%d/%d/%d", faces[i].elem[j].v, faces[i].elem[j].t, faces[i].elem[j].n);
		}
	}
}

void			print_indices(t_indice *indice)
{
	int		i;

	i = -1;
	while (++i < indice->count)
		ft_print(DEBUG, 0, "%d", indice->array[i]);
}

void			print_texture_array(t_texture_coord *textures)
{
	int		i;

	i = -1;
	while (++i < textures->count)
		ft_print(DEBUG, 0, "%f", textures->array[i]);
}

void			print_first_passage_info(t_mesh *mesh)
{
	ft_print(DEBUG, 0, "First passage:");
	ft_print(DEBUG, 1, "%i vertices.", mesh->num_vertex);
	ft_print(DEBUG, 1, "%i texture coords.", mesh->num_textures);
	ft_print(DEBUG, 1, "%i normal coords.", mesh->num_normals);
	ft_print(DEBUG, 1, "%i faces.", mesh->num_faces);
}

void			init_mesh(t_mesh *mesh)
{
	mesh->vertex = NULL;
	mesh->num_vertex = 0;
	mesh->textures = NULL;
	mesh->num_textures = 0;
	mesh->normals = NULL;
	mesh->num_normals = 0;
	mesh->faces = NULL;
	mesh->num_faces = 0;
}

void			malloc_mesh(t_mesh *mesh)
{
	if (mesh->num_vertex)
	{
		mesh->vertex = (t_vec3f*)malloc(sizeof(t_vec3f) * mesh->num_vertex);
		if (!mesh->vertex)
			ft_print(EXIT_ERROR, 0, "Failed to malloc mesh.");
	}
	else
		ft_print(EXIT_ERROR, 0, "No vertex found.");
	if (mesh->num_textures)
	{
		mesh->textures = (t_vec2f*)malloc(sizeof(t_vec2f) * mesh->num_textures);
		if (!mesh->textures)
			ft_print(EXIT_ERROR, 0, "Failed to malloc mesh.");
	}
	if (mesh->num_normals)
	{
		mesh->normals = (t_vec3f*)malloc(sizeof(t_vec3f) * mesh->num_normals);
		if (!mesh->normals)
			ft_print(EXIT_ERROR, 0, "Failed to malloc mesh.");
	}
	if (mesh->num_faces)
	{
		mesh->faces = (t_face*)malloc(sizeof(t_face) * mesh->num_faces);
		if (!mesh->faces)
			ft_print(EXIT_ERROR, 0, "Failed to malloc mesh.");
	}
	else
		ft_print(EXIT_ERROR, 0, "No face found.");
}

void			first_passage(FILE *fp, t_mesh *mesh)
{
	char	buf[256];

	while (fgets(buf, sizeof (buf), fp))
	{
		if (!strncmp(buf, "v ", 2))
			mesh->num_vertex++;
		else if (!strncmp(buf, "vt ", 3))
			mesh->num_textures++;
		else if (!strncmp(buf, "vn ", 3))
			mesh->num_normals++;
		else if (buf[0] == 'v')
			ft_print(WARNING, 0, "Unknow token \"%s\".", buf);
		else if (!strncmp(buf, "f ", 2))
			mesh->num_faces++;

	}
	print_first_passage_info(mesh);
}


void			stock_vec3f(t_vec3f *vec3f, int current, char *buf)
{
	if (sscanf(buf + 2, "%f %f %f", &vec3f[current].x, &vec3f[current].y, &vec3f[current].z) != 3)	
		ft_print(EXIT_ERROR, 0, "Error reading vertex data.");
}

void			stock_vec2f(t_vec2f *vec2f, int current, char *buf)
{
	if (sscanf(buf + 2, "%f %f", &vec2f[current].x, &vec2f[current].y) != 2)
		ft_print(EXIT_ERROR, 0, "Error reading vertex data.");
}

void			stock_elem_face(t_elem *elem, char *buf, int num_elems)
{
	int		i;

	i = 0;
	while (i < num_elems)
	{
		buf = strchr(buf, ' ');
		buf++;
		if (sscanf(buf, "%d/%d/%d", &elem[i].v, &elem[i].t, &elem[i].n) != 3)
		{
			if (sscanf(buf, "%d/%d", &elem[i].v, &elem[i].t) != 2)
			{
				if (sscanf(buf, "%d//%d", &elem[i].v, &elem[i].n) != 2)
						sscanf(buf, "%d", &elem[i].v);
			}
		}
		i++;
	}
}

int				face_get_texture(char *buf)
{
	int		i;

	i = 0;
	while (buf[i] != '/' && buf[i])
		i++;
	if (buf[i] == '\0' || buf[i + 1] == '/')
		return (0);
	return (1);
}

void			stock_face(t_face *face, int current, char *buf)
{
	char	*pbuf;
	int		i;

	pbuf = buf;
	printf("%s", pbuf);
	face[current].num_elems = 0;
	if (face_get_texture(buf))
		face[current].has_textures = 1;
	else
		face[current].has_textures = 0;
	while (*pbuf)
	{
		if (*pbuf == ' ' && *(pbuf + 1) != 0x0d)
			face[current].num_elems++;
		pbuf++;
	}
	face[current].elem = (t_elem*)malloc(sizeof(t_elem) * face[current].num_elems);
	if (!face[current].elem)
		ft_print(EXIT_ERROR, 0, "Failed to malloc face.");
	i = -1;
	while (++i < face[current].num_elems)
		stock_elem_face(face[current].elem, buf, face[current].num_elems);
}

int				get_indices_size(t_face *faces, int num_faces)
{
	int		i;
	int		j;
	int		count;

	count = -1;
	i = -1;
	while (++i < num_faces)
	{
		count++;
		j = -1;
		while (++j < faces[i].num_elems)
			count++;
	}
	return (count);
}

void			fill_indices(t_face *faces, int num_faces, t_indice *indice)
{
	int		i;
	int		j;
	int		c;

	indice->count = get_indices_size(faces, num_faces);
	indice->array = (GLuint*)malloc(sizeof(GLuint) * indice->count);
	if (!indice->array)
		ft_print(EXIT_ERROR, 0, "Couldn't malloc indice array.");
	c = 0;
	i = -1;
	while (++i < num_faces)
	{
		j = -1;
		while (++j < faces[i].num_elems)
		{
			indice->array[c] = faces[i].elem[j].v - 1;
			c++;
		}
		indice->array[c] = 65535;
		c++;
	}
}

void			fill_vertices(t_mesh *mesh, t_vertice *vertices)
{
	int		i;
	int		j;

	vertices->count = mesh->num_vertex * 3;
	vertices->array = (GLfloat*)malloc(sizeof(GLfloat) * vertices->count);
	j = 0;
	i = -1;
	while (++i < mesh->num_vertex)
	{
		vertices->array[j++] = mesh->vertex[i].x;
		vertices->array[j++] = mesh->vertex[i].y;
		vertices->array[j++] = mesh->vertex[i].z;
	}
}

void			fill_textures(t_mesh *mesh, t_texture_coord *textures)
{
	int		i;
	int		j;
	int		current_vertex_pointer;
	t_vec2f	current_tex;

	textures->count = mesh->num_vertex * 2;
	textures->array = (GLfloat*)malloc(sizeof(GLfloat) * textures->count);
	if (!textures->array)
		ft_print(EXIT_ERROR, 0, "Couldn't malloc textures.");
	i = -1;
	while (++i < mesh->num_faces)
	{
		j = -1;
		while (++j < mesh->faces[i].num_elems)
		{
			current_vertex_pointer = mesh->faces[i].elem[j].v - 1;
			if (mesh->faces[i].has_textures)
			{
				current_tex = mesh->textures[mesh->faces[i].elem[j].t - 1];
				textures->array[current_vertex_pointer * 2] = current_tex.x;
				textures->array[current_vertex_pointer * 2 + 1] = current_tex.y;
			}
			else
			{
				textures->array[current_vertex_pointer * 2] = mesh->vertex[mesh->faces[i].elem[j].v - 1].x;
				textures->array[current_vertex_pointer * 2 + 1] = mesh->vertex[mesh->faces[i].elem[j].v - 1].y;
			}
		}
	}
}

void			second_passage(FILE *fp, t_mesh *mesh, t_env *env)
{
	char	buf[256];
	int		num_vertex;
	int		num_textures;
	int		num_normals;
	int		num_faces;

	num_vertex = 0;
	num_textures = 0;
	num_normals = 0;
	num_faces = 0;
	while (fgets(buf, sizeof (buf), fp))
	{
		if (!strncmp(buf, "v ", 2))
		{
			stock_vec3f(mesh->vertex, num_vertex, buf);
			num_vertex++;
		}
		else if (!strncmp(buf, "vt ", 3))
		{
			stock_vec2f(mesh->textures, num_textures, buf);
			num_textures++;
		}
		else if (!strncmp(buf, "vn ", 3))
		{
			stock_vec3f(mesh->normals, num_normals, buf);
			num_normals++;
		}
		else if (buf[0] == 'v')
			ft_print(WARNING, 0, "Unknow token \"%s\".", buf);
		else if (!strncmp(buf, "f ", 2))
		{
			stock_face(mesh->faces, num_faces, buf);
			num_faces++;
		}
	}
	fill_vertices(mesh, &env->vertices);
	fill_indices(mesh->faces, mesh->num_faces, &env->indice);
	fill_textures(mesh, &env->texture_array);
}

t_raw_model		load_obj_model(const char *filename, t_env *env)
{
	FILE	*fp;

	if (!(fp = fopen(filename, "rb")))
		ft_print(EXIT_ERROR, 0, "Couldn't open \"%s\".", filename);
	init_mesh(&(env->mesh));
	first_passage(fp, &(env->mesh));
	malloc_mesh(&(env->mesh));
	rewind(fp);
	second_passage(fp, &(env->mesh), env);
	return (load_to_vao(env, env->indice));
}
