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

#include <QtTest/QtTest>
#include <QGraphicsObject>
#include <QFont>
#include <QtCore/qmath.h>
#include <QIntValidator>
#include "tst_quickcomponentstest.h"

static const QString EDITOR_STYLE_FONT = "Nokia Sans,-1,20,5,50,0,0,0,0,0";

class tst_quickcomponentstextarea : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void validateSymbianProperties();
    void defaultPropertyValues();
    void placeholderText();
    void placeholderTextAndPresetText();
    void placeholderTextAndReadOnly();
    void placeholderTextAndRichText();
    void implicitSize();
    void font();
    void focus();
    void cursorRectangle();

private:
    QObject* m_componentObject;
    QScopedPointer<QDeclarativeView> m_view;
};

void tst_quickcomponentstextarea::initTestCase()
{
    QString errors;
    m_componentObject = tst_quickcomponentstest::createComponentFromFile("tst_quickcomponentstextarea.qml", &errors);
    QVERIFY2(m_componentObject, qPrintable(errors));

    m_view.reset(tst_quickcomponentstest::createDeclarativeView("tst_quickcomponentstextarea.qml"));
    QTest::qWaitForWindowShown(m_view.data());
    QVERIFY(m_view.data());
    QVERIFY(m_view->rootObject());
    QTRY_COMPARE(QApplication::activeWindow(), static_cast<QWidget *>(m_view.data()));
}

void tst_quickcomponentstextarea::validateSymbianProperties()
{
    QGraphicsObject *textArea = m_componentObject->findChild<QGraphicsObject*>("textArea");
    QVERIFY(textArea);
    QVariant property;

    //placeholderText
    property = textArea->property("placeholderText");
    QVERIFY(property.isValid());
    QVERIFY(property.canConvert(QVariant::String));

    // ImplicitHeight
    property = textArea->property("implicitHeight");
    QVERIFY(property.isValid());
    QVERIFY(property.canConvert(QVariant::Double));

    // ImplicitWidth
    property = textArea->property("implicitWidth");
    QVERIFY(property.isValid());
    QVERIFY(property.canConvert(QVariant::Double));

    // maxImplicitHeight
    property = textArea->property("maxImplicitHeight");
    QVERIFY(property.isValid());
    QVERIFY(property.canConvert(QVariant::Double));

    // maxImplicitWidth
    property = textArea->property("maxImplicitWidth");
    QVERIFY(property.isValid());
    QVERIFY(property.canConvert(QVariant::Double));
}

void tst_quickcomponentstextarea::defaultPropertyValues()
{
    QGraphicsObject *textArea = m_componentObject->findChild<QGraphicsObject*>("textArea");
    QGraphicsObject *placeHolder = m_view->rootObject()->findChild<QGraphicsObject*>("placeholder");
    QVERIFY(textArea);
    QVERIFY(placeHolder);
    QVariant property;

    // Font
    property = textArea->property("font");
    QCOMPARE(property.toString(), EDITOR_STYLE_FONT);

    // CursorPosition
    property = textArea->property("cursorPosition");
    int cursorPosition = property.toInt();
    QCOMPARE(cursorPosition, 0);

    // HorizontalAlignment
    property = textArea->property("horizontalAlignment");
    Qt::Alignment horizontalAlignment = static_cast<Qt::Alignment>(property.toInt());
    QCOMPARE(horizontalAlignment, Qt::AlignLeft);

    // VerticalAlignment
    property = textArea->property("verticalAlignment");
    Qt::Alignment verticalAlignment = static_cast<Qt::Alignment>(property.toInt());
    QCOMPARE(verticalAlignment, Qt::AlignTop);

    // ReadOnly
    property = textArea->property("readOnly");
    bool readOnly = property.toBool();
    QCOMPARE(readOnly, false);

    // SelectedText
    property = textArea->property("selectedText");
    QString selectedText = property.toString();
    QVERIFY(selectedText.isEmpty());

    // SelectionEnd
    property = textArea->property("selectionEnd");
    int selectionEnd = property.toInt();
    QCOMPARE(selectionEnd, 0);

    // SelectionStart
    property = textArea->property("selectionStart");
    int selectionStart = property.toInt();
    QCOMPARE(selectionStart, 0);

    // Text
    property = textArea->property("text");
    QString text = property.toString();
    QVERIFY(text.isEmpty());

    // TextFormat
    property = textArea->property("textFormat");
    Qt::TextFormat textFormat = static_cast<Qt::TextFormat>(property.toInt());
    QCOMPARE(textFormat, Qt::AutoText);

    // WrapMode
    property = textArea->property("wrapMode");
    QTextOption::WrapMode wrapMode = static_cast<QTextOption::WrapMode>(property.toInt());
    QCOMPARE(wrapMode, QTextOption::WrapAtWordBoundaryOrAnywhere);

    //placeholderText
    property = textArea->property("placeholderText");
    QString promptText = property.toString();
    QVERIFY(promptText.isEmpty());
    property = placeHolder->property("font");
    QCOMPARE(property.toString(), EDITOR_STYLE_FONT); // same as editor's font
}

