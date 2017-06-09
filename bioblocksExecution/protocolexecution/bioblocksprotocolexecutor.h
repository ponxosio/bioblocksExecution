#ifndef BIOBLOCKSPROTOCOLEXECUTOR_H
#define BIOBLOCKSPROTOCOLEXECUTOR_H

#include <QTime>

#include <memory>

#include <protocolGraph/execution_interface/protocolexecutorinterface.h>

class BioBlocksProtocolExecutor : public ProtocolExecutorInterface
{
public:
    BioBlocksProtocolExecutor(std::shared_ptr<ProtocolGraph> protocol,
                              int mainLoopStartId,
                              std::shared_ptr<QTime> timer);

    virtual ~BioBlocksProtocolExecutor();

    virtual void executeProtocol(std::shared_ptr<ActuatorsExecutionInterface> executor,int nargs, ...) throw (std::runtime_error);

protected:
    int mainLoopStartId;
    std::shared_ptr<QTime> timer;
};

#endif // BIOBLOCKSPROTOCOLEXECUTOR_H
