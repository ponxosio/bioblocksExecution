#include "generalmodelexecutor.h"

GeneralModelExecutor::GeneralModelExecutor(
        std::shared_ptr<ModelInterface> model,
        std::shared_ptr<MappingInterface> mapping,
        std::shared_ptr<UserCommunicationInterface> userCom,
        const std::unordered_map<int, std::string> & containerAlias) :
    containersUsedInProtocol(mapping->getAllContainersUseInProtocol()), cAlias(containerAlias)
{
    this->flowsNeedUpdate = false;

    this->model = model;
    this->mapping = mapping;
    this->userCom = userCom;

    timer = std::make_shared<QTime>();
    mutex = new QMutex();
    condition = new QWaitCondition();

    aboutToQuit = false;
    waiting = false;
}

GeneralModelExecutor::~GeneralModelExecutor() {
    delete mutex;
    delete condition;
}

void GeneralModelExecutor::applyLigth(const std::string & sourceId, units::Length wavelength, units::LuminousIntensity intensity) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "apply ligth to" << sourceId << " with: wavelength: " << wavelength.to(units::nm) << " nm and intensity: " << intensity.to(units::cd) << " cd";
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::apply_light, 2, intensity, wavelength);
}

void GeneralModelExecutor::stopApplyLigth(const std::string & sourceId) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "stop apply ligth to " << sourceId;
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::apply_light, 0);
}

void GeneralModelExecutor::applyTemperature(const std::string & sourceId, units::Temperature temperature) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "apply temperature to " << sourceId << " with " << temperature.to(units::C) << " ºC";
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::heat, 1, temperature);
}

void GeneralModelExecutor::stopApplyTemperature(const std::string & sourceId) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "stop apply temperature to " << sourceId;
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::heat, 0);
}

void GeneralModelExecutor::stir(const std::string & idSource, units::Frequency intensity) {
    int machineSourceId = mapping->getMappedComponent(idSource);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "stir " << idSource << " with " << intensity.to(units::Hz) << " Hz";
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::stir, 1, intensity);
}

void GeneralModelExecutor::stopStir(const std::string & idSource) {
    int machineSourceId = mapping->getMappedComponent(idSource);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "stop stir of " << idSource;
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::stir, 0);
}

void GeneralModelExecutor::centrifugate(const std::string & idSource, units::Frequency intensity) {
    int machineSourceId = mapping->getMappedComponent(idSource);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "centrifugate " << idSource << " with " << intensity.to(units::Hz) << " Hz";
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::centrifugate, 1, intensity);
}

void GeneralModelExecutor::stopCentrifugate(const std::string & idSource) {
    int machineSourceId = mapping->getMappedComponent(idSource);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "stop centrifugation of " << idSource;
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::centrifugate, 0);
}

void GeneralModelExecutor::shake(const std::string & idSource, units::Frequency intensity) {
    int machineSourceId = mapping->getMappedComponent(idSource);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "shake " << idSource << " with " << intensity.to(units::Hz) << " Hz";
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::shake, 1, intensity);
}

void GeneralModelExecutor::stopShake(const std::string & idSource) {
    int machineSourceId = mapping->getMappedComponent(idSource);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "stop shake of " << idSource;
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::shake, 0);
}

void GeneralModelExecutor::startElectrophoresis(const std::string & idSource, units::ElectricField fieldStrenght) {
    int machineSourceId = mapping->getMappedComponent(idSource);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "start electrophoresis to " << idSource << " with " << fieldStrenght.to(units::V / units::cm) << " V/cm";
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::electrophoresis, 1, fieldStrenght);
}

std::shared_ptr<ElectrophoresisResult> GeneralModelExecutor::stopElectrophoresis(const std::string & idSource) {
    int machineSourceId = mapping->getMappedComponent(idSource);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "stop electrophoresis of " << idSource;
    userCom->sendUserMessage(addTimeStamp(message.str()));

    std::shared_ptr<MultiUnitsWrapper> value = componentPtr->doOperation(Function::electrophoresis, 0);
    if (value != NULL) {
        return value->getElectrophoresisResult();
    } else {
        throw(std::runtime_error("GeneralModelExecutor::stopElectrophoresis. container " +
                                 std::to_string(machineSourceId) + " has returned a NULL electrophoresis result"));
    }
}

