#include "imebradicomstudy.h"

#include <imebradicomseries.h>

using namespace std;
using namespace puntoexe;
using namespace puntoexe::imebra;

ImebraDICOMStudy::ImebraDICOMStudy(puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord) : pRecord(pRecord)
{
    parse();
}

void ImebraDICOMStudy::parse()
{
    ptr<dataSet> pRecordDataSet(pRecord->getRecordDataSet());

    name = getTagValue(pRecordDataSet,8,4144);

    scanChildren(pRecord->getFirstChildRecord());
}

void ImebraDICOMStudy::scanChildren(ptr<directoryRecord> pRecord)
{
    for(;pRecord != 0; pRecord = pRecord->getNextRecord())
        series.push_back(new ImebraDICOMSeries(pRecord));
}

