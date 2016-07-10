#include "imebradicomdirfile.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace puntoexe;
using namespace puntoexe::imebra;

ImebraDICOMDIRFile::ImebraDICOMDIRFile(std::string path) : DICOMDIRFile(path)
{

}

void ImebraDICOMDIRFile::parseDICOMDIR()
{
    // Open the file containing the dicom directory
    ptr<puntoexe::stream> inputStream(new puntoexe::stream);
    inputStream->openFile(path, std::ios_base::in);

    // Connect a stream reader to the dicom stream
    ptr<puntoexe::streamReader> reader(new streamReader(inputStream));

    // Get a codec factory and let it use the right codec to create a dataset
    //  from the input stream
    ptr<codecs::codecFactory> codecsFactory(codecs::codecFactory::getCodecFactory());
    ptr<dataSet> loadedDataSet(codecsFactory->load(reader, 2048));

    // Now create a dicomdir object
    ptr<dicomDir> directory(new dicomDir(loadedDataSet));

    //wofstream myfile;
    //myfile.open ("C:\\Users\\adamt_000\\Desktop\\dicomdir.xml");
    //myfile << L"<dicomdir>";
    scanChildren(directory->getFirstRootRecord());
    //myfile << L"</dicomdir>";

    //myfile.close();
}

//
// Scan all the sibling records (and their children) of
//  the specified one
//
void ImebraDICOMDIRFile::scanChildren(ptr<directoryRecord> pRecord)
{
    for(;pRecord != 0; pRecord = pRecord->getNextRecord())
        patients.push_back(new ImebraDICOMPatient(pRecord));
}
