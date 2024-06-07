#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VECTORS 100
#define EPSILON 1e-6

typedef struct {
    float x, y, z;
} Vector;

// Функция для чтения векторов из файла
int read_vectors(const char *filename, Vector vectors[], int max_vectors) {
    FILE *file = fopen(filename, "r");

    int count = 0;
    while (count < max_vectors && fscanf(file, "%f %f %f", &vectors[count].x, &vectors[count].y, &vectors[count].z) == 3) {
        count++;
    }

    fclose(file);
    return count;
}

// Функция для записи векторов в файл
void write_vectors(const char *filename, Vector vectors[], int vector_count) {
    FILE *file = fopen(filename, "w");

    for (int i = 0; i < vector_count; i++) {
        fprintf(file, "%.1f %.1f %.1f\n", vectors[i].x, vectors[i].y, vectors[i].z);
    }

    fclose(file);
}

// Функция для проверки ортогональности двух векторов
int is_orthogonal(Vector a, Vector b) {
    float dot_product = a.x * b.x + a.y * b.y + a.z * b.z;
    return fabs(dot_product) < EPSILON;
}

int main() {
    const char *input_filename = "vectors.txt";
    const char *output_filename = "filtered_vectors.txt";

    Vector vectors[MAX_VECTORS];
    int vector_count = read_vectors(input_filename, vectors, MAX_VECTORS);
    if (vector_count == -1) {
        return 1;
    }

    Vector given_vector = {1.0, 2.0, 3.0};

    Vector filtered_vectors[MAX_VECTORS];
    int filtered_count = 0;

    for (int i = 0; i < vector_count; i++) {
        if (!is_orthogonal(given_vector, vectors[i])) {
            filtered_vectors[filtered_count++] = vectors[i];
        }
    }

    write_vectors(output_filename, filtered_vectors, filtered_count);

    return 0;
}
