#include "imebradicompatient.h"
#include "imebradicomstudy.h"

using namespace std;
using namespace puntoexe;
using namespace puntoexe::imebra;

ImebraDICOMPatient::ImebraDICOMPatient(ptr<directoryRecord> pRecord) : pRecord(pRecord)
{
    parse();
}

void ImebraDICOMPatient::parse()
{
    ptr<dataSet> pRecordDataSet(pRecord->getRecordDataSet());

    name = getTagValue(pRecordDataSet,16,16);

    scanChildren(pRecord->getFirstChildRecord());
}

void ImebraDICOMPatient::scanChildren(ptr<directoryRecord> pRecord)
{
    for(;pRecord != 0; pRecord = pRecord->getNextRecord())
        studies.push_back(new ImebraDICOMStudy(pRecord));
}

