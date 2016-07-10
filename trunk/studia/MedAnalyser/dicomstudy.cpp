#include "dicomstudy.h"

DICOMStudy::DICOMStudy()
{

}

DICOMStudy::~DICOMStudy()
{
    for(DICOMSeries* s : series)
        delete s;
}

