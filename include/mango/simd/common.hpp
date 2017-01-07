/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2017 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#pragma once

#include "simd.hpp"

namespace mango {
namespace simd {

    // ------------------------------------------------------------------
    // Trigonometric functions
    // ------------------------------------------------------------------

    float32x4 float32x4_sin(float32x4__ a);
    float32x4 float32x4_cos(float32x4__ a);
    float32x4 float32x4_tan(float32x4__ a);
    float32x4 float32x4_asin(float32x4__ a);
    float32x4 float32x4_acos(float32x4__ a);
    float32x4 float32x4_atan(float32x4__ a);
    float32x4 float32x4_exp(float32x4__ a);
    float32x4 float32x4_log(float32x4__ a);
    float32x4 float32x4_exp2(float32x4__ a);
    float32x4 float32x4_log2(float32x4__ a);
    float32x4 float32x4_pow(float32x4__ a, float32x4__ b);
    float32x4 float32x4_atan2(float32x4__ a, float32x4__ b);

    float64x4 float64x4_sin(float64x4__ a);
    float64x4 float64x4_cos(float64x4__ a);
    float64x4 float64x4_tan(float64x4__ a);
    float64x4 float64x4_asin(float64x4__ a);
    float64x4 float64x4_acos(float64x4__ a);
    float64x4 float64x4_atan(float64x4__ a);
#if 0 // TODO
    float64x4 float64x4_exp(float64x4__ a);
    float64x4 float64x4_log(float64x4__ a);
    float64x4 float64x4_exp2(float64x4__ a);
    float64x4 float64x4_log2(float64x4__ a);
    float64x4 float64x4_pow(float64x4__ a, float64x4__ b);
#endif
    float64x4 float64x4_atan2(float64x4__ a, float64x4__ b);

    // ------------------------------------------------------------------
    // Common scalar variations
    // ------------------------------------------------------------------

    // int32x4

    static inline int32x4 int32x4_add(int a, int32x4__ b)
    {
        return int32x4_add(int32x4_set1(a), b);
    }

    static inline int32x4 int32x4_add(int32x4__ a, int b)
    {
        return int32x4_add(a, int32x4_set1(b));
    }

    static inline int32x4 int32x4_sub(int a, int32x4__ b)
    {
        return int32x4_sub(int32x4_set1(a), b);
    }

    static inline int32x4 int32x4_sub(int32x4__ a, int b)
    {
        return int32x4_sub(a, int32x4_set1(b));
    }

    static inline int32x4 int32x4_and(int a, int32x4__ b)
    {
        return int32x4_and(int32x4_set1(a), b);
    }

    static inline int32x4 int32x4_and(int32x4__ a, int b)
    {
        return int32x4_and(a, int32x4_set1(b));
    }

    static inline int32x4 int32x4_nand(int a, int32x4__ b)
    {
        return int32x4_nand(int32x4_set1(a), b);
    }

    static inline int32x4 int32x4_nand(int32x4__ a, int b)
    {
        return int32x4_nand(a, int32x4_set1(b));
    }

    static inline int32x4 int32x4_or(int a, int32x4__ b)
    {
        return int32x4_or(int32x4_set1(a), b);
    }

    static inline int32x4 int32x4_or(int32x4__ a, int b)
    {
        return int32x4_or(a, int32x4_set1(b));
    }

    static inline int32x4 int32x4_xor(int a, int32x4__ b)
    {
        return int32x4_xor(int32x4_set1(a), b);
    }

    static inline int32x4 int32x4_xor(int32x4__ a, int b)
    {
        return int32x4_xor(a, int32x4_set1(b));
    }

    static inline int32x4 int32x4_compare_eq(int32x4__ a, int b)
    {
        return int32x4_compare_eq(a, int32x4_set1(b));
    }

    static inline int32x4 int32x4_compare_gt(int32x4__ a, int b)
    {
        return int32x4_compare_gt(a, int32x4_set1(b));
    }

    static inline int32x4 int32x4_select(int32x4__ mask, int a, int32x4__ b)
    {
        return int32x4_select(mask, int32x4_set1(a), b);
    }

    static inline int32x4 int32x4_select(int32x4__ mask, int32x4__ a, int b)
    {
        return int32x4_select(mask, a, int32x4_set1(b));
    }

    static inline int32x4 int32x4_select(int32x4__ mask, int a, int b)
    {
        return int32x4_select(mask, int32x4_set1(a), int32x4_set1(b));
    }

    // float32x4

    static inline float32x4 float32x4_add(float a, float32x4__ b)
    {
        return float32x4_add(float32x4_set1(a), b);
    }

    static inline float32x4 float32x4_add(float32x4__ a, float b)
    {
        return float32x4_add(a, float32x4_set1(b));
    }

    static inline float32x4 float32x4_sub(float a, float32x4__ b)
    {
        return float32x4_sub(float32x4_set1(a), b);
    }

    static inline float32x4 float32x4_sub(float32x4__ a, float b)
    {
        return float32x4_sub(a, float32x4_set1(b));
    }

