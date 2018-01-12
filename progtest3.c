#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#define INVALID_DATE (-1)
#endif /* __PROGTEST__ */

int isLeapYear(int y) //0 ~ no; 1 ~ yes
{
  if (y % 4000 == 0)
  {
    return 0;
  }
  else
  {
    if (y % 400 == 0)
    {
      return 1;
    }
    else
    {
      if (y % 100 == 0)
      {
        return 0;
      }
      else
      {
        if (y % 4 == 0)
        {
          return 1;
        }
        else
        {
          return 0;
        }
      }
    }
  }
}

int daysSince2000(int d, int m, int y) //means <1.1.2000 ; dd.mm.yyyy>
{
  int a = (y / 4) - (y / 100) + (y / 400) - (y / 4000); //number of leap years
  a = (a * 366) + ((y-a)*365) - 730484; //days to 1.1.y

  int b = 0;
  if (isLeapYear(y) == 1)
  {
    b = 1;
  }

  switch(m)
  {
    case	1: //Jan
      a = a + d;
      break;
    case	2: //Feb
      a = a + 31 + d;
      break;
    case	3: //Mar
      a = a + 59 + d + b;
      break;
    case	4: //Apr
      a = a + 90 + d + b;
      break;
    case	5: //May
      a = a + 120 + d + b;
      break;
    case	6: //Jun
      a = a + 151 + d + b;
      break;
    case	7: //Jul
      a = a + 181 + d + b;
      break;
    case	8: //Aug
      a = a + 212 + d + b;
      break;
    case	9: //Sep
      a = a + 243 + d + b;
      break;
    case	10: //Oct
      a = a + 273 + d + b;
      break;
    case	11: //Nov
      a = a + 304 + d + b;
      break;
    case	12: //Dec
      a = a + 334 + d + b;
      break;
  }

  if (y == 2000)
  {
    a--;
  }

  return a - 1;
}

long long int SecondsSinceRef(int y, int m, int d, int hod, int min, int sec)
{
  long long time = daysSince2000(d, m, y);
  long long ref_time = (197*86400)+(13*3600)+(55*60)+12;
  time = (time*86400) + sec + (min*60) + (hod*3600) - ref_time;
  return time;
}

int inputCheck(int y, int m, int d)
{
  if (y < 2000 || m < 1 || m > 12 || d > 31)
  {
    return (-1);
  }

  if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && d > 31) {return (-1);}
  if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) {return (-1);}
  if (m == 2)
  {
    if (isLeapYear(y) == 1 && d > 29) {return (-1);}
    if (isLeapYear(y) == 0 && d > 28) {return (-1);}
  }
  return 1;
}

int isFullMoon ( int y, int m, int d ) //přidat fci pro začátek roku 2000!!!!
{
  if (inputCheck(y, m, d) == (-1)) {return (-1);}

  if (y == 2000 && m == 7 && d == 16) {return 1;}


  int a = SecondsSinceRef(y, m, d, 0, 0, 0) / 2551443;
  int b = SecondsSinceRef(y, m, d, 23, 59, 59) / 2551443;

  return b - a;
}



int prevFullMoon ( int y, int m, int d,
                   int * prevY, int * prevM, int * prevD ) //VSTUPYYYYYYY!!!!!
{
  if (inputCheck(y, m, d) == (-1)) {return (-1);}
  long long int a = SecondsSinceRef(y, m, d, 0, 0, 0);

  a = (a % 2551443) / 86400 + 1;

  int month_changed = 0;

  int day = d;
  int month = m;
  int year = y;

  day = d - a;

  if (day < 1)
  {
    if (month == 3)
    {
      if (isLeapYear(year) == 1)
      {
        day = day + 29;
        month--;
      }

      if (isLeapYear(year) == 0)
      {
        day = day + 28;
        month--;
      }
    }

    if (month == 1)
    {
      day = day + 31;
      month = 12;
      year--;
      month_changed = 1;
    }

    if ((month == 5 || month == 7 || month == 10 || month == 12) && month_changed == 0)
    {
      day = day + 30;
      month--;
      month_changed = 1;
    }

    if (month == 2)
    {
      day = day + 31;
      month--;
    }

    if ((month == 4 || month == 6 || month == 8 || month == 9 || month == 11) && month_changed == 0)
    {
      day = day + 31;
      month--;
    }

  }

  *prevY = year;
  *prevM = month;
  *prevD = day;

  if (y == 2000)
  {
    if ((m == 7 && d <= 16) || (m == 6 && d > 16))
    {
      *prevM = 6;
      *prevD = 16;
    }
    if ((m == 6 && d <= 16) || (m == 5 && d > 18))
    {
      *prevM = 5;
      *prevD = 18;
    }
    if ((m == 5 && d <= 18) || (m == 4 && d > 18))
    {
      *prevM = 4;
      *prevD = 18;
    }
    if ((m == 4 && d <= 18) || (m == 3 && d > 20))
    {
      *prevM = 3;
      *prevD = 20;
    }
    if ((m == 3 && d <= 20) || (m == 2 && d > 19))
    {
      *prevM = 2;
      *prevD = 19;
    }
    if ((m == 2 && d <= 19) || (m == 1 && d > 21))
    {
      *prevM = 1;
      *prevD = 21;
    }
    if (m == 1 && d <= 21)
    {
      *prevM = 12;
      *prevD = 22;
      *prevY = 1999;
    }
  }

  return 1;
}

int nextFullMoon ( int y, int m, int d,
                   int * nextY, int * nextM, int * nextD )
{
  if (inputCheck(y, m, d) == (-1)) {return (-1);}
  long long int b = SecondsSinceRef(y, m, d, 23, 59, 59);
  b = (2551443 - (b % 2551443)) / 86400 + 1;

  int day = d;
  int month = m;
  int year = y;

  day = d + b;

  if (day >= 29)
  {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10)
    {
      if (day > 31)
      {
        day = day - 31;
        month++;
      }
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
      if (day > 30)
      {
        day = day - 30;
        month++;
      }
    }

    if (month == 2)
    {
      if (day > 29 && isLeapYear(year) == 1)
      {
        day = day - 29;
        month++;
      }

      if (day > 28 && isLeapYear(year) == 0)
      {
        day = day - 28;
        month++;
      }
    }

    if (month == 12)
    {
      if (day > 31)
      {
        day = day - 31;
        month = 1;
        year++;
      }
    }
  }

  if (day == 51 && month == 0)
  {
    day = 21;
    month = 1;
  }

  *nextY = year;
  *nextM = month;
  *nextD = day;

  if (y == 2000)
  {
    if ((m == 7 && d < 16) || (m == 6 && d >= 16))
    {
      *nextM = 7;
      *nextD = 16;
    }
    if ((m == 6 && d < 16) || (m == 5 && d >= 18))
    {
      *nextM = 6;
      *nextD = 16;
    }
    if ((m == 5 && d < 18) || (m == 4 && d >= 18))
    {
      *nextM = 5;
      *nextD = 18;
    }
    if ((m == 4 && d < 18) || (m == 3 && d >= 20))
    {
      *nextM = 4;
      *nextD = 18;
    }
    if ((m == 3 && d < 20) || (m == 2 && d >= 19))
    {
      *nextM = 3;
      *nextD = 20;
    }
    if ((m == 2 && d < 19) || (m == 1 && d >= 21))
    {
      *nextM = 2;
      *nextD = 19;
    }
    if (m == 1 && d < 21)
    {
      *nextM = 1;
      *nextD = 21;
    }
  }

  return 1;
}
