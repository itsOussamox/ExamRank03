/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymini.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 19:20:33 by obouadel          #+#    #+#             */
/*   Updated: 2022/01/08 23:44:39 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

int height;
int width;
char background;
char **arr;

typedef struct s_paint
{
    char 	type;
    float	x;
    float	y;
    float	width;
    float	height;
    char	c;
} t_paint;

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int	draw(FILE *file)
{
	int i = 0;
	while (i < height)
    {
        write(1, arr[i++], width);
        write(1,"\n",1);
    }
    if (file)
        fclose(file);
	return (0);
}

int	end_program(char *err, int error, FILE *file)
{
	if (error == 1)
	{
		write(1, err, ft_strlen(err));
		return (1);	
	}
	if (error == 2)
		write(1, err, ft_strlen(err));
	if (file)
		fclose(file);
	return (1);
}

int check_line(t_paint rect)
{
	if (rect.type != 'r' && rect.type != 'R')
		return (0);
	if (rect.height <= 0 || rect.width <= 0)
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	FILE	*file = NULL;
	int		i = 0;
	int		get = 0;
	int		row = 0;
	int		col = 0;
	t_paint rect;
	
	if (ac != 2)
		return (end_program("Error: argument", 1, file));
	if (file = fopen(av[1], "r"))
	{	
		if ((get = fscanf(file, "%d %d %c\n", &width, &height, &background)) == 3)
		{
			if (width > 0 && width <= 300 && height > 0 && height <= 300)
			{
				arr = malloc(height * sizeof(char *));
				while (i < height)
				{
					arr[i] = malloc(width * sizeof(char));
					memset(arr[i], background, width);
					i++;
				}
				while (1)
				{
					get = fscanf(file, "%c %f %f %f %f %c", &rect.type, &rect.x , &rect.y, &rect.width, &rect.height, &rect.c);
					if (get == -1)
						return (draw(file));
					if (!check_line(rect) || get != 6)
						break ;
					while (row < height)
					{
						while (col < width)
						{
							
							col++;
						}
						row++;
					}
				}
			}

		}
	}
	return (end_program("Error: Operation file corrupted", 2, file));
}