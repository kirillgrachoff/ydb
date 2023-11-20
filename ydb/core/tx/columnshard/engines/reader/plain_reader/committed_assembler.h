#pragma once
#include "source.h"
#include <ydb/core/tx/columnshard/engines/reader/conveyor_task.h>
#include <ydb/core/tx/columnshard/engines/reader/read_metadata.h>
#include <ydb/core/tx/columnshard/engines/portions/portion_info.h>
#include <ydb/core/tx/columnshard/counters/common/object_counter.h>
#include <ydb/core/tx/columnshard/counters/scan.h>
#include <ydb/core/formats/arrow/arrow_filter.h>

namespace NKikimr::NOlap::NPlainReader {
class TCommittedAssembler: public NColumnShard::IDataTasksProcessor::ITask, public NColumnShard::TMonitoringObjectsCounter<TCommittedAssembler, true> {
private:
    using TBase = NColumnShard::IDataTasksProcessor::ITask;
    TString BlobData;
    TReadMetadata::TConstPtr ReadMetadata;
    const std::shared_ptr<IDataSource> Source;
    ui64 SchemaVersion;
    TSnapshot DataSnapshot;

    std::shared_ptr<NArrow::TColumnFilter> EarlyFilter;
    std::shared_ptr<arrow::RecordBatch> ResultBatch;
    const NColumnShard::TCounterGuard TaskGuard;
protected:
    virtual bool DoExecute() override;
    virtual bool DoApply(IDataReader& owner) const override;
public:
    virtual TString GetTaskClassIdentifier() const override {
        return "PlainReader::TCommittedAssembler";
    }

    TCommittedAssembler(const NActors::TActorId& scanActorId, const TString& blobData, const TReadMetadata::TConstPtr& readMetadata, const std::shared_ptr<IDataSource>& source,
        const TCommittedBlob& cBlob, NColumnShard::TCounterGuard&& taskGuard);
};
}
