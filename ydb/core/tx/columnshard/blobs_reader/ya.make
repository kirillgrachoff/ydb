LIBRARY()

SRCS(
    actor.cpp
    task.cpp
    events.cpp
    read_coordinator.cpp
)

PEERDIR(
    ydb/core/protos
    library/cpp/actors/core
    ydb/core/tablet_flat
)

END()
