/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

import Qt 4.7
import "." 1.0

Item {
    id: window

    property bool inPortrait: height > width

    signal orientationChangeAboutToStart
    signal orientationChangeStarted
    signal orientationChangeFinished

    // Deprecated, use Dialog.open() instead
    function showPopup(component) {
        console.log("warning: use of deprecated method showPopup, use Dialog.open() instead")
        var popupObj = component.createObject(window);
        if (popupObj == null)
            return false;
        popupObj.open();
       return true;
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

    Binding { target: window; property: "height"; value: screen.height; when: screen.height > 0 }
    Binding { target: window; property: "width"; value: screen.width; when: screen.width > 0 }

    Connections {
        target: screen
        onOrientationChanged: window.orientationChangeFinished()
        onDisplayChanged: {
            window.orientationChangeAboutToStart()
            window.orientationChangeStarted()
        }
    }
}
