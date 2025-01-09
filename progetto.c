/*
AUTORI
Iacobucci Luca      20035727
Fasano Lorenzo      20028396
Raffaele Alessandro 20025449
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Funzione da integrare: sqrt(abs(sin(x)))
double integrand(double x) {
    return sqrt(fabs(sin(x)));
}

// Funzione per generare un numero casuale in [min, max]
double random_double(double min, double max) {
    return min + (max - min) * ((double)rand() / RAND_MAX);
}

int main() {
    double a, b;           // Intervallo [a, b]
    int n_points;          // Numero di punti casuali
    char output_file[100]; // Nome file di output

    // Input: intervallo [a, b], numero di punti e nome file
    printf("Inserisci l'estremo inferiore dell'intervallo a (0 < a < 10): ");
    scanf("%lf", &a);
    printf("Inserisci l'estremo superiore dell'intervallo b (a < b <= 10): ");
    scanf("%lf", &b);

    if (a < 0 || b > 10 || a >= b) {
        printf("Intervallo non valido. Assicurati che 0 < a < b <= 10.\n");
        return 1;
    }

    printf("Inserisci il numero di punti casuali da generare: ");
    scanf("%d", &n_points);

    if (n_points <= 0) {
        printf("Il numero di punti deve essere maggiore di 0.\n");
        return 1;
    }

    printf("Inserisci il nome del file di output per i punti (es. data_1000.txt): ");
    scanf("%s", output_file);

    // Determinazione del rettangolo di bounding
    double max_f = 0;
    for (double x = a; x <= b; x += 0.001) {
        double f_x = integrand(x);
        if (f_x > max_f) {
            max_f = f_x;
        }
    }

    // Apertura file per salvare i punti
    FILE *file = fopen(output_file, "w");
    if (!file) {
        printf("Errore nell'apertura del file %s\n", output_file);
        return 1;
    }

    // Generazione punti casuali e calcolo dell'integrale
    int inside = 0;
    srand(time(NULL)); // Inizializzazione del generatore di numeri casuali

    for (int i = 0; i < n_points; i++) {
        double x = random_double(a, b);
        double y = random_double(0, max_f);

        if (y <= integrand(x)) {
            inside++;
        }

        // Salva i punti nel file
        fprintf(file, "%f %f\n", x, y);
    }

    fclose(file);

    // Area del rettangolo
    double rectangle_area = (b - a) * max_f;

    // Valore approssimato dell'integrale
    double integral = rectangle_area * ((double)inside / n_points);

    printf("\nValore approssimato dell'integrale: %.6f\n", integral);
    printf("Numero di punti interni: %d\n", inside);
    printf("Errore stimato rispetto al valore noto (7.47626): %.6f\n", fabs(integral - 7.47626));

    printf("Punti salvati nel file: %s\n", output_file);

    return 0;
}