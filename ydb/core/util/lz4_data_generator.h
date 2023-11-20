#include <util/generic/string.h>
#include <util/random/fast.h>

#include <contrib/libs/lz4/lz4.h>

namespace NKikimr {

template <class ResultContainer = TString>
inline ResultContainer GenDataForLZ4(const ui64 size, const ui64 seed = 0) {
    ResultContainer data = ResultContainer::Uninitialized(size);
    const ui32 long_step = Max<ui32>(2027, size / 20);
    const ui32 short_step = Min<ui32>(53, long_step / 400);
    char *buffer = [&]() -> char * {
        if constexpr(std::is_same<ResultContainer, TString>::value) {
            return data.Detach();
        } else {
            return data.mutable_data();
        }
    }();
    for (ui32 i = 0; i < data.size(); ++i) {
        const ui32 j = i + seed;
        buffer[i] = 0xff & (j % short_step + j / long_step);
    }
    return data;
}

inline TString FastGenDataForLZ4(size_t size, ui64 seed) {
    TString data = TString::Uninitialized(size);

    TReallyFastRng32 rng(seed);

    constexpr size_t minRunLen = 32;
    constexpr size_t maxRunLen = 64;
    const size_t runLen = minRunLen + sizeof(ui32) * (rng() % ((maxRunLen - minRunLen) / sizeof(ui32) + 1));

    char run[maxRunLen];
    ui32 i;
    for (i = 0; i < runLen; i += sizeof(ui32)) {
        reinterpret_cast<ui32&>(i[run]) = rng();
    }
    Y_DEBUG_ABORT_UNLESS(i == runLen);

    char *ptr = data.Detach();
    for (; size >= runLen; size -= runLen, ptr += runLen) {
        memcpy(ptr, run, runLen);
    }
    memcpy(ptr, run, size);

    return data;
}

}
