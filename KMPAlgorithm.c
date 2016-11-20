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
  int success;
  char text[] = "aaaaaabbbbc";
  char pattern[] = "aaaabbbbc";

 success = stringMatch(text, strlen(text), pattern, strlen(pattern));
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

int stringMatch(char *text, int textSize, char *pattern, int patternSize)
{
  int i = 0;
  int j = 0;
  int *failureTable = makeFailureTable(pattern, patternSize);
  
  while(i < textSize)
  {
    while(j >= 0 && text[i] != pattern[j])
    {
      j = failureTable[j];
    }
    i++;
    j++;
    if(j == patternSize)
    {
      printf("Found match at %d\n", (i - patternSize));
    }
  }

  free(failureTable);
  return 1;
}
