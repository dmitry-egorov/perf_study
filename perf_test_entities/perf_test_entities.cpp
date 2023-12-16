#include <cstdint>
#include <cstdlib>
#include <cstdio>

#include <intrin.h>
typedef uint32_t u32;
typedef uint64_t u64;
typedef double f64;

#include "utility/syntax.h"
#include "utility/malloc_ex.h"

struct vector3 {
    float x, y, z;
};

#pragma optimize("", off)
void __declspec(noinline) apply_velocity_noopt(vector3* positions, vector3* velocities, int count) {
    for (auto i = 0; i < count; i++) {
        positions[i].x += velocities[i].x;
        positions[i].y += velocities[i].y;
        positions[i].z += velocities[i].z;
    }
}

void __declspec(noinline) apply_velocity_dual_noopt(vector3* positions, vector3* velocities, int count) {
    for (auto i = 0; i < count; i += 2) {
        positions[i].x += velocities[i].x;
        positions[i].y += velocities[i].y;
        positions[i].z += velocities[i].z;

        positions[i + 1].x += velocities[i + 1].x;
        positions[i + 1].y += velocities[i + 1].y;
        positions[i + 1].z += velocities[i + 1].z;
    }
}

void __declspec(noinline) apply_velocity_quad_noopt(vector3* positions, vector3* velocities, int count) {
    for (auto i = 0; i < count; i += 4) {
        positions[i].x += velocities[i].x;
        positions[i].y += velocities[i].y;
        positions[i].z += velocities[i].z;

        positions[i + 1].x += velocities[i + 1].x;
        positions[i + 1].y += velocities[i + 1].y;
        positions[i + 1].z += velocities[i + 1].z;

        positions[i + 2].x += velocities[i + 2].x;
        positions[i + 2].y += velocities[i + 2].y;
        positions[i + 2].z += velocities[i + 2].z;

        positions[i + 3].x += velocities[i + 3].x;
        positions[i + 3].y += velocities[i + 3].y;
        positions[i + 3].z += velocities[i + 3].z;
    }
}

void __declspec(noinline) apply_velocity_octo_noopt(vector3* positions, vector3* velocities, int count) {
    for (auto i = 0; i < count; i += 8) {
        positions[i].x += velocities[i].x;
        positions[i].y += velocities[i].y;
        positions[i].z += velocities[i].z;

        positions[i + 1].x += velocities[i + 1].x;
        positions[i + 1].y += velocities[i + 1].y;
        positions[i + 1].z += velocities[i + 1].z;

        positions[i + 2].x += velocities[i + 2].x;
        positions[i + 2].y += velocities[i + 2].y;
        positions[i + 2].z += velocities[i + 2].z;

        positions[i + 3].x += velocities[i + 3].x;
        positions[i + 3].y += velocities[i + 3].y;
        positions[i + 3].z += velocities[i + 3].z;

        positions[i + 4].x += velocities[i + 4].x;
        positions[i + 4].y += velocities[i + 4].y;
        positions[i + 4].z += velocities[i + 4].z;

        positions[i + 5].x += velocities[i + 5].x;
        positions[i + 5].y += velocities[i + 5].y;
        positions[i + 5].z += velocities[i + 5].z;

        positions[i + 6].x += velocities[i + 6].x;
        positions[i + 6].y += velocities[i + 6].y;
        positions[i + 6].z += velocities[i + 6].z;

        positions[i + 7].x += velocities[i + 7].x;
        positions[i + 7].y += velocities[i + 7].y;
        positions[i + 7].z += velocities[i + 7].z;
    }
}

void __declspec(noinline) apply_velocity_ref_noopt(vector3* positions, vector3* velocities, int count) {
    for (auto i = 0; i < count; i++) {
        auto& p = positions[i];
        auto& v = velocities[i];
        p.x += v.x;
        p.y += v.y;
        p.z += v.z;
    }
}

void __declspec(noinline) apply_velocity_soa_noopt(float* pxs, float* pys, float* pzs, float* vxs, float* vys, float* vzs, int count) {
    for (auto i = 0; i < count; i++) {
        pxs[i] += vxs[i];
        pys[i] += vys[i];
        pzs[i] += vzs[i];
    }
}

#pragma optimize("", on)

void __declspec(noinline) apply_velocity_opt(vector3* positions, vector3* velocities, int count) {
    for (auto i = 0; i < count; i++) {
        positions[i].x += velocities[i].x;
        positions[i].y += velocities[i].y;
        positions[i].z += velocities[i].z;
    }
}