    static inline float32x4 float32x4_mul(float32x4__ a, float b)
    {
        return float32x4_mul(a, float32x4_set1(b));
    }

    static inline float32x4 float32x4_mul(float a, float32x4__ b)
    {
        return float32x4_mul(float32x4_set1(a), b);
    }

    static inline float32x4 float32x4_div(float a, float32x4__ b)
    {
        return float32x4_div(float32x4_set1(a), b);
    }

    static inline float32x4 float32x4_madd(float a, float32x4__ b, float32x4__ c)
    {
        return float32x4_madd(float32x4_set1(a), b, c);
    }

    static inline float32x4 float32x4_madd(float32x4__ a, float b, float32x4__ c)
    {
        return float32x4_madd(a, float32x4_set1(b), c);
    }

    static inline float32x4 float32x4_madd(float32x4__ a, float32x4__ b, float c)
    {
        return float32x4_madd(a, b, float32x4_set1(c));
    }

    static inline float32x4 float32x4_min(float a, float32x4__ b)
    {
        return float32x4_min(float32x4_set1(a), b);
    }

    static inline float32x4 float32x4_min(float32x4__ a, float b)
    {
        return float32x4_min(a, float32x4_set1(b));
    }

    static inline float32x4 float32x4_max(float a, float32x4__ b)
    {
        return float32x4_max(float32x4_set1(a), b);
    }

    static inline float32x4 float32x4_max(float32x4__ a, float b)
    {
        return float32x4_max(a, float32x4_set1(b));
    }

    static inline float32x4 float32x4_clamp(float32x4__ v, float vmin, float vmax)
    {
        return float32x4_clamp(v, float32x4_set1(vmin), float32x4_set1(vmax));
    }

    static inline float32x4 float32x4_compare_neq(float32x4__ a, float b)
    {
        return float32x4_compare_neq(a, float32x4_set1(b));
    }

    static inline float32x4 float32x4_compare_eq(float32x4__ a, float b)
    {
        return float32x4_compare_eq(a, float32x4_set1(b));
    }

    static inline float32x4 float32x4_compare_lt(float32x4__ a, float b)
    {
        return float32x4_compare_lt(a, float32x4_set1(b));
    }

    static inline float32x4 float32x4_compare_le(float32x4__ a, float b)
    {
        return float32x4_compare_le(a, float32x4_set1(b));
    }

    static inline float32x4 float32x4_compare_gt(float32x4__ a, float b)
    {
        return float32x4_compare_gt(a, float32x4_set1(b));
    }

    static inline float32x4 float32x4_compare_ge(float32x4__ a, float b)
    {
        return float32x4_compare_ge(a, float32x4_set1(b));
    }

    static inline float32x4 float32x4_select(float32x4__ mask, float a, float32x4__ b)
    {
        return float32x4_select(mask, float32x4_set1(a), b);
    }

    static inline float32x4 float32x4_select(float32x4__ mask, float32x4__ a, float b)
    {
        return float32x4_select(mask, a, float32x4_set1(b));
    }

    static inline float32x4 float32x4_select(float32x4__ mask, float a, float b)
    {
        return float32x4_select(mask, float32x4_set1(a), float32x4_set1(b));
    }

    static inline float32x4 float32x4_mod(float32x4__ a, float32x4__ b)
    {
        float32x4 temp = float32x4_floor(float32x4_div(a, b));
        return float32x4_sub(a, float32x4_mul(b, temp));
    }

    static inline float32x4 float32x4_sign(float32x4__ a)
    {
        const float32x4 zero_mask = float32x4_compare_neq(a, float32x4_zero());
        const float32x4 sign_bits = float32x4_and(a, float32x4_set1(-0.0f));
        const float32x4 signed_one = float32x4_or(sign_bits, float32x4_set1(1.0f));
        return float32x4_and(signed_one, zero_mask);
    }

    static inline float32x4 float32x4_radians(float32x4__ a)
    {
        static const float32x4 s = float32x4_set1(0.01745329251f);
        return float32x4_mul(a, s);
    }

    static inline float32x4 float32x4_degrees(float32x4__ a)
    {
        static const float32x4 s = float32x4_set1(57.2957795131f);
        return float32x4_mul(a, s);
    }

    static inline float32x4 float32x4_square(float32x4__ a)
    {
        return float32x4_dot4(a, a);
    }

    static inline float32x4 float32x4_length(float32x4__ a)
    {
        return float32x4_sqrt(float32x4_dot4(a, a));
    }

    static inline float32x4 float32x4_normalize(float32x4__ a)
    {
        return float32x4_mul(a, float32x4_rsqrt(float32x4_dot4(a, a)));
    }

    // float64x4

    static inline float64x4 float64x4_add(double a, float64x4__ b)
    {
        return float64x4_add(float64x4_set1(a), b);
    }

    static inline float64x4 float64x4_add(float64x4__ a, double b)
    {
        return float64x4_add(a, float64x4_set1(b));
    }

