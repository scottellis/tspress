/*
 * Copyright (c) 2015, Jumpnow Technologies, LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "tspress.h"
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qevent.h>
#include <qpainter.h>

#include <qdebug.h>

#define MIN_WIDTH_FOR_BUTTONS 400

TsPress::TsPress(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    setAttribute(Qt::WA_AcceptTouchEvents);

    m_down.setX(-1);
    m_up.setX(-1);

    // setFixedSize(480, 800);

    layoutWindow();

    connect(m_exitButton, SIGNAL(pressed()), SLOT(close()));
}

void TsPress::onPressed(int btn)
{
    m_which->setText(QString("Btn: %1").arg(btn));
    m_down.setX(-1);
    m_up.setX(-1);
    update();
}

void TsPress::mousePressEvent(QMouseEvent *event)
{
    m_which->setText(QString("Down: %1, %2").arg(event->pos().x()).arg(event->pos().y()));
    m_down = event->pos();
    m_up.setX(-1);
    update();
}

void TsPress::mouseReleaseEvent(QMouseEvent *event)
{
    m_which->setText(QString("Up: %1, %2").arg(event->pos().x()).arg(event->pos().y()));
    m_up = event->pos();
    update();
}

void TsPress::paintEvent(QPaintEvent *)
{
    QPen pen;

    QPainter painter(this);

    pen.setColor(Qt::black);
    painter.setPen(pen);

    drawCalTargets(&painter);

    if (m_down.x() >= 0 && m_down != m_up) {
        pen.setColor(Qt::blue);
        painter.setPen(pen);
        painter.drawLine(m_down.x() - 8, m_down.y(), m_down.x() + 8, m_down.y());
        painter.drawLine(m_down.x(), m_down.y() - 8, m_down.x(), m_down.y() + 8);
    }

    if (m_up.x() >= 0) {
        pen.setColor(Qt::red);
        painter.setPen(pen);
        painter.drawLine(m_up.x() - 8, m_up.y(), m_up.x() + 8, m_up.y());
        painter.drawLine(m_up.x(), m_up.y() - 8, m_up.x(), m_up.y() + 8);
    }
}

void TsPress::drawCross(QPainter *painter, int x, int y)
{
    painter->drawLine(x - 5, y, x + 5, y);
    painter->drawLine(x, y - 5, x, y + 5);
}

void TsPress::drawCalTargets(QPainter *painter)
{
    int h = height();
    int w = width();

    for (int x = 100; x < (w - 70); x += 100) {
        for (int y = 100; y < (h - 70); y += 100) {
            drawCross(painter, x, y);
        }
    }
}

void TsPress::layoutWindow()
{
    QHBoxLayout *btnLayout;
    QPushButton *btn;

    int w = width();

    if (w > MIN_WIDTH_FOR_BUTTONS) {
        for (int i = 0; i < 8; i++) {
            btn = new QPushButton(QString::number(i+1));
            btn->setFixedSize(50, 40);
            connect(btn, &QPushButton::pressed, this, [this, i]{ onPressed(i+1); });
            m_btns.append(btn);
        }
    }

    m_exitButton = new QPushButton("Exit");
    m_exitButton->setMinimumSize(72, 40);

    m_which = new QLabel("#");
    m_which->setStyleSheet("font-size: 20pt; color: green;");

    QVBoxLayout *mainLayout = new QVBoxLayout;

    if (w > MIN_WIDTH_FOR_BUTTONS) {
        btnLayout = new QHBoxLayout;

        for (int i = 0; i < 3; i++) {
            btnLayout->addWidget(m_btns.at(i));

            if (i < 2) {
                btnLayout->addStretch();
            }
        }

        mainLayout->addLayout(btnLayout);
    }

    mainLayout->addStretch();

    btnLayout = new QHBoxLayout;

    if (w > MIN_WIDTH_FOR_BUTTONS) {
        btnLayout->addWidget(m_btns.at(3));
    }

    btnLayout->addStretch();
    btnLayout->addWidget(m_exitButton);
    btnLayout->addStretch();

    if (width() > MIN_WIDTH_FOR_BUTTONS) {
        btnLayout->addWidget(m_btns.at(4));
    }

    mainLayout->addLayout(btnLayout);

    if (w > MIN_WIDTH_FOR_BUTTONS) {
        QHBoxLayout *outputLayout = new QHBoxLayout;
        outputLayout->addStretch();
        outputLayout->addWidget(m_which);
        outputLayout->addStretch();

        mainLayout->addSpacing(8);
        mainLayout->addLayout(outputLayout);
        mainLayout->addStretch();

        btnLayout = new QHBoxLayout;

        for (int i = 5; i < 8; i++) {
            btnLayout->addWidget(m_btns.at(i));

            if (i < 7) {
                btnLayout->addStretch();
            }
        }

        mainLayout->addLayout(btnLayout);
    }
    else {
        mainLayout->addStretch();
    }

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);
}

namespace  {

QString toString(Qt::TouchPointState state){
    switch (state) {
    case Qt::TouchPointPressed: return "Pressed";
    case Qt::TouchPointMoved: return "Moved";
    case Qt::TouchPointStationary: return "Stationary";
    case Qt::TouchPointReleased: return "Released";
    default: return "???";
    }
}

}

bool TsPress::event(QEvent* event)
{
    QString type;

    switch (event->type()) {
    case QEvent::TouchBegin: type ="Begin"; break;
    case QEvent::TouchUpdate:  type = "Update"; break;
    case QEvent::TouchEnd:  type ="End"; break;
    default: return QMainWindow::event(event);
    }

    const auto e = static_cast<QTouchEvent*>(event);
    qInfo() << e << ":" << e->type() << e->device() << e->target() << e->window() << "time:" << e->timestamp()
            << "\n   points" << e->touchPoints()
            << "\n   states:" << e->touchPointStates()
            << "\n   modifiers" << e->modifiers();

    auto str = QString("%1 %2 (%3 point(s))\n").arg(type, e->device()->name()).arg(e->touchPoints().count());

    for (const auto &p: e->touchPoints()) {
        str += QString("(%0,%1 %2)").arg(p.pos().x()).arg(p.pos().y()).arg(toString(p.state()));
    }
    m_which->setText(str);
    return true;

}
