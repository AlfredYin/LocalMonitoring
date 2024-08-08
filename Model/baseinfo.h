#ifndef BASEINFO_H
#define BASEINFO_H

#include <QString>

class BaseInfo {

public:
    QString getName() const{
        return m_InfoName;
    }

protected:
    QString m_InfoName;

};

#endif // BASEINFO_H
