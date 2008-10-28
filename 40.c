#include <stdio.h>
#include <string.h>

int power (int n, int power) {
    int retval = 1;
    for (int i = 1; i < power; i++) retval *= n;
    return retval;
}

int d (int n) {
    int actualNumber = 0;
    int index;
    
    int level; // size of the current number in digits
    int digitsSoFar;
    int previousDigits = 0;
    for (level = 1;; level++) {
        digitsSoFar = level * 9 * power(10, level) + previousDigits;
        printf("level %d\n", level);
        printf("digits so far %d\n", digitsSoFar);
        if (digitsSoFar > n) {
            int difference = n - previousDigits;
            printf("difference %d\n", difference);
            actualNumber += (difference - 1) / level + 1;
            index = (difference - 1) % level;
            break;
        }       
          
        actualNumber += 9 * power(10, level);
        previousDigits = digitsSoFar;
        printf("actual number %d\n", actualNumber);
    }
    
    char buf[20];
    sprintf(buf, "%d", actualNumber);
    printf("N: %d I:%d\n", actualNumber, index);
    return (int)buf[index] - 48; /* ASCII value for 0 */
}

int main (int argc, char **argv) {
    printf("%d\n", d(1) * d(10) * d(100) * d(1000) * d(10000) * d(100000) * d(1000000));
}