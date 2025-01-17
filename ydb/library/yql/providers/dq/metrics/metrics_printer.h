#pragma once

#include <ydb/library/yql/providers/common/metrics/metrics_registry.h>

#include <library/cpp/actors/core/actor_bootstrapped.h>


namespace NYql {

NActors::IActor* CreateMetricsPrinter(const NMonitoring::TDynamicCounterPtr& counters);

} // namespace NYql
