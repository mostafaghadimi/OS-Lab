#include <immintrin.h>
#include <intrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union Mat44 {
    float m[4][4];
    __m128 row[4];
};

// reference implementation
void matmult_ref(Mat44 &out, const Mat44 &A, const Mat44 &B)
{
    Mat44 t; // write to temp
    for (int i=0; i < 4; i++)
        for (int j=0; j < 4; j++)
            t.m[i][j] = A.m[i][0]*B.m[0][j] + A.m[i][1]*B.m[1][j] + A.m[i][2]*B.m[2][j] + A.m[i][3]*B.m[3][j];

    out = t;
}

// linear combination:
// a[0] * B.row[0] + a[1] * B.row[1] + a[2] * B.row[2] + a[3] * B.row[3]
static inline __m128 lincomb_SSE(const __m128 &a, const Mat44 &B)
{
    __m128 result;
    result = _mm_mul_ps(_mm_shuffle_ps(a, a, 0x00), B.row[0]);
    result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(a, a, 0x55), B.row[1]));
    result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(a, a, 0xaa), B.row[2]));
    result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(a, a, 0xff), B.row[3]));
    return result;
}

// implementing SSE
void matmult_SSE(Mat44 &out, const Mat44 &A, const Mat44 &B)
{
    // out_ij = sum_k a_ik b_kj
    // => out_0j = a_00 * b_0j + a_01 * b_1j + a_02 * b_2j + a_03 * b_3j
    __m128 out0x = lincomb_SSE(A.row[0], B);
    __m128 out1x = lincomb_SSE(A.row[1], B);
    __m128 out2x = lincomb_SSE(A.row[2], B);
    __m128 out3x = lincomb_SSE(A.row[3], B);

    out.row[0] = out0x;
    out.row[1] = out1x;
    out.row[2] = out2x;
    out.row[3] = out3x;
}

// Test
static float randf()
{
    return (rand() - 16384.0f) / 1024.0f;
}

static void randmat(Mat44 &M)
{
    for (int i=0; i < 4; i++)
        for (int j=0; j < 4; j++)
            M.m[i][j] = randf();
}

int the_mask = 0; // global so the compiler can't be sure what its value is for opt.

static void run_ref(Mat44 *out, const Mat44 *A, const Mat44 *B, int count)
{
    for (int i=0; i < count; i++)
    {
        int j = i & the_mask;
        matmult_ref(out[j], A[j], B[j]);
    }
}

static void run_SSE(Mat44 *out, const Mat44 *A, const Mat44 *B, int count)
{
    for (int i=0; i < count; i++)
    {
        int j = i & the_mask;
        matmult_SSE(out[j], A[j], B[j]);
    }
}

int main(int argc, char **argv)
{
    static const struct {
        const char *name;
        void (*matmult)(Mat44 &out, const Mat44 &A, const Mat44 &B);
    } variants[] = {
        { "ref",      matmult_ref },
        { "SSE",      matmult_SSE },
    };
    static const int nvars = (int) (sizeof(variants) / sizeof(*variants));
    
    srand(1234);

    // correctness tests
    for (int i=0; i < 1000000; i++)
    {
        Mat44 A, B, out, ref_out;
        randmat(A);
        randmat(B);
        matmult_ref(ref_out, A, B);

        for (int j=0; j < nvars; j++)
        {
            variants[j].matmult(out, A, B);
            if (memcmp(&out, &ref_out, sizeof(out)) != 0)
            {
                fprintf(stderr, "%s fails test\n", variants[j].name);
                exit(1);
            }
        }
    }

    printf("all ok.\n");

    // performance tests

    static const struct {
        const char *name;
        void (*run)(Mat44 *out, const Mat44 *A, const Mat44 *B, int count);
    } perf_variants[] = {
        { "ref",      run_ref },
        { "SSE",      run_SSE },
    };
    static const int nperfvars = (int) (sizeof(perf_variants) / sizeof(*perf_variants));
    
    /* 
    test done on my laptop with following results:
                 ref: 59.00 cycles
                 SSE: 20.52 cycles
    */
    
    Mat44 Aperf, Bperf, out;
    randmat(Aperf);
    randmat(Bperf);

    for (int i=0; i < nvars; i++)
    {
        static const int nruns = 4096;
        static const int muls_per_run = 4096;
        unsigned long long best_time = ~0ull;

        for (int run=0; run < nruns; run++)
        {
            unsigned long long time = __rdtsc();
            perf_variants[i].run(&out, &Aperf, &Bperf, muls_per_run);
            time = __rdtsc() - time;
            if (time < best_time)
                best_time = time;
        }

        double cycles_per_run = (double) best_time / (double) muls_per_run;
        printf("%12s: %.2f cycles\n", perf_variants[i].name, cycles_per_run);
    }

    return 0;
}
