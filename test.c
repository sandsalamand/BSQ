/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 17:21:22 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/06/04 23:47:04 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	print_array(int arr[10][10])
{
	int		x;
	int		y;
	y = 0;

	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			printf("%d", arr[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}


int		main(void)
{
	int		x;
	int		y;
	int		cur_x;
	int		cur_y;
	int		starting_x;
	int 	starting_y;
	int		size;
	int		arr[10][10];

	x = 0;
	y = 0;
	// fill a 10x10 array with 0's
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			arr[y][x] = 0;
			x++;
		}
		y++;
	}
	arr[3][3] = 1;
	y = 0;
	// print the 10x10 array of 0's
	print_array(arr);
	// add +1 to each point in the square
	starting_x = 0;
	starting_y = 0;
	size = 2;
	cur_y = 0;
	while (starting_y < 10)
	{
		while (starting_x < 10)
		{
			while (size < 10)
			{
				while (cur_y < (starting_y + size))
				{
					cur_x = starting_x;
					while (cur_x < (starting_x + size))
					{
						arr[cur_x][cur_y] = 1;
						//printf("%d", arr[cur_y][cur_x]);
						cur_x++;
					}
					//printf("\n");
					cur_y++;
				}
				size++;
			}
			starting_x++;
			size = 0;
		}	
		starting_x = 0;
		starting_y++;
		size = 0;
	}
	print_array(arr);
	return (0);
}

