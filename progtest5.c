#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

#define BLOCK_DARR_SIZE 1000

int inputCheck(double a)
{
  if ( fabs(a) < DBL_EPSILON )
  {
    return 2; //is zero
  }

  double b = round(a);
  if ( fabs(a-b) < DBL_EPSILON )
  {
    return 0; //ok
  }
  else
  {
    return 1; //is not an int num
  }
}

int gcd(unsigned long long a, unsigned long long b) //Greatest common divisor
{
  while(b) b ^= a ^= b ^= a %= b;
  return a;
}

int lcm(unsigned long long a, unsigned long long b) //Least common multiple
{
  return (a / gcd (a, b)) * b;
}

int main()
{
  char c1 = 0;
  double input = 0;
  int *road_map = 0;
  int odd_run = 1;
  int input_counter = 0;

  double from_in = 0;
  double to_in = 0;
  int from = 0;
  int to = 0;
  unsigned long long result = 1;
  unsigned long long road_map_ll;
  int input_test;

  printf("Pocty pruhu:\n");
  if (scanf(" %c", &c1) != 1 || c1 != 123)
  {
    printf("Nespravny vstup.\n");
    return 1;
  }

  road_map = (int *)malloc(sizeof(int)*BLOCK_DARR_SIZE);

  while(1)
  {
    if (odd_run) //an int num is expected
    {
      if (scanf("%lf", &input) != 1 || inputCheck(input) || input <= 0)
      {
        printf("Nespravny vstup.\n");
        free(road_map);
        return 1;
      }

      road_map[input_counter] = round(input);

      if (input_counter % BLOCK_DARR_SIZE == (BLOCK_DARR_SIZE - 1))
      {
        road_map = (int *)realloc(road_map, sizeof(int) * (input_counter + BLOCK_DARR_SIZE));
      }

      input_counter++;
      odd_run = 0;
    }
    else //even run (a char is expected)
    {
      if (scanf(" %c", &c1) != 1)
      {
        printf("Nespravny vstup.\n");
        free(road_map);
        return 1;
      }

      if (c1 == 44)
      {
        odd_run = 1;
        continue;
      }

      if (c1 == 125)
      {
        odd_run = 1;
        break;
      }

      if (c1 != 125 && c1 != 44)
      {
        printf("Nespravny vstup.\n");
        free(road_map);
        return 1;
      }
    }
  }

  printf("Trasy:\n");

  while(1)
  {
    input_test = scanf("%lf %lf", &from_in, &to_in);
    if(input_test != 2 || inputCheck(from_in) == 1 || inputCheck(to_in) == 1)
    {
      if (input_test == EOF)
      {
        break;
      }
      printf("Nespravny vstup.\n");
      free(road_map);
      return 1;
    }

    from = from_in;
    to = to_in;

    if (from >= to || from < 0 || to > input_counter)
    {
      printf("Nespravny vstup.\n");
      free(road_map);
      return 1;
    }

    for (int j = from; j < to; j++)
    {
      road_map_ll = road_map[j];
      result = lcm (result, road_map_ll);
    }

    printf("Vozidel: %llu\n", result);
    result = 1;
  }

  free(road_map);
  return 0;
}
