#ifndef IMEBRADICOMIMAGE_H
#define IMEBRADICOMIMAGE_H

#include <dicomimage.h>
#include <imebraobject.h>

class ImebraDICOMImage : public DICOMImage, ImebraObject
{
public:
    ImebraDICOMImage(puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord);
    virtual void parse();
    virtual void openImageFile();
    virtual void convertImage();
protected:
    puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord;
private:
    puntoexe::ptr<puntoexe::imebra::image> orgImage;
};

#endif // IMEBRADICOMIMAGE_H
