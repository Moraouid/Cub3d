/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-abbo <sel-abbo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:24:52 by zatais            #+#    #+#             */
/*   Updated: 2025/08/12 12:12:45 by sel-abbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