void tst_quickcomponentstextarea::placeholderText()
{
    QGraphicsObject *textArea = m_view->rootObject()->findChild<QGraphicsObject*>("textArea");
    QGraphicsObject *button = m_view->rootObject()->findChild<QGraphicsObject*>("click");
    QGraphicsObject *textEdit = m_view->rootObject()->findChild<QGraphicsObject*>("textEdit");
    QGraphicsObject *placeHolder = m_view->rootObject()->findChild<QGraphicsObject*>("placeholder");

    QVERIFY(textArea);
    QVERIFY(button);
    QVERIFY(textEdit);
    QVERIFY(placeHolder);

    textArea->setProperty("text", QString(""));
    textArea->setProperty("placeholderText", QString("placeholderText"));

    // Place holder should be visible
    QVERIFY(placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QCOMPARE(textArea->property("text").toString(), QString(""));

    // Focus textArea
    textArea->setFocus(Qt::OtherFocusReason);
    QVERIFY(!placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QCOMPARE(textArea->property("text").toString(), QString(""));

    //Type something
    textArea->setProperty("text", QString("Test"));
    QVERIFY(!placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QCOMPARE(textArea->property("text").toString(), QString("Test"));

    // Focus another component
    button->setFocus(Qt::OtherFocusReason);

    QVERIFY(!placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QCOMPARE(textArea->property("text").toString(), QString("Test"));

    // Focus back, empty text and focus out again
#ifdef Q_OS_SYMBIAN
    // To avoid virtual keyboard on symbian
    textArea->setProperty("readOnly", QVariant(true));
#endif
    textArea->setFocus(Qt::OtherFocusReason);
    textArea->setProperty("text", QString(""));
    button->setFocus(Qt::OtherFocusReason);

    QVERIFY(placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QCOMPARE(textArea->property("text").toString(), QString(""));
#ifdef Q_OS_SYMBIAN
    // To avoid virtual keyboard on symbian
    textArea->setProperty("readOnly", QVariant(false));
#endif

    // Empty prompt text
    textArea->setProperty("placeholderText", QString(""));
    QVERIFY(!placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString(""));
    QCOMPARE(textArea->property("text").toString(), QString(""));
}

void tst_quickcomponentstextarea::placeholderTextAndPresetText()
{
    QGraphicsObject *textArea = m_view->rootObject()->findChild<QGraphicsObject*>("textArea");
    QGraphicsObject *button = m_view->rootObject()->findChild<QGraphicsObject*>("click");
    QGraphicsObject *textEdit = m_view->rootObject()->findChild<QGraphicsObject*>("textEdit");
    QGraphicsObject *placeHolder = m_view->rootObject()->findChild<QGraphicsObject*>("placeholder");

    QVERIFY(textArea);
    QVERIFY(button);
    QVERIFY(textEdit);
    QVERIFY(placeHolder);

    textArea->setProperty("text", QString("Preset text here."));
    textArea->setProperty("placeholderText", QString("placeholderText"));

    // Preset text should displayed
    QVERIFY(!placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QCOMPARE(textArea->property("text").toString(), QString("Preset text here."));

    // Focus textArea
    textArea->setFocus(Qt::OtherFocusReason);

    QVERIFY(!placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QCOMPARE(textArea->property("text").toString(), QString("Preset text here."));

    // Focus out
    button->setFocus(Qt::OtherFocusReason);

    QVERIFY(!placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QCOMPARE(textArea->property("text").toString(), QString("Preset text here."));

    // Focus back and empty text and focus out again
#ifdef Q_OS_SYMBIAN
    // To avoid virtual keyboard on symbian
    textArea->setProperty("readOnly", QVariant(true));
#endif
    textArea->setFocus(Qt::OtherFocusReason);
    textArea->setProperty("text", QString(""));
    button->setFocus(Qt::OtherFocusReason);

    QVERIFY(placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QCOMPARE(textArea->property("text").toString(), QString(""));
#ifdef Q_OS_SYMBIAN
    // To avoid virtual keyboard on symbian
    textArea->setProperty("readOnly", QVariant(false));
#endif

    // Empty prompt text
    textArea->setProperty("placeholderText", QString(""));
    QVERIFY(!placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString(""));
    QCOMPARE(textArea->property("text").toString(), QString(""));
}

void tst_quickcomponentstextarea::placeholderTextAndReadOnly()
{
    QGraphicsObject *textArea = m_view->rootObject()->findChild<QGraphicsObject*>("textArea");
    QGraphicsObject *button = m_view->rootObject()->findChild<QGraphicsObject*>("click");
    QGraphicsObject *textEdit = m_view->rootObject()->findChild<QGraphicsObject*>("textEdit");
    QGraphicsObject *placeHolder = m_view->rootObject()->findChild<QGraphicsObject*>("placeholder");

    QVERIFY(textArea);
    QVERIFY(button);
    QVERIFY(textEdit);
    QVERIFY(placeHolder);

    textArea->setProperty("text", QString(""));
    textArea->setProperty("placeholderText", QString("placeholderText"));
    textArea->setProperty("readOnly", QVariant(true));

    // Prompt should be visible
    QVERIFY(placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QCOMPARE(textArea->property("text").toString(), QString(""));

    // Focus textArea
    textArea->setFocus(Qt::OtherFocusReason);

    QVERIFY(!placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QCOMPARE(textArea->property("text").toString(), QString(""));

    // Focus out
    button->setFocus(Qt::OtherFocusReason);
}

// rich text format is a special case, since in that case text property contains empty html tags
void tst_quickcomponentstextarea::placeholderTextAndRichText()
{
    QGraphicsObject *textArea = m_view->rootObject()->findChild<QGraphicsObject*>("textArea");
    QGraphicsObject *button = m_view->rootObject()->findChild<QGraphicsObject*>("click");
    QGraphicsObject *textEdit = m_view->rootObject()->findChild<QGraphicsObject*>("textEdit");
    QGraphicsObject *placeHolder = m_view->rootObject()->findChild<QGraphicsObject*>("placeholder");

    QVERIFY(textArea);
    QVERIFY(button);
    QVERIFY(textEdit);
    QVERIFY(placeHolder);

    textArea->setProperty("text", QString(""));
    textArea->setProperty("placeholderText", QString("placeholderText"));
    textArea->setProperty("textFormat", QVariant(Qt::RichText));

    // Prompt should be visible
    QVERIFY(placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QVERIFY(textArea->property("text").toString().length() > 0); // contains empty html tags

    // Focus textArea
    textArea->setFocus(Qt::OtherFocusReason);

    QVERIFY(!placeHolder->property("visible").toBool());
    QVERIFY(textEdit->property("visible").toBool());
    QCOMPARE(textArea->property("placeholderText").toString(), QString("placeholderText"));
    QVERIFY(textArea->property("text").toString().length() > 0); // contains empty html tags
}

void tst_quickcomponentstextarea::implicitSize()
{
    QGraphicsObject *textArea = m_componentObject->findChild<QGraphicsObject*>("textArea");
    QVERIFY(textArea);

    QFontMetricsF metrics(textArea->property("font").value<QFont>());
    qreal parentHeight = m_componentObject->property("height").toReal();
    qreal parentWidth = m_componentObject->property("width").toReal();
    qreal implicitHeight = textArea->property("implicitHeight").toReal();
    qreal implicitWidth = textArea->property("implicitWidth").toReal();
    qreal maxImplicitHeight = textArea->property("maxImplicitHeight").toReal();
    qreal maxImplicitWidth = textArea->property("maxImplicitWidth").toReal();

    QVERIFY(implicitHeight >= metrics.height());
    QVERIFY(implicitWidth >= metrics.width("                    "));
    QCOMPARE(maxImplicitHeight, parentHeight - textArea->property("y").toReal());
    QCOMPARE(maxImplicitWidth, parentWidth - textArea->property("x").toReal());

    textArea->setProperty("text", QString("test"));
    implicitHeight = textArea->property("implicitHeight").toReal();
    implicitWidth = textArea->property("implicitWidth").toReal();

    QVERIFY(implicitHeight >= metrics.height());
    QVERIFY(implicitWidth >= metrics.width("test"));

    // Type over parent width
    do {
        textArea->setProperty("text", textArea->property("text").toString() + QString("a"));
    } while (qFuzzyCompare(implicitHeight, textArea->property("implicitHeight").toReal()));

    int pos = 0;
    int width = qCeil(textArea->property("width").toReal());
    QIntValidator range(width - qCeil(metrics.width("a")), qCeil(maxImplicitWidth), 0);
    QString impWidth = textArea->property("implicitWidth").toString();
    QCOMPARE(range.validate(impWidth,pos), QValidator::Acceptable);

    // Type some more
    textArea->setProperty("text", textArea->property("text").toString() + QString("a"));
    implicitWidth = textArea->property("implicitWidth").toReal();
    QVERIFY(implicitWidth <= maxImplicitWidth);

    // Type until parent height
    do {
        textArea->setProperty("text", textArea->property("text").toString() + QString("Aaaaaaaaaa"));
        implicitHeight = textArea->property("implicitHeight").toReal();
        QVERIFY(implicitHeight >= metrics.height());
    } while (implicitHeight < maxImplicitHeight);
    QCOMPARE(implicitHeight, textArea->property("height").toReal());

    // Type some more
    textArea->setProperty("text", textArea->property("text").toString() + QString("A"));
    implicitHeight = textArea->property("implicitHeight").toReal();
    QCOMPARE(implicitHeight, maxImplicitHeight);
}

void tst_quickcomponentstextarea::font()
{
    QGraphicsObject *textArea = m_view->rootObject()->findChild<QGraphicsObject*>("textArea");
    QGraphicsObject *textEdit = m_view->rootObject()->findChild<QGraphicsObject*>("textEdit");
    QGraphicsObject *placeHolder = m_view->rootObject()->findChild<QGraphicsObject*>("placeholder");
    QVERIFY(textArea);
    QVERIFY(textEdit);
    QVERIFY(placeHolder);

    QFont font;
    font.setBold(true);
    font.setPixelSize(25);
    font.setFamily("Arial");
    textArea->setProperty("font", font);

    QCOMPARE(font, textArea->property("font").value<QFont>());
    QCOMPARE(font, textEdit->property("font").value<QFont>());
    QCOMPARE(font, placeHolder->property("font").value<QFont>());
}

void tst_quickcomponentstextarea::focus()
{
    QGraphicsObject *textArea = m_view->rootObject()->findChild<QGraphicsObject*>("textArea");
    QGraphicsObject *textEdit = m_view->rootObject()->findChild<QGraphicsObject*>("textEdit");
    QGraphicsObject *button = m_view->rootObject()->findChild<QGraphicsObject*>("click");
    QVERIFY(textArea);
    QVERIFY(textEdit);
    QVERIFY(button);

    button->setFocus(Qt::OtherFocusReason);

    QVERIFY(!textArea->property("focus").toBool());
    QVERIFY(!textArea->property("activeFocus").toBool());
    QVERIFY(textEdit->property("focus").toBool());
    QVERIFY(!textEdit->property("activeFocus").toBool());

    textArea->setFocus(Qt::OtherFocusReason);

    QVERIFY(textArea->property("focus").toBool());
    QVERIFY(textArea->property("activeFocus").toBool());
    QVERIFY(textEdit->property("focus").toBool());
    QVERIFY(textEdit->property("activeFocus").toBool());

    button->setFocus(Qt::OtherFocusReason);

    QVERIFY(!textArea->property("focus").toBool());
    QVERIFY(!textArea->property("activeFocus").toBool());
    QVERIFY(textEdit->property("focus").toBool());
    QVERIFY(!textEdit->property("activeFocus").toBool());

    textArea->setFocus(Qt::OtherFocusReason);

    QVERIFY(textArea->property("focus").toBool());
    QVERIFY(textArea->property("activeFocus").toBool());
    QVERIFY(textEdit->property("focus").toBool());
    QVERIFY(textEdit->property("activeFocus").toBool());
}

void tst_quickcomponentstextarea::cursorRectangle()
{
    QGraphicsObject *textArea = m_view->rootObject()->findChild<QGraphicsObject*>("textArea");
    QGraphicsObject *button = m_view->rootObject()->findChild<QGraphicsObject*>("click");
    QVERIFY(textArea);
    QVERIFY(button);

    QVariant cursorRect;
    textArea->setProperty("text", "");
    QVERIFY2(QMetaObject::invokeMethod(textArea,
                                       "positionToRectangle",
                                       Q_RETURN_ARG(QVariant, cursorRect),
                                       Q_ARG(QVariant, textArea->property("cursorPosition").toInt())),
                                       "Could not call positionToRectangle");

    button->setFocus(Qt::OtherFocusReason);
    QVERIFY(!m_view->scene()->inputMethodQuery(Qt::ImMicroFocus).isValid());
    QVERIFY(!QApplication::focusWidget()->inputMethodQuery(Qt::ImMicroFocus).isValid());

    textArea->setFocus(Qt::OtherFocusReason);
    QVariant cursorRectFromScene = m_view->scene()->inputMethodQuery(Qt::ImMicroFocus);
    QVariant cursorRectFromApp = QApplication::focusWidget()->inputMethodQuery(Qt::ImMicroFocus);
    QVERIFY(cursorRectFromScene.isValid());
    QCOMPARE(textArea-> mapRectFromScene(cursorRectFromScene.toRectF()), cursorRect.toRectF());
    QVERIFY(cursorRectFromApp.isValid());
    QCOMPARE(textArea-> mapRectFromScene(cursorRectFromApp.toRectF()), cursorRect.toRectF());
}

QTEST_MAIN(tst_quickcomponentstextarea)

#include "tst_quickcomponentstextarea.moc"
