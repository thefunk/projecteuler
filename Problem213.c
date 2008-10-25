#include <stdio.h>
#include <string.h>

#define SIZE 30
#define NUM_ITERATIONS 50
#define curIndex (i*SIZE + j)

void resetBoard(double *board, int size) {
    memset(board, 0, size*size*sizeof(double));
}

double prob(int i, int j) {
    if ((i==0 && j==0) || 
        (i==0 && j==SIZE-1) ||
        (i==SIZE-1 && j==0) ||
        (i==SIZE-1 && j==SIZE-1)) {
        return 0.5;
    } else if (i==0 || i==SIZE-1 || j==0 || j==SIZE-1) {
        static double onethird = 1.0/3.0;
        return onethird;
    } else {
        return 0.25;
    }
}

void iterate(double *board, int size, int times) {
    static double workBoard[SIZE*SIZE] = {0};
    double *curBoard = board;
    double *nextBoard = workBoard;
    
    for (int k = 0; k < times; k++) {
        resetBoard(nextBoard, size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i != 0) {
                    double a = curBoard[(i-1)*size + j] * prob(i-1, j);
                    double b = nextBoard[curIndex];
                    nextBoard[curIndex] += a;//1.0 - (1.0 - a)*(1.0 - b);
                }
                if (i != size-1) {
                    double a = curBoard[(i+1)*size + j] * prob(i+1, j);
                    double b = nextBoard[curIndex];
                    nextBoard[curIndex] += a;//1.0 - (1.0 - a)*(1.0 - b);
                }
                if (j != 0) {
                    double a = curBoard[i*size + j-1] * prob(i, j-1);
                    double b = nextBoard[curIndex];
                    nextBoard[curIndex] += a;//1.0 - (1.0 - a)*(1.0 - b);
                }
                if (j != size-1) {
                    double a = curBoard[i*size + j+1] * prob(i, j+1);
                    double b = nextBoard[curIndex];
                    nextBoard[curIndex] += a;//1.0 - (1.0 - a)*(1.0 - b);
                }
                
            }
        }
        double *tmp = curBoard;
        curBoard = nextBoard;
        nextBoard = tmp;
    }
    
    if (curBoard != board)
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                board[curIndex] = curBoard[curIndex];
        
}

void addToTotal(double *current, double *total, int size) {
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < size; j++) {
            double a = total[curIndex];
            total[curIndex] = 1.0 - (1.0 - current[curIndex])*(1.0 - a);
        }
}

double calculateExpectation(double *total, int size) {
    double expectedValue = 0.0;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            expectedValue += (1.0 - total[curIndex]);

    return expectedValue;
}

void printBoard(char *name, double *board, int size) {
    printf("%s:\n", name);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("[%lf]%s", board[curIndex], j == size -1 ? "\n" : ", ");
        }
    }
    printf("\n");
}
        

int main (int argc, char *argv[]) {
    double total[SIZE*SIZE] = {0};
    double current[SIZE*SIZE] = {0};
    resetBoard(total, SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //printBoard("total", total, SIZE);
            resetBoard(current, SIZE);
            current[curIndex] = 1.0; // seed board with a flea.
            iterate(current, SIZE, NUM_ITERATIONS);
            //printBoard("current", current, SIZE);
            addToTotal(current, total, SIZE);
        }
    }
    //printBoard("total", total, SIZE);
    printf("Expected Number of Empty %lf\n", calculateExpectation(total, SIZE));
    return 0;
}
