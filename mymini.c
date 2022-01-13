/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   er3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 03:48:04 by marvin            #+#    #+#             */
/*   Updated: 2022/01/14 03:48:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	width = 0;
int	height = 0;
char background = 0;
char **zone = NULL;

typedef struct s_rect
{
	char	type;
	char	c;
	float		width;
	float		height;
	float		x;
	float		y;
}			t_rect;

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}
int	draw(FILE *file)
{
	int	i = -1;
	while (++i < height)
	{
		write(1, zone[i], width);
		write(1, "\n", 1);
	}
	if (file)
		fclose(file);
	return (0);
}

int	valid_rect(t_rect rect)
{
	if (rect.height > 0 && rect.width > 0 && (rect.type == 'R' ||rect.type == 'r'))
		return (1);
	return (0);
}

int	in_rect(t_rect rect, float x, float y)
{
	if (rect.x > x || rect.x + rect.width < x || rect.y > y || rect.y + rect.height < y)
		return (0);
		//(xw - x < 1 || 1 > x + w - xw|| yh - y < 1 || 1 > y + h - yh)
	// if (x - rect.x < 1.000 ||1.000 > rect.x + rect.width - x || y - rect.y < 1.000 || 1.000 > rect.y + rect.height - y)
	if (1.00 > x - rect.x || 1.00 > rect.x + rect.width - x || 1.00 > y - rect.y || 1.000 > rect.y + rect.height - y)
		return (2);
	return (1);
}
int	main(int ac, char **av)
{
	int	ret = 0;
	int	init = 0;
	int i = 0;
	int	j = 0;
	FILE	*file = NULL;
	t_rect	rect;
	if (ac != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	file = fopen(av[1], "r");
	if (file)
	{
		if ((ret = fscanf(file, "%d %d %c", &width, &height, &background)) == 3)
		{
			if (width > 0 && width <= 300 && height > 0 && height <= 300) 
			{
				zone = malloc(height * sizeof(char *));
				while (i < height)
				{
					zone[i] = malloc(width * sizeof(char));
					memset(zone[i], background, width);
					i++;
				}
				while (1337)
				{
					ret = fscanf(file, "\n%c %f %f %f %f %c", &rect.type, &rect.x, &rect.y, &rect.height, &rect.width, &rect.c);
					if (ret != 6 || !valid_rect(rect))
						return (draw(file));
					i = 0;
					while (i < height)
					{
						j = 0;
						while (j < width)
						{
							init = in_rect(rect, j, i);
							if (rect.type == 'r' && init == 2)
								zone[i][j] = rect.c;
							if (rect.type == 'R' && init)
								zone[i][j] = rect.c;
							j++;
						}
						i++;
					}
				}
			}
		}
	}
	if (file)
		fclose(file);
	write (1, "Error: Operation file corrupted\n", 32);
	return (1);
}