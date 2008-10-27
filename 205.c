#include <stdio.h>

void getDiceProbs(double *probs, int numDice, int maxVal) {
    int dice[numDice]; // Array to enumerate states of the dice
    for (int i = 0; i < numDice; i++) dice[i] = 1;
    
    int numWays[numDice * maxVal + 1]; // Array representing the number of different ways the sum of the dice can be made
    for (int i = 0; i < numDice *maxVal + 1; i++) numWays[i] = 0;
    
    do {
        int sum = 0;
        for (int i=0; i < numDice; i++) sum += dice[i];
        (numWays[sum])++;
        
        // Increment to the next combination of dice.  
        // This is a simple counting algorithm with the max value being the base
        for (int i = 0; i < numDice; i++) {
            (dice[i])++;
            if (dice[i] > maxVal && (i != numDice - 1))
                dice[i] = 1;
            else
                break;
        }
    } while (dice[numDice - 1] <= maxVal); // Once we exceed the value that the dice can hold, we're done.

    // Translate from number of ways a sum can be made to the probability of getting that sum.
    int possibleOutcomes = 1;
    for (int i = 0; i < numDice; i++) possibleOutcomes *= maxVal;
    for (int i = numDice; i <= numDice * maxVal; i++) probs[i] = (double)numWays[i]/(double)possibleOutcomes;
}

void printProbs(double *probs, int numDice, int maxVal) {
    for (int i= numDice; i <= numDice * maxVal; i++) printf("%d: %.8lf\n", i, probs[i]);
}


void compareProbabilities (double *pete, double *colin) {
    double totalProb = 0.0;
    for (int i = 6; i < 36; i++) {
        double peteWinsProb = 0.0;
        for (int j = i+1; j <= 36; j++) {
            peteWinsProb += pete[j];
        }
        totalProb += peteWinsProb * colin[i];
    }
    printf("The probability that pete beats colin is %.7lf\n", totalProb);
}

int main (int argc, char **argv) {
    double peteProbs[37] = {0};
    double colinProbs[37] = {0};
    getDiceProbs(peteProbs, 9, 4);
    getDiceProbs(colinProbs, 6, 6);
    compareProbabilities(peteProbs, colinProbs);
}

