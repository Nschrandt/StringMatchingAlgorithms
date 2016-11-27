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
long patternHash(char* pattern, int alphabetSize, int length);
long update(char letter, char minus, int alphabet, long hash, long h);
char* intial(FILE* in);


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
    h = (h * alphabet)%prime;
  }
//  h=(int)pow(alphabet, patternlength-1)%prime;

 matches = reader(pattern,in,alphabet,h);
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
  char* copy;
  char charc;
  int sizeOfPattern;
  long hashPattern;
  long hashTemp;
  int alphabet;
  int numberOfMatches = 0;
  int passes = 0;
  int i;
  int j;
  int k;
  int letterMatches=0;
  
  tempString = malloc(sizeof(char*));
  alphabet = alpha;
  sizeOfPattern = strlen(pattern);
  
 tempString = intial(in);
  
 
  hashPattern = patternHash(pattern, alphabet,sizeOfPattern);
  hashTemp = patternHash(tempString, alphabet,sizeOfPattern);
  
  if (hashPattern == hashTemp)
  {
//    printf("hashPattern %lu hashTemp %lu \n",hashPattern,hashTemp);
    return 1;
  }
////  printf("hashPattern %lu hashTemp %lu \n",hashPattern,hashTemp);
//  while((fscanf(in,"%c",&charc))!= EOF)
//  {
//    tem[0] = charc;
////    strcat(tempString,tem);
//    hashTemp = update(tem[0],tempString[passes%sizeOfPattern], alphabet, hashTemp,h);
//    tempString[passes%sizeOfPattern] = tem[0];
////    tempString = tempString+1;
//    
////    printf("hashPattern %s %lu hashTemp %s %lu \n",pattern,hashPattern,tempString,hashTemp);
//    if(hashTemp == hashPattern)
//    {
////      printf("Match\n");
//      printf("hashPattern %s %ld hashTemp %s %ld, index of first letter %d\n",pattern,hashPattern,tempString,hashTemp,passes%sizeOfPattern);
//      numberOfMatches++;
//
//    }
  for(i=0;i<strlen(tempString)-sizeOfPattern;i++)
  {
    if(hashPattern==hashTemp)
    {
      
      for(j = 0;j<sizeOfPattern;j++)
      {
//        printf("Pattern[j+i] %c", tempString[j+i]);
        if(pattern[j] != tempString[j+i])
        {
          break;
        }
        else
        {
          letterMatches++;
        }
      }
      if(letterMatches == sizeOfPattern)
      {
        numberOfMatches++;
      }
      letterMatches = 0;
    }
   hashTemp = update(tempString[i+sizeOfPattern], tempString[i], 255, hashTemp, h);
//    passes++;
//          printf("hashPattern %s %ld hashTemp %s %ld\n",pattern,hashPattern,tempString,hashTemp);

  }


  
//  tempString = tempString -3;
  free(tempString);
  return numberOfMatches;
  
}
long patternHash(char* pattern, int alphabetSize, int length)
{
  int i;
  long patternHash;
  patternHash = 0;
//  length = strlen(pattern);
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
  temp = (hash - temp)%prime;
//  printf("Temp2 %d\n",temp);
//  printf("Alpabet %d, Letter %c, minus %c, h %lu\n",alphabet,letter,minus,h);
  
  hash = (alphabet*(temp)+letter)%prime;
  if(hash<0)
  {
    hash = hash+prime;
  }
  return hash;
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
  //  printf("%s\n",file);
  return file;
}
int reader(char* pattern, FILE* in, int alphabet, long h)
{
  int matches;
  char * tempString;
  int patternLength;
  long patternHash =0;
  long tempHash = 0;
  tempString = intial(in);
  long tempLength = strlen(tempString);
  int i;
  int j;
  patternLength =(int) strlen(pattern);
  
  
  for(i=0;i<patternLength;i++)
  {
    patternHash =((alphabet * patternHash)+pattern[i]) %prime;
    tempHash = ((alphabet * tempHash)+tempString[i]) %prime;
  }
//  printf("Pattern Hash is %ld\n", patternHash);
//  printf("Temp Hash is %ld\n", tempHash);
  for(j = 0; j< tempLength; j++)
  {
    
    if(patternHash == tempHash)
    {
//      printf("One match was found");
      
      for(i = 0; i<patternLength;i++)
      {
        if(tempString[i+j] != pattern[i]) break;
      }
      if(i==patternLength)
      {
        matches++;

      }
    
    }
//    if(tempString[j-1] == 'c')
//    {
//      printf("hash is %ld", tempHash);
//    }
    if(i<tempLength-patternLength)
    {
    tempHash = (alphabet*((tempHash - tempString[j]*h)%prime)+tempString[j+patternLength])%prime;
    if(tempHash<0)
    {
//     printf("Hash is less than zero\n");
      tempHash = tempHash+prime;
    }
//    printf("Hash is %ld",tempHash);
    }
  }
  
  return matches;
}