units::Volume GeneralModelExecutor::getVirtualVolume(const std::string & sourceId) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "get virtual volume of " << sourceId;
    userCom->sendUserMessage(addTimeStamp(message.str()));

    return componentPtr->getActualVolume();
}

void GeneralModelExecutor::loadContainer(const std::string & sourceId, units::Volume initialVolume) {
    int machineSourceId = mapping->getMappedComponent(sourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "[USER_QUESTION]fill machine's container: " << cAlias[machineSourceId] << " with " << initialVolume.to(units::ml)
            << " ml of protocol's container: " << sourceId << ", click OK when ready.";

    userCom->sendUserMessage(addTimeStamp(message.str()));

    if(!aboutToQuit) {
        userCom->getUserResponse();
    }
}

void GeneralModelExecutor::startMeasureOD(const std::string & sourceId, units::Frequency measurementFrequency, units::Length wavelength) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "start measuring OD from " << sourceId << " with: measurement frequency: " << measurementFrequency.to(units::Hz)
            << " Hz and waveLength: " << wavelength.to(units::nm) << " nm";

    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::measure_od, 2, measurementFrequency, wavelength);
}

double GeneralModelExecutor::getMeasureOD(const std::string & sourceId) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::shared_ptr<MultiUnitsWrapper> value = componentPtr->doOperation(Function::measure_od, 0);
    if (value != NULL) {
        std::stringstream message;
        message << std::fixed;
        message << std::setprecision(2);

        message << "measured OD of " << sourceId << " is " << value->getNoUnits();
        userCom->sendUserMessage(addTimeStamp(message.str()));

        return value->getNoUnits();
    } else {
        throw(std::runtime_error("GeneralModelExecutor::getMeasureOD. container " +
                                 std::to_string(machineSourceId) + " has returned a NULL od measurement result"));
    }
}

void GeneralModelExecutor::startMeasureTemperature(const std::string & sourceId, units::Frequency measurementFrequency) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "start measuring Temperature from " << sourceId << " with measurement frequency: " << measurementFrequency.to(units::Hz) << " Hz";
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::measure_temperature, 1, measurementFrequency);
}

units::Temperature GeneralModelExecutor::getMeasureTemperature(const std::string & sourceId) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::shared_ptr<MultiUnitsWrapper> value = componentPtr->doOperation(Function::measure_temperature, 0);
    if (value != NULL) {
        std::stringstream message;
        message << std::fixed;
        message << std::setprecision(2);

        message << "measures temperature of " << sourceId << " is " << value->getTemperature();
        userCom->sendUserMessage(addTimeStamp(message.str()));

        return value->getTemperature();
    } else {
        throw(std::runtime_error("GeneralModelExecutor::getMeasureTemperature. container " +
                                 std::to_string(machineSourceId) + " has returned a NULL temperature measurement result"));
    }
}

void GeneralModelExecutor::startMeasureLuminiscense(const std::string & sourceId, units::Frequency measurementFrequency) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "start measuring luminiscence of " << sourceId << " with measurement frequency: " << measurementFrequency.to(units::Hz) << " Hz";
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::measure_luminiscence, 1, measurementFrequency);
}

units::LuminousIntensity GeneralModelExecutor::getMeasureLuminiscense(const std::string & sourceId) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::shared_ptr<MultiUnitsWrapper> value = componentPtr->doOperation(Function::measure_luminiscence, 0);
    if (value != NULL) {
        std::stringstream message;
        message << std::fixed;
        message << std::setprecision(2);

        message << "measured luminiscence of " << sourceId << " is " << value->getLuminousIntensity();
        userCom->sendUserMessage(addTimeStamp(message.str()));

        return value->getLuminousIntensity();
    } else {
        throw(std::runtime_error("GeneralModelExecutor::getMeasureLuminiscense. container " +
                                 std::to_string(machineSourceId) + " has returned a NULL luminescence measurement result"));
    }
}

