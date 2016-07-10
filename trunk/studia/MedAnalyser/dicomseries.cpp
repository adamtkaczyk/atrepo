#include "dicomseries.h"

DICOMSeries::DICOMSeries()
{

}

DICOMSeries::~DICOMSeries()
{
    for(DICOMImage* im : images)
        delete im;
}

