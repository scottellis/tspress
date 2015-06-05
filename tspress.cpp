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
#include <qdebug.h>

TsPress::TsPress(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);

	layoutWindow();

	connect(m_exitButton, SIGNAL(pressed()), SLOT(close()));
}

void TsPress::onPressed(int btn)
{
    m_which->setText(QString("Button: %1").arg(btn));
}

void TsPress::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Down:" << event->x() << event->y();
}

void TsPress::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Up  :" << event->x() << event->y();
}

void TsPress::layoutWindow()
{
    QPushButton *btn;
	m_signalMap = new QSignalMapper(this);
	connect(m_signalMap, SIGNAL(mapped(int)), SLOT(onPressed(int)));

    for (int i = 0; i < 12; i++) {
        btn = new QPushButton(QString::number(i+1));
        btn->setFixedSize(60, 40);
        m_signalMap->setMapping(btn, i+1);
		connect(btn, SIGNAL(pressed()), m_signalMap, SLOT(map()));
		m_btns.append(btn);
	}

    m_exitButton = new QPushButton("Exit");
    m_exitButton->setMinimumSize(60, 40);
    m_which = new QLabel("Click a button");
    m_which->setStyleSheet("font-size: 18px;");

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
}