    static inline float64x4 float64x4_sub(double a, float64x4__ b)
    {
        return float64x4_sub(float64x4_set1(a), b);
    }

    static inline float64x4 float64x4_sub(float64x4__ a, double b)
    {
        return float64x4_sub(a, float64x4_set1(b));
    }

    static inline float64x4 float64x4_mul(float64x4__ a, double b)
    {
        return float64x4_mul(a, float64x4_set1(b));
    }

    static inline float64x4 float64x4_mul(double a, float64x4__ b)
    {
        return float64x4_mul(float64x4_set1(a), b);
    }

    static inline float64x4 float64x4_div(double a, float64x4__ b)
    {
        return float64x4_div(float64x4_set1(a), b);
    }

    static inline float64x4 float64x4_madd(double a, float64x4__ b, float64x4__ c)
    {
        return float64x4_madd(float64x4_set1(a), b, c);
    }

    static inline float64x4 float64x4_madd(float64x4__ a, double b, float64x4__ c)
    {
        return float64x4_madd(a, float64x4_set1(b), c);
    }

    static inline float64x4 float64x4_madd(float64x4__ a, float64x4__ b, double c)
    {
        return float64x4_madd(a, b, float64x4_set1(c));
    }

    static inline float64x4 float64x4_min(double a, float64x4__ b)
    {
        return float64x4_min(float64x4_set1(a), b);
    }

    static inline float64x4 float64x4_min(float64x4__ a, double b)
    {
        return float64x4_min(a, float64x4_set1(b));
    }

    static inline float64x4 float64x4_max(double a, float64x4__ b)
    {
        return float64x4_max(float64x4_set1(a), b);
    }

    static inline float64x4 float64x4_max(float64x4__ a, double b)
    {
        return float64x4_max(a, float64x4_set1(b));
    }

    static inline float64x4 float64x4_clamp(float64x4__ v, double vmin, double vmax)
    {
        return float64x4_clamp(v, float64x4_set1(vmin), float64x4_set1(vmax));
    }

    static inline float64x4 float64x4_compare_neq(float64x4__ a, double b)
    {
        return float64x4_compare_neq(a, float64x4_set1(b));
    }

    static inline float64x4 float64x4_compare_eq(float64x4__ a, double b)
    {
        return float64x4_compare_eq(a, float64x4_set1(b));
    }

    static inline float64x4 float64x4_compare_lt(float64x4__ a, double b)
    {
        return float64x4_compare_lt(a, float64x4_set1(b));
    }

    static inline float64x4 float64x4_compare_le(float64x4__ a, double b)
    {
        return float64x4_compare_le(a, float64x4_set1(b));
    }

    static inline float64x4 float64x4_compare_gt(float64x4__ a, double b)
    {
        return float64x4_compare_gt(a, float64x4_set1(b));
    }

    static inline float64x4 float64x4_compare_ge(float64x4__ a, double b)
    {
        return float64x4_compare_ge(a, float64x4_set1(b));
    }

    static inline float64x4 float64x4_select(float64x4__ mask, double a, float64x4__ b)
    {
        return float64x4_select(mask, float64x4_set1(a), b);
    }

    static inline float64x4 float64x4_select(float64x4__ mask, float64x4__ a, double b)
    {
        return float64x4_select(mask, a, float64x4_set1(b));
    }

    static inline float64x4 float64x4_select(float64x4__ mask, double a, double b)
    {
        return float64x4_select(mask, float64x4_set1(a), float64x4_set1(b));
    }

    static inline float64x4 float64x4_mod(float64x4__ a, float64x4__ b)
    {
        float64x4 temp = float64x4_floor(float64x4_div(a, b));
        return float64x4_sub(a, float64x4_mul(b, temp));
    }

    static inline float64x4 float64x4_sign(float64x4__ a)
    {
        const float64x4 zero_mask = float64x4_compare_neq(a, float64x4_zero());
        const float64x4 sign_bits = float64x4_and(a, float64x4_set1(-0.0));
        const float64x4 signed_one = float64x4_or(sign_bits, float64x4_set1(1.0));
        return float64x4_and(signed_one, zero_mask);
    }

    static inline float64x4 float64x4_radians(float64x4__ a)
    {
        static const float64x4 s = float64x4_set1(0.01745329251);
        return float64x4_mul(a, s);
    }

    static inline float64x4 float64x4_degrees(float64x4__ a)
    {
        static const float64x4 s = float64x4_set1(57.2957795131);
        return float64x4_mul(a, s);
    }

    static inline float64x4 float64x4_square(float64x4__ a)
    {
        return float64x4_dot4(a, a);
    }

    static inline float64x4 float64x4_length(float64x4__ a)
    {
        return float64x4_sqrt(float64x4_dot4(a, a));
    }

    static inline float64x4 float64x4_normalize(float64x4__ a)
    {
        return float64x4_mul(a, float64x4_rsqrt(float64x4_dot4(a, a)));
    }

} // namespace simd
} // namespace mango