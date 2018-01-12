/*
   \_\_    _/_/
       \__/
       (oo)\_______
       (__)\       )\/\
           ||----w |
           ||     ||
*/

#include <stdio.h>
#include <float.h>
#include <math.h>

#define STREET_LIMIT 100

int isInt(double a)
{
  double b = round(a);

  if (fabs(a-b) < DBL_EPSILON)
  {
    return 1; // OK
  }
  else
  {
    return 0; // Isn't an integer
  }
}

int parkCheck(int a, int m, int arr[]) // Park is represented by 0
{
  int no_park = 0;

  for (int i = 0; i < a; i++)
  {
    if (arr[i] != 0)
    {
      no_park++;
    }
    else
    {
      no_park = 0;
    }

    if (no_park > m) return 0; // Too many without park
  }

  return 1; // OK
}

int industryCheck(int a, int arr[]) // Industry is represented by 3
{
  int is_industry = 0;
  int industry_block = 0;

  if (a == 1 && arr[0] == 3) return 0;

  for (int i = 0; i < a; i++)
  {
    if (arr[i] == 3)
    {
      is_industry++;
      industry_block = 1;
    }
    else
    {
      if (is_industry < 2 && industry_block) return 0; // Less then 2
      is_industry = 0;
      industry_block = 0;
    }
  }

  if (is_industry < 2 && industry_block) return 0;
  return 1; // OK
}

int commCheck(int a, int m, int arr[]) // Commercial is represented by 2
{
  int no_comm = 0;
  int i = 0;

  while (arr[i] != 2 && i < a) i++;

  if (i == a)
  {
    return 1; // OK
  }
  else
  {
    i++;
  }

  for (i = i; i < a; i++)
  {
    if (arr[i] != 2)
    {
      no_comm++;
    }
    else
    {
      if (no_comm < m) return 0; // Less then m
      no_comm = 0;
    }
  }

  return 1; // OK
}

void arrayPrint(int a, int arr[])
{
  printf("[");
  for (int i = 0; i < a; i++)
  {
    if (arr[i] == 0) printf("P");
    if (arr[i] == 1) printf("R");
    if (arr[i] == 2) printf("C");
    if (arr[i] == 3) printf("I");
  }
  printf("]\n");
}

int main()
{
  double m_in;
  int m = 0, i = 0;
  int street[STREET_LIMIT] = {0};
  int counter = 0;

  static char query[100000];
  int query_parameter = 0;
  int query_type = 0;

  printf("Modul:\n");
  if (scanf("%lf", &m_in) != 1 || isInt(m_in) == 0 || m_in < 1 || m_in > 10)
  {
    printf("Nespravny vstup.\n");
    return 1;
  }

  m = m_in;

  printf("Vypocty:\n");

  while(1)
  {
    if (scanf("%s", query) == EOF)
    {
      return 0;
    }

    if (query[0] == 99 && query[1] == 111 && query[2] == 117 && query[3] == 110 && query[4] == 116 && query[5] == 0)
    {
      query_type = 1; //Count
    }

    if(query[0] == 108 && query[1] == 105 && query[2] == 115 && query[3] == 116 && query[4] == 0)
    {
      query_type = 2; //List
    }

    if (query_type == 0)
    {
      printf("Nespravny vstup.\n");
      return 1;
    }

    if (scanf("%d", &query_parameter) != 1 || query_parameter < 1 || query_parameter > (STREET_LIMIT-1))
    {
      printf("Nespravny vstup.\n");
      return 1;
    }

    while (1)
    {
        if (parkCheck(query_parameter, m, street) && industryCheck(query_parameter, street) && commCheck(query_parameter, m, street))
        {
          if (query_type == 2) arrayPrint(query_parameter, street); // List
          counter++;
        }

        street[i]++;
        while (street[i] == 4)
        {
          street[i] = 0;
          i++;
          street[i]++;
        }

        if (i == query_parameter) break;
        i = 0;
    }

    printf("=> %d\n", counter);

    street[query_parameter] = 0;
    query_type = 0;
    counter = 0;
    i = 0;
  }

  return 0;
}
