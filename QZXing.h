#ifndef QZXING_H
#define QZXING_H

#include "QZXing_global.h"
#include <QObject>
#include <QImage>

#if QT_VERSION >= 0x040700
#include <QtDeclarative>
#include <QDeclarativeEngine>
#endif

/**
  * A class containing a very very small subset of the ZXing library.
  * Created for ease of use.
  *
  * Anyone interested in using more technical stuff
  * from the ZXing library is welcomed to add/edit on free will.
  *
  * Regarding DecoderFormat, by default all of those are enabled (except DataMatrix will is still not supported)
  */
class QZXINGSHARED_EXPORT QZXing : public QObject{
    Q_OBJECT
    Q_ENUMS(DecoderFormat)
public:
    enum DecoderFormat {
                    DecoderFormat_None = 0,
                    DecoderFormat_QR_CODE,
                    DecoderFormat_DATA_MATRIX,
                    DecoderFormat_UPC_E,
                    DecoderFormat_UPC_A,
                    DecoderFormat_EAN_8,
                    DecoderFormat_EAN_13,
                    DecoderFormat_CODE_128,
                    DecoderFormat_CODE_39,
                    DecoderFormat_ITF
            } ;

public:
    QZXing(QObject *parent = NULL);

    /**
      * Set the enabled decoders.
      * As argument it is possible to pass conjuction of decoders by using logic OR.
      * e.x. setDecoder ( DecoderFormat_QR_CODE | DecoderFormat_EAN_13 | DecoderFormat_CODE_39 )
      */
    void setDecoder(DecoderFormat hint);

#if QT_VERSION >= 0x040700
    static void registerQMLTypes()
    {
        qmlRegisterType<QZXing>("QZXing", 1, 0, "QZXing");
    }

    static QDeclarativeEngine *engine;
#endif

public slots:
    /**
      * The decoding function. Will try to decode the given image based on the enabled decoders.
      *
      */
    QString decodeImage(const QString &url);

signals:
    void decodingStarted();
    void decodingFinished(bool succeeded);
    void tagFound(QString tag);

private:
    void* decoder;


};

#endif // QZXING_H

