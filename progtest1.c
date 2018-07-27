#include <stdio.h> 
#include <math.h> 
#include <float.h>

double velikost(double u1, double u2) {
    return sqrt((u1 * u1) + (u2 * u2));
}

double pravyUhel(double u1, double u2, double v1, double v2) {
    if (fabs((u1 * v1) + (u2 * v2)) < 100 * DBL_EPSILON * fabs(u1 * v1) + 0.000000001) {
        return 1; // Je pravy
    } else {
        return 0; // Neni pravy
    }
}

int main(int argc, char
    const * argv[]) {

    double a1, a2, b1, b2, c1, c2;
    double aa1, aa2, bb1, bb2, cc1, cc2;
    double u1, u2, v1, v2;
    double velikost_u, velikost_v;
    double pravy;
    char z1, z2, z3;

    /* VSTUP A KONTROLA DAT */

    printf("Bod A:\n");
    if (scanf(" %c %lf %c %lf %c", & z1, & a1, & z2, & a2, & z3) != 5 || z1 != 91 || z2 != 44 || z3 != 93) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod B:\n");
    if (scanf(" %c %lf %c %lf %c", & z1, & b1, & z2, & b2, & z3) != 5 || z1 != 91 || z2 != 44 || z3 != 93) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod C:\n");
    if (scanf(" %c %lf %c %lf %c", & z1, & c1, & z2, & c2, & z3) != 5 || z1 != 91 || z2 != 44 || z3 != 93) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    if ((a1 == b1 && a2 == b2) || (b1 == c1 && b2 == c2) || (a1 == c1 && a2 == c2)) {
        printf("Rovnobezniky nelze sestrojit.\n");
        return 1;
    }

    double s1 = (b2 - a2) / (b1 - a1);
    double s2 = (c2 - b2) / (c1 - b1);

    if (fabs(s1 - s2) < 100 * DBL_EPSILON * s2) {
        printf("Rovnobezniky nelze sestrojit.\n");
        return 1;
    }

    /* ---- A' B' C' ---- */

    //aa
    u1 = c1 - a1;
    u2 = c2 - a2;

    aa1 = b1 + u1;
    aa2 = b2 + u2;

    //bb
    u1 = a1 - b1;
    u2 = a2 - b2;

    bb1 = c1 + u1;
    bb2 = c2 + u2;

    //cc
    u1 = a1 - c1;
    u2 = a2 - c2;

    cc1 = b1 + u1;
    cc2 = b2 + u2;

    /* ---- BOD A'---- */

    u1 = b1 - a1;
    u2 = b2 - a2;

    v1 = c1 - a1;
    v2 = c2 - a2;

    velikost_u = velikost(u1, u2);
    velikost_v = velikost(v1, v2);
    pravy = pravyUhel(u1, u2, v1, v2);

    if (fabs(velikost_u - velikost_v) <= 100 * DBL_EPSILON * velikost_v && pravy == 1) {
        printf("A': [%.13g,%.13g], ctverec\n", aa1, aa2);
    }

    if (fabs(velikost_u - velikost_v) <= 100 * DBL_EPSILON * velikost_v && pravy == 0) {
        printf("A': [%.13g,%.13g], kosoctverec\n", aa1, aa2);
    }

    if (fabs(velikost_u - velikost_v) >= 100 * DBL_EPSILON * velikost_v && pravy == 1) {
        printf("A': [%.13g,%.13g], obdelnik\n", aa1, aa2);
    }

    if (fabs(velikost_u - velikost_v) >= 100 * DBL_EPSILON * velikost_v && pravy == 0) {
        printf("A': [%.13g,%.13g], rovnobeznik\n", aa1, aa2);
    }

    /* ---- BOD B'---- */

    u1 = b1 - c1;
    u2 = b2 - c2;

    v1 = b1 - a1;
    v2 = b2 - a2;

    velikost_u = velikost(u1, u2);
    velikost_v = velikost(v1, v2);
    pravy = pravyUhel(u1, u2, v1, v2);

    if (fabs(velikost_u - velikost_v) <= 100 * DBL_EPSILON * velikost_v && pravy == 1) {
        printf("B': [%.13g,%.13g], ctverec\n", bb1, bb2);
    }

    if (fabs(velikost_u - velikost_v) <= 100 * DBL_EPSILON * velikost_v && pravy == 0) {
        printf("B': [%.13g,%.13g], kosoctverec\n", bb1, bb2);
    }

    if (fabs(velikost_u - velikost_v) >= 100 * DBL_EPSILON * velikost_v && pravy == 1) {
        printf("B': [%.13g,%.13g], obdelnik\n", bb1, bb2);
    }

    if (fabs(velikost_u - velikost_v) >= 100 * DBL_EPSILON * velikost_v && pravy == 0) {
        printf("B': [%.13g,%.13g], rovnobeznik\n", bb1, bb2);
    }

    /* ---- BOD C'---- */

    u1 = c1 - a1;
    u2 = c2 - a2;

    v1 = c1 - b1;
    v2 = c2 - b2;

    velikost_u = velikost(u1, u2);
    velikost_v = velikost(v1, v2);
    pravy = pravyUhel(u1, u2, v1, v2);

    if (fabs(velikost_u - velikost_v) <= 100 * DBL_EPSILON * velikost_v && pravy == 1) {
        printf("C': [%.13g,%.13g], ctverec\n", cc1, cc2);
    }

    if (fabs(velikost_u - velikost_v) <= 100 * DBL_EPSILON * velikost_v && pravy == 0) {
        printf("C': [%.13g,%.13g], kosoctverec\n", cc1, cc2);
    }

    if (fabs(velikost_u - velikost_v) >= 100 * DBL_EPSILON * velikost_v && pravy == 1) {
        printf("C': [%.13g,%.13g], obdelnik\n", cc1, cc2);
    }

    if (fabs(velikost_u - velikost_v) >= 100 * DBL_EPSILON * velikost_v && pravy == 0) {
        printf("C': [%.13g,%.13g], rovnobeznik\n", cc1, cc2);
    }

    return 0;
}
