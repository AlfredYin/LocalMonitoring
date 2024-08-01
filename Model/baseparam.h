#ifndef BASEPARAM_H
#define BASEPARAM_H

#include <QString>

class BaseParam {

public:
    QString getName() const;

protected:
    QString m_updateDataName;

};

#endif // BASEPARAM_H
