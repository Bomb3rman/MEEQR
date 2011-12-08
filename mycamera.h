#ifndef MYCAMERA_H
#define MYCAMERA_H

#include <QObject>
#include <QCamera>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>
#include <QImage>
#include <QAbstractVideoSurface>
#include <qdeclarative.h>
#include <QDeclarativeItem>
#include <videosurface.h>

class MyCamera : public QDeclarativeItem
{
    Q_OBJECT
public:
    explicit MyCamera(QDeclarativeItem *parent = 0);

protected:
    //void paintEvent(QPaintEvent *);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

signals:

public slots:
    void repaint();
    void output(QCamera::Error err);

private:
    QCamera *m_camera;
    myVideoSurface *videoSurface;

};

/*class MySurface : public QAbstractVideoSurface
{
public:
    MySurface(QObject *parent = 0);

    bool isFormatSupported ( const QVideoSurfaceFormat & format ) const;
    bool present(const QVideoFrame & frame);
    bool start(const QVideoSurfaceFormat & format);
    void stop();

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;

    QVideoSurfaceFormat nearestFormat ( const QVideoSurfaceFormat & format ) const;

    QImage currentFrame;
    QImage backBuffer;

    QImage::Format m_imageFormat;
    QVideoSurfaceFormat m_videoFormat;
};*/

#endif // MYCAMERA_H
