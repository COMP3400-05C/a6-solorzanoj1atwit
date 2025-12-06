#include "parta.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("ERROR: Missing arguments\n");
        return 1;
    }

    if (strcmp(argv[1], "fcfs") == 0) {
        if (argc < 3) {
            printf("ERROR: Missing arguments\n");
            return 1;
        }

        int plen = argc - 2;
        int* bursts = malloc(sizeof(int) * plen);
        if (!bursts) return 1;

        for (int i = 0; i < plen; ++i) {
            bursts[i] = parse_int_or_zero(argv[2 + i]);
        }

        printf("Using FCFS\n\n");
        for (int i = 0; i < plen; ++i) {
            printf("Accepted P%d: Burst %d\n", i, bursts[i]);
        }

        struct pcb* procs = init_procs(bursts, plen);
        if (!procs) {
            free(bursts);
            return 1;
        }

        (void) fcfs_run(procs, plen); /* updates procs[].wait */

        double total_wait = 0.0;
        for (int i = 0; i < plen; ++i) total_wait += procs[i].wait;
        printf("Average wait time: %.2f\n", total_wait / plen);

        free(bursts);
        free(procs);
        return 0;
    }
    else if (strcmp(argv[1], "rr") == 0) {
        if (argc < 4) {
            printf("ERROR: Missing arguments\n");
            return 1;
        }

        int quantum = parse_int_or_zero(argv[2]);
        int plen = argc - 3;
        int* bursts = malloc(sizeof(int) * plen);
        if (!bursts) return 1;

        for (int i = 0; i < plen; ++i) {
            bursts[i] = parse_int_or_zero(argv[3 + i]);
        }

        printf("Using RR(%d).\n\n", quantum);
        for (int i = 0; i < plen; ++i) {
            printf("Accepted P%d: Burst %d\n", i, bursts[i]);
        }

        struct pcb* procs = init_procs(bursts, plen);
        if (!procs) {
            free(bursts);
            return 1;
        }

        (void) rr_run(procs, plen, quantum); /* updates procs[].wait */

        double total_wait = 0.0;
        for (int i = 0; i < plen; ++i) total_wait += procs[i].wait;
        printf("Average wait time: %.2f\n", total_wait / plen);

        free(bursts);
        free(procs);
        return 0;
    }
    else {
        printf("ERROR: Missing arguments\n");
        return 1;
    }
}
