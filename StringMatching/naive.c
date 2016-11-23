//
//  main.c
//  StringMatching
//
//  Created by Family on 11/10/16.
//  Copyright © 2016 Family. All rights reserved.
//

#include <stdio.h>
#include <string.h>

char* intialize(FILE* in, int sizeOfPattern);

int main(int argc, const char * argv[]) {
  // insert code here...

  char* infile;
  char* outfile;
  char* pattern;
  
  FILE* in;
  if(argc != 3)
  {
    printf("wrong number of args\n");
    return 1;
  }
  pattern = argv[1];
  infile = argv[2];
  
  in = fopen(infile, "rb");
  if(in == NULL)
  {
    printf("couldn't open %s for reading\n", infile);
    return 2;
  }
  
 
  readAndUpdate(pattern,in);
  
    return 0;
}
int readAndUpdate(char* pattern, FILE* in)
{
  char tem[2];
  char* tempString;
  char charc;
  int sizeOfPattern;
  printf("%s \n ",pattern);
  sizeOfPattern = strlen(pattern);
  printf("%d size is \n",sizeOfPattern);

  tempString = intialize(in,sizeOfPattern);
  

  if(matching(pattern,tempString,sizeOfPattern))
  {
    printf("This two strings are matching %s %s",pattern,tempString);
    return 1;
    
  }
  while((fscanf(in,"%c",&charc))!= EOF)
  {
    tem[0] = charc;
    strcat(tempString,tem);
    tempString = tempString+1;
    if(matching(pattern,tempString,sizeOfPattern))
    {
      printf("This two strings are matching %s %s \n",pattern,tempString);
      return 1;
      
    }
  }

  printf("This sucks\n");
  return 0;

}
char* intialize(FILE* in, int sizeOfPattern)
{
  int i;
  char* intial;
  intial= malloc(sizeof(char*));
  char charc;
  char c[2];
  c[1]= '\0';
  for (i=0; i<sizeOfPattern-1; i++)
  {
    fscanf(in,"%c",&charc);

    c[0] = charc;
    printf("%s\n",c);

    strcat(intial,c);
  }
//  printf("temp %s", intial);
  return intial;
}

int matching(char* pattern, char* temp,int sizeOfPattern)
{
  int i;

  for (i=0; i<sizeOfPattern-1; i++) {
    if(pattern[i]!= temp[i])
    {
      return 0;
    }
  }
 
  return 1;
}

