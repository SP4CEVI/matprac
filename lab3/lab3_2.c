#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

struct Vector {
    double *coordinates;
    int dimension;
};

enum Status {
    SUCCESS,
    ERROR,
    INVALID
};

enum Status normMax(struct Vector *vector, double *result) {
    if (vector->dimension <= 0) {
        return INVALID;
    }

    double max = vector->coordinates[0];
    for (int i = 1; i < vector->dimension; i++) {
        if (vector->coordinates[i] > max) {
            max = vector->coordinates[i];
        }
    }
    *result = max;
    return SUCCESS;
}

enum Status normP(struct Vector *vector, int p, double *result) {
    if (p < 1 || vector->dimension <= 0) {
        return INVALID;
    }

    double sum = 0;
    for (int i = 0; i < vector->dimension; i++) {
        sum += pow(fabs(vector->coordinates[i]), p);
    }
    *result = pow(sum, 1.0 / p);
    return SUCCESS;
}

enum Status normA(struct Vector *vector, double *result) {
    if (vector->dimension <= 0) {
        return INVALID;
    }

    int matrix[vector->dimension][vector->dimension];
    double data[vector->dimension];

    for (int i = 0; i < vector->dimension; i++) {
        for (int j = 0; j < vector->dimension; j++) {
            if (i == j) {
                matrix[i][j] = 1;
            } else {
                matrix[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < vector->dimension; i++) {
        double sum = 0;
        for (int j = 0; j < vector->dimension; j++) {
            sum += matrix[i][j] * vector->coordinates[j];
        }
        data[i] = sum;
    }

    double value = 0;
    for (int i = 0; i < vector->dimension; i++) {
        value += data[i] * data[i];
    }

    *result = sqrt(value);
    return SUCCESS;
}

enum Status findLongestVectors(double *result, struct Vector *vector, int p, enum Status (*norm1)(struct Vector *, double *), enum Status (*norm2)(struct Vector *, int, double *), enum Status (*norm3)(struct Vector *, double *), int count, ...) {
    va_list normFunctions;
    va_start(normFunctions, count);

    double max_vals[3] = {INT_MIN, INT_MIN, INT_MIN};
    int numLongestVectors[3] = {0};

    for (int i = 0; i < count; i++) {
        struct Vector v = va_arg(normFunctions, struct Vector);
        double res[3];

        if (norm1(&v, &(res[0])) != SUCCESS || norm2(&v, p, &(res[1])) != SUCCESS || norm3(&v, &(res[2])) != SUCCESS) {
            return ERROR;
        }

        for (int j = 0; j < 3; j++) {
            if (res[j] > max_vals[j]) {
                max_vals[j] = res[j];
                result[j] = max_vals[j];
                numLongestVectors[j] = 1;
                vector[j].coordinates = v.coordinates;
                vector[j].dimension = v.dimension;
            } else if (res[j] == max_vals[j]) {
                numLongestVectors[j]++;
            }
        }
    }

    va_end(normFunctions);
    return SUCCESS;
}

int main() {
    int n = 3;
    int p = 1;

    double vec1_data[] = {1.0, 2.0, 3.0};
    double vec2_data[] = {-1.0, 0.0, 1.0};
    double vec3_data[] = {2.0, 2.0, 2.0};

    struct Vector vec1 = {vec1_data, n};
    struct Vector vec2 = {vec2_data, n};
    struct Vector vec3 = {vec3_data, n};

    enum Status (*norm1)(struct Vector *, double *) = normMax;
    enum Status (*norm2)(struct Vector *, int, double *) = normP;
    enum Status (*norm3)(struct Vector *, double *) = normA;

    double result[3];
    struct Vector longest_vectors[3];
    int numLongestVectors[3];

    enum Status status = findLongestVectors(result, longest_vectors, p, norm1, norm2, norm3, 3, vec1, vec2, vec3);

    if (status == SUCCESS) {
        for (int i = 0; i < 3; i++) {
            printf("Longest vector for norm %d: (", i + 1);
            for (int j = 0; j < longest_vectors[i].dimension; j++) {
                printf("%f", longest_vectors[i].coordinates[j]);
                if (j < longest_vectors[i].dimension - 1) {
                    printf(", ");
                }
            }
            printf(")\n");
        }
    } else {
        printf("Error in finding longest vectors.\n");
    }

    return 0;
}