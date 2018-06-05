/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgrindhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 17:21:22 by sgrindhe          #+#    #+#             */
/*   Updated: 2018/06/05 15:55:50 by sgrindhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	print_array(int arr[4][4])
{
	int		x;
	int		y;
	y = 0;

	while (y < 4)
	{
		x = 0;
		while (x < 4)
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
	int		arr[4][4];
	int		square_holder_map[4][4];

	x = 0;
	y = 0;
	// fill a 4x4 array with 0's
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			arr[y][x] = 0;
			x++;
		}
		y++;
	}
	//arr[4][4] = 1;
	y = 0;
	// print the 4x4 array of 0's
	print_array(arr);
	// add +1 to each point in the square
	starting_x = 0;
	starting_y = 0;
	size = 2;
	cur_y = 0;
	cur_x = 0;
	while (starting_y < 4)
	{
		while (starting_x < 4)
		{
			//this condition checks to make sure the square hasn't grown out of the bounds of the map
			while (size <= 4 && starting_x + size <= 4 && starting_y + size <= 4)
			{
				cur_y = starting_y;
				while (cur_y < (starting_y + size) && cur_y < 4 && arr[cur_x][cur_y] != 1)
				{
					cur_x = starting_x;
					while (cur_x < (starting_x + size) && cur_x < 4 && arr[cur_x][cur_y] != 1)
					{
						arr[cur_y][cur_x] = arr[cur_y][cur_x] + 1;
						cur_x++;
					}
					cur_y++;
				}
				size++;
			}
			starting_x++;
			size = 2;
		}	
		starting_x = 0;
		starting_y++;
		size = 2;
	}
	print_array(arr);
	return (0);
}