void __declspec(noinline) apply_velocity_dual_opt(vector3* positions, vector3* velocities, int count) {
    for (auto i = 0; i < count; i += 2) {
        positions[i].x += velocities[i].x;
        positions[i].y += velocities[i].y;
        positions[i].z += velocities[i].z;

        positions[i + 1].x += velocities[i + 1].x;
        positions[i + 1].y += velocities[i + 1].y;
        positions[i + 1].z += velocities[i + 1].z;
    }
}

void __declspec(noinline) apply_velocity_quad_opt(vector3* positions, vector3* velocities, int count) {
    for (auto i = 0; i < count; i += 4) {
        positions[i].x += velocities[i].x;
        positions[i].y += velocities[i].y;
        positions[i].z += velocities[i].z;

        positions[i + 1].x += velocities[i + 1].x;
        positions[i + 1].y += velocities[i + 1].y;
        positions[i + 1].z += velocities[i + 1].z;

        positions[i + 2].x += velocities[i + 2].x;
        positions[i + 2].y += velocities[i + 2].y;
        positions[i + 2].z += velocities[i + 2].z;

        positions[i + 3].x += velocities[i + 3].x;
        positions[i + 3].y += velocities[i + 3].y;
        positions[i + 3].z += velocities[i + 3].z;
    }
}

void __declspec(noinline) apply_velocity_octo_opt(vector3* positions, vector3* velocities, int count) {
    for (auto i = 0; i < count; i += 8) {
        positions[i].x += velocities[i].x;
        positions[i].y += velocities[i].y;
        positions[i].z += velocities[i].z;

        positions[i + 1].x += velocities[i + 1].x;
        positions[i + 1].y += velocities[i + 1].y;
        positions[i + 1].z += velocities[i + 1].z;

        positions[i + 2].x += velocities[i + 2].x;
        positions[i + 2].y += velocities[i + 2].y;
        positions[i + 2].z += velocities[i + 2].z;

        positions[i + 3].x += velocities[i + 3].x;
        positions[i + 3].y += velocities[i + 3].y;
        positions[i + 3].z += velocities[i + 3].z;

        positions[i + 4].x += velocities[i + 4].x;
        positions[i + 4].y += velocities[i + 4].y;
        positions[i + 4].z += velocities[i + 4].z;

        positions[i + 5].x += velocities[i + 5].x;
        positions[i + 5].y += velocities[i + 5].y;
        positions[i + 5].z += velocities[i + 5].z;

        positions[i + 6].x += velocities[i + 6].x;
        positions[i + 6].y += velocities[i + 6].y;
        positions[i + 6].z += velocities[i + 6].z;

        positions[i + 7].x += velocities[i + 7].x;
        positions[i + 7].y += velocities[i + 7].y;
        positions[i + 7].z += velocities[i + 7].z;
    }
}

void __declspec(noinline) apply_velocity_soa_opt(float* pxs, float* pys, float* pzs, float* vxs, float* vys, float* vzs, int count) {
    for (auto i = 0; i < count; i++) {
        pxs[i] += vxs[i];
        pys[i] += vys[i];
        pzs[i] += vzs[i];
    }
}

void __declspec(noinline) apply_velocity_dual_soa_opt(float* pxs, float* pys, float* pzs, float* vxs, float* vys, float* vzs, int count) {
    for (auto i = 0; i < count; i += 2) {
        pxs[i] += vxs[i];
        pys[i] += vys[i];
        pzs[i] += vzs[i];

        pxs[i + 1] += vxs[i + 1];
        pys[i + 1] += vys[i + 1];
        pzs[i + 1] += vzs[i + 1];
    }
}

void __declspec(noinline) apply_velocity_quad_soa_opt(float* pxs, float* pys, float* pzs, float* vxs, float* vys, float* vzs, int count) {
    for (auto i = 0; i < count; i += 4) {
        pxs[i] += vxs[i];
        pys[i] += vys[i];
        pzs[i] += vzs[i];

        pxs[i + 1] += vxs[i + 1];
        pys[i + 1] += vys[i + 1];
        pzs[i + 1] += vzs[i + 1];

        pxs[i + 2] += vxs[i + 2];
        pys[i + 2] += vys[i + 2];
        pzs[i + 2] += vzs[i + 2];

        pxs[i + 3] += vxs[i + 3];
        pys[i + 3] += vys[i + 3];
        pzs[i + 3] += vzs[i + 3];
    }
}

