#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define RESIZE_CONST 20

char * RLEDecompress ( const char * src )
{
  int digit_counter = 0;
  int chars = 0;
  int another_counter = 0;
  int l = 0;
  char tmp = 0;

  char *output = (char *)malloc(sizeof(char) * (strlen(src) + RESIZE_CONST));

  for (int i = strlen(src)-1; i>0; i--)
  {
    if (isdigit(src[i]))
    {
      chars = chars + (src[i]-48) * pow(10, digit_counter);
      digit_counter++;
    }
    else
    {
      if (digit_counter)
      {
        for (int j = 0; j<chars; j++)
        {
          output[another_counter] = src[i];
          another_counter++;
          if ((another_counter % RESIZE_CONST) == (RESIZE_CONST - 1))
          {
            output = (char *)realloc(output, sizeof(char) * (strlen(src) + (2*RESIZE_CONST) + another_counter));
          }
        }
        digit_counter = 0;
        chars = 0;
      }
      else
      {
        output[another_counter] = src[i];
        another_counter++;
        if (another_counter % RESIZE_CONST == 0)
        {
          output = (char *)realloc(output, sizeof(char) * (strlen(src) + (2*RESIZE_CONST) + another_counter));
        }
        digit_counter = 0;
        chars = 0;
      }
    }
  }
  if (chars == 0 && src[1] != 48) {chars = 1;}
  for (int k = 0; k<chars; k++)
  {
    output[another_counter] = src[0];
    another_counter++;
    if (another_counter % RESIZE_CONST == 0)
    {
      output = (char *)realloc(output, sizeof(char) * (strlen(src) + (2*RESIZE_CONST) + another_counter));
    }
  }

  int arr_size = another_counter;
  another_counter--;

  while (another_counter - l > 0)
  {
    tmp = output[l];
    output[l] = output[another_counter];
    output[another_counter] = tmp;
    l++;
    another_counter--;
  }

  output[arr_size] = '\0';
  return output;
}

int main()
{
  printf("ME  >%s<\n", RLEDecompress ( "Hello world!" ));
  printf("REF >Hello world!<\n\n");

  printf("ME  >%s<\n", RLEDecompress ( "Hello 30world!" ));
  printf("REF >Hello                              world!<\n\n");

  printf("ME  >%s<\n", RLEDecompress ( "Hel2o world!10" ));
  printf("REF >Hello world!!!!!!!!!!<\n\n");

  printf("ME  >%s<\n", RLEDecompress ( "H2e6l8o15 35w5o6r-2d0!"));
  printf("REF >HHeeeeeellllllllooooooooooooooo                                   wwwwwoooooor--!<\n\n");

  printf("ME  >%s<\n", RLEDecompress ( "321" ));
  printf("REF >333333333333333333333<\n\n");


  return 0;
}



// #ifndef __PROGTEST__
// int main ( int argc, char * argv [] )
// {
//   char * res;
//
//   assert ( ! strcmp (
//     (res = RLEDecompress ( "Hello world!" )),
//     "Hello world!" ));
//   free ( res );
//
//   assert ( ! strcmp (
//     (res = RLEDecompress ( "Hello 30world!" )),
//     "Hello                              world!" ));
//   free ( res );
//
//   assert ( ! strcmp (
//     (res = RLEDecompress ( "Hel2o world!10" )),
//     "Hello world!!!!!!!!!!" ));
//   free ( res );
//
//   assert ( ! strcmp (
//     (res = RLEDecompress ( "H2e6l8o15 35w5o6r-2d0!" )),
//     "HHeeeeeellllllllooooooooooooooo                                   wwwwwoooooor--!" ));
//   free ( res );
//
//   assert ( ! strcmp (
//     (res = RLEDecompress ( "321" )),
//     "333333333333333333333" ));
//   free ( res );
//
//   return 0;
// }
// #endif /* __PROGTEST__ */
