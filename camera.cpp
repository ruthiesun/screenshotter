#include "camera.h"
#include <iostream>
#include <QGuiApplication>
#include <QScreen>

Camera::Camera(QWidget *parent, Qt::WindowFlags f) :  QDialog(parent){
    button = new QPushButton("TAKE PIC");
    QSize fullSize = QGuiApplication::primaryScreen()->size();
    this->resize(fullSize.width()*0.9, fullSize.height()*0.9);
    this->setSizeGripEnabled(true);
    this->setVisible(false);
}
