LIBRARY()

SRCS(
    channel_storage.cpp
    spilling_counters.cpp
    spilling_file.cpp
    spilling.cpp
)

PEERDIR(
    ydb/library/services
    ydb/library/yql/dq/common
    ydb/library/yql/dq/actors
    ydb/library/yql/dq/runtime
    ydb/library/yql/utils

    library/cpp/actors/core
    library/cpp/actors/util
    library/cpp/monlib/dynamic_counters
    library/cpp/monlib/service/pages
)

YQL_LAST_ABI_VERSION()

END()

RECURSE_FOR_TESTS(
    ut
)
