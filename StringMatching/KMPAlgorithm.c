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

char* intial(FILE* in)
{
  long len;
  char* file;
  fseek(in, 0, SEEK_END);
  len = ftell(in);
  rewind(in);
  file = calloc(1,len+1);
  fread(file,len,1,in);
  return file;
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
  return failureTable;
}

int stringMatch(FILE* in, char *pattern, int patternSize)
{
  int i = 0;
  int j = 0;
  int counter = 0;
  char * textFile;
  long fileLength;
  int *failureTable = makeFailureTable(pattern, patternSize);
  textFile = intial(in);
  fileLength = strlen(textFile);
  for(i = 0; i <fileLength; i++)
  {
    while(j >= 0 && textFile[i]  != pattern[j])
    {
      j = failureTable[j];
    }
    j++;
    if(j == patternSize)
    {
      counter++;
    }
  }
  printf("%d matches were found.\n", counter);
  free(failureTable);
  return 0;
}
