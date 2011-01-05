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

#ifndef SSTYLEWRAPPER_P_H
#define SSTYLEWRAPPER_P_H

#include "sstylewrapper.h"

class SStyleWrapperPrivate
{
    Q_DECLARE_PUBLIC(SStyleWrapper)

public:
    SStyleWrapperPrivate(SStyleWrapper *qq);
    ~SStyleWrapperPrivate();

    QFont fetchFont(SStyleWrapper::FontRole role, qreal textPaneHeight = -1) const;
    QColor fetchThemeColor(const QString &colorName) const;
    qreal fetchLayoutParameter(const QString &layoutParameterName) const;
    void displayChanged();
    void play(int effect);
    void updateStyle();
    void invalidateStyle();
    void initScreenPtr() const;

    QVariant buttonProperty(const QString &propertyName) const;
    QVariant textEditProperty(const QString &propertyName) const;
    QVariant titleBarProperty(const QString &propertyName) const;
    QVariant listItemProperty(const QString &propertyName) const;
    QVariant basicListItemImageProperty(const QString &propertyName) const;
    QVariant pageContainerProperty(const QString &propertyName) const;
    QVariant checkBoxProperty(const QString &propertyName) const;
    QVariant dialogProperty(const QString &propertyName) const;
    QVariant scrollBarProperty(const QString &propertyName) const;
    QVariant progressBarProperty(const QString &propertyName) const;
    QVariant radioButtonProperty(const QString &propertyName) const;
    QVariant toolTipProperty(const QString &propertyName) const;

    void _q_desktopWorkareaChanged();
    void _q_displayChanged();

    SStyleWrapper *q_ptr;
    QString mode;
    QString styleClass;
    QString styleType;
    QString styleObjectName;

private:
    // Helpers
    QVariant buttonPropertyBackground() const;
    QVariant buttonPropertyTextColor() const;
    QVariant textEditPropertyFrame() const;
    QVariant listItemPropertyMainTextColor() const;
    QVariant listItemPropertySubTextColor() const;

private:
    mutable bool updateOnScreenAreaChange;
    mutable bool listeningDisplayChange;
};

#endif // SSTYLEWRAPPER_P_H