#include "tp2.c"
#include <time.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

void heapify(int *tab, unsigned n, unsigned pos)
{
  unsigned l = 2 * pos + 1;
  unsigned r = 2 * pos + 2;
  unsigned larg;

  if (l < n && tab[l] > tab[pos])
    larg = l;
  else
    larg = pos;

  if (r < n && tab[r] > tab[larg])
    larg = r;

  if (larg != pos)
  {
    int tmp = tab[pos];
    tab[pos] = tab[larg];
    tab[larg] = tmp;
    heapify(tab, n, larg);
  }
}

void make_heap(int *tab, unsigned n)
{
  int i = n / 2 - 1;
  while (i >= 0)
    heapify(tab, n, i--);
}

bool check_heap(int *heap, unsigned n)
{
  unsigned i;
  for (i = 0; i <= n / 2 - 1; i++)
  {
    if(2 * i + 2 < n)
    {
      if (heap[i] < heap[2 * i + 1] || heap[i] < heap[2 * i + 2])
        return false;
    }
    else
      break;
  }
  if (2 * i + 1 < n && heap[i] < heap[2 * i + 1])
    return false;

  return true;
}

void pretty_print_heap(FILE *out, const int *tab, int n)
{
  int countn = 0;
  int w = ints_width(tab, n); // Largeur nombre
  int h = 1; // Hauteur
  int i;
  for (i = 1; 2 * i <= n; i = 2 * i)
    h++;
  int t = (w + 1) * pow(2, h); // Longueur ligne
  int line = 1;
  int c = 1;

  for (; line <= h && countn < n; line++)
  {
    int s = t / c - w; // Espace séparateur

    fprintf(out, "%*s%d", s / 4 + w - int_width(tab[countn]) - 1, "", tab[countn]);
    int tmp = 1;
    countn++;
    while (countn < n && tmp < c)
    {
      fprintf(out, "%*s%d", s / 2 + w - int_width(tab[countn]) - 1, "", tab[countn]);
      tmp++;
      countn++;
    }
    fprintf(out, "\n");
    c *= 2;
  }
}

void swap(int *a, int *b)
{
  int c;
  c = *a;
  *a = *b;
  *b = c;
}

int pop_heap(int *heap, unsigned *n)
{
  int tmp = *heap;
  *heap = heap[*n - 1];
  *n = *n - 1;
  unsigned i = 0;
  do
    {
      if (2 * i + 2 < *n && heap[2 * i + 2] > heap[2 * i + 1])
	{
	  if (!check_heap(heap, *n))
	    {
	      swap(heap + i, heap + (2 * i + 2));
	      i = 2 * i + 2;
	    }
	  else
	    break;
	}
      else if (2 * i + 1 < *n)
	{
	  if (!check_heap(heap, *n))
	    {
	      swap(heap + i, heap + (2 * i + 1));
	      i = 2 *i + 1;
	    }
	  else
	    break;
	}
      else
	break;
    }while (!check_heap(heap, *n));
  return tmp;
}

void heap_sort(int *tab, unsigned n)
{
  int i;
  for (i = (n - 1) / 2; i >= 0; i--)
    heapify(tab, n, i);

  for (i = n -1; i > 0; i--)
  {
    int tmp = tab[i];
    tab[i] = tab[0];
    tab[0] = tmp;
    n--;
    heapify(tab, n, 0);
  }
}
