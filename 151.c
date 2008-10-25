#include <stdio.h>

double expectedValue = 0.0;
void nextBatch(double probability, int numOnes, int nA2, int nA3, int nA4, int nA5) {
    //printf("A2: %d A3: %d A4: %d A5: %d Probability %lf Ones %d \n", nA2, nA3, nA4, nA5, probability, numOnes);
    int numChildren = nA2 + nA3 + nA4 + nA5;
    if (numChildren == 1 && nA5 == 1) {
        expectedValue += probability * (double)numOnes;
        return;
    }
    if (numChildren == 1) numOnes++;
    double childsProb = probability * 1.0/(double)numChildren;
    if (nA2) nextBatch(nA2*childsProb, numOnes, nA2-1, nA3+1, nA4+1, nA5+1);
    if (nA3) nextBatch(nA3*childsProb, numOnes, nA2, nA3-1, nA4+1, nA5+1);
    if (nA4) nextBatch(nA4*childsProb, numOnes, nA2, nA3, nA4-1, nA5+1);
    if (nA5) nextBatch(nA5*childsProb, numOnes, nA2, nA3, nA4, nA5-1);
}

int main (int argc, char **argv) {
    nextBatch(1.0, 0, 1, 1, 1, 1);
    printf("The expected number is %lf", expectedValue);
}