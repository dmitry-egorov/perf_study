#include <cstdint>
#include <cstdlib>
#include <cstdio>

#include <intrin.h>

typedef uint32_t u32;
typedef uint64_t u64;
typedef double f64;

#include "utility/syntax.h"
#include "utility/malloc_ex.h"
#include "utility/cpu_freq.h"

#pragma optimize("", off)
int sum_naive(const int* data, int count) {
    auto sum = 0;
    for (auto i = 0; i < count; i++)
        sum += data[i];

    return sum;
}

int sum2(const int* data, int count) {
    auto sum0 = 0;
    auto sum1 = 0;

    for (auto i = 0; i < count; i += 2) {
        sum0 += data[i + 0];
        sum1 += data[i + 1];
    }

    return sum0 + sum1;
}

int sum4(const int* data, int count) {
    auto sum0 = 0;
    auto sum1 = 0;
    auto sum2 = 0;
    auto sum3 = 0;

    for (auto i = 0; i < count; i += 4) {
        sum0 += data[i + 0];
        sum1 += data[i + 1];
        sum2 += data[i + 2];
        sum3 += data[i + 3];
    }

    return sum0 + sum1 + sum2 + sum3;
}

int sum8(const int* data, int count) {
    auto sum0 = 0;
    auto sum1 = 0;
    auto sum2 = 0;
    auto sum3 = 0;
    auto sum4 = 0;
    auto sum5 = 0;
    auto sum6 = 0;
    auto sum7 = 0;

    for (auto i = 0; i < count; i += 8) {
        sum0 += data[i + 0];
        sum1 += data[i + 1];
        sum2 += data[i + 2];
        sum3 += data[i + 3];
        sum4 += data[i + 4];
        sum5 += data[i + 5];
        sum6 += data[i + 6];
        sum7 += data[i + 7];
    }

    return sum0 + sum1 + sum2 + sum3 + sum4 + sum5 + sum6 + sum7;
}

int sum16(const int* data, int count) {
    auto sum0  = 0;
    auto sum1  = 0;
    auto sum2  = 0;
    auto sum3  = 0;
    auto sum4  = 0;
    auto sum5  = 0;
    auto sum6  = 0;
    auto sum7  = 0;
    auto sum8  = 0;
    auto sum9  = 0;
    auto sum10 = 0;
    auto sum11 = 0;
    auto sum12 = 0;
    auto sum13 = 0;
    auto sum14 = 0;
    auto sum15 = 0;

    for (auto i = 0; i < count; i += 16) {
        sum0  += data[i +  0];
        sum1  += data[i +  1];
        sum2  += data[i +  2];
        sum3  += data[i +  3];
        sum4  += data[i +  4];
        sum5  += data[i +  5];
        sum6  += data[i +  6];
        sum7  += data[i +  7];
        sum8  += data[i +  8];
        sum9  += data[i +  9];
        sum10 += data[i + 10];
        sum11 += data[i + 11];
        sum12 += data[i + 12];
        sum13 += data[i + 13];
        sum14 += data[i + 14];
        sum15 += data[i + 15];
    }

    return sum0
         + sum1
         + sum2
         + sum3
         + sum4
         + sum5
         + sum6
         + sum7
         + sum8
         + sum9
         + sum10
         + sum11
         + sum12
         + sum13
         + sum14
         + sum15
    ;
}

int sum16_ptr(const int* data, int count) {
    auto sum0  = 0;
    auto sum1  = 0;
    auto sum2  = 0;
    auto sum3  = 0;
    auto sum4  = 0;
    auto sum5  = 0;
    auto sum6  = 0;
    auto sum7  = 0;
    auto sum8  = 0;
    auto sum9  = 0;
    auto sum10 = 0;
    auto sum11 = 0;
    auto sum12 = 0;
    auto sum13 = 0;
    auto sum14 = 0;
    auto sum15 = 0;

    count /= 16;

    while (count--) {
        sum0  += data[ 0];
        sum1  += data[ 1];
        sum2  += data[ 2];
        sum3  += data[ 3];
        sum4  += data[ 4];
        sum5  += data[ 5];
        sum6  += data[ 6];
        sum7  += data[ 7];
        sum8  += data[ 8];
        sum9  += data[ 9];
        sum10 += data[10];
        sum11 += data[11];
        sum12 += data[12];
        sum13 += data[13];
        sum14 += data[14];
        sum15 += data[15];
        data += 16;
    }

    return sum0
         + sum1
         + sum2
         + sum3
         + sum4
         + sum5
         + sum6
         + sum7
         + sum8
         + sum9
         + sum10
         + sum11
         + sum12
         + sum13
         + sum14
         + sum15
    ;
}

