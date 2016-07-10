#include "imebradicomseries.h"

#include <imebradicomimage.h>

using namespace std;
using namespace puntoexe;
using namespace puntoexe::imebra;

ImebraDICOMSeries::ImebraDICOMSeries(puntoexe::ptr<puntoexe::imebra::directoryRecord> pRecord) : pRecord(pRecord)
{
    parse();
}

void ImebraDICOMSeries::parse()
{
    ptr<dataSet> pRecordDataSet(pRecord->getRecordDataSet());

    name = getTagValue(pRecordDataSet,8,4158);

    scanChildren(pRecord->getFirstChildRecord());
}

void ImebraDICOMSeries::scanChildren(ptr<directoryRecord> pRecord)
{
    for(;pRecord != 0; pRecord = pRecord->getNextRecord())
        images.push_back(new ImebraDICOMImage(pRecord));
}
