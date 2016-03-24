/* fct qui change un *char en char** */

#include <err.h>
#include <stdlib.h>
#include <stdio.h>

struct keyboard
{
  int dec;
  char* character;
};

 const struct keyboard key[] = {
	{ 0x08, "[BACK]" },
	{ 0x09, "[TAB]" },
	{ 0x0C, "[CLR]" },
	{ 0x0D, "[ENTER]" },
	{ 0x10, "[SHIFT]" },
	{ 0x11, "[CTRL]" },
	{ 0x12, "[ALT]" },
	{ 0x14, "[CAPS LOCK]" },
	{ 0x1B, "[ESC]" },
	{ 0x20, "[SPACE]" },
	{ 0x21, "[PGUP]" },
	{ 0x22, "[PGDW]" },
	{ 0x23, "[END]" },
	{ 0x24, "[HOME]" },
	{ 0x25, "[LEFT]" },
	{ 0x26, "[UP]" },
	{ 0x27, "[RIGHT]" },
	{ 0x28, "[DOWN]" },
	{ 0x2C, "[PRTSCRN]" },
	{ 0x2D, "[insert]" },
	{ 0x2E, "[DEL]" },
	{ 0x30, "0" },
	{ 0x31, "1" },
	{ 0x32, "2" },
	{ 0x33, "3" },
	{ 0x34, "4" },
	{ 0x35, "5" },
	{ 0x36, "6" },
	{ 0x37, "7" },
	{ 0x38, "8" },
	{ 0x39, "9" },
	{ 0x41, "A" },
	{ 0x42, "B" },
	{ 0x43, "C" },
	{ 0x44, "D" },
	{ 0x45, "E" },
	{ 0x46, "F" },
	{ 0x47, "G" },
	{ 0x48, "H" },
	{ 0x49, "I" },
	{ 0x4A, "J" },
	{ 0x4B, "K" },
	{ 0x4C, "L" },
	{ 0x4D, "M" },
	{ 0x4E, "N" },
	{ 0x4F, "O" },
	{ 0x50, "P" },
	{ 0x51, "Q" },
	{ 0x52, "R" },
	{ 0x53, "S" },
	{ 0x54, "T" },
	{ 0x55, "U" },
	{ 0x56, "V" },
	{ 0x57, "W" },
	{ 0x58, "X" },
	{ 0x59, "Y" },
	{ 0x5A, "Z" },
	{ 0x60, "0" },
	{ 0x61, "1" },
	{ 0x62, "2" },
	{ 0x63, "3" },
	{ 0x64, "4" },
	{ 0x65, "5" },
	{ 0x66, "6" },
	{ 0x67, "7" },
	{ 0x68, "8" },
	{ 0x69, "9" },
	{ 0xA2, "[CTRL]" },
	{ 0xA3, "[CTRL]" },
	{ 0xA0, "[SHIFT]" },
	{ 0xA1, "[SHIFT]" },
	{ 0xBF, "[/]" },
	{ 0x90, "[NUMLOCK]" },
	{ 0x6F, "[/]" },
	{ 0x6A, "[*]" },
	{ 0x6B, "[+]" },
	{ 0x6D, "-" },
	{ 0x6E, "[.]" },
	{ 0x70, "[f1]" },
	{ 0x71, "[f2]" },
	{ 0x72, "[f3]" },
	{ 0x73, "[f4]" },
	{ 0x74, "[f5]" },
	{ 0x75, "[f6]" },
	{ 0x76, "[f7]" },
	{ 0x77, "[f8]" },
	{ 0x78, "[f9]" },
	{ 0x79, "[f10]" },
	{ 0x7A, "[f11]" },
	{ 0x7B, "[f12]" },
	{ 0x5B, "[WIN]" },
	{ 0x5C, "[WIN]" },
	{ 0xBD, "[-]" },
	{ 0xBB, "[+]" },
	{ 0xBA, "[;]" },
	{ 0xC0, "[`]"},
	{ 0xDB, "[ [ ]" },
	{ 0xDC, "[\\]" },
	{ 0xDD, "[ ] ]" },
	{ 0xDE, "[']" },
	{ 0xBC, "," },
	{ 0xBE, "."},
	{ 0x5D, "[APPS]" },
	{0, "[UNKNOWN]"}
};


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
