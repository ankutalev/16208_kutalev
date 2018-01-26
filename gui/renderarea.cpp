/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "renderarea.h"

#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include<QWindow>
#include <QScrollBar>
#include<info.h>
#include "/home/ulyssess/qtProjects/testGUI/controller.h"
//! [0]
RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{

     setBackgroundRole(QPalette::Shadow);
     setAutoFillBackground(true);
     //scroll = parent;

}
//! [0]
void RenderArea::speedUpClick() {
    std::cout<<" STATES FOR DRAWING= " << StatesForDrawing <<std::endl;
    if (StatesForDrawing+10> UpLimit)
        StatesForDrawing = UpLimit;
    else
    StatesForDrawing+=10;
}
void RenderArea::speedDownClick() {
     std::cout<<" STATES FOR DRAWING= " << StatesForDrawing <<std::endl;
    if (StatesForDrawing-10<DownLimit)
        StatesForDrawing = DownLimit;
    else
        StatesForDrawing-=10;
}

void RenderArea::tick() {
    std::cout<<"huy";
    Fields.clear();
    std::pair <int, bool> x {-1,true};
    for (int i = 0; i< Size;i++) {
        Fields.push_back (x);
    }
}

void RenderArea::ButtonClick() {
    drawing=!drawing;
}

//! [1]
//!
QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}
//! [1]

//! [2]
QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}
//! [2]

//! [3]
void RenderArea::setShape(Shape shape)
{
    update();
}
//! [3]

//! [4]
//!
void RenderArea::setPen(const QPen &pen)
{
    update();
}
//! [4]

//! [5]
void RenderArea::setBrush(const QBrush &brush)
{
    update();
}
//! [5]
//! [6]
void RenderArea::setAntialiased(bool antialiased)
{
    update();
}
//! [6]

//! [7]
void RenderArea::setTransformed(bool transformed)
{
    update();
}
//! [7]

//! [8]
void RenderArea::ControlCommand(int Warrior, int Address, bool isDanger) {
   // if(drawing) {
        drawing = true;
         States++;
         Fields[Address] = {Warrior,isDanger};
        if(States==StatesForDrawing) {
            repaint();
            States = 0;
        }
}
void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    if (drawing) {
    QColor c;
    QPainter p (this);
    int warNum;
   for (int i = 0; i < Size;i++) {
       warNum =std::get<0>(Fields[i]);
       if( warNum== -1)
            c = Qt::black;
        else {
          c = (std::get<1>(Fields[i])) ? Colours[warNum*2+1] : Colours[warNum*2];
       }
        QPen x(c,5,Qt::SolidLine);
        p.setPen(x);
        p.fillRect(widthRange*(i%CellsInWidth)+1,heightRange*(i/CellsInWidth)  ,CellSize,CellSize,c);

        }
    }
}

void RenderArea::mouseDoubleClickEvent(QMouseEvent *event) {
    if (drawing && event->button()==Qt::LeftButton) {
        if (event->x() % widthRange <= CellSize && event->y() % heightRange <= CellSize ) {
            int CellNumber = event->x()/ widthRange + (event->y() / heightRange)*CellsInWidth;
            std::string WarriorName = controller::get_instance()->getWName(std::get<0>(Fields[CellNumber]));
            std::shared_ptr<infoWindow> info(new infoWindow());
            info.get()->setWindowTitle("Info about cell");
            info.get()->setName(WarriorName);
            info.get()->setCommand(controller::get_instance()->getCommandName(CellNumber));
            info.get()->setPosition(CellNumber+1);
            info.get()->setDanger(Fields[CellNumber].second);
            info.get()->setGeometry(event->x(),event->y(),200,200);
            info.get()->setBackgroundRole(QPalette::Shadow);
            info.get()->setAutoFillBackground(true);
            infos.push_back(info);
            info->show();
        }
    }
}

void RenderArea::wheelEvent(QWheelEvent *event) {
    const int degrees = event->delta() / 8;
    int steps = degrees / 15;
    int scaleFactor = 1;
    widthRange = CellSize +2;
    heightRange = CellSize +4;
    if(steps > 0) {
        CellSize = (CellSize >= maxSize) ? CellSize : (CellSize + scaleFactor);
        widthRange = (CellSize >= maxSize) ? widthRange : (widthRange + scaleFactor);
        heightRange = (CellSize >= maxSize) ? heightRange : (heightRange + scaleFactor);
        if(size().width()> widthRange*CellsInWidth)
            widthRange = size().width()/ CellsInWidth +1;
        if(size().height()> heightRange*StringsInHeight)
            widthRange = size().height()/ StringsInHeight +1;
    }
    else {
        CellSize = (CellSize <= minSize) ? CellSize : (CellSize - scaleFactor);
        widthRange = (CellSize <= minSize) ? widthRange : (widthRange - scaleFactor);
        heightRange = (CellSize <= minSize) ? heightRange : (heightRange - scaleFactor);
        //setMinimumSize(widthRange*CellsInWidth,heightRange*StringsInHeight);
        if(size().width()> widthRange*CellsInWidth)
            widthRange = size().width()/ CellsInWidth +1;
        if(size().height()> heightRange*StringsInHeight)
            widthRange = size().height()/ StringsInHeight +1;
    }

    repaint();
}
void RenderArea::setScroll(QScrollArea *sc) {
    scroll = sc;
}

void RenderArea::mouseMoveEvent(QMouseEvent *event) {
    QPoint delta = event->pos() - last;
    if (delta.x() < -30 &&  scroll->horizontalScrollBar()->value()!= scroll->horizontalScrollBar()->maximum()) {
        scroll->horizontalScrollBar()->setValue(scroll->horizontalScrollBar()->value() +150);
    }
    else if (delta.x()>30 &&scroll->horizontalScrollBar()->value()!= scroll->horizontalScrollBar()->minimum())
         scroll->horizontalScrollBar()->setValue(scroll->horizontalScrollBar()->value() -150);
    if (delta.y() < -30 && scroll->verticalScrollBar()->value()!= scroll->verticalScrollBar()->maximum())
         scroll->verticalScrollBar()->setValue(scroll->verticalScrollBar()->value() +150);
    else if (delta.y()>30 && scroll->verticalScrollBar()->value()!= scroll->verticalScrollBar()->minimum())
         scroll->verticalScrollBar()->setValue(scroll->verticalScrollBar()->value() -150);

}
void RenderArea::mousePressEvent(QMouseEvent *event) {
    if(event->button()==Qt::LeftButton)
        last = event->pos();
    else
        infos.clear();
}

int RenderArea::getAreaWidth() {
    return widthRange*CellsInWidth;
}
int RenderArea::getAreaHeight() {
    return heightRange* StringsInHeight;
}
void RenderArea::setSize(int size) {
    Size = size;
    StringsInHeight = Size / CellsInWidth +1;
    std::pair <int, bool> x {-1,true};
    Fields.clear();
    for (int i = 0; i< Size;i++) {
        Fields.push_back (x);
    }
    setMinimumSize(widthRange*CellsInWidth,heightRange*StringsInHeight);
}
//! [13]
