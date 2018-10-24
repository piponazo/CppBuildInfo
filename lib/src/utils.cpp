#include <CppBuildInfo/utils.h>

size_t maximumNumberOfParallelCompilations(const std::vector<TranslationUnit> &units)
{
    std::vector<TranslationUnit> concurrentProcs;
    std::size_t maxProcs = 0;

    for (const auto& p : units) {
        if (!concurrentProcs.empty() && concurrentProcs.back().end < p.start) {
            concurrentProcs.pop_back();
        }

        concurrentProcs.push_back(p);

        std::sort(concurrentProcs.begin(), concurrentProcs.end(), std::greater<TranslationUnit>());
        maxProcs = std::max(maxProcs, concurrentProcs.size());
    }

    return maxProcs;
}

size_t getTotalCompilationTime(const std::vector<TranslationUnit> &units)
{
    if (units.empty()) {
        return 0;
    }
    return static_cast<std::size_t>(units.back().end - units.front().start);
}