int sum_avx_ptr(int* data, int count) {
    auto sum = _mm256_setzero_si256();

    count /= 8;
    while (count--) {
        sum = _mm256_add_epi32(sum, _mm256_loadu_si256((__m256i*)&data[0]));
        data += 8;
    }

    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_add_epi32 (sum, _mm256_permute2x128_si256(sum, sum, 1 | (1 << 4)));

    return _mm256_cvtsi256_si32(sum);
}

int sum_avx_dual_ptr(int* data, int count) {
    auto sum0 = _mm256_setzero_si256();
    auto sum1 = _mm256_setzero_si256();

    count /= 16;
    while (count--) {
        sum0 = _mm256_add_epi32(sum0, _mm256_loadu_si256((__m256i*)&data[0]));
        sum1 = _mm256_add_epi32(sum1, _mm256_loadu_si256((__m256i*)&data[8]));

        data += 16;
    }

    auto sum = _mm256_add_epi32(sum0, sum1);
    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_add_epi32 (sum, _mm256_permute2x128_si256(sum, sum, 1 | (1 << 4)));

    return _mm256_cvtsi256_si32(sum);
}

int sum_avx_quad_ptr(int* data, int count) {
    auto sum0 = _mm256_setzero_si256();
    auto sum1 = _mm256_setzero_si256();
    auto sum2 = _mm256_setzero_si256();
    auto sum3 = _mm256_setzero_si256();

    count /= 32;
    while (count--) {
        sum0 = _mm256_add_epi32(sum0, _mm256_loadu_si256((__m256i*)&data[ 0]));
        sum1 = _mm256_add_epi32(sum1, _mm256_loadu_si256((__m256i*)&data[ 8]));
        sum2 = _mm256_add_epi32(sum2, _mm256_loadu_si256((__m256i*)&data[16]));
        sum3 = _mm256_add_epi32(sum3, _mm256_loadu_si256((__m256i*)&data[24]));

        data += 32;
    }

    auto sum01 = _mm256_add_epi32( sum0, sum1 );
    auto sum23 = _mm256_add_epi32( sum2, sum3 );
    auto sum   = _mm256_add_epi32(sum01, sum23);

    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_add_epi32 (sum, _mm256_permute2x128_si256(sum, sum, 1 | (1 << 4)));

    return _mm256_cvtsi256_si32(sum);
}

int sum_avx_octo_ptr(int* data, int count) {
    auto sum0 = _mm256_setzero_si256();
    auto sum1 = _mm256_setzero_si256();
    auto sum2 = _mm256_setzero_si256();
    auto sum3 = _mm256_setzero_si256();
    auto sum4 = _mm256_setzero_si256();
    auto sum5 = _mm256_setzero_si256();
    auto sum6 = _mm256_setzero_si256();
    auto sum7 = _mm256_setzero_si256();

    count /= 64;
    while (count--) {
        sum0 = _mm256_add_epi32(sum0, _mm256_loadu_si256((__m256i*)&data[0]));
        sum1 = _mm256_add_epi32(sum1, _mm256_loadu_si256((__m256i*)&data[8]));
        sum2 = _mm256_add_epi32(sum2, _mm256_loadu_si256((__m256i*)&data[16]));
        sum3 = _mm256_add_epi32(sum3, _mm256_loadu_si256((__m256i*)&data[24]));
        sum4 = _mm256_add_epi32(sum4, _mm256_loadu_si256((__m256i*)&data[32]));
        sum5 = _mm256_add_epi32(sum5, _mm256_loadu_si256((__m256i*)&data[40]));
        sum6 = _mm256_add_epi32(sum6, _mm256_loadu_si256((__m256i*)&data[48]));
        sum7 = _mm256_add_epi32(sum7, _mm256_loadu_si256((__m256i*)&data[56]));

        data += 64;
    }

    auto sum01   = _mm256_add_epi32(   sum0, sum1   );
    auto sum23   = _mm256_add_epi32(   sum2, sum3   );
    auto sum45   = _mm256_add_epi32(   sum4, sum5   );
    auto sum67   = _mm256_add_epi32(   sum6, sum7   );
    auto sum0123 = _mm256_add_epi32(  sum01, sum23  );
    auto sum4567 = _mm256_add_epi32(  sum45, sum67  );
    auto sum     = _mm256_add_epi32(sum0123, sum4567);

    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_add_epi32 (sum, _mm256_permute2x128_si256(sum, sum, 1 | (1 << 4)));

    return _mm256_cvtsi256_si32(sum);
}

