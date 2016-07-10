#include "imebraobject.h"

#include <fstream>

using namespace std;
using namespace puntoexe;
using namespace puntoexe::imebra;

ImebraObject::ImebraObject()
{
    dir = "C:\\Users\\adamt_000\\Downloads\\dicom_images\\matlab\\examples\\sample_data\\DICOM\\cd1\\";
}

std::string ImebraObject::getTagValue(ptr<dataSet> pDataSet, imbxUint16 group, imbxUint16 tag)
{
    ///TODO: Weryfikować czy dany tag istnieje bo w tej chwili zwraca segfault
    ptr<handlers::dataHandler> tagHandler(pDataSet->getDataHandler(group, 0, tag, 0, false));

    wstring output;

    for(size_t scanValues(0); tagHandler->pointerIsValid(scanValues); ++scanValues) {
        if(scanValues != 0)
            output += L"\\";
        output += tagHandler->getUnicodeString(scanValues);
    }

    return string(output.begin(), output.end());
}
