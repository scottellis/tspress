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

TsPress::TsPress(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);

	layoutWindow();

	connect(m_exitButton, SIGNAL(pressed()), SLOT(close()));
}

void TsPress::onPressed(int btn)
{
    m_output->setText(QString("Button : %1").arg(btn));
}

void TsPress::layoutWindow()
{
	m_exitButton = new QPushButton("Exit");
	m_exitButton->setMinimumSize(60, 40);

	m_signalMap = new QSignalMapper(this);
	connect(m_signalMap, SIGNAL(mapped(int)), SLOT(onPressed(int)));

	QHBoxLayout *btnLayout = new QHBoxLayout;

	for (int i = 0; i < 5; i++) {
		QPushButton *btn = new QPushButton(QString::number(i));
		btn->setFixedSize(50, 30);
		m_signalMap->setMapping(btn, i);
		connect(btn, SIGNAL(pressed()), m_signalMap, SLOT(map()));
		m_btns.append(btn);
		btnLayout->addWidget(btn);

		if (i < 4)
			btnLayout->addStretch();
	}

	QHBoxLayout *exitLayout = new QHBoxLayout;
	exitLayout->addStretch();
	exitLayout->addWidget(m_exitButton);
	exitLayout->addStretch();

    m_output = new QLabel;
   
    QHBoxLayout *outputLayout = new QHBoxLayout;
    outputLayout->addStretch();
    outputLayout->addWidget(m_output);
    outputLayout->addStretch();
 
	QVBoxLayout *vLayout = new QVBoxLayout;

	vLayout->addLayout(btnLayout);
	vLayout->addStretch();	
	vLayout->addLayout(exitLayout);
	vLayout->addStretch();
    vLayout->addLayout(outputLayout);

	QWidget *widget = new QWidget;
	widget->setLayout(vLayout);

	setCentralWidget(widget);
}

