/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2017 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#ifdef MANGO_INCLUDE_SIMD

    // -----------------------------------------------------------------
    // float32x2
    // -----------------------------------------------------------------

    // shuffle

    template <uint32 x, uint32 y>
    static inline float32x2 float32x2_shuffle(float32x2 v);

    template <>
    inline float32x2 float32x2_shuffle<0, 0>(float32x2 v)
    {
        // .xx
        return vdup_lane_f32(v, 0);
    }

    template <>
    inline float32x2 float32x2_shuffle<0, 1>(float32x2 v)
    {
        // .xy
        return v;
    }

    template <>
    inline float32x2 float32x2_shuffle<1, 0>(float32x2 v)
    {
        // .yx
        return vrev64_f32(v);
    }

    template <>
    inline float32x2 float32x2_shuffle<1, 1>(float32x2 v)
    {
        // .yy
        return vdup_lane_f32(v, 1);
    }

    // indexed access

    template <int Index>
    static inline float32x2 float32x2_set_component(float32x2 a, float s)
    {
        static_assert(Index >= 0 && Index < 2, "Index out of range.");
        return vset_lane_f32(s, a, Index);
    }

    template <int Index>
    static inline float float32x2_get_component(float32x2 a)
    {
        static_assert(Index >= 0 && Index < 2, "Index out of range.");
        return vget_lane_f32(a, Index);
    }

    static inline float32x2 float32x2_zero()
    {
        return vdup_n_f32(0.0f);
    }

    static inline float32x2 float32x2_set1(float s)
    {
        return vdup_n_f32(s);
    }

    static inline float32x2 float32x2_set2(float x, float y)
    {
        float32x2_t temp = { x, y };
        return temp;
    }

    static inline float32x2 float32x2_uload(const float* source)
    {
        float32x2_t temp = { source[0], source[1] };
        return temp;
    }

    static inline void float32x2_ustore(float* dest, float32x2 a)
    {
        dest[0] = vget_lane_f32(a, 0);
        dest[1] = vget_lane_f32(a, 1);
    }

    static inline float32x2 float32x2_unpackhi(float32x2 a, float32x2 b)
    {
        float32x2x2_t temp = vzip_f32(a, b);
        return temp.val[1];
    }

    static inline float32x2 float32x2_unpacklo(float32x2 a, float32x2 b)
    {
        float32x2x2_t temp = vzip_f32(a, b);
        return temp.val[0];
    }

    // logical

    static inline float32x2 float32x2_and(float32x2 a, float32x2 b)
    {
        return vreinterpret_f32_s32(vand_s32(vreinterpret_s32_f32(a), vreinterpret_s32_f32(b)));
    }

    static inline float32x2 float32x2_nand(float32x2 a, float32x2 b)
    {
        return vreinterpret_f32_s32(vbic_s32(vreinterpret_s32_f32(a), vreinterpret_s32_f32(b)));
    }

    static inline float32x2 float32x2_or(float32x2 a, float32x2 b)
    {
        return vreinterpret_f32_s32(vorr_s32(vreinterpret_s32_f32(a), vreinterpret_s32_f32(b)));
    }

    static inline float32x2 float32x2_xor(float32x2 a, float32x2 b)
    {
        return vreinterpret_f32_s32(veor_s32(vreinterpret_s32_f32(a), vreinterpret_s32_f32(b)));
    }

    static inline float32x2 float32x2_min(float32x2 a, float32x2 b)
    {
        return vmin_f32(a, b);
    }

    static inline float32x2 float32x2_max(float32x2 a, float32x2 b)
    {
        return vmax_f32(a, b);
    }

    static inline float32x2 float32x2_abs(float32x2 a)
    {
        return vabs_f32(a);
    }

    static inline float32x2 float32x2_neg(float32x2 a)
    {
        return vneg_f32(a);
    }

    static inline float32x2 float32x2_add(float32x2 a, float32x2 b)
    {
        return vadd_f32(a, b);
    }

    static inline float32x2 float32x2_sub(float32x2 a, float32x2 b)
    {
        return vsub_f32(a, b);
    }

    static inline float32x2 float32x2_mul(float32x2 a, float32x2 b)
    {
        return vmul_f32(a, b);
    }

#ifdef __aarch64__

    static inline float32x2 float32x2_div(float32x2 a, float32x2 b)
    {
        return vdiv_f32(a, b);
    }

    static inline float32x2 float32x2_div(float32x2 a, float b)
    {
        float32x2 s = vdup_n_f32(b);
        return vdiv_f32(a, s);
    }

#else

    static inline float32x2 float32x2_div(float32x2 a, float32x2 b)
    {
        float32x2 n = vrecpe_f32(b);
        n = vmul_f32(vrecps_f32(n, b), n);
        n = vmul_f32(vrecps_f32(n, b), n);
        return vmul_f32(a, n);
    }

    static inline float32x2 float32x2_div(float32x2 a, float b)
    {
        float32x2 s = vdup_n_f32(b);
        float32x2 n = vrecpe_f32(s);
        n = vmul_f32(vrecps_f32(n, s), n);
        n = vmul_f32(vrecps_f32(n, s), n);
        return vmul_f32(a, n);
    }

