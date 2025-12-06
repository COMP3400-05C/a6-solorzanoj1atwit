#include "parta.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * TODO: Describe what the function does
 */
struct pcb* init_procs(int* bursts, int blen) {
    if (blen <= 0 || bursts == NULL) return NULL;

    struct pcb* procs = malloc(sizeof(struct pcb) * blen);
    if (!procs) return NULL;

    for (int i = 0; i < blen; ++i) {
        procs[i].pid = i;
        procs[i].burst_left = bursts[i];
        procs[i].wait = 0;
    }

    return procs;
}

/**
 * TODO: Describe what the function does
 */
void printall(struct pcb* procs, int plen) {
    if (!procs || plen <= 0) return;
    for (int i = 0; i < plen; ++i) {
        printf("PID %d: burst_left=%d wait=%d\n", procs[i].pid, procs[i].burst_left, procs[i].wait);
    }
}

/**
 * TODO: Describe what the function does
 */
void run_proc(struct pcb* procs, int plen, int current, int amount) {
    if (!procs || plen <= 0) return;
    if (current < 0 || current >= plen) return;
    if (amount <= 0) return;

    int actual = amount;
    if (actual > procs[current].burst_left) {
        actual = procs[current].burst_left;
    }

    procs[current].burst_left -= actual;

    for (int i = 0; i < plen; ++i) {
        if (i == current) continue;
        if (procs[i].burst_left > 0) {
            procs[i].wait += actual;
        }
    }
}

/**
 * TODO: Describe what the function does
 */
int fcfs_run(struct pcb* procs, int plen) {
    if (!procs || plen <= 0) return 0;

    int elapsed = 0;
    for (int i = 0; i < plen; ++i) {
        if (procs[i].burst_left > 0) {
            int to_run = procs[i].burst_left; /* run until completion */
            run_proc(procs, plen, i, to_run);
            elapsed += to_run;
        }
    }
    return elapsed;
}

/**
 * TODO: Describe what the function does
 */
int rr_next(int current, struct pcb* procs, int plen) {
    f (!procs || plen <= 0) return -1;

    int start;
    if (prev < 0) start = 0;
    else start = (prev + 1) % plen;

    for (int i = 0; i < plen; ++i) {
        int idx = (start + i) % plen;
        if (procs[idx].burst_left > 0) return idx;
    }

    return -1;
}
/**
 * TODO: Describe what the function does
 */
int rr_run(struct pcb* procs, int plen, int quantum) {
    if (!procs || plen <= 0 || quantum <= 0) return 0;

    int elapsed = 0;
    int prev = -1;

    while (1) {
        int cur = rr_next(prev, procs, plen);
        if (cur == -1) break; /* nothing runnable */

        int run_for = procs[cur].burst_left;
        if (run_for > quantum) run_for = quantum;

        run_proc(procs, plen, cur, run_for);
        elapsed += run_for;

        prev = cur;
    }

    return elapsed;
}

