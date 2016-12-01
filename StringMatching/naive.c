

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* intial(FILE* in);
int readAndUpdate(const char* pattern, FILE* in);



int main(int argc, const char * argv[]) {

 const char* infile;
 const char* pattern;
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
/*
 Read and update is a method that takes in a char * and file*
 It first calls intial on the file* it then takes the returned char* and looks for 
 matches of the pattern in it.
 */
int readAndUpdate(const char* pattern, FILE* in)
{
  char* tempString;
  int sizeOfPattern;
  int i;
  int j;
  int matches = 0;
  int letterMatches =0;
  int sizeOfTemp;
  sizeOfPattern = strlen(pattern);
  
  tempString = intial(in);
  sizeOfTemp = strlen(tempString);

  for(i=0;i<=sizeOfTemp-sizeOfPattern;i++)
  {
    for(j=0;j<sizeOfPattern;j++)
    {
      if(pattern[j] != tempString[i+j]) break;
      
    }
    if (j == sizeOfPattern)
    {
      matches++;
    }
    letterMatches =0;
  }
  free(tempString);
  return matches;
}
/*
 Intial is a method that takes a file as a paramater.
 With that file it checks the size and allocs memory for a char* of that size
 It then reads the file into that char *
 */
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

