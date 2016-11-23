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
#include <stdlib.h>

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
  printf("Alphabet %d\n",alphabet);
  prime = 15485863;
  patternlength = strlen(pattern);
  for (i = 0; i < patternlength; i++)
  {
    h = (h*alphabet)%prime;
    
  }
  readAndUpdate(pattern,in,alphabet);
  return 0;
}
char* intialize(FILE* in, int sizeOfPattern)
{
  int i;
  char* intial;
  intial=malloc(sizeof(char)*sizeOfPattern);
  char charc;
  char c[2];
  c[1]='\0';
  for (i=0; i<sizeOfPattern-1; i++)
  {
    fscanf(in,"%c",&charc);
    c[0] = charc;
    strcat(intial,c);
  }
  printf("Intial works");
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
  sizeOfPattern = strlen(pattern);
  tempString = intialize(in,sizeOfPattern);
  
  printf("alphabet %d",alpha);
  hashPattern = patternHash(pattern, alphabet);
  hashTemp = patternHash(tempString, alphabet);
  
  if (hashPattern == hashTemp)
  {
    printf("hashPattern %lu hashTemp %lu \n",hashPattern,hashTemp);
    printf("Pattern %s, Temp %s",pattern,tempString);
    return 1;
  }
  while((fscanf(in,"%c",&charc))!= EOF)
  {
    tem[0] = charc;
    strcat(tempString,tem);
    hashTemp = update(tem[0],tempString[0], alphabet, hashTemp);

    if(hashTemp == hashPattern)
    {
      printf("Match\n");
      printf("hashPattern %lu hashTemp %lu \n",hashPattern,hashTemp);
      printf("Pattern %s, Temp %s\n",pattern,tempString);
      return 1;
      
    }
    tempString = tempString+1;


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
  for(i = 1; i<length; i++)
  {
//    printf("pattern[i] %c, int value %d",pattern[i],pattern[i]);
//    printf("Alphabet Size = %d, PatternHash = %lu, pattern[i] = %d\n",alphabetSize,patternHash,pattern[i] );
    patternHash = (alphabetSize*patternHash+(int)pattern[i])%prime;

  }
  printf("PatternHash is intialized");
  return patternHash;
}
long update(char letter, char minus, int alphabet, long hash)
{
  hash = (alphabet*(hash-(minus*h))+(int)letter)%prime;
  return hash;
}
