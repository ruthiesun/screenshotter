#include "camera.h"
#include <QGuiApplication>
#include <QScreen>
#include <QBoxLayout>
#include <iostream>

Camera::Camera(QWidget *parent, Qt::WindowFlags f) :  QDialog(parent) {
    button = new QPushButton("CAPTURE");
    prevPos = nullptr;
    setup();

    QObject::connect(this, &Camera::rejected,
                     this, &Camera::handleRejection);
}

QPoint* Camera::getPrevPos() {
    return prevPos;
}

void Camera::closeEvent(QCloseEvent *event) {
    delete prevPos;
    prevPos = new QPoint(this->pos());
}

void Camera::handleRejection() {
    closeEvent(nullptr);
}

void Camera::takePic() {
    closeEvent(nullptr);
    QRect dialogSize = this->grab().rect();
    QPoint topLeftGlobal = QWidget::mapToGlobal(this->geometry().topLeft());

    this->setVisible(false);
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QPixmap ss = QPixmap(screen->grabWindow(0));
        emit snapped(new QPixmap(ss.copy(topLeftGlobal.x(), topLeftGlobal.y(), dialogSize.width(), dialogSize.height())));
    }
    this->move(*prevPos);
    this->show();
}

void Camera::setup() {
    QObject::connect(button, &QPushButton::clicked,
                     this, &Camera::takePic);

    QSize fullSize = QGuiApplication::primaryScreen()->size();
    this->resize(fullSize.width()*0.8, fullSize.height()*0.8);
    this->setWindowOpacity(0.5);
    this->setModal(false);
    this->setSizeGripEnabled(true);
    this->setWindowTitle("Camera view");

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::BottomToTop, this);
    layout->addWidget(button, 0, Qt::AlignBottom);
}
