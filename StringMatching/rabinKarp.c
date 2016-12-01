#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int prime;
char* intial(FILE* in);
int reader(const char* pattern, FILE* in, int alphabet, long h);


int main(int argc, const char * argv[]) {
  
  long h;
  const char* infile;
  const char* pattern;
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
/*
 reader is the method where all the work happens. Reader takes in a pattern
 an in file and a long h. Pattern calls intial on the in file, it then builds the intial 
 hash for pattern and tempString. It then tries to match. Will there are still possible
 matches it updates the tempHash.
 */
int reader(const char* pattern, FILE* in, int alphabet, long h)
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

  for(j = 0; j< tempLength; j++)
  {
    
    if(patternHash == tempHash)
    {
      
      for(i = 0; i<patternLength;i++)
      {
        if(tempString[i+j] != pattern[i]) break;
      }
      if(i==patternLength)
      {
        matches++;

      }
    
    }
    if(i<tempLength-patternLength)
    {
    tempHash = (alphabet*((tempHash - tempString[j]*h)%prime)+tempString[j+patternLength])%prime;
    if(tempHash<0)
    {
      tempHash = tempHash+prime;
    }
    }
  }
  
  return matches;
}

