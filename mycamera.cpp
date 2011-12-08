#include "mycamera.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include <QVideoRendererControl>
#include <QPaintEvent>
#include <QPaintEngine>

MyCamera::MyCamera(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    videoSurface = new myVideoSurface();
    m_camera = new QCamera(this);
    //m_camera->setViewfinder(videoSurface);
    m_camera->setCaptureMode(QCamera::CaptureStillImage);
    QVideoRendererControl *control = (QVideoRendererControl*)
                m_camera->service()->requestControl("com.nokia.Qt.QVideoRendererControl/1.0");
    if(control){
        control->setSurface(videoSurface);
        qDebug()<<control->surface();
    }
    //videoSurface->start(QVideoSurfaceFormat(QSize(480, 360), QVideoFrame::Format_RGB24));
    m_camera->start();
    QTimer *timer = new QTimer();
    timer->start(400);
    connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));
    connect(m_camera,SIGNAL(error(QCamera::Error)),this,SLOT(output(QCamera::Error)));

    qDebug()<<"error" << m_camera->error() <<" "<< m_camera->errorString();
    qDebug()<<"VS active"<< videoSurface->isActive();
    qDebug()<<"Available "<<m_camera->isAvailable();
    qDebug()<<"State " <<m_camera->state();
    qDebug()<<"Status " << m_camera->status();
    qDebug()<<"Locked " <<m_camera->lockStatus();
    qDebug()<<"Capture mode supported " << m_camera->isCaptureModeSupported(QCamera::CaptureStillImage);
}



void MyCamera::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    if (m_camera->status() == QCamera::UnloadedStatus)
        m_camera->start();
    qDebug()<<"Repaint";
    //if (videoSurface->backBuffer.format()!=QImage::Format_Invalid && !videoSurface->backBuffer.isNull()) {
        qDebug()<<"Image painted "<< videoSurface->backBuffer.size();
        painter->drawImage(this->boundingRect(),videoSurface->backBuffer);
    //}
    painter->setPen(Qt::black);
    painter->drawRect(0,0,300,300);
}

void MyCamera::output(QCamera::Error err)
{
    qDebug()<<err;
}

void MyCamera::repaint()
{
    this->update();
}


/*MySurface::MySurface(QObject *parent) : QAbstractVideoSurface(parent)
{
    currentFrame = QImage();
    //backBuffer = new QImage;
    m_imageFormat = QImage::Format_Invalid;
}

bool MySurface::isFormatSupported ( const QVideoSurfaceFormat & format ) const
{
    qDebug()<<"Format wird unterstützt...." << format;
    return true;
}

QList<QVideoFrame::PixelFormat> MySurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    QList<QVideoFrame::PixelFormat> formats;
    formats << QVideoFrame::Format_Invalid;
    formats << QVideoFrame::Format_YUV444;
    formats << QVideoFrame::Format_RGB24;
    formats << QVideoFrame::Format_RGB32;
    formats << QVideoFrame::Format_RGB24;
    formats << QVideoFrame::Format_YUYV;
    formats << QVideoFrame::Format_UYVY;
    formats << QVideoFrame::Format_YV12;
    formats << QVideoFrame::Format_AYUV444;
    formats << QVideoFrame::Format_YUV420P;
    formats << QVideoFrame::Format_Y16;
    formats << QVideoFrame::Format_Y8;
    formats << QVideoFrame::Format_IMC1;
    formats << QVideoFrame::Format_IMC2;
    formats << QVideoFrame::Format_IMC3;
    formats << QVideoFrame::Format_IMC4;
    formats << QVideoFrame::Format_AYUV444_Premultiplied;
    formats << QVideoFrame::Format_ARGB32_Premultiplied;
    formats << QVideoFrame::Format_RGB565;
    formats << QVideoFrame::Format_RGB555;
    formats << QVideoFrame::Format_ARGB8565_Premultiplied;
    formats << QVideoFrame::Format_BGRA32;
    formats << QVideoFrame::Format_BGRA32_Premultiplied;
    formats << QVideoFrame::Format_BGR32;
    formats << QVideoFrame::Format_BGR24;
    formats << QVideoFrame::Format_BGR565;
    formats << QVideoFrame::Format_BGR555;
    formats << QVideoFrame::Format_BGRA5658_Premultiplied;
    formats << QVideoFrame::Format_NV12;
    formats << QVideoFrame::Format_NV21;
    formats << QVideoFrame::Format_Jpeg;
    formats << QVideoFrame::Format_CameraRaw;
    formats << QVideoFrame::Format_AdobeDng;


    qDebug()<<"Format abgefragt...";
    return formats;
}

 QVideoSurfaceFormat MySurface::nearestFormat ( const QVideoSurfaceFormat & format ) const
 {
     qDebug()<< "Asking for nearest format...got"<<format;
     return QVideoSurfaceFormat ();
 }

bool MySurface::present(const QVideoFrame & frame)
{
    QVideoFrame newFrame(frame);
    newFrame.map(QAbstractVideoBuffer::ReadOnly);

    //Flip front and backbuffer
    //QImage *tmp = currentFrame;
    currentFrame = QImage(newFrame.bits(),newFrame.width(),newFrame.height(),m_imageFormat);
    //if(!currentFrame.save("testimage.jpg"))
    //  qDebug()<<"Could not save image";
    backBuffer = currentFrame.convertToFormat(QImage::Format_ARGB32);
    qDebug()<<"Presenting frame "<< frame.isMapped() << " "<< frame.isValid() << " " << frame.isReadable() << " " << frame.pixelFormat()<< " "<<frame.size();

    newFrame.unmap();
    qDebug()<<"Video frame unmapped";
    return true;
}

bool MySurface::start(const QVideoSurfaceFormat & format)
{
    qDebug()<< "Video Surface started";
    m_videoFormat = format;
    m_imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());

    QAbstractVideoSurface::start(format);
    return true;
}

void MySurface::stop()
{
    QAbstractVideoSurface::stop();
}*/
