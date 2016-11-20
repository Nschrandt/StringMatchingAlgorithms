//
//  rabinKarp.c
//  StringMatching
//
//  Created by Family on 11/16/16.
//  Copyright © 2016 Family. All rights reserved.
//

#include "rabinKarp.h"
#include <stdio.h>
#include <string.h>

long h;
int prime;
long patternHash(char* pattern, int alphabetSize);
long update(char letter, char minus, int alphabet, long hash);

int main(int argc, const char * argv[]) {
  // insert code here...
  
  char* infile;
  char* outfile;
  char* pattern;
  int patternlength;
  int i;
  int alphabet;
  
  FILE* in;
  printf("Rabin Karp\n");
  if(argc != 4)
  {
    printf("wrong number of args\n");
    return 1;
  }
  pattern = argv[1];
  infile = argv[2];
  alphabet = atoi(argv[3]);
  in = fopen(infile, "rb");
  if(in == NULL)
  {
    printf("couldn't open %s for reading\n", infile);
    return 2;
  }
  prime = 4957;
  patternlength = strlen(pattern);
  for (i = 0; i < patternlength; i++)
  {
    h = (h* alphabet)%prime;
  }
  readAndUpdate(pattern,in);
  printf("Stuck here\n");
  return 0;
}
char* intialize(FILE* in, int sizeOfPattern)
{
  int i;
  char* intial;
  intial=malloc(sizeof(char)*sizeOfPattern);
  char charc;
  char c[2];
  for (i=0; i<sizeOfPattern-1; i++)
  {
    fscanf(in,"%c",&charc);
    c[0] = charc;
    strcat(intial,c);
  }
  printf("This is intial %s", intial);
  return intial;
}

int readAndUpdate(char* pattern, FILE* in, int alpha)
{
  char tem[2];
  char* tempString;
  char charc;
  int sizeOfPattern;
  long hashPattern;
  long hashTemp;
  int alphabet;
  alphabet = alpha;
  sizeOfPattern = sizeof(pattern)/sizeof(char);
  tempString = intialize(in,sizeOfPattern);
  
  //  printf("%s\n",tempString);
  printf("%d\n",sizeOfPattern);
 
  hashPattern = patternHash(pattern, alphabet);
  hashTemp = patternHash(tempString, alphabet);
  
  if (hashPattern == hashTemp)
  {
    printf("hashPattern %lu hashTemp %lu \n",hashPattern,hashTemp);
    return 1;
  }
  while((fscanf(in,"%c",&charc))!= EOF)
  {
    tem[0] = charc;
    strcat(tempString,tem);
    hashTemp = update(tem[0],tempString[0], alphabet, hashTemp);
    tempString = tempString+1;

    if(hashTemp == hashPattern)
    {
      printf("Match\n");
      printf("hashPattern %lu hashTemp %lu \n",hashPattern,hashTemp);
      return 1;
      
    }

  }
  
  printf("This sucks\n");
  return 0;
  
}
long patternHash(char* pattern, int alphabetSize)
{
  int length;
  int i;
  long patternHash;
  patternHash = 0;
  length = strlen(pattern);
  for(i = 0; i<length; i++)
  {
    patternHash = (alphabetSize*patternHash+pattern[i])%prime;
  }
  printf("%s has a hash of %lu ",pattern, patternHash);
  return patternHash;
}
long update(char letter, char minus, int alphabet, long hash)
{
  hash = (alphabet*(hash-minus*h)+letter)%prime;
  return hash;
}
