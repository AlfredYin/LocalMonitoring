#include "devicecommand.h"

#include "LoginCommand.h"
#include "Patterns/Facade.h"
#include "Interface/INotification.h"

#include "deviceparam.h"
#include "deviceproxy.h"
#include "devicestateresult.h"


DeviceCommand::DeviceCommand()
{

}

// 常封装了一个操作或一系列操作，并且可以调用 Proxy 完成业务逻辑。
void DeviceCommand::excute(INotification *notification)
{
    DeviceProxy *deviceProxy=(DeviceProxy *)Facade::getInstance()->retrieveProxy("DeviceProxy");
//    deviceProxy->getDevicestate((DeviceParam *)notification->getBody());
}
