/*

  _--___-__--__-_-_--_--___--_-__-_--__-_-
  _---_--__--__-_-__-______--_-__-_--_---_
  __-______--____-_--_---__--____-_---__-_
  _--___--_--_-____--_-__-_---__--_--_--_-

*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int cols = 0, rows = 0;
  int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
  int sum, max_size = 0, sum_sum = 0;
  int list_counter = 0;

  static char query[1000000];
  int query_parameter = 0;
  int query_type = 0;



  printf("Velikost mapy:\n");
  if (scanf("%d", &cols) != 1 || cols <= 0 || cols > 2000)
  {
    printf("Nespravny vstup.\n");
    return 1;
  }

  if (scanf("%d", &rows) != 1 || rows <= 0 || rows > 2000)
  {
    printf("Nespravny vstup.\n");
    return 1;
  }

  static int map[2000][2000];

  printf("Cenova mapa:\n");

  for (int j = 0; j < rows; j++)
  {
    for (int i = 0; i < cols; i++)
    {
      if (scanf("%d", &map[i][j]) != 1 || map[i][j] < 1)
      {
        printf("Nespravny vstup.\n");
        return 1;

      }

      if (i != 0 && j != 0) map[i][j] = map[i][j] + map[i-1][j] + map[i][j-1] - map[i-1][j-1];
      else
      {
        if (i == 0 && j != 0) map[i][j] = map[i][j] + map[i][j-1];
        if (i != 0 && j == 0) map[i][j] = map[i][j] + map[i-1][j];
      }
    }
  }

  static int list_arr_sum[3000];
  static int list_arr_width[3000];
  static int list_arr_height[3000];
  static int list_arr_x1[3000];
  static int list_arr_x2[3000];

  printf("Dotazy:\n");

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

    if (scanf("%d", &query_parameter) != 1 || query_parameter < 1)
    {
      printf("Nespravny vstup.\n");
      return 1;
    }

    for (int k = 0; k <= rows; k++)
    {
      for (int l = 0; l <= cols; l++)
      {
        for (int m = 0; m < (rows-k); m++)
        {
          for (int n = 0; n < (cols-l); n++)
          {
            x1 = n;
            x2 = m;
            y1 = n + l;
            y2 = m + k;
  /*
          [x1,x2] +---------+
                  |         |
                  |         |
                  +---------+ [y1,y2]
  */
            if (x1 == 0 && x2 == 0)
            {
              sum =  map[y1][y2];
            }

            if (x1 == 0 && x2 != 0)
            {
              sum = map[y1][y2] - map[y1][x2-1];
            }

            if (x1 != 0 && x2 == 0)
            {
              sum = map[y1][y2] - map[x1-1][y2];
            }

            if (x1 != 0 && x2 != 0)
            {
              sum = map[y1][y2] + map[x1-1][x2-1] - map[y1][x2-1] - map[x1-1][y2];
            }

            if ( (l+1)*(k+1) == max_size && sum <= query_parameter)
            {
              sum_sum++;

              if (query_type == 2)
              {
                list_arr_sum[list_counter] = sum;
                list_arr_width[list_counter] = (l+1);
                list_arr_height[list_counter] = (k+1);
                list_arr_x1[list_counter] = x1;
                list_arr_x2[list_counter] = x2;
                list_counter++;
              }

            }

            if ( (l+1)*(k+1) > max_size && sum <= query_parameter)
            {
              max_size = (l+1)*(k+1);
              sum_sum = 1;

              if (query_type == 2)
              {
                list_counter = 0;

                list_arr_sum[list_counter] = sum;
                list_arr_width[list_counter] = (l+1);
                list_arr_height[list_counter] = (k+1);
                list_arr_x1[list_counter] = x1;
                list_arr_x2[list_counter] = x2;
                list_counter++;
              }
            }
          }
        }
      }
    }

    if (max_size == 0 && sum_sum == 0)
    {
      printf("Nenalezeno.\n");
    }
    else
    {
      printf("Max. rozloha: %d (x %d)\n", max_size, sum_sum);
    }

    if (query_type == 2)
    {
      for (int o = 0; o < list_counter; o++)
      {
        printf("%d: %d x %d @ (%d,%d)\n", list_arr_sum[o], list_arr_width[o], list_arr_height[o], list_arr_x1[o], list_arr_x2[o]);
      }
    }

    list_counter = 0;
    sum = 0;
    max_size = 0;
    sum_sum = 0;

  }

  return 0;
}
