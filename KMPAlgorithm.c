/***********************************************************/
/* Nick Schrandt and Kevin Omidvaran			   */
/* 							   */
/* KMP Algorithm for String matching			   */
/* CS361 Final Project					   */
/* 							   */
/* This algorithm compares a pattern String with a text	   */
/* and prints out the index in the text where the	   */
/* pattern can be found. It uses a failure table to enable */
/* efficient backtracking.				   */
/***********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
  char* infile;
  char* outfile;
  char* pattern;
  int patternlength;
  int i;
  int alphabet;
  int success;
  FILE* in;

  printf("KMP Algorithm\n");
  if(argc != 3)
  {
    printf("Wrong number of arguments.\n");
    return 1;
  }
  pattern = argv[1];
  infile = argv[2];
  in = fopen(infile, "rb");
  if(in == NULL)
  {
    printf("Couldn't open %s for reading\n", infile);
    return 2;
  }
  patternlength = strlen(pattern);
  success = stringMatch(in, pattern, strlen(pattern));
}

int *makeFailureTable(char *pattern, int psize)
{
  int *failureTable = malloc(sizeof(int)*psize);
  int patternIndex = 0;
  int failTableIndex = -1;
  failureTable[patternIndex] = failTableIndex;
  while(patternIndex < psize)
  {
    while(failTableIndex >= 0 && pattern[patternIndex] 
	  != pattern[failTableIndex])
    {
      failTableIndex = failureTable[failTableIndex];
    }
    patternIndex++;
    failTableIndex++;
    failureTable[patternIndex] = failTableIndex;
  }
  int k;
  return failureTable;
}

int stringMatch(FILE* in, char *pattern, int patternSize)
{
  int i = 0;
  int j = 0;
  int counter = 0;
  char charc;
  int *failureTable = makeFailureTable(pattern, patternSize);
  while((fscanf(in, "%c", &charc ))!= EOF)
  {
    while(j >= 0 && charc != pattern[j])
    {
      j = failureTable[j];
    }
    i++;
    j++;
    if(j == patternSize)
    {
      printf("Found match at %d\n", i);
      counter++;
    }
  }
  printf("%d matches were found.\n", counter);
  free(failureTable);
  return 0;
}
