#include "devicestatelistcommand.h"
#include "deviceproxy.h"

DeviceStateListCommand::DeviceStateListCommand()
{

}

void DeviceStateListCommand::excute(INotification *notification)
{
    DeviceProxy *deviceProxy=(DeviceProxy *)Facade::getInstance()->retrieveProxy("DeviceProxy");
    deviceProxy->getDeviceStatesList((DeviceParam *)notification->getBody());
}
