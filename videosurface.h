#ifndef NEWCAM_H
#define NEWCAM_H

#include <QAbstractVideoSurface>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>


class myVideoSurface : public QAbstractVideoSurface
{
        Q_OBJECT
public:
        myVideoSurface(QObject *parent = 0);
        bool present(const QVideoFrame &frame);
        QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType type=QAbstractVideoBuffer::NoHandle ) const;
        bool start(const QVideoSurfaceFormat &format);
        void stop();

        QImage backBuffer;
        QImage currentFrame;

private:
          QVideoFrame m_frame;
          QImage::Format m_imageFormat;
          QVideoSurfaceFormat m_videoFormat;

          //VideoSurfaceImageObserver *observer;
};

#endif // NEWCAM_H
