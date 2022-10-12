#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QGLWidget>
#include <QImage>

#include <QQueue>
#include <QTimer>
#include <QMutex>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);

    void UpdateImage(const QImage &image);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
private:
    void initTextures();
    void initShaders();
    void setImage(const QImage &image);
private:
    QVector<QVector3D> vertices;
    QVector<QVector2D> texCoords;
    QOpenGLShaderProgram program;
    QOpenGLTexture *texture;
    QMatrix4x4 projection;

    QMutex m_dataMutex;
    //QQueue<QImage> allImages;
    QImage varShowImage;
    QTimer timer;
};

#endif // MYGLWIDGET_H