void __declspec(noinline) apply_velocity_soa_avx(float* pxs, float* pys, float* pzs, float* vxs, float* vys, float* vzs, int count) {
    for (auto i = 0; i < count; i += 8) {
        _mm256_store_ps(&pxs[i], _mm256_add_ps(_mm256_load_ps(&pxs[i]), _mm256_load_ps(&vxs[i])));
        _mm256_store_ps(&pys[i], _mm256_add_ps(_mm256_load_ps(&pys[i]), _mm256_load_ps(&vys[i])));
        _mm256_store_ps(&pzs[i], _mm256_add_ps(_mm256_load_ps(&pzs[i]), _mm256_load_ps(&vzs[i])));
    }
}

void __declspec(noinline) apply_velocity_soa_dual_avx(float* pxs, float* pys, float* pzs, float* vxs, float* vys, float* vzs, int count) {
    for (auto i = 0; i < count; i += 16) {
        _mm256_store_ps(&pxs[i], _mm256_add_ps(_mm256_load_ps(&pxs[i]), _mm256_load_ps(&vxs[i])));
        _mm256_store_ps(&pys[i], _mm256_add_ps(_mm256_load_ps(&pys[i]), _mm256_load_ps(&vys[i])));
        _mm256_store_ps(&pzs[i], _mm256_add_ps(_mm256_load_ps(&pzs[i]), _mm256_load_ps(&vzs[i])));

        _mm256_store_ps(&pxs[i + 8], _mm256_add_ps(_mm256_load_ps(&pxs[i + 8]), _mm256_load_ps(&vxs[i + 8])));
        _mm256_store_ps(&pys[i + 8], _mm256_add_ps(_mm256_load_ps(&pys[i + 8]), _mm256_load_ps(&vys[i + 8])));
        _mm256_store_ps(&pzs[i + 8], _mm256_add_ps(_mm256_load_ps(&pzs[i + 8]), _mm256_load_ps(&vzs[i + 8])));
    }
}

void __declspec(noinline) apply_velocity_soa_quad_avx(float* pxs, float* pys, float* pzs, float* vxs, float* vys, float* vzs, int count) {
    for (auto i = 0; i < count; i += 32) {
        _mm256_store_ps(&pxs[i], _mm256_add_ps(_mm256_load_ps(&pxs[i]), _mm256_load_ps(&vxs[i])));
        _mm256_store_ps(&pys[i], _mm256_add_ps(_mm256_load_ps(&pys[i]), _mm256_load_ps(&vys[i])));
        _mm256_store_ps(&pzs[i], _mm256_add_ps(_mm256_load_ps(&pzs[i]), _mm256_load_ps(&vzs[i])));

        _mm256_store_ps(&pxs[i +  8], _mm256_add_ps(_mm256_load_ps(&pxs[i +  8]), _mm256_load_ps(&vxs[i +  8])));
        _mm256_store_ps(&pys[i +  8], _mm256_add_ps(_mm256_load_ps(&pys[i +  8]), _mm256_load_ps(&vys[i +  8])));
        _mm256_store_ps(&pzs[i +  8], _mm256_add_ps(_mm256_load_ps(&pzs[i +  8]), _mm256_load_ps(&vzs[i +  8])));

        _mm256_store_ps(&pxs[i + 16], _mm256_add_ps(_mm256_load_ps(&pxs[i + 16]), _mm256_load_ps(&vxs[i + 16])));
        _mm256_store_ps(&pys[i + 16], _mm256_add_ps(_mm256_load_ps(&pys[i + 16]), _mm256_load_ps(&vys[i + 16])));
        _mm256_store_ps(&pzs[i + 16], _mm256_add_ps(_mm256_load_ps(&pzs[i + 16]), _mm256_load_ps(&vzs[i + 16])));

        _mm256_store_ps(&pxs[i + 24], _mm256_add_ps(_mm256_load_ps(&pxs[i + 24]), _mm256_load_ps(&vxs[i + 24])));
        _mm256_store_ps(&pys[i + 24], _mm256_add_ps(_mm256_load_ps(&pys[i + 24]), _mm256_load_ps(&vys[i + 24])));
        _mm256_store_ps(&pzs[i + 24], _mm256_add_ps(_mm256_load_ps(&pzs[i + 24]), _mm256_load_ps(&vzs[i + 24])));
    }
}

