#pragma once

#include "cbi_export.h"

#include <CppBuildInfo/TranslationUnit.h>

#include <vector>

/// Compute the number of maximum parallel compilations by analyzing the start & end times.
CBI_EXPORT size_t maximumNumberOfParallelCompilations(const std::vector<TranslationUnit>& units);

/// Returns the total amount of time spent in the compilations
/// \pre  The translations unit must be sorted.
/// \note At this moment, this does not take into account the linking times.
CBI_EXPORT size_t getTotalCompilationTime(const std::vector<TranslationUnit>& units);
