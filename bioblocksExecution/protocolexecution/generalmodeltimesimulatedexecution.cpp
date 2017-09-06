#include "generalmodeltimesimulatedexecution.h"

GeneralModelTimeSimulatedExecution::GeneralModelTimeSimulatedExecution(
        std::shared_ptr<ModelInterface> model,
        std::shared_ptr<MappingInterface> mapping,
        std::shared_ptr<UserCommunicationInterface> userCom,
        const std::unordered_map<int, std::string> & containerAlias,
        std::shared_ptr<TimeStampSimulator> timestampManager) :
    GeneralModelExecutor(model, mapping, userCom, containerAlias)
{
    this->timestampManager = timestampManager;
    this->started = false;
}

GeneralModelTimeSimulatedExecution::~GeneralModelTimeSimulatedExecution() {

}

units::Time GeneralModelTimeSimulatedExecution::timeStep() {
    if (flowsNeedUpdate) {
        model->processFlows(containersUsedInProtocol);
        flowsNeedUpdate = false;
    }

    if (!started) {
        units::Time millisecondsPass = timer->elapsed() * units::ms;
        timestampManager->passTime(millisecondsPass);

        started = true;
    }

    timestampManager->passTime(timeSlice);
    return timeSlice;
}

std::string GeneralModelTimeSimulatedExecution::addTimeStamp(const std::string & str) {
    return timestampManager->getTimeStamp() + "." + str;
}
