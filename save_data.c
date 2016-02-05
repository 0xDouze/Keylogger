#include <err.h>
#include <stdio.h>

void  save_data (char *buffer)
{

  FILE *fp;

  fp = fopen("data-keylogger.txt","a");
  if (fp == NULL)
    err(1, "Problem with fopen data-keylogger");

  if (fprintf(fp, "%s \n", buffer) < 0)
    err(1, "Problem with fprintf");

  if ((fclose(fp)) != 0)
    err(1, "Problem with fclose");


}

/* int main () 
{

  char buffer[42] = "coucou";
  
  save_data (buffer);

  return 0;

} */

