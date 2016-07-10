#ifndef IMEBRAOBJECT_H
#define IMEBRAOBJECT_H

#include <imebra/include/imebra.h>

class ImebraObject
{
protected:
    std::string getTagValue(puntoexe::ptr<puntoexe::imebra::dataSet> pDataSet, imbxUint16 group, imbxUint16 tag);
    std::string dir;
public:
    ImebraObject();
};

#endif // IMEBRAOBJECT_H
