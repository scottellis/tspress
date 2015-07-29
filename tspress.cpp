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

TsPress::TsPress(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);

    m_down.setX(-1);
    m_up.setX(-1);

    initStyleSheets();
	layoutWindow();

	connect(m_exitButton, SIGNAL(pressed()), SLOT(close()));
}

void TsPress::onPressed(int btn)
{
    m_which->setText(QString::number(btn));
    m_down.setX(-1);
    m_up.setX(-1);
    update();
}

void TsPress::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Down:" << event->x() << event->y();
    m_down = event->pos();
    m_up.setX(-1);
    update();
}

void TsPress::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Up  :" << event->x() << event->y();
    m_up = event->pos();
    update();
}

void TsPress::paintEvent(QPaintEvent *)
{
    if (m_down.x() < 0 && m_up.x() < 0)
        return;

    QPainter painter(this);

    if (m_down.x() >= 0 && m_down != m_up) {
        painter.drawLine(m_down.x() - 6, m_down.y(), m_down.x() + 6, m_down.y());
        painter.drawLine(m_down.x(), m_down.y() - 6, m_down.x(), m_down.y() + 6);
    }

    if (m_up.x() >= 0) {
        QPen pen;

        pen.setColor(Qt::red);
        painter.setPen(pen);

        painter.drawLine(m_up.x() - 6, m_up.y(), m_up.x() + 6, m_up.y());
        painter.drawLine(m_up.x(), m_up.y() - 6, m_up.x(), m_up.y() + 6);
    }
}

void TsPress::layoutWindow()
{
    QPushButton *btn;
	m_signalMap = new QSignalMapper(this);
	connect(m_signalMap, SIGNAL(mapped(int)), SLOT(onPressed(int)));

    for (int i = 0; i < 12; i++) {
        btn = new QPushButton(QString::number(i+1));
        btn->setFixedSize(60, 50);
        btn->setStyleSheet(m_btnStyle);
        m_signalMap->setMapping(btn, i+1);
		connect(btn, SIGNAL(pressed()), m_signalMap, SLOT(map()));
		m_btns.append(btn);
	}

    m_exitButton = new QPushButton("Exit");
    m_exitButton->setMinimumSize(60, 50);
    m_exitButton->setStyleSheet(m_btnStyle);

    m_which = new QLabel("#");
    m_which->setStyleSheet(m_lblStyle);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *btnLayout = new QHBoxLayout;

    for (int i = 0; i < 5; i++) {
        btnLayout->addWidget(m_btns.at(i));

        if (i < 4)
            btnLayout->addStretch();
    }

    mainLayout->addLayout(btnLayout);
    mainLayout->addStretch();

    btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_btns.at(5));
    btnLayout->addStretch();
    btnLayout->addWidget(m_exitButton);
    btnLayout->addStretch();
    btnLayout->addWidget(m_btns.at(6));
    mainLayout->addLayout(btnLayout);

    QHBoxLayout *outputLayout = new QHBoxLayout;
    outputLayout->addStretch();
    outputLayout->addWidget(m_which);
    outputLayout->addStretch();
 
    mainLayout->addSpacing(8);
    mainLayout->addLayout(outputLayout);
    mainLayout->addStretch();

    btnLayout = new QHBoxLayout;

    for (int i = 7; i < 12; i++) {
        btnLayout->addWidget(m_btns.at(i));

        if (i < 11)
            btnLayout->addStretch();
    }

    mainLayout->addLayout(btnLayout);

	QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

	setCentralWidget(widget);
    setStyleSheet(m_winStyle);
}

void TsPress::initStyleSheets()
{
    m_btnStyle = "background-color:  rgb(86, 104, 118);"
                 " color: white;"
                 " font-size: 14pt;"
                 " border-width: 2px;"
                 " border-radius: 10px;";

    m_lblStyle = "font-size: 28pt;"
                 " color: green;";

    m_winStyle = "background-color: rgb(220, 220, 220)";
}
