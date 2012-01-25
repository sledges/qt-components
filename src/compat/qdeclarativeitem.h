/*
    Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef QDECLARATIVEITEM_H
#define QDECLARATIVEITEM_H

#include "qgraphicsobject.h"

struct CompatQDeclarativeItem : public CompatQGraphicsObject
{
    CompatQDeclarativeItem(CompatQDeclarativeItem *parent = 0) : CompatQGraphicsObject(parent) {}

    void setZValue(qreal value) { setZ(value); }

    void setFlag(DeprecatedGraphicsItemFlags flag, bool enabled = true)
    {
        switch (flag) {
            case ItemHasNoContents:
                CompatQGraphicsObject::setFlag(ItemHasContents, !enabled);
                break;
            default:
                Q_ASSERT_X(false, "CompatQDeclarativeItem", "Unknown deprecated enum");
        }
    }

    CompatQDeclarativeItem* parentItem() const
    {
        return static_cast<CompatQDeclarativeItem*>(CompatQGraphicsObject::parentItem());
    }
};

typedef QQuickItem::ItemChange GraphicsItemChange;

#endif
