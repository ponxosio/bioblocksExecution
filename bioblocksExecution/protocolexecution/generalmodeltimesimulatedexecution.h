#ifndef GENERALMODELTIMESIMULATEDEXECUTION_H
#define GENERALMODELTIMESIMULATEDEXECUTION_H

#include <memory>

#include <QDateTime>

#include <utils/timestampsimulator.h>
#include <utils/units.h>

#include "bioblocksExecution/protocolexecution/generalmodelexecutor.h"

class GeneralModelTimeSimulatedExecution : public GeneralModelExecutor
{
public:
    GeneralModelTimeSimulatedExecution(std::shared_ptr<ModelInterface> model,
                                       std::shared_ptr<MappingInterface> mapping,
                                       std::shared_ptr<UserCommunicationInterface> userCom,
                                       std::shared_ptr<TimeStampSimulator> timestampManager);
    virtual ~GeneralModelTimeSimulatedExecution();

    virtual units::Time timeStep();

protected:
    std::shared_ptr<TimeStampSimulator> timestampManager;
    bool started;

    virtual std::string addTimeStamp(const std::string & str);
};

#endif // GENERALMODELTIMESIMULATEDEXECUTION_H
