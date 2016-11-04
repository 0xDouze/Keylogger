#include "tp3.c"

unsigned pivot_first(const int* tab, unsigned l, unsigned r, int (*cmp)(int a, int b))
{
  (void) tab;
  (void) r;
  (void) cmp;
  return l;
}

unsigned pivot_rand(const int* tab, unsigned l, unsigned r, int (*cmp)(int a, int b))
{
  (void) tab;
  (void) cmp;
  return l + (rand() % (r - l));
}

unsigned pivot_median3(const int *tab, unsigned l, unsigned r, int (*cmp)(int a, int b))
{
  unsigned i;
  int a[3] = {tab[l], tab[l + ((r - l) / 2)], tab[r - 1]};

  insert_sort_cmp(a, 3, cmp);

  for (i = 0; tab[i] != a[1]; i++);

  return i;
}

unsigned partition_cmp(int* tab, unsigned b, unsigned e, unsigned p, int (*cmp)(int a, int b))
{
  int left = b - 1;
  int rigth = e;
  int pivot = tab[p];

  while (1)
  {
    do
    {
      left++;
    } while (cmp(tab[left], pivot) < 0);

    do
    {
      rigth--;
    } while (cmp(tab[rigth], pivot) > 0);

    if (rigth <= left)
      return left + (left == rigth);
    else
    {
      int tmp = tab[left];
      tab[left] = tab[rigth];
      tab[rigth] = tmp;
    }
  }
}
