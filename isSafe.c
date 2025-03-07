/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isSafe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moussade <moussade@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:33:32 by moussade          #+#    #+#             */
/*   Updated: 2025/03/01 18:50:28 by moussade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>

#define GRID_SIZE 4				// 4 x 4 grid

// this function checks if a number is already present in the same row or colum

bool  isSafe(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int height)
{
	for (int i = 0; i < GRID_SIZE; i++)       // height check on rows
	{
		if (grid[row][i] == height)
		{
			return false;
		}
	}

	for (int i = 0; i < GRID_SIZE; i++)	// height check on cols
	{
		if (grid[i][col] == height)
		{
			return false;
		}
	}
	return true;
}

bool solveSkyscraper(int grid[GRID_SIZE][GRID_SIZE], int row, int col) 
{
	if (row == GRID_SIZE) 
	{
		return true;
	}

	int nextRow = (col == GRID_SIZE - 1) ? row + 1 : row;
	int nextCol = (col == GRID_SIZE - 1) ? 0 : col + 1;

	if (grid[row][col] != 0) 
	{
		return solveSkyscraper(grid, nextRow, nextCol);
	}
	
	for (int height = 1; height <= GRID_SIZE; height++) 
	{
		if (isSafe(grid, row, col, height)) 
		{  
			grid[row][col] = height;
			if (solveSkyscraper(grid, nextRow, nextCol)) 
			{
					return true;
			}
			grid[row][col] = 0;
		}
    }
	return false;
}


int visibility_fx(int line[GRID_SIZE])
{
	int max_height = 0;		// tallest building so far
	int visible_count = 0;		// numbers of buildings visible

	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (line[i] > max_height)
		{
			max_height = line[i];			// update tallest seen
			visible_count++;			// count this building as visible
		}
	}
	return visible_count;
}

void printGrid(int grid[GRID_SIZE][GRID_SIZE])
{
	printf("\nCurrent Grid:\n");
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			printf("%d ", grid[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int grid[GRID_SIZE][GRID_SIZE] = {0};
	// Test isSafe
	grid[0][0] = 1;
	printGrid(grid);

	printf("Test 1 (valid placement) : %d\n", isSafe(grid, 0, 1, 2));
	printf("Test 2 (duplicate in a row) : %d\n", isSafe(grid, 0, 2, 1));
	printf("Test 3 (duplicate in column) : %d\n", isSafe(grid, 2, 0, 1));

	int row1[GRID_SIZE] = {2, 3, 1, 4};
	int row2[GRID_SIZE] = {1, 4, 3, 2};

	printf("Visible buildings from the left (row1): %d\n", visibility_fx(row1));
	// should print 3
	printf("Visible buildings from the left (row2): %d\n", visibility_fx(row2));
	// should print 2

    printf("\nSolving the puzzle...\n");
    if (solveSkyscraper(grid, 0, 0)) 
	{
        printf("\nSolution Found:\n");
        printGrid(grid); 
    } 
	else 
	{
        printf("No solution found.\n"); 
    }

    return 0; 
}
