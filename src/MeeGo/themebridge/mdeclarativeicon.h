/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project on Qt Labs.
**
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions contained
** in the Technology Preview License Agreement accompanying this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
****************************************************************************/

#ifndef MDECLARATIVEICON_H
#define MDECLARATIVEICON_H

#include <QDeclarativeItem>

class QPixmap;

class MDeclarativeIcon : public QDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(QString iconId READ iconId WRITE setIconId NOTIFY iconIdChanged);

public:
    MDeclarativeIcon(QDeclarativeItem *parent = 0);
    virtual ~MDeclarativeIcon();

    QString iconId() const;
    void setIconId(const QString &iconId);

Q_SIGNALS:
    void iconIdChanged(QString iconId);

protected Q_SLOTS:
    void checkPendingPixmap();

protected:
    friend class MThemeBridge;

    void refreshPixmap();
    bool hasPendingPixmap();

    virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

    QString m_iconId;
    const QPixmap *m_icon;
    int m_pendingPixmap : 1;
};

#endif //MDECLARATIVEICON_H
