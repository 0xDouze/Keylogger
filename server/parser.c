/* fct qui change un *char en char** */

#include <err.h>
#include <stdlib.h>
#include <stdio.h>

struct keyboard 
{
  char* dec;
  char* character;
}

static const struct keyboard key[] = {
  { "0x30", "0"},
  {"0", "[UNKNOWN]"},
}


char** parser (char* buffer)
{
  char **trad;
  size_t cpt = 0;
  size_t col;
  size_t i = 0;
  size_t j = 0;

  while (*buffer != '\0')
  {
    if (*buffer == 32) // code ASCII de SPACE en decimal
      cpt++; // nb de mots contenus dans le buffer
    buffer++;
  }


  trad = calloc(cpt, sizeof(char*)); // tableau qui contient un mot (en dec) sur chaque ligne
  if (trad == NULL)  
    err(-1,"Problem with 1st calloc");

  col = cpt;
  while (col > 0)
  {
    *trad = calloc(5,sizeof(char)); // chaque ligne du tableau contient 5 cases (une case par lettre (en dec))
    if (*trad == NULL)
      err(-1, "Problem with 2nd calloc");   
    col --;
  }

  
  while (*buffer != '\0')
  {
    while (*buffer |= 32)
    {
      trad[i][j] = *buffer;
      j++;
    }
    j = 0;
    i++;
    buffer++;
  }

  return trad;
}

int main ()
{
  char* buffer = "Je me presente, je m'appelle Kevin";
  char** tab = parser(buffer);
  printf("%s \n", tab[1]);
  return 0;
}
