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
char* intial(FILE* in);


int main(int argc, const char * argv[]) {
  // insert code here...

  char* infile;
  char* outfile;
  char* pattern;
  int matches;
  
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
  
 
  matches = readAndUpdate(pattern,in);
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

int readAndUpdate(char* pattern, FILE* in)
{
  char tem[2];
  char* tempString;
  char charc;
  int sizeOfPattern;
  int i;
  int j;
  int matches = 0;
  int letterMatches =0;
  printf("%s \n ",pattern);
  sizeOfPattern = strlen(pattern);
  printf("%d size is \n",sizeOfPattern);
  
  tempString = intial(in);
  
  printf("hello\n");

 

  for(i=0;i<=strlen(tempString)-sizeOfPattern;i++)
  {
    for(j=0;j<sizeOfPattern;j++)
    {
      if(pattern[j] != tempString[i+j])
      {
        break;
      }
      else
      {
        letterMatches++;
      }
      
    }
    if (letterMatches == sizeOfPattern) {
//      printf("%c,%c",tempString[i],tempString[i+j]);
      matches++;
    }
    letterMatches =0;
    
  
//    if(matching(pattern,strcpy(tempString+i,sizeOfPattern),sizeOfPattern))
//    {
//      printf("This two strings are matching %s %s \n",pattern,tempString);
//      matches ++;
//      
//    }
  }

  printf("This sucks\n");
  return matches;

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

