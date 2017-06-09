#include "bioblocksexecution.h"

BioblocksExecution::BioblocksExecution(
        std::shared_ptr<PluginAbstractFactory> pluginFactory,
        std::shared_ptr<UserCommunicationInterface> userComm)
{
    this->pluginFactory = pluginFactory;
    this->userComm = userComm;
}

BioblocksExecution::~BioblocksExecution() {

}

void BioblocksExecution::executeNewProtocol(
        const std::string & protocolJSONFile,
        const std::string & machineJSONFile,
        units::Time timeSlice)
{
    BioBlocksTranslator translator(timeSlice, protocolJSONFile);

    std::shared_ptr<LogicBlocksManager> logicBlocks = std::make_shared<LogicBlocksManager>();
    std::shared_ptr<ProtocolGraph> protocol = translator.translateFile(logicBlocks);

    MachineLoader machineLoader;
    std::shared_ptr<ModelInterface> model = machineLoader.loadModel(machineJSONFile);
    model->updatePluginFactory(pluginFactory);

    std::shared_ptr<MappingInterface> mapping = model->findProtocolRelation(protocol);

    std::shared_ptr<GeneralModelExecutor> actuatorsExecutor = std::make_shared<GeneralModelExecutor>(model, mapping, userComm);

    int mainLoopId = logicBlocks->getMainLoopId();
    BioBlocksProtocolExecutor protocolExecutor(protocol, mainLoopId, actuatorsExecutor->getTimer());

    protocolExecutor.executeProtocol(actuatorsExecutor, 0);
}
