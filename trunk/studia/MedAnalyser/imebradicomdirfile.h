#ifndef IMEBRADICOMDIRFILE_H
#define IMEBRADICOMDIRFILE_H

#include <dicomdirfile.h>
#include <imebradicompatient.h>
#include <imebra/include/imebra.h>

class ImebraDICOMDIRFile : public DICOMDIRFile
{
private:
    void parseDICOMDIR() override;

    void scanChildren(puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord);
    //void outputTag(puntoexe::ptr<puntoexe::imebra::dataSet> pDataSet, imbxUint16 group, imbxUint16 tag, std::wostream* pOutputStream, std::wstring tagName, imbxUint16 id = 0);
    //std::wstring xmlEntities(std::wstring value);
public:
    ImebraDICOMDIRFile(std::string path);
};

#endif // IMEBRADICOMDIRFILE_H
