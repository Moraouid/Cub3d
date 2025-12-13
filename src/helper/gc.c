/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozemrani <ozemrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:51:09 by sel-abbo          #+#    #+#             */
/*   Updated: 2025/12/13 00:25:37 by ozemrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	my_exit(t_game *game)
{
	if (!game)
		exit(0);
	if (game->mlx.mlx)
	{
		if (game->south.img)
			mlx_destroy_image(game->mlx.mlx, game->south.img);
		if (game->north.img)
			mlx_destroy_image(game->mlx.mlx, game->north.img);
		if (game->east.img)
			mlx_destroy_image(game->mlx.mlx, game->east.img);
		if (game->wast.img)
			mlx_destroy_image(game->mlx.mlx, game->wast.img);
		if (game->img.img)
			mlx_destroy_image(game->mlx.mlx, game->img.img);
		if (game->mlx.win)
			mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
	}
	if (game->gc)
		gc_clean(&game->gc);
	exit(0);
}

void	gc_clean(t_gc **gc)
{
	t_gc	*current;
	t_gc	*next;

	current = *gc;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*gc = NULL;
}

void	gc_add(t_gc **gc, void *ptr)
{
	t_gc	*node;

	node = malloc(sizeof(t_gc));
	if (!node)
	{
		write(2, "Error: gc_add malloc failed\n", 28);
		gc_clean(gc);
		exit(1);
	}
	node->ptr = ptr;
	node->next = *gc;
	*gc = node;
}

void	*gc_malloc(t_gc **gc, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "Error: malloc failed\n", 21);
		gc_clean(gc);
		exit(1);
	}
	gc_add(gc, ptr);
	return (ptr);
}
