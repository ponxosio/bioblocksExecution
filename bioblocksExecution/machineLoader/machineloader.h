#ifndef MACHINELOADER_H
#define MACHINELOADER_H

#include <string>

#include <commonmodel/modelinterface/modelinterface.h>

class MachineLoader
{
public:
    MachineLoader();
    virtual ~MachineLoader();

    std::shared_ptr<ModelInterface> loadModel(const std::string & path);
};

#endif // MACHINELOADER_H