#pragma optimize("", on)
int sum_opt(int* data, int count) {
    auto sum = 0;
    for (auto i = 0; i < count; i++)
        sum += data[i];

    return sum;
}

int sum_ptr_opt(int* data, int count) {
    auto sum = 0;
    while (count--)
        sum += *data++;

    return sum;
}

int sum_avx_ptr_opt(int* data, int count) {
    auto sum = _mm256_setzero_si256();

    count /= 8;
    while (count--) {
        sum = _mm256_add_epi32(sum, _mm256_loadu_si256((__m256i*)&data[0]));
        data += 8;
    }

    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_add_epi32 (sum, _mm256_permute2x128_si256(sum, sum, 1 | (1 << 4)));

    return _mm256_cvtsi256_si32(sum);
}

int sum_avx_dual_ptr_opt(int* data, int count) {
    auto sum0 = _mm256_setzero_si256();
    auto sum1 = _mm256_setzero_si256();

    count /= 16;
    while (count--) {
        sum0 = _mm256_add_epi32(sum0, _mm256_loadu_si256((__m256i*)&data[0]));
        sum1 = _mm256_add_epi32(sum1, _mm256_loadu_si256((__m256i*)&data[8]));

        data += 16;
    }

    auto sum = _mm256_add_epi32(sum0, sum1);
    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_add_epi32 (sum, _mm256_permute2x128_si256(sum, sum, 1 | (1 << 4)));

    return _mm256_cvtsi256_si32(sum);
}

int sum_avx_quad_ptr_opt(int* data, int count) {
    auto sum0 = _mm256_setzero_si256();
    auto sum1 = _mm256_setzero_si256();
    auto sum2 = _mm256_setzero_si256();
    auto sum3 = _mm256_setzero_si256();

    count /= 32;
    while (count--) {
        sum0 = _mm256_add_epi32(sum0, _mm256_loadu_si256((__m256i*)&data[0]));
        sum1 = _mm256_add_epi32(sum1, _mm256_loadu_si256((__m256i*)&data[8]));
        sum2 = _mm256_add_epi32(sum2, _mm256_loadu_si256((__m256i*)&data[16]));
        sum3 = _mm256_add_epi32(sum3, _mm256_loadu_si256((__m256i*)&data[24]));

        data += 32;
    }

    auto sum01 = _mm256_add_epi32(sum0, sum1);
    auto sum23 = _mm256_add_epi32(sum2, sum3);
    auto sum   = _mm256_add_epi32(sum01, sum23);

    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_add_epi32 (sum, _mm256_permute2x128_si256(sum, sum, 1 | (1 << 4)));

    return _mm256_cvtsi256_si32(sum);
}

