#include <stdio.h>
#include <stdarg.h>
#include <math.h>

typedef enum {
    CONVEX_NO,
    CONVEX_YES
} ConvexStatus;

typedef struct {
    double x;
    double y;
} Point;

int sign(double x) {
    if (x > 0) {
        return 1;
    } 
    else if (x < 0) {
        return -1;
    } 
    else {
        return 0;
    }
}

int orientation(Point p1, Point p2, Point p3) {
    double x1 = p2.x - p1.x;
    double y1 = p2.y - p1.y;
    double x2 = p3.x - p2.x;
    double y2 = p3.y - p2.y;
    return sign(x1 * y2 - y1 * x2);
}

ConvexStatus isConvex(int n, ...) {
    if (n < 3) {
        printf("The polygon must have at least 3 vertices.\n");
        return CONVEX_NO;
    }

    va_list args;
    va_start(args, n);

    Point p1 = va_arg(args, Point);
    Point p2 = va_arg(args, Point);
    Point p3 = va_arg(args, Point);

    int prevOrientation = orientation(p1, p2, p3);
    int currOrientation;

    for (int i = 0; i < n - 1; i++) {
        currOrientation = orientation(p1, p2, p3);
        p1 = p2;
        p2 = p3;
        p3 = va_arg(args, Point);
        if (currOrientation != prevOrientation) {
            return CONVEX_NO;
        }

        prevOrientation = currOrientation;
    }

    va_end(args);

    return CONVEX_YES;
}

double polynomialValue(double x, int n, ...) {
    va_list args;
    va_start(args, n);

    double result = 0;
    double coefficient;

    for (int i = 0; i <= n; i++) {
        coefficient = va_arg(args, double);
        result += coefficient * pow(x, n - i);
    }

    va_end(args);

    return result;
}

int main() {
    Point p1 = {0.0, 0.0};
    Point p2 = {0.0, 1.0};
    Point p3 = {1.0, 1.0};
    Point p4 = {1.0, 0.0};

    ConvexStatus convex = isConvex(4, p1, p2, p3, p4);

    if (convex == CONVEX_YES) {
        printf("The polygon is convex.\n");
    } else {
        printf("The polygon is not convex.\n");
    }

    double x = 2.0;
    double coefficient1 = 1.467189;
    double coefficient2 = -2.0;
    double coefficient3 = 3.0;

    double value = polynomialValue(x, 2, coefficient1, coefficient2, coefficient3);

    printf("The value of the polynomial at x = %.2f is %.2f.\n", x, value);

    return 0;
}