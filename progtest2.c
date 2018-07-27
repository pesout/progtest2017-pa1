/*
(c) ŠTĚPÁN PEŠOUT, 2017
*/

#include <stdio.h>
#include <float.h> 
#include <math.h>

int extremeAcc(double a) //Checks, if there isn't higher accuracy than one decimal place
{
    if (fabs(a) < DBL_EPSILON) {
        return 0;
    }
    a = 10 * a;
    double b = round(a);
    if (fabs(a - b) < DBL_EPSILON) {
        return 0;
    } else {
        return 1;
    }
}

int gcd(long a, long b) //Greatest common divisor
{
    while (b) b ^= a ^= b ^= a %= b;
    return a;
}

int lcm(long a, long b) //Least common multiple
{
    return (a / gcd(a, b)) * b;
}

int main() {
    double minWidth, minLength;
    double tile_in, seam_in;
    long long tile = 0, tile_counted = 0, seam = 0, seam_counted = 0;
    int cycle = 0;
    int input_ok = 0;
    int first_run = 0;
    long long a, b;

    printf("Minimalni velikost:\n"); //Minimal size
    if (scanf("%lf %lf", & minWidth, & minLength) != 2 || minWidth <= 0 || minLength <= 0 || extremeAcc(minWidth) == 1 || extremeAcc(minLength) == 1 || minWidth > 10000000 || minLength > 10000000) {
        printf("Nespravny vstup.\n"); //Wrong input
        return 1;
    }

    int min_w = minWidth * 10;
    int min_l = minLength * 10;

    printf("Dlazdicky:\n"); //Tile & seam sizes input

    while (1) {
        if (scanf("%lf %lf", & tile_in, & seam_in) != 2 || tile_in <= 0 || seam_in < 0 || extremeAcc(tile_in) == 1 || extremeAcc(seam_in) == 1 || tile_in > 10000000 || seam_in > 10000000) break;
        else input_ok = 1;

        tile = tile_in * 10;
        seam = seam_in * 10;

        if (first_run == 0) {
            tile_counted = tile + seam;
            seam_counted = tile + seam + seam;

            first_run = 1;
        } else {
            if ((tile % tile_counted == 0) && ((seam - seam_counted) % tile_counted != 0)) {
                printf("Reseni neexistuje.\n"); //No solution
                return 1;
            }

            tile = tile + seam;

            a = seam_counted;
            b = seam;

            while (a != b) {
                if (a < b) {
                    a = a + tile_counted;
                } else {
                    b = b + tile;
                }

                cycle++;
                if (cycle > 10000000) {
                    printf("Reseni neexistuje.\n"); //No solution
                    return 1;
                }
            }

            tile_counted = lcm(tile_counted, tile);
            seam_counted = a;
        }

    }
    if (!feof(stdin) || input_ok == 0) {
        printf("Nespravny vstup.\n"); //Wrong input
        return 1;
    }

    // Output processing
    int width_corr = seam_counted;
    int length_corr = seam_counted;

    while (width_corr < min_w) {
        width_corr = width_corr + tile_counted;
    }

    while (length_corr < min_l) {
        length_corr = length_corr + tile_counted;
    }

    double resW = width_corr;
    double resL = length_corr;

    printf("Velikost: %.1f x %.1f\n", resW / 10, resL / 10); //Measurements output

    return 0;
}