int sum_avx_octo_ptr_opt(int* data, int count) {
    auto sum0 = _mm256_setzero_si256();
    auto sum1 = _mm256_setzero_si256();
    auto sum2 = _mm256_setzero_si256();
    auto sum3 = _mm256_setzero_si256();
    auto sum4 = _mm256_setzero_si256();
    auto sum5 = _mm256_setzero_si256();
    auto sum6 = _mm256_setzero_si256();
    auto sum7 = _mm256_setzero_si256();

    count /= 64;
    while (count--) {
        sum0 = _mm256_add_epi32(sum0, _mm256_loadu_si256((__m256i*)&data[ 0]));
        sum1 = _mm256_add_epi32(sum1, _mm256_loadu_si256((__m256i*)&data[ 8]));
        sum2 = _mm256_add_epi32(sum2, _mm256_loadu_si256((__m256i*)&data[16]));
        sum3 = _mm256_add_epi32(sum3, _mm256_loadu_si256((__m256i*)&data[24]));
        sum4 = _mm256_add_epi32(sum4, _mm256_loadu_si256((__m256i*)&data[32]));
        sum5 = _mm256_add_epi32(sum5, _mm256_loadu_si256((__m256i*)&data[40]));
        sum6 = _mm256_add_epi32(sum6, _mm256_loadu_si256((__m256i*)&data[48]));
        sum7 = _mm256_add_epi32(sum7, _mm256_loadu_si256((__m256i*)&data[56]));

        data += 64;
    }

    auto sum01   = _mm256_add_epi32(sum0   , sum1   );
    auto sum23   = _mm256_add_epi32(sum2   , sum3   );
    auto sum45   = _mm256_add_epi32(sum4   , sum5   );
    auto sum67   = _mm256_add_epi32(sum6   , sum7   );
    auto sum0123 = _mm256_add_epi32(sum01  , sum23  );
    auto sum4567 = _mm256_add_epi32(sum45  , sum67  );
    auto sum     = _mm256_add_epi32(sum0123, sum4567);

    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_hadd_epi32(sum, sum);
    sum = _mm256_add_epi32 (sum, _mm256_permute2x128_si256(sum, sum, 1 | (1 << 4)));

    return _mm256_cvtsi256_si32(sum);
}

int main(int argc, char**) {
    printf("Guessing CPU frequency...\n");
    u64 freq = guess_cpu_frequency(300);
    printf("Guessed frequency: %llu\n", freq);

    int iteration_count = 1024 / 16;
    int      data_size  = 128 * 1024 * 1024 * argc;
    int     items_count = data_size / 4;

    int* data = aligned_malloc<int>(items_count, 32); defer { _aligned_free(data); };
    for (int i = 0; i < items_count; i++)
        data[i] = rand();

    int ref_sum = sum_naive(data, items_count);

    int last_sum = 0;

    auto run_test_ = [&](auto func, const char* func_name) {
        int full_sum = 0;
        u64 min_elapsed_cycles = -1;
        for (int it_i = 0; it_i < iteration_count; it_i++) {
            u64 start_clock = __rdtsc();

            int sum = func();
            u64 end_clock = __rdtsc();
            u64 elapsed_cycles = end_clock - start_clock;
            if (elapsed_cycles < min_elapsed_cycles)
                min_elapsed_cycles = elapsed_cycles;

            last_sum  = sum;
            full_sum += sum;
        }

        f64 op_per_clock = (f64)items_count / (f64)min_elapsed_cycles;
        f64 bytes_per_clock = ((f64)freq / 1000000000.0) * (f64)data_size / (f64)min_elapsed_cycles;

        printf("%s, ref sum: %d, sum: %d, full sum: %d, op/clock: %f, GB/sec: %f\n", func_name, ref_sum, last_sum, full_sum, op_per_clock, bytes_per_clock);
    };

#define run_test(func_name) run_test_([&] { return func_name(data, items_count); }, #func_name)
    run_test(sum_naive);
    run_test(sum2);
    run_test(sum4);
    run_test(sum8);
    run_test(sum16);
    run_test(sum16_ptr);
    run_test(sum_avx_ptr);
    run_test(sum_avx_dual_ptr);
    run_test(sum_avx_quad_ptr);
    run_test(sum_avx_octo_ptr);
    run_test(sum_opt);
    run_test(sum_ptr_opt);
    run_test(sum_avx_ptr_opt);
    run_test(sum_avx_dual_ptr_opt);
    run_test(sum_avx_quad_ptr_opt);
    run_test(sum_avx_octo_ptr_opt);
#undef run_test

    return 0;
}