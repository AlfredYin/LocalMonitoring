#ifndef BASEINFO_H
#define BASEINFO_H

#include <QString>

class BaseInfo {

public:
    QString getName() const;

protected:
    QString m_updateDataName;

};

#endif // BASEINFO_H
