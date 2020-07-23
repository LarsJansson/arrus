#ifndef ARRUS_API_MATLAB_WRAPPERS_COMMON_H
#define ARRUS_API_MATLAB_WRAPPERS_COMMON_H

#include <cstdint>
#include <string>

#include <core/common/compiler.h>

COMPILER_PUSH_DIAGNOSTIC_STATE
#pragma warning(disable: 4100 4189 4458 4702)
#include <mex.hpp>
#include <mexAdapter.hpp>
COMPILER_POP_DIAGNOSTIC_STATE

namespace arrus::matlab_wrappers {
    using MexObjectHandle = uint32_t;
    using MexObjectMethodId = std::string;
    using MexObjectClassId = std::string;

    using MexMethodArgs = ::matlab::mex::ArgumentList;
}

#endif //ARRUS_API_MATLAB_WRAPPERS_COMMON_H
