#include <QtGui/QApplication>
#include <QZXing.h>
#include "qmlapplicationviewer.h"
#include <QDebug>
#include <mycamera.h>
#include <videosurface.h>
#include <QCamera>
#include <QVideoRendererControl>

int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    //QZXing::registerQMLTypes();

    qmlRegisterType<MyCamera>("XZCamera", 1, 0, "XZCamera");

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationLockPortrait);
    viewer->setMainQmlFile(QLatin1String("qml/MeeQR/main.qml"));
    viewer->showExpanded();

    //QZXing::engine = viewer->engine();

    //qDebug()<<viewer->engine()->imageProvider("camera");

    /*QCamera *camera_ = new QCamera;
    myVideoSurface *surface = new myVideoSurface();

    QVideoRendererControl *control = qobject_cast<QVideoRendererControl *>(
                            camera_->service()->requestControl("com.nokia.Qt.QVideoRendererControl/1.0"));
    if(control){
            control->setSurface(surface);
    }

    surface->start(QVideoSurfaceFormat(QSize(480, 360), QVideoFrame::Format_RGB24));
    camera_->start();
*/
    return app->exec();
}
