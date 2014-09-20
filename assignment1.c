
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct candidate {
    char name[20];
    int votes;
};

FILE *ifp;

void Initialize(struct candidate electionCandidates[7]);

void Processvotes (struct candidate electionCandidates[7]);

void printResults (struct candidate electionCandidates[7]);

int main () {
    ifp = fopen("elections.txt", "r");
    struct candidate electionCandidates[7];
    Initialize(electionCandidates);
    Processvotes(electionCandidates);
    printResults(electionCandidates);
    return 0;
}

void Initialize (struct candidate electionCandidates[7]) {

    int counter;
    for (counter = 0; counter <= 6; counter++) {
        fgets((electionCandidates[counter].name), 100, ifp); //Gets the full name of each candidate.
    }
}

void Processvotes(struct candidate electionCandidates[7]) { //As long as the file continues
    int counter;                                            //The function will continue to read in votes.
    int vote;
    for (counter = 0; counter <=6; counter++){
        electionCandidates[counter].votes = 0;
    }
    while (fscanf(ifp, "%d", &vote) != EOF){
        if (vote >=1 && vote <= 7 && vote) {
            electionCandidates[vote-1].votes += 1;
        }
    }
}

void printResults (struct candidate electionCandidates[7]) {
    int results = -1, counter, tieArray[7], tieCounter, arrayNextCounter = 0;
    int expectedVotes, totalVotes = 0;
    printf("How many total votes were you expecting?\n");
    scanf("%d", &expectedVotes);
    for (counter = 0; counter <= 6; counter++){ //Used to calculate the number of spoiled votes.
        totalVotes += electionCandidates[counter].votes;
    }
    for (counter = 0; counter <= 6; counter++){
        if (electionCandidates[counter].votes > results){ //If someone has a new highest number of votes, clear the tie array.
            for (tieCounter = 0; tieCounter <= 6; tieCounter++){
                tieArray[tieCounter] = -1;
            }
            tieArray[0] = counter;
            results = electionCandidates[counter].votes;
            arrayNextCounter = 1;
        }
        else if (electionCandidates[counter].votes == results){ //Tie case.
            tieArray[arrayNextCounter] = counter;
            arrayNextCounter++;
        }
    }
    if (tieArray[1] == -1) {
        printf("The winner is candidate %d with a total of %d votes.\n", tieArray[0]+1, electionCandidates[tieArray[0]].votes);
        printf("There was a total of %d spoiled votes.", expectedVotes-totalVotes);
    }
    else{
        printf("There has been a tie between candidate %d", tieArray[0]+1);

        for (counter = 1; counter <= 6; counter++){
            if (tieArray[counter] != -1){
                printf(" and candidate %d", tieArray[counter]+1);

            }
        }
        printf(", with each candidate receiving %d votes.\n", electionCandidates[tieArray[0]].votes);
        printf("There was a total of %d spoiled votes.", expectedVotes-totalVotes);
    }
}