#endif

    static inline float32x2 float32x2_madd(float32x2 a, float32x2 b, float32x2 c)
    {
        return vmla_f32(a, b, c);
    }

    static inline float32x2 float32x2_msub(float32x2 a, float32x2 b, float32x2 c)
    {
        return vmls_f32(a, b, c);
    }

    static inline float32x2 float32x2_fast_reciprocal(float32x2 a)
    {
        float32x2_t n = vrecpe_f32(a);
        n = vmul_f32(vrecps_f32(n, a), n);
        return n;
    }

    static inline float32x2 float32x2_fast_rsqrt(float32x2 a)
    {
        float32x2_t n = vrsqrte_f32(a);
        n = vmul_f32(n, vrsqrts_f32(vmul_f32(n, a), n));
        return n;
    }

    static inline float32x2 float32x2_fast_sqrt(float32x2 a)
    {
        float32x2_t n = vrsqrte_f32(a);
        n = vmul_f32(n, vrsqrts_f32(vmul_f32(n, a), n));
        return vmul_f32(a, n);
    }

    static inline float32x2 float32x2_reciprocal(float32x2 a)
    {
        float32x2_t n = vrecpe_f32(a);
        n = vmul_f32(vrecps_f32(n, a), n);
        n = vmul_f32(vrecps_f32(n, a), n);
        return n;
    }

    static inline float32x2 float32x2_rsqrt(float32x2 a)
    {
        float32x2_t n = vrsqrte_f32(a);
        n = vmul_f32(n, vrsqrts_f32(vmul_f32(n, a), n));
        n = vmul_f32(n, vrsqrts_f32(vmul_f32(n, a), n));
        n = vmul_f32(n, vrsqrts_f32(vmul_f32(n, a), n));
        return n;
    }

    static inline float32x2 float32x2_sqrt(float32x2 a)
    {
        float32x2_t n = vrsqrte_f32(a);
        n = vmul_f32(n, vrsqrts_f32(vmul_f32(n, a), n));
        n = vmul_f32(n, vrsqrts_f32(vmul_f32(n, a), n));
        n = vmul_f32(n, vrsqrts_f32(vmul_f32(n, a), n));
        return vmul_f32(a, n);
    }

    static inline float32x2 float32x2_dot2(float32x2 a, float32x2 b)
    {
        const float32x2_t xy = vmul_f32(a, b);
        return vpadd_f32(xy, xy);
    }

    // compare

    static inline float32x2 float32x2_compare_neq(float32x2 a, float32x2 b)
    {
        return vreinterpret_f32_u32(vmvn_u32(vceq_f32(a, b)));
    }

    static inline float32x2 float32x2_compare_eq(float32x2 a, float32x2 b)
    {
        return vreinterpret_f32_u32(vceq_f32(a, b));
    }

    static inline float32x2 float32x2_compare_lt(float32x2 a, float32x2 b)
    {
        return vreinterpret_f32_u32(vclt_f32(a, b));
    }

    static inline float32x2 float32x2_compare_le(float32x2 a, float32x2 b)
    {
        return vreinterpret_f32_u32(vcle_f32(a, b));
    }

    static inline float32x2 float32x2_compare_gt(float32x2 a, float32x2 b)
    {
        return vreinterpret_f32_u32(vcgt_f32(a, b));
    }

    static inline float32x2 float32x2_compare_ge(float32x2 a, float32x2 b)
    {
        return vreinterpret_f32_u32(vcge_f32(a, b));
    }

    static inline float32x2 float32x2_select(float32x2 mask, float32x2 a, float32x2 b)
    {
        return vbsl_f32(vreinterpret_u32_f32(mask), a, b);
    }

    // rounding

#if __ARM_ARCH >= 8 && !defined(MANGO_COMPILER_CLANG)

    // Disabled with clang until supported in NDK

    static inline float32x2 float32x2_round(float32x2 s)
    {
        return vrnda_f32(s);
    }

    static inline float32x2 float32x2_trunc(float32x2 s)
    {
        return vrnd_f32(s);
    }

    static inline float32x2 float32x2_floor(float32x2 s)
    {
        return vrndm_f32(s);
    }

    static inline float32x2 float32x2_ceil(float32x2 s)
    {
        return vrndp_f32(s);
    }

#else

    static inline float32x2 float32x2_round(float32x2 s)
    {
        const float32x2_t magic = vdup_n_f32(12582912.0f); // 1.5 * (1 << 23)
        return vsub_f32(vadd_f32(s, magic), magic);
    }

    static inline float32x2 float32x2_trunc(float32x2 s)
    {
        const int32x2_t truncated = vcvt_s32_f32(s);
        return vcvt_f32_s32(truncated);
    }

    static inline float32x2 float32x2_floor(float32x2 s)
    {
        const float32x2_t temp = float32x2_round(s);
        const uint32x2_t mask = vclt_f32(s, temp);
        const uint32x2_t one = vdup_n_u32(0x3f800000);
        return vsub_f32(temp, vreinterpret_f32_u32(vand_u32(mask, one)));
    }

    static inline float32x2 float32x2_ceil(float32x2 s)
    {
        const float32x2_t temp = float32x2_round(s);
        const uint32x2_t mask = vcgt_f32(s, temp);
        const uint32x2_t one = vdup_n_u32(0x3f800000);
        return vadd_f32(temp, vreinterpret_f32_u32(vand_u32(mask, one)));
    }

#endif

    static inline float32x2 float32x2_fract(float32x2 s)
    {
        return vsub_f32(s, float32x2_floor(s));
    }

#endif // MANGO_INCLUDE_SIMD
