#include "ApplicationFacade.h"
#include "LoginCommand.h"
#include "LoginMediator.h"
#include "LoginProxy.h"

#include "changepwdcommand.h"

#include "devicecommand.h"
#include "devicemediator.h"
#include "deviceproxy.h"
#include "ApplicationMediator.h"

// 客户端初始化时须对Mediator，Command，Proxy进行注册，以表明各自感兴趣的消息（观察者模式中的订阅）。
ApplicationFacade::ApplicationFacade() : Facade()
{
}

// Mediator（中介者）负责管理和协调不同组件之间的通信。注册各个组件并管理它们之间的消息传递。
void ApplicationFacade::initializeMediator()
{
    registerMediator(new LoginMediator());

    registerMediator(new DeviceMediator());

    registerMediator(new ApplicationMediator());
}

// Command（命令）表示一个执行操作或命令的对象。通常封装了一个操作或一系列操作，并且可以调用 Proxy 完成业务逻辑。
void ApplicationFacade::initializeCommand()
{
    registerCommand("login_check", new LoginCommand());
    registerCommand("change_passwd", new ChangePwdCommand());

    registerCommand("get_devicestate",new DeviceCommand());
}

// 负责处理真正的业务逻辑和数据操作。可以作为数据模型的抽象层，与数据库或其他数据源交互。
void ApplicationFacade::initializeProxy()
{
    registerProxy(new LoginProxy());
    registerProxy(new DeviceProxy());
}
