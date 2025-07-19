#ifndef PROCESSOR_H
#define PROCESSOR_H

typedef struct {
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
} cpu_stats_t;

int read_cpu_stats(cpu_stats_t *stats);
int read_all_cpu_stats(cpu_stats_t *stats_array, int *core_count);
float calculate_cpu_usage(const cpu_stats_t *prev, const cpu_stats_t *curr);

#endif // UI_H
