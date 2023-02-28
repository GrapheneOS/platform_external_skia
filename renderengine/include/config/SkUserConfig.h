// DO NOT MODIFY! This file is autogenerated by gn_to_bp.py.
// If need to change a define, modify SkUserConfigManual.h
#pragma once
#include "SkUserConfigManual.h"

#ifndef SKSL_ENABLE_TRACING
#define SKSL_ENABLE_TRACING
#endif

#ifndef SK_ANDROID_FRAMEWORK_USE_PERFETTO
#define SK_ANDROID_FRAMEWORK_USE_PERFETTO
#endif

#ifndef SK_ENABLE_PRECOMPILE
#define SK_ENABLE_PRECOMPILE
#endif

#ifndef SK_ENABLE_SKSL
#define SK_ENABLE_SKSL
#endif

#ifndef SK_ENCODE_PNG
#define SK_ENCODE_PNG
#endif

#ifndef SK_GAMMA_APPLY_TO_A8
#define SK_GAMMA_APPLY_TO_A8
#endif

#ifndef SK_GANESH
#define SK_GANESH
#endif

#ifndef SK_GL
#define SK_GL
#endif

#ifndef SK_IN_RENDERENGINE
#define SK_IN_RENDERENGINE
#endif

#ifndef SK_USE_VMA
#define SK_USE_VMA
#endif

#ifndef SK_VULKAN
#define SK_VULKAN
#endif

#ifndef SK_BUILD_FOR_ANDROID
    #error "SK_BUILD_FOR_ANDROID must be defined!"
#endif
#if defined(SK_BUILD_FOR_IOS) || defined(SK_BUILD_FOR_MAC) || \
    defined(SK_BUILD_FOR_UNIX) || defined(SK_BUILD_FOR_WIN)
    #error "Only SK_BUILD_FOR_ANDROID should be defined!"
#endif
