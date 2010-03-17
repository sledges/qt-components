/****************************************************************************
**
** Copyright (C) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the Qt Components project on Trolltech Labs.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 or 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QPROGRESSBARMODEL_H
#define QPROGRESSBARMODEL_H

#include <QtCore/qobject.h>
#include <QtDeclarative/qdeclarative.h>

class Q_GUI_EXPORT QProgressBarModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged);

public:
    QProgressBarModel(QObject *parent = 0);
    ~QProgressBarModel();

    int value() const;

Q_SIGNALS:
    void running();
    void paused();
    //void resumed();
    void canceled();
    void finished();
    void valueChanged(); //### ==running?

public Q_SLOTS:
    void start();
    void pause();
    void resume();
    void reset();
    void setValue(int value);

private:
    qreal m_progressValue;

};

QML_DECLARE_TYPE(QProgressBarModel)

#endif // QPROGRESSBARMODEL_H
