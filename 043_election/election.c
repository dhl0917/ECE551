#include "election.h"

#include <stdio.h>
#include <stdlib.h>
//include any other headers you need here...

state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t mystate;
  int i = 0;
  //Check input
  int count = 0;
  while (line[i] != '\0') {
    if (line[0] < 'A' || line[0] > 'Z') {
      fprintf(stderr, "Wrong First input!\n");
      exit(EXIT_FAILURE);
    }
    if (count == 0) {
      if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z') ||
          line[i] == ' ' || line[i] == ':') {
        if (line[i] == ':') {
          count += 1;
          i++;
          continue;
        }
      }
      else {
        fprintf(stderr, "Wrong input for states' name!\n");
        exit(EXIT_FAILURE);
      }
    }
    if (count == 1) {
      if ((line[i] >= '0' && line[i] <= '9') || line[i] == ':') {
        if (line[i] == ':') {
          if (line[i - 1] == ':') {
            fprintf(stderr, "Wrong input for population!\n");
            exit(EXIT_FAILURE);
          }
          count += 1;
          i++;
          continue;
        }
      }
      else {
        fprintf(stderr, "Wrong input for population!\n");
        exit(EXIT_FAILURE);
      }
    }
    if (count == 2) {
      if ((line[i] >= '0' && line[i] <= '9')) {
      }
      else {
        fprintf(stderr, "Wrong input for Votes!\n");
        exit(EXIT_FAILURE);
      }
    }
    i++;
  }
  if (count != 2) {
    fprintf(stderr, "Less <:>!\n");
    exit(EXIT_FAILURE);
  }

  i = 0;
  int flag1 = 0;
  int flag2 = 0;
  int flag3 = 0;
  while (line[i] != '\0') {
    if ((line[i] == ':') && (flag1 == 0)) {
      flag1 = i;
      i++;
      continue;
    }
    if ((line[i] == ':') && (flag1 != 0)) {
      flag2 = i;
      i++;
      continue;
    }
    i++;
  }
  flag3 = i;
  char pop[flag2 - flag1];
  char num[flag3 - flag2];
  for (int i = 0; i < flag1; i++) {
    mystate.name[i] = line[i];
  }
  mystate.name[flag1] = '\0';
  for (int i = 0; i < flag2 - flag1 - 1; i++) {
    pop[i] = line[i + flag1 + 1];
  }
  pop[flag2 - flag1 - 1] = '\0';
  for (int i = 0; i < flag3 - flag2 - 1; i++) {
    num[i] = line[i + flag2 + 1];
  }
  num[flag3 - flag2 - 1] = '\0';
  mystate.population = atoi(pop);
  mystate.electoralVotes = atoi(num);
  return mystate;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int votes = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > 0.5 * stateData[i].population) {
      votes += stateData[i].electoralVotes;
    }
  }

  return votes;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] >= 0.495 * stateData[i].population &&
        voteCounts[i] <= 0.505 * stateData[i].population) {
      fprintf(stdout,
              "%s requires a recount (Candidate A has %.2f%% of the vote)\n",
              stateData[i].name,
              100 * voteCounts[i] / (1.0 * stateData[i].population));
    }
  }
}
void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
}
