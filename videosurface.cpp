#include "videosurface.h"
#include <QDebug>

myVideoSurface::myVideoSurface(QObject *parent) :
        QAbstractVideoSurface(parent)
{
        m_imageFormat = QImage::Format_Invalid;
}

bool myVideoSurface::present(const QVideoFrame &frame){

    QVideoFrame newFrame(frame);
    newFrame.map(QAbstractVideoBuffer::ReadOnly);

    //Flip front and backbuffer
    //QImage *tmp = currentFrame;
    currentFrame = QImage(newFrame.bits(),newFrame.width(),newFrame.height(),newFrame.bytesPerLine(),m_imageFormat);
    qDebug()<<currentFrame.size()<<" "<<newFrame.bits()<<" "<<newFrame.width()<<" "<<newFrame.height()<<
              " "<<newFrame.bytesPerLine()<<" "<<m_imageFormat;
    //if(!currentFrame.save("testimage.jpg"))
    //  qDebug()<<"Could not save image";
    backBuffer = currentFrame.convertToFormat(QImage::Format_ARGB32);
    //qDebug()<<"Presenting frame "<< frame.isMapped() << " "<< frame.isValid() << " " << frame.isReadable() << " " << frame.pixelFormat()<< " "<<frame.size();

    newFrame.unmap();
    qDebug()<<"Video frame unmapped";
    return true;
    /*
        m_frame = frame;
        if(surfaceFormat().pixelFormat() != m_frame.pixelFormat() ||
                surfaceFormat().frameSize() != m_frame.size()) {
                stop();
                qDebug() << "surface: return false";
                return false;
        } else {
                if (m_frame.map(QAbstractVideoBuffer::ReadOnly)) {
                 QImage image(
                                 m_frame.bits(),
                                 m_frame.width(),
                                 m_frame.height(),
                                 m_frame.bytesPerLine(),
                                 m_imageFormat);
                }
                return true;
        }*/
}

bool myVideoSurface::start(const QVideoSurfaceFormat &format){
        qDebug() << "surface: start";

        qDebug()<< "Video Surface started "<< format;
        m_videoFormat = format;
        m_imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());

        QAbstractVideoSurface::start(format);
        return true;
}

void myVideoSurface::stop(){
        QAbstractVideoSurface::stop();
}

QList<QVideoFrame::PixelFormat> myVideoSurface::supportedPixelFormats(
                        QAbstractVideoBuffer::HandleType handleType) const
{
        if (handleType == QAbstractVideoBuffer::NoHandle) {
                return QList<QVideoFrame::PixelFormat>()
                                << QVideoFrame::Format_RGB32
                                << QVideoFrame::Format_ARGB32
                                << QVideoFrame::Format_ARGB32_Premultiplied
                                << QVideoFrame::Format_RGB565
                                << QVideoFrame::Format_RGB555
                                << QVideoFrame::Format_YUYV
                                << QVideoFrame::Format_UYVY;
        } else {
                return QList<QVideoFrame::PixelFormat>();
        }
}
