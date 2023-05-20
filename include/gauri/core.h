/*!
 * @file core.h
 * @author leeh8
 * @brief
 * @version 0.1
 * @date 2023-05-15
 *
 * @copyright Copyright (c) 2023
 */
#pragma once

#include <cstdint>

#ifdef GR_ENABLE_ASSERTS
#define GR_ASSERT(x, ...)                                                                                              \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            GR_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                            \
            __debugbreak();                                                                                            \
        }                                                                                                              \
    }
#define GR_CORE_ASSERT(x, ...)                                                                                         \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            GR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);                                                       \
            __debugbreak();                                                                                            \
        }                                                                                                              \
    }
#else
#define GR_ASSERT(x, ...)
#define GR_CORE_ASSERT(x, ...)
#endif

template <uint32_t N> constexpr uint32_t bit = (1 << N);

#define GR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
