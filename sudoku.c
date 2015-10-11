#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define GRID_SIZE 9

void *processRowOrCol(void *avar);
void *processCube(void *avar);

int grid[GRID_SIZE][GRID_SIZE] = {
    {6,5,3,1,2,8,7,9,4}, 
    {1,7,4,3,5,9,6,8,2}, 
    {9,2,8,4,6,7,5,3,1}, 
    {2,8,6,5,1,4,3,7,9}, 
    {3,9,1,7,8,2,4,5,6}, 
    {5,4,7,6,9,3,2,1,8}, 
    {8,6,5,2,3,1,9,4,7}, 
    {4,1,2,9,7,5,8,6,3}, 
    {7,3,9,8,4,6,1,2,5}
};

int main(int argc, char const *argv[])
{
    printf("CS149 Sudoku from Joshua Wertheim\n");

    pthread_t thread_rows, thread_cols, thread_3x3s;
    int rows_res, cols_res, x_res;

    int rows[GRID_SIZE] = {0};
    int cols[GRID_SIZE] = {0};

    intptr_t flag;

    int i;
    for(i = 0; i < GRID_SIZE; i++) {
        rows_res = pthread_create(&thread_rows, NULL, processRowOrCol, (void *) grid[i]);
        void *row_result;
        pthread_join(thread_rows, &row_result);
        flag = (intptr_t)row_result;
        rows[i] = flag;
    }

    int row_result = 0;
    for(i = 0; i < GRID_SIZE; i++) {
        if(rows[i] == 0)
            row_result = 0;
        else row_result = 1;
    }

    int colArrs[GRID_SIZE][GRID_SIZE] = {{0}};

    for(i = 0; i < GRID_SIZE; i++) {
        int j;
        for(j = 0; j < GRID_SIZE; j++) {
            colArrs[i][j] = grid[j][i];
        }

        cols_res = pthread_create(&thread_cols, NULL, processRowOrCol, (void *) colArrs[i]);
        void *col_result;
        pthread_join(thread_rows, &col_result);
        flag = (intptr_t)col_result;
        cols[i] = flag;
    }

    int col_result = 0;
    for(i = 0; i < GRID_SIZE; i++) {
        if(cols[i] == 0)
            col_result = 0;
        else col_result = 1;
    }

    printf("\n");

    x_res = pthread_create(&thread_cols, NULL, processCube, (void *) grid);
    void *cube_thread_result;
    pthread_join(thread_rows, &cube_thread_result);
    flag = (intptr_t)cube_thread_result;
    int cube_result = flag;


    int j;
    for(i = 0; i < GRID_SIZE; i++) {
        for(j = 0; j < GRID_SIZE; j++) {
            if(j+1 != GRID_SIZE) {
                printf("%d, ", grid[i][j]);
            } else {
                printf("%d", grid[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n");

    if(row_result && col_result && cube_result) { 
        printf("Valid grid."); 
    } else {
        printf("Invalid grid.");
    }

    printf("\n");
    return 0;
}

void *processRowOrCol(void *avar)
{
    int *arr;
    arr = (int *) avar;

    int digits[GRID_SIZE] = {0};

    int i;
    for(i = 0; i < GRID_SIZE; i++) {
        int currInt = arr[i];
        if(digits[currInt] == 0) {
            digits[currInt] = 1;
        } else if(digits[currInt] == 1) {
            return (void *) 0;
        }
    }
    return (void *) 1;
}

void *processCube(void *avar)
{
    int i = 0;
    int j = 0;

    int digits[GRID_SIZE] = {0};

    for(i = 0; i < GRID_SIZE/3; i++) {
        for(j = 0; j < GRID_SIZE/3; j++) {
            int currInt = grid[i][j];
            if(digits[currInt] == 0) {
                digits[currInt] = 1;
            } else if(digits[currInt] == 1) {
                printf("Failure!\n");
                return (void *) 0;
            }
        }
    }

    memset(digits, 0, sizeof(digits));

    for(i = 3; i < GRID_SIZE/2; i++) {
        for(j = 3; j < GRID_SIZE/2; j++) {
            int currInt = grid[i][j];
            if(digits[currInt] == 0) {
                digits[currInt] = 1;
            } else if(digits[currInt] == 1) {
                printf("Failure!\n");
                return (void *) 0;
            }
        }
    }

    memset(digits, 0, sizeof(digits));

    for(i = 6; i < GRID_SIZE; i++) {
        for(j = 6; j < GRID_SIZE; j++) {
            int currInt = grid[i][j];
            if(digits[currInt] == 0) {
                digits[currInt] = 1;
            } else if(digits[currInt] == 1) {
                printf("Failure!\n");
                return (void *) 0;
            }
        }
    }

    return (void *) 1;
}