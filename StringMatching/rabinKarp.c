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
  int matches;
  
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
  h = 1;
  patternlength = strlen(pattern);
  for (i = 1; i < patternlength; i++)
  {
    h = (h * alphabet)%15485863;
  }
//  h=(int)pow(alphabet, patternlength-1)%prime;

 matches = readAndUpdate(pattern,in,alphabet,h);
  if(matches == 0)
  {
    printf("Sorry no matches were found\n");
  }
  else
  {
    printf("There were %d matches\n",matches);
  }
  
  
  return 0;
}
char* intialize(FILE* in, int sizeOfPattern)
{
  int i;
  char* intial;
  intial=(char*)malloc(sizeof(10200));
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
  int numberOfMatches = 0;
  int passes = 0;

  tempString = malloc(sizeof(char*));
  alphabet = alpha;
  sizeOfPattern = strlen(pattern);
  
 tempString = intialize(in,sizeOfPattern);
  
 
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
//    strcat(tempString,tem);
    hashTemp = update(tem[0],tempString[passes%sizeOfPattern], alphabet, hashTemp,h);
    tempString[passes%sizeOfPattern] = tem[0];
//    tempString = tempString+1;
    
//    printf("hashPattern %s %lu hashTemp %s %lu \n",pattern,hashPattern,tempString,hashTemp);
    if(hashTemp == hashPattern)
    {
//      printf("Match\n");
      printf("hashPattern %s %lu hashTemp %s %lu \n",pattern,hashPattern,tempString,hashTemp);
      numberOfMatches++;

    }
    passes++;


  }
//  tempString = tempString -3;
  free(tempString);
  return numberOfMatches;
  
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
