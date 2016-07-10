#include "imebradicomimage.h"

using namespace std;
using namespace puntoexe;
using namespace puntoexe::imebra;

ImebraDICOMImage::ImebraDICOMImage(ptr<directoryRecord> pRecord) : pRecord(pRecord)
{
    parse();
}

void ImebraDICOMImage::parse()
{
    ptr<dataSet> pRecordDataSet(pRecord->getRecordDataSet());

    filepath = dir + getTagValue(pRecordDataSet,4,5376);
}

void ImebraDICOMImage::openImageFile()
{
    ptr<puntoexe::stream> inputStream(new puntoexe::stream);
    inputStream->openFile(filepath, std::ios_base::in);

    ptr<puntoexe::streamReader> reader(new streamReader(inputStream));

    ptr<codecs::codecFactory> codecsFactory(codecs::codecFactory::getCodecFactory());
    ptr<imebra::dataSet> imageDataSet = codecsFactory->load(reader, 2048);

    orgImage = imageDataSet->getModalityImage(0);

    if(!imageConverted) {
        convertImage();
        normalizeImage();
    }
}

void ImebraDICOMImage::convertImage()
{
    imbxUint32 rowSize, channelPixelSize, channelsNumber;
    ptr<imebra::handlers::dataHandlerNumericBase> myHandler = orgImage->getDataHandler(false, &rowSize, &channelPixelSize, &channelsNumber);
    imbxUint32 sizeX, sizeY;
    orgImage->getSize(&sizeX, &sizeY);

    cv::Mat res = cv::Mat(sizeY, sizeX, CV_16UC1);
    cv::Mat_<int> _R = res;

    minValue = myHandler->getSignedLong(0);
    maxValue = myHandler->getSignedLong(0);

    imbxUint32 index(0);
    for (imbxUint32 scanY = 0; scanY < sizeY; ++scanY)
    {
        // Scan all the columns
        for (imbxUint32 scanX = 0; scanX < sizeX; ++scanX)
        {
            // Scan all the channels
            for (imbxUint32 scanChannel = 0; scanChannel < channelsNumber; ++scanChannel)
            {
                imbxInt32 channelValue = myHandler->getSignedLong(index++);

                _R(scanY, scanX) = channelValue;
                if (channelValue > maxValue)
                    maxValue = channelValue;
                if (channelValue < minValue)
                    minValue = channelValue;
            }
        }
    }

    res = _R;

    image = res;
    imageConverted = true;
}

