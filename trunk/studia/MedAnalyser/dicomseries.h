#ifndef DICOMSERIES_H
#define DICOMSERIES_H

#include <string>
#include <vector>

#include <dicomimage.h>

#include <QMetaType>

class DICOMSeries
{
public:
    DICOMSeries();
    virtual ~DICOMSeries();
    virtual void parse() = 0;
    std::vector<DICOMImage*> getImages() { return images; }
    std::string getName() { return name; }
protected:
    std::string name;
    std::vector<DICOMImage*> images;
};

Q_DECLARE_METATYPE(DICOMSeries*)

#endif // DICOMSERIES_H
