/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2017 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#ifdef MANGO_INCLUDE_SIMD

    // -----------------------------------------------------------------
    // float64x4
    // -----------------------------------------------------------------

    template <uint32 x, uint32 y, uint32 z, uint32 w>
    static inline float64x4 shuffle(float64x4 v)
    {
        static_assert(x < 4 && y < 4 && z < 4 && w < 4, "Index out of range.");
        const int select0 = ((y & 1) << 1) | (x & 1);
        const int select1 = ((w & 1) << 1) | (z & 1);
        const __m128d& v0 = x & 2 ? v.zw : v.xy;
        const __m128d& v1 = y & 2 ? v.zw : v.xy;
        const __m128d& v2 = z & 2 ? v.zw : v.xy;
        const __m128d& v3 = w & 2 ? v.zw : v.xy;
        float64x4 result;
        result.xy = _mm_shuffle_pd(v0, v1, select0);
        result.zw = _mm_shuffle_pd(v2, v3, select1);
        return result;
    }

    template <>
    inline float64x4 shuffle<0, 1, 2, 3>(float64x4 v)
    {
        // .xyzw
        return v;
    }

    template <>
    inline float64x4 shuffle<0, 0, 0, 0>(float64x4 v)
    {
        // .xxxx
        const __m128d xx = _mm_shuffle_pd(v.xy, v.xy, 0);
        float64x4 result;
        result.xy = xx;
        result.zw = xx;
        return result;
    }

    template <>
    inline float64x4 shuffle<1, 1, 1, 1>(float64x4 v)
    {
        // .yyyy
        const __m128d yy = _mm_shuffle_pd(v.xy, v.xy, 3);
        float64x4 result;
        result.xy = yy;
        result.zw = yy;
        return result;
    }

    template <>
    inline float64x4 shuffle<2, 2, 2, 2>(float64x4 v)
    {
        // .zzzz
        const __m128d zz = _mm_shuffle_pd(v.zw, v.zw, 0);
        float64x4 result;
        result.xy = zz;
        result.zw = zz;
        return result;
    }

    template <>
    inline float64x4 shuffle<3, 3, 3, 3>(float64x4 v)
    {
        // .wwww
        const __m128d ww = _mm_shuffle_pd(v.zw, v.zw, 3);
        float64x4 result;
        result.xy = ww;
        result.zw = ww;
        return result;
    }

    // set component

    template <int Index>
    static inline float64x4 set_component(float64x4 a, double s);

    template <>
    inline float64x4 set_component<0>(float64x4 a, double x)
    {
        a.xy = _mm_move_sd(a.xy, _mm_set1_pd(x));
        return a;
    }

    template <>
    inline float64x4 set_component<1>(float64x4 a, double y)
    {
        a.xy = _mm_move_sd(_mm_set1_pd(y), a.xy);
        return a;
    }

    template <>
    inline float64x4 set_component<2>(float64x4 a, double z)
    {
        a.zw = _mm_move_sd(a.zw, _mm_set1_pd(z));
        return a;
    }

    template <>
    inline float64x4 set_component<3>(float64x4 a, double w)
    {
        a.zw = _mm_move_sd(_mm_set1_pd(w), a.zw);
        return a;
    }

    // get component

    template <int Index>
    static inline double get_component(float64x4 a);

    template <>
    inline double get_component<0>(float64x4 a)
    {
        return _mm_cvtsd_f64(a.xy);
    }

    template <>
    inline double get_component<1>(float64x4 a)
    {
        const __m128d yy = _mm_unpackhi_pd(a.xy, a.xy);
        return _mm_cvtsd_f64(yy);
    }

    template <>
    inline double get_component<2>(float64x4 a)
    {
        return _mm_cvtsd_f64(a.zw);
    }

    template <>
    inline double get_component<3>(float64x4 a)
    {
        const __m128d ww = _mm_unpackhi_pd(a.zw, a.zw);
        return _mm_cvtsd_f64(ww);
    }

    static inline float64x4 float64x4_zero()
    {
        float64x4 result;
        result.xy =
        result.zw = _mm_setzero_pd();
        return result;
    }

    static inline float64x4 float64x4_set1(double s)
    {
        float64x4 result;
        result.xy =
        result.zw = _mm_set1_pd(s);
        return result;
    }

    static inline float64x4 float64x4_set4(double x, double y, double z, double w)
    {
        float64x4 result;
        result.xy = _mm_setr_pd(x, y);
        result.zw = _mm_setr_pd(z, w);
        return result;
    }

    static inline float64x4 float64x4_uload(const double* source)
    {
        float64x4 result;
        result.xy = _mm_loadu_pd(source + 0);
        result.zw = _mm_loadu_pd(source + 2);
        return result;
    }

    static inline void float64x4_ustore(double* dest, float64x4 a)
    {
        _mm_storeu_pd(dest + 0, a.xy);
        _mm_storeu_pd(dest + 2, a.zw);
    }

    static inline float64x4 movelh(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = a.xy;
        result.zw = b.xy;
        return result;
    }

    static inline float64x4 movehl(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = b.zw;
        result.zw = a.zw;
        return result;
    }

    static inline float64x4 unpackhi(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_unpackhi_pd(a.xy, b.xy);
        result.zw = _mm_unpackhi_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 unpacklo(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_unpacklo_pd(a.xy, b.xy);
        result.zw = _mm_unpacklo_pd(a.zw, b.zw);
        return result;
    }

    // bitwise

    static inline float64x4 float64x4_and(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_and_pd(a.xy, b.xy);
        result.zw = _mm_and_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 float64x4_nand(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_andnot_pd(a.xy, b.xy);
        result.zw = _mm_andnot_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 float64x4_or(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_or_pd(a.xy, b.xy);
        result.zw = _mm_or_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 float64x4_xor(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_xor_pd(a.xy, b.xy);
        result.zw = _mm_xor_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 min(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_min_pd(a.xy, b.xy);
        result.zw = _mm_min_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 max(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_max_pd(a.xy, b.xy);
        result.zw = _mm_max_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 hmin(float64x4 a)
    {
        const __m128d xy = _mm_min_pd(a.xy, _mm_shuffle_pd(a.xy, a.xy, 0x01));
        const __m128d zw = _mm_min_pd(a.xy, _mm_shuffle_pd(a.zw, a.zw, 0x01));
        float64x4 result;
        result.xy = _mm_min_pd(xy, _mm_shuffle_pd(zw, zw, 0x02));
        result.zw = _mm_min_pd(zw, _mm_shuffle_pd(xy, xy, 0x02));
        return result;
    }

    static inline float64x4 hmax(float64x4 a)
    {
        const __m128d xy = _mm_max_pd(a.xy, _mm_shuffle_pd(a.xy, a.xy, 0x01));
        const __m128d zw = _mm_max_pd(a.xy, _mm_shuffle_pd(a.zw, a.zw, 0x01));
        float64x4 result;
        result.xy = _mm_max_pd(xy, _mm_shuffle_pd(zw, zw, 0x02));
        result.zw = _mm_max_pd(zw, _mm_shuffle_pd(xy, xy, 0x02));
        return result;
    }

    static inline float64x4 abs(float64x4 a)
    {
        const __m128d mask = _mm_castsi128_pd(_mm_set1_epi64x(0x7fffffffffffffff));
        float64x4 result;
        result.xy = _mm_and_pd(a.xy, mask);
        result.zw = _mm_and_pd(a.zw, mask);
        return result;
    }

    static inline float64x4 neg(float64x4 a)
    {
        const __m128d mask = _mm_castsi128_pd(_mm_set1_epi64x(0x8000000000000000));
        float64x4 result;
        result.xy = _mm_xor_pd(a.xy, mask);
        result.zw = _mm_xor_pd(a.zw, mask);
        return result;
    }

    static inline float64x4 add(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_add_pd(a.xy, b.xy);
        result.zw = _mm_add_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 sub(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_sub_pd(a.xy, b.xy);
        result.zw = _mm_sub_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 mul(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_mul_pd(a.xy, b.xy);
        result.zw = _mm_mul_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 div(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_div_pd(a.xy, b.xy);
        result.zw = _mm_div_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 div(float64x4 a, double b)
    {
        const __m128d bb = _mm_set1_pd(b);
        float64x4 result;
        result.xy = _mm_div_pd(a.xy, bb);
        result.zw = _mm_div_pd(a.zw, bb);
        return result;
    }

#if defined(MANGO_ENABLE_FMA3)

    static inline float64x4 madd(float64x4 a, float64x4 b, float64x4 c)
    {
        float64x4 result;
        result.xy = _mm_fmadd_pd(b.xy, c.xy, a.xy);
        result.zw = _mm_fmadd_pd(b.zw, c.zw, a.zw);
        return result;
    }

    static inline float64x4 msub(float64x4 a, float64x4 b, float64x4 c)
    {
        float64x4 result;
        result.xy = _mm_fnmadd_pd(b.xy, c.xy, a.xy);
        result.zw = _mm_fnmadd_pd(b.zw, c.zw, a.zw);
        return result;
    }

#else

    static inline float64x4 madd(float64x4 a, float64x4 b, float64x4 c)
    {
        float64x4 result;
        result.xy = _mm_add_pd(a.xy, _mm_mul_pd(b.xy, c.xy));
        result.zw = _mm_add_pd(a.zw, _mm_mul_pd(b.zw, c.zw));
        return result;
    }

    static inline float64x4 msub(float64x4 a, float64x4 b, float64x4 c)
    {
        float64x4 result;
        result.xy = _mm_sub_pd(a.xy, _mm_mul_pd(b.xy, c.xy));
        result.zw = _mm_sub_pd(a.zw, _mm_mul_pd(b.zw, c.zw));
        return result;
    }

#endif

    static inline float64x4 fast_reciprocal(float64x4 a)
    {
        const __m128d one = _mm_set1_pd(1.0);
        float64x4 result;
        result.xy = _mm_div_pd(one, a.xy);
        result.zw = _mm_div_pd(one, a.zw);
        return result;
    }

    static inline float64x4 fast_rsqrt(float64x4 a)
    {
        const __m128d one = _mm_set1_pd(1.0);
        float64x4 result;
        result.xy = _mm_div_pd(one, _mm_sqrt_pd(a.xy));
        result.zw = _mm_div_pd(one, _mm_sqrt_pd(a.zw));
        return result;
    }

    static inline float64x4 fast_sqrt(float64x4 a)
    {
        float64x4 result;
        result.xy = _mm_sqrt_pd(a.xy);
        result.zw = _mm_sqrt_pd(a.zw);
        return result;
    }

    static inline float64x4 reciprocal(float64x4 a)
    {
        const __m128d one = _mm_set1_pd(1.0);
        float64x4 result;
        result.xy = _mm_div_pd(one, a.xy);
        result.zw = _mm_div_pd(one, a.zw);
        return result;
    }

    static inline float64x4 rsqrt(float64x4 a)
    {
        const __m128d one = _mm_set1_pd(1.0);
        float64x4 result;
        result.xy = _mm_div_pd(one, _mm_sqrt_pd(a.xy));
        result.zw = _mm_div_pd(one, _mm_sqrt_pd(a.zw));
        return result;
    }

    static inline float64x4 sqrt(float64x4 a)
    {
        float64x4 result;
        result.xy = _mm_sqrt_pd(a.xy);
        result.zw = _mm_sqrt_pd(a.zw);
        return result;
    }

    static inline float64x4 dot4(float64x4 a, float64x4 b)
    {
        const __m128d xy = _mm_mul_pd(a.xy, b.xy);
        const __m128d zw = _mm_mul_pd(a.zw, b.zw);
        __m128d s;
        s = _mm_add_pd(xy, zw);
        s = _mm_add_pd(s, _mm_shuffle_pd(xy, xy, 0x01));
        s = _mm_add_pd(s, _mm_shuffle_pd(zw, zw, 0x01));

        float64x4 result;
        result.xy = s;
        result.zw = s;
        return result;
    }

    // compare

    static inline float64x4 compare_neq(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_cmpneq_pd(a.xy, b.xy);
        result.zw = _mm_cmpneq_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 compare_eq(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_cmpeq_pd(a.xy, b.xy);
        result.zw = _mm_cmpeq_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 compare_lt(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_cmplt_pd(a.xy, b.xy);
        result.zw = _mm_cmplt_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 compare_le(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_cmple_pd(a.xy, b.xy);
        result.zw = _mm_cmple_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 compare_gt(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_cmpgt_pd(a.xy, b.xy);
        result.zw = _mm_cmpgt_pd(a.zw, b.zw);
        return result;
    }

    static inline float64x4 compare_ge(float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_cmpge_pd(a.xy, b.xy);
        result.zw = _mm_cmpge_pd(a.zw, b.zw);
        return result;
    }

#if defined(MANGO_ENABLE_SSE4_1)

    static inline float64x4 select(float64x4 mask, float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_blendv_pd(b.xy, a.xy, mask.xy);
        result.zw = _mm_blendv_pd(b.zw, a.zw, mask.zw);
        return result;
    }

#else

    static inline float64x4 select(float64x4 mask, float64x4 a, float64x4 b)
    {
        float64x4 result;
        result.xy = _mm_or_pd(_mm_and_pd(mask.xy, a.xy), _mm_andnot_pd(mask.xy, b.xy));
        result.zw = _mm_or_pd(_mm_and_pd(mask.zw, a.zw), _mm_andnot_pd(mask.zw, b.zw));
        return result;
    }

#endif

    // rounding

#if defined(MANGO_ENABLE_SSE4_1)

    static inline float64x4 round(float64x4 s)
    {
        float64x4 result;
        result.xy = _mm_round_pd(s.xy, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
        result.zw = _mm_round_pd(s.zw, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
        return result;
    }

    static inline float64x4 trunc(float64x4 s)
    {
        float64x4 result;
        result.xy = _mm_round_pd(s.xy, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
        result.zw = _mm_round_pd(s.zw, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
        return result;
    }

    static inline float64x4 floor(float64x4 s)
    {
        float64x4 result;
        result.xy = _mm_round_pd(s.xy, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
        result.zw = _mm_round_pd(s.zw, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
        return result;
    }

    static inline float64x4 ceil(float64x4 s)
    {
        float64x4 result;
        result.xy = _mm_round_pd(s.xy, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
        result.zw = _mm_round_pd(s.zw, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
        return result;
    }

#else

    static inline float64x4 round(float64x4 s)
    {
        float64x4 result;
        result.xy = _mm_cvtepi32_pd(_mm_cvtpd_epi32(s.xy));
        result.zw = _mm_cvtepi32_pd(_mm_cvtpd_epi32(s.zw));
        return result;
    }

    static inline float64x4 trunc(float64x4 s)
    {
        float64x4 result;
        result.xy = _mm_cvtepi32_pd(_mm_cvttpd_epi32(s.xy));
        result.zw = _mm_cvtepi32_pd(_mm_cvttpd_epi32(s.zw));
        return result;
    }

    static inline float64x4 floor(float64x4 s)
    {
        const __m128d one = _mm_set1_pd(1.0);
        const __m128d temp_xy = _mm_cvtepi32_pd(_mm_cvtpd_epi32(s.xy));
        const __m128d temp_zw = _mm_cvtepi32_pd(_mm_cvtpd_epi32(s.zw));
        const __m128d mask_xy = _mm_cmplt_pd(s.xy, temp_xy);
        const __m128d mask_zw = _mm_cmplt_pd(s.zw, temp_zw);

        float64x4 result;
        result.xy = _mm_sub_pd(temp_xy, _mm_and_pd(mask_xy, one));
        result.zw = _mm_sub_pd(temp_zw, _mm_and_pd(mask_zw, one));
        return result;
    }

    static inline float64x4 ceil(float64x4 s)
    {
        const __m128d one = _mm_set1_pd(1.0);
        const __m128d temp_xy = _mm_cvtepi32_pd(_mm_cvtpd_epi32(s.xy));
        const __m128d temp_zw = _mm_cvtepi32_pd(_mm_cvtpd_epi32(s.zw));
        const __m128d mask_xy = _mm_cmpgt_pd(s.xy, temp_xy);
        const __m128d mask_zw = _mm_cmpgt_pd(s.zw, temp_zw);

        float64x4 result;
        result.xy = _mm_add_pd(temp_xy, _mm_and_pd(mask_xy, one));
        result.zw = _mm_add_pd(temp_zw, _mm_and_pd(mask_zw, one));
        return result;
    }

#endif

    static inline float64x4 fract(float64x4 s)
    {
        const __m128d one = _mm_set1_pd(1.0);
        const __m128d temp_xy = _mm_cvtepi32_pd(_mm_cvtpd_epi32(s.xy));
        const __m128d temp_zw = _mm_cvtepi32_pd(_mm_cvtpd_epi32(s.zw));
        const __m128d mask_xy = _mm_cmplt_pd(s.xy, temp_xy);
        const __m128d mask_zw = _mm_cmplt_pd(s.zw, temp_zw);
        const __m128d xy = _mm_sub_pd(temp_xy, _mm_and_pd(mask_xy, one));
        const __m128d zw = _mm_sub_pd(temp_zw, _mm_and_pd(mask_zw, one));

        float64x4 result;
        result.xy = _mm_sub_pd(s.xy, xy);
        result.zw = _mm_sub_pd(s.zw, zw);
        return result;
    }

#endif // MANGO_INCLUDE_SIMD