#include <math.h>
#include <starpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "starpu_helpers.h"

#define MAX_RAND 2048
#define MIN_RAND -2048

void reduc_sum(void** buffers, void* cl_arg);

unsigned int merge_depth(unsigned int items, unsigned int degree);

int generate_random_int(const int max, const int min);

struct starpu_task* submit_reduction_task(
    int blksize,
    int blkid,
    starpu_data_handle_t* input_handle,
    starpu_data_handle_t* output_handle,
    unsigned int n_deps,
    struct starpu_task* dependencies[]);

double get_time(void);

struct starpu_codelet reduc_cl = {
    .where = STARPU_CPU,
    .cpu_funcs = { reduc_sum },
    .nbuffers = 2,
    .modes = { STARPU_R, STARPU_W }
};

typedef struct {
    unsigned int begin;
    unsigned int end;
} reduc_params_t;