void __declspec(noinline) apply_velocity_soa_avx_2(float* pxs, float* pys, float* pzs, float* vxs, float* vys, float* vzs, int count) {
    for (auto i = 0; i < count; i += 8) {
        auto npx = _mm256_add_ps(_mm256_load_ps(&pxs[i]), _mm256_load_ps(&vxs[i]));
        auto npy = _mm256_add_ps(_mm256_load_ps(&pys[i]), _mm256_load_ps(&vys[i]));
        auto npz = _mm256_add_ps(_mm256_load_ps(&pzs[i]), _mm256_load_ps(&vzs[i]));

        _mm256_store_ps(&pxs[i], npx);
        _mm256_store_ps(&pys[i], npy);
        _mm256_store_ps(&pzs[i], npz);
    }
}

float random_float_01() {
    return (float)((double)rand() / (double)INT_MAX);
}

int main(int argc, char**)
{
    int alignment = 32;
    int item_size = 6 * sizeof(float);
    int iteration_count = 64 * 1024;
    int      data_size  = 3 * 8 * 1024 * argc;
    int     items_count = data_size / item_size;

    auto positions  = aligned_malloc<vector3>(items_count, alignment); defer { _aligned_free(positions); };
    auto velocities = aligned_malloc<vector3>(items_count, alignment); defer { _aligned_free(velocities); };

    auto pxs = aligned_malloc<float>(items_count, alignment); defer { _aligned_free(pxs); };
    auto pys = aligned_malloc<float>(items_count, alignment); defer { _aligned_free(pys); };
    auto pzs = aligned_malloc<float>(items_count, alignment); defer { _aligned_free(pzs); };

    auto vxs = aligned_malloc<float>(items_count, alignment); defer { _aligned_free(vxs); };
    auto vys = aligned_malloc<float>(items_count, alignment); defer { _aligned_free(vys); };
    auto vzs = aligned_malloc<float>(items_count, alignment); defer { _aligned_free(vzs); };

    for (int i = 0; i < items_count; i++) {
        positions[i].x = random_float_01();
        positions[i].y = random_float_01();
        positions[i].z = random_float_01();


        velocities[i].x = random_float_01();
        velocities[i].y = random_float_01();
        velocities[i].z = random_float_01();

        pxs[i] = random_float_01();
        pys[i] = random_float_01();
        pzs[i] = random_float_01();

        vxs[i] = random_float_01();
        vys[i] = random_float_01();
        vzs[i] = random_float_01();
    }

    apply_velocity_noopt(positions, velocities, items_count);
    u64 min_elapsed_cycles;
    u64 end_clock;
    u64 elapsed_cycles;
    f64 op_per_clock;


#define test_func(func_name)                                         \
    min_elapsed_cycles = -1;                                         \
    for (int it_i = 0; it_i < iteration_count; it_i++) {             \
        u64 start_clock = __rdtsc();                                 \
                                                                     \
        func_call(func_name);               \
                                                                     \
        end_clock = __rdtsc();                                       \
        elapsed_cycles = end_clock - start_clock;                    \
        if (elapsed_cycles < min_elapsed_cycles)                     \
            min_elapsed_cycles = elapsed_cycles;                     \
                                                                     \
        if (elapsed_cycles <= 1)                                     \
            printf("Hey!\n");                                        \
    }                                                                \
                                                                     \
    op_per_clock = 3.0 * (f64)items_count / (f64)min_elapsed_cycles; \
    printf("%s: op/clock: %f\n", #func_name, op_per_clock)           \

#define func_call(func_name) func_name(positions, velocities, items_count)
    test_func(apply_velocity_noopt);
    test_func(apply_velocity_dual_noopt);
    test_func(apply_velocity_quad_noopt);
    test_func(apply_velocity_octo_noopt);
    test_func(apply_velocity_ref_noopt);
    test_func(apply_velocity_opt);
    test_func(apply_velocity_dual_opt);
    test_func(apply_velocity_quad_opt);
    test_func(apply_velocity_octo_opt);
#undef func_call

#define func_call(func_name) func_name(pxs, pys, pzs, vxs, vys, vzs, items_count)
    test_func(apply_velocity_soa_noopt);
    test_func(apply_velocity_soa_opt);
    test_func(apply_velocity_dual_soa_opt);
    test_func(apply_velocity_quad_soa_opt);
    test_func(apply_velocity_soa_avx);
    test_func(apply_velocity_soa_dual_avx);
    test_func(apply_velocity_soa_quad_avx);
    test_func(apply_velocity_soa_avx_2);
#undef func_call

    return 0;
}