void GeneralModelExecutor::startMeasureVolume(const std::string & sourceId, units::Frequency measurementFrequency) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "start measuring volume of " << sourceId << " with measurement frequency: " << measurementFrequency.to(units::Hz) << " Hz";
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::measure_volume, 1, measurementFrequency);
}

units::Volume GeneralModelExecutor::getMeasureVolume(const std::string & sourceId) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::shared_ptr<MultiUnitsWrapper> value = componentPtr->doOperation(Function::measure_volume, 0);
    if (value != NULL) {
        std::stringstream message;
        message << std::fixed;
        message << std::setprecision(2);

        message << "measured volume of " << sourceId << " is " << value->getVolume();
        userCom->sendUserMessage(addTimeStamp(message.str()));

        return value->getVolume();
    } else {
        throw(std::runtime_error("GeneralModelExecutor::getMeasureVolume. container " +
                                 std::to_string(machineSourceId) + " has returned a NULL volume measurement result"));
    }
}

void GeneralModelExecutor::startMeasureFluorescence(
        const std::string & sourceId,
        units::Frequency measurementFrequency,
        units::Length excitation,
        units::Length emission)
{
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "start measuring fluorescence from " << sourceId << " with: measurement frequency: " << measurementFrequency.to(units::Hz) << " Hz";
    message << ", excitation: " << excitation.to(units::nm) << " nm and emission: " << emission.to(units::nm) << " nm";
    userCom->sendUserMessage(addTimeStamp(message.str()));

    componentPtr->doOperation(Function::measure_fluorescence, 3, measurementFrequency, excitation, emission);
}

units::LuminousIntensity GeneralModelExecutor::getMeasureFluorescence(const std::string & sourceId) {
    int machineSourceId = mapping->getMappedComponent(sourceId);
    std::shared_ptr<ComponentInterface> componentPtr = model->getComponent(machineSourceId);

    std::shared_ptr<MultiUnitsWrapper> value = componentPtr->doOperation(Function::measure_fluorescence, 0);
    if (value != NULL) {
        std::stringstream message;
        message << std::fixed;
        message << std::setprecision(2);

        message << "measured fluorescence from " << sourceId << " is " << value->getLuminousIntensity();
        userCom->sendUserMessage(addTimeStamp(message.str()));

        return value->getLuminousIntensity();
    } else {
        throw(std::runtime_error("GeneralModelExecutor::getMeasureFluorescence. container " +
                                 std::to_string(machineSourceId) + " has returned a NULL fluorescence measurement result"));
    }
}

void GeneralModelExecutor::setContinuosFlow(const std::string & idSource, const std::string & idTarget, units::Volumetric_Flow rate) {
    int machineSourceId = mapping->getMappedComponent(idSource);
    int machineTargetId = mapping->getMappedComponent(idTarget);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "set continuous flow from " << idSource << " to " << idTarget << " at " << rate.to(units::ml/units::hr) << " ml/h";
    userCom->sendUserMessage(addTimeStamp(message.str()));

    flowsNeedUpdate = true;
    model->setContinuousFlow(machineSourceId, machineTargetId, rate);
}

void GeneralModelExecutor::stopContinuosFlow(const std::string & idSource, const std::string & idTarget) {
    int machineSourceId = mapping->getMappedComponent(idSource);
    int machineTargetId = mapping->getMappedComponent(idTarget);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "stop continuous flow from " << idSource << " to " << idTarget;
    userCom->sendUserMessage(addTimeStamp(message.str()));

    flowsNeedUpdate = true;
    model->stopContinuousFlow(machineSourceId, machineTargetId);
}

units::Time GeneralModelExecutor::transfer(const std::string & idSource, const std::string & idTarget, units::Volume volume) {
    int machineSourceId = mapping->getMappedComponent(idSource);
    int machineTargetId = mapping->getMappedComponent(idTarget);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "transfer " << volume.to(units::ml) << " ml from " << idSource << " to " << idTarget;
    userCom->sendUserMessage(addTimeStamp(message.str()));

    flowsNeedUpdate = true;
    return model->transferLiquid(machineSourceId, machineTargetId, volume);
}

void GeneralModelExecutor::stopTransfer(const std::string & idSource, const std::string & idTarget) {
    int machineSourceId = mapping->getMappedComponent(idSource);
    int machineTargetId = mapping->getMappedComponent(idTarget);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "stop transfer from " << idSource << " to " << idTarget;
    userCom->sendUserMessage(addTimeStamp(message.str()));

    flowsNeedUpdate = true;
    model->stopTransferLiquid(machineSourceId, machineTargetId);
}

units::Time GeneralModelExecutor::mix(
        const std::string & idSource1,
        const std::string & idSource2,
        const std::string & idTarget,
        units::Volume volume1,
        units::Volume volume2)
{
    int machineSourceId1 = mapping->getMappedComponent(idSource1);
    int machineSourceId2 = mapping->getMappedComponent(idSource2);
    int machineTargetId = mapping->getMappedComponent(idTarget);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "mix " << volume1.to(units::ml) << "ml form " << idSource1 << " and " << volume2.to(units::ml) << " ml from " << idSource2 << " into " << idTarget;
    userCom->sendUserMessage(addTimeStamp(message.str()));

    flowsNeedUpdate = true;

    return model->mix(machineSourceId1, machineSourceId2, machineTargetId, volume1, volume2);
}

void GeneralModelExecutor::stopMix(
        const std::string & idSource1,
        const std::string & idSource2,
        const std::string & idTarget)
{
    int machineSourceId1 = mapping->getMappedComponent(idSource1);
    int machineSourceId2 = mapping->getMappedComponent(idSource2);
    int machineTargetId = mapping->getMappedComponent(idTarget);

    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "stop mixing " << idSource1 << " and " << idSource2 << " into " << idTarget;
    userCom->sendUserMessage(addTimeStamp(message.str()));

    flowsNeedUpdate = true;
    model->stopMix(machineSourceId1, machineSourceId2, machineTargetId);
}

void GeneralModelExecutor::setTimeStep(units::Time time) {
    std::stringstream message;
    message << std::fixed;
    message << std::setprecision(2);

    message << "setting time step to " << time.to(units::s) << " s";
    userCom->sendUserMessage(addTimeStamp(message.str()));

    this->timeSlice = time;
}

units::Time GeneralModelExecutor::timeStep() {
    if (flowsNeedUpdate) {
        model->processFlows(containersUsedInProtocol);
        flowsNeedUpdate = false;
    }

    units::Time millisecondsPass = timer->elapsed() * units::ms;

    units::Time time2wait = timeSlice - millisecondsPass;
    if (time2wait > 0*units::ms) {
        if(!aboutToQuit) {
            waiting = true;
            waitMs(time2wait.to(units::ms));
            waiting = false;
        }

        timer->restart();
        return timeSlice;
    } else {
        timer->restart();
        return millisecondsPass;
    }
}

void GeneralModelExecutor::finishExecution() {
    aboutToQuit = true;
    if (waiting) {
        condition->wakeAll();
    }
}

std::string GeneralModelExecutor::addTimeStamp(const std::string & str) {
    QDateTime now = QDateTime::currentDateTime();

    std::string timeStap = now.toString("dd hh:mm:ss").toStdString();
    return timeStap + " . " + str;
}

void GeneralModelExecutor::waitMs(unsigned long ms) {
    CustomSleepMsThread sleepThread(mutex, condition, ms);
    mutex->lock();
    sleepThread.start();
    sleepThread.wait();
    mutex->unlock();
}
