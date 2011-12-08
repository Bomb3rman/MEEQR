#include "QZXing.h"

#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/DecodeHints.h>
#include "CameraImageWrapper.h"

#include <QDebug>

#include <QFile>

using namespace zxing;

QDeclarativeEngine *QZXing::engine = 0;

QZXing::QZXing(QObject *parent) : QObject(parent)
{
    decoder = new MultiFormatReader();
    ((MultiFormatReader*)decoder)->setHints(DecodeHints::DEFAULT_HINT);
}

void QZXing::setDecoder(DecoderFormat hint)
{
    DecodeHints enabledDecoders;

    if(hint & DecoderFormat_QR_CODE)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_QR_CODE);

    if(hint & DecoderFormat_DATA_MATRIX)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_DATA_MATRIX);

    if(hint & DecoderFormat_UPC_E)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_UPC_E);

    if(hint & DecoderFormat_UPC_A)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_UPC_A);

    if(hint & DecoderFormat_EAN_8)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_EAN_8);

    if(hint & DecoderFormat_EAN_13)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_EAN_13);

    if(hint & DecoderFormat_CODE_128)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_CODE_128);

    if(hint & DecoderFormat_CODE_39)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_CODE_39);

    if(hint & DecoderFormat_ITF)
        enabledDecoders.addFormat((BarcodeFormat)DecoderFormat_ITF);

    ((MultiFormatReader*)decoder)->setHints(enabledDecoders);
}

QString QZXing::decodeImage(const QString &url)
{
    Ref<Result> res;
    qDebug()<<url;
//    QString provider = url.split("//").last();
//    QString iid = provider.split("/").last();
//    provider = provider.split("/").first();
//    qDebug()<<"Provider: "<<provider << " ID: " << iid;
//    QDeclarativeImageProvider *imgProv = engine->imageProvider("");
//    qDebug()<<"providing Image " << imgProv;
//    qDebug()<<imgProv->imageType();
//    QImage image = imgProv->requestImage("camera/preview_1", new QSize(640,480), QSize(640,480));

    QImage image(":/camera/preview_1");

    emit decodingStarted();
    qDebug()<<image.size();

    try{
        Ref<LuminanceSource> imageRef(new CameraImageWrapper(image));
        GlobalHistogramBinarizer* binz = new GlobalHistogramBinarizer(imageRef);

        Ref<Binarizer> bz (binz);
        BinaryBitmap* bb = new BinaryBitmap(bz);

        Ref<BinaryBitmap> ref(bb);

        res = ((MultiFormatReader*)decoder)->decode(ref);

        QString string = QString(res->getText()->getText().c_str());
        emit tagFound(string);
        emit decodingFinished(true);
        qDebug()<<"Tag found";
        return string;
    }
    catch(zxing::Exception& e)
    {
       emit decodingFinished(false);
       qDebug()<<"No tag found " << e.what();
       return "";
    }
}
