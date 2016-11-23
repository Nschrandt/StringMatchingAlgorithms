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
#include <math.h>
#include <stdlib.h>
int prime;
long patternHash(char* pattern, int alphabetSize);
long update(char letter, char minus, int alphabet, long hash, long h);

int main(int argc, const char * argv[]) {
  // insert code here...
  long h;
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
  prime = 4957;
  patternlength = strlen(pattern);
//  for (i = 0; i < patternlength-1; i++)
//  {
//    h = (h* alphabet)%prime;
//  }
  h=(int)pow(alphabet, patternlength-1)%prime;

  readAndUpdate(pattern,in,alphabet,h);
  return 0;
}
char* intialize(FILE* in, int sizeOfPattern)
{
  int i;
  char* intial;
  intial=malloc(sizeof(char*));
  char charc;
  char c[2];
  c[1]='\0';
  for (i=0; i<sizeOfPattern; i++)
  {
    fscanf(in,"%c",&charc);
    c[0] = charc;
    strcat(intial,c);
  }
  return intial;
}

int readAndUpdate(char* pattern, FILE* in, int alpha, long h)
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
  
  tempString= intialize(in,sizeOfPattern);
  
 
  hashPattern = patternHash(pattern, alphabet);
  hashTemp = patternHash(tempString, alphabet);
  
  if (hashPattern == hashTemp)
  {
    printf("hashPattern %lu hashTemp %lu \n",hashPattern,hashTemp);
    return 1;
  }
//  printf("hashPattern %lu hashTemp %lu \n",hashPattern,hashTemp);
  while((fscanf(in,"%c",&charc))!= EOF)
  {
    tem[0] = charc;
    strcat(tempString,tem);
    hashTemp = update(tem[0],tempString[0], alphabet, hashTemp,h);
    tempString = tempString+1;
//    printf("hashPattern %s %lu hashTemp %s %lu \n",pattern,hashPattern,tempString,hashTemp);
    if(hashTemp == hashPattern)
    {
      printf("Match\n");
      printf("hashPattern %s %lu hashTemp %s %lu \n",pattern,hashPattern,tempString,hashTemp);
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
    patternHash = ((alphabetSize*patternHash)+pattern[i])%prime;
//    printf("Pattern Hash %lu\n", patternHash);
  }
  return patternHash;
}
long update(char letter, char minus, int alphabet, long hash, long h)
{
  long temp;
  temp = ((minus)*h)%prime;
//  printf("hash %lu", hash);
//  printf("Temp 1 %lu\n",temp);
  temp = (hash - temp);
//  printf("Temp2 %d\n",temp);
//  printf("Alpabet %d, Letter %c, minus %c, h %lu\n",alphabet,letter,minus,h);
  
  hash = (alphabet*(temp)+letter)%prime;
  if(hash<0)
  {
    hash = hash+prime;
  }
  return hash;
}
