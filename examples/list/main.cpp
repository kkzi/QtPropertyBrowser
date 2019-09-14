/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Solutions component.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include <QDate>
#include <QLocale>
#include <QTimer>
#include "qtpropertymanager.h"
#include "qtvariantproperty.h"
#include "qteditorfactory.h"
#include "qttreepropertybrowser.h"
#include "qtlistpropertybrowser.h"
#include "collapsiblecontainer.h"
#include "listpropertywidget.h"
#include <QTextEdit>
#include <QStringList>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QtVariantPropertyManager* variantManager = new QtVariantPropertyManager();

    int i = 0;
    QtProperty* topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), QString::number(i++) + QLatin1String(" Group Property"));

    QtVariantProperty* item = variantManager->addProperty(QVariant::Bool, QString::number(i++) + QLatin1String(" Bool Property"));
    item->setValue(true);
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Int, QString::number(i++) + QLatin1String(" Int Property"));
    item->setValue(20);
    item->setAttribute(QLatin1String("minimum"), 0);
    item->setAttribute(QLatin1String("maximum"), 100);
    item->setAttribute(QLatin1String("singleStep"), 10);
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Int, QString::number(i++) + QLatin1String(" Int Property (ReadOnly)"));
    item->setValue(20);
    item->setAttribute(QLatin1String("minimum"), 0);
    item->setAttribute(QLatin1String("maximum"), 100);
    item->setAttribute(QLatin1String("singleStep"), 10);
    item->setAttribute(QLatin1String("readOnly"), true);
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Double, QString::number(i++) + QLatin1String(" Double Property"));
    item->setValue(1.2345);
    item->setAttribute(QLatin1String("singleStep"), 0.1);
    item->setAttribute(QLatin1String("decimals"), 3);
    topItem->addSubProperty(item);

    QtProperty* topItem2 = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), QString::number(i++) + QLatin1String(" Group Property"));
    item = variantManager->addProperty(QVariant::Double, QString::number(i++) + QLatin1String(" Double Property (ReadOnly)"));
    item->setValue(1.23456);
    item->setAttribute(QLatin1String("singleStep"), 0.1);
    item->setAttribute(QLatin1String("decimals"), 5);
    item->setAttribute(QLatin1String("readOnly"), true);
    topItem2->addSubProperty(item);

    item = variantManager->addProperty(QVariant::String, QString::number(i++) + QLatin1String(" String Property"));
    item->setValue("Value");
    topItem2->addSubProperty(item);

    item = variantManager->addProperty(QVariant::String, QString::number(i++) + QLatin1String(" String Property (Password)"));
    item->setAttribute(QLatin1String("echoMode"), QLineEdit::Password);
    item->setValue("Password");
    topItem2->addSubProperty(item);

    // Readonly String Property
    item = variantManager->addProperty(QVariant::String, QString::number(i++) + QLatin1String(" String Property (ReadOnly)"));
    item->setAttribute(QLatin1String("readOnly"), true);
    item->setValue("readonly text");
    topItem2->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Date, QString::number(i++) + QLatin1String(" Date Property"));
    item->setValue(QDate::currentDate().addDays(2));
    topItem2->addSubProperty(item);

    QtProperty* topItem3 = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), QString::number(i++) + QLatin1String(" Group Property"));
    item = variantManager->addProperty(QVariant::Time, QString::number(i++) + QLatin1String(" Time Property"));
    item->setValue(QTime::currentTime());
    topItem3->addSubProperty(item);

    item = variantManager->addProperty(QVariant::DateTime, QString::number(i++) + QLatin1String(" DateTime Property"));
    item->setValue(QDateTime::currentDateTime());
    topItem3->addSubProperty(item);

    item = variantManager->addProperty(QVariant::KeySequence, QString::number(i++) + QLatin1String(" KeySequence Property"));
    item->setValue(QKeySequence(Qt::ControlModifier | Qt::Key_Q));
    topItem3->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Char, QString::number(i++) + QLatin1String(" Char Property"));
    item->setValue(QChar(386));
    topItem3->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Locale, QString::number(i++) + QLatin1String(" Locale Property"));
    item->setValue(QLocale(QLocale::Polish, QLocale::Poland));
    topItem3->addSubProperty(item);



    auto enummgr = new QtEnumPropertyManager();
    auto enumfct = new QtEnumEditorFactory();
    auto topItem4 = enummgr->addProperty("Calibration Function");
    enummgr->setEnumNames(topItem4, QStringList{ "Linear", "Polynomial" });
    QObject::connect(enummgr, &QtEnumPropertyManager::valueChanged, [=](QtProperty* property, int val)
    {
        for (auto p : topItem4->subProperties()) {
            topItem4->removeSubProperty(p);
        }
        if (val == 0) {
            auto p1 = variantManager->addProperty(QVariant::String, "P1");
            topItem4->addSubProperty(p1);
            auto m1 = variantManager->addProperty(QVariant::Double, "M1");
            topItem4->addSubProperty(m1);
        }
        else {
            auto p2 = variantManager->addProperty(QVariant::String, "P2");
            topItem4->addSubProperty(p2);
            auto m2 = variantManager->addProperty(QVariant::Double, "M2");
            topItem4->addSubProperty(m2);
        }
    }
    );
    //funp->setEnabled(false);


    QtProperty* topItem5 = variantManager->addProperty(QVariant::String, QString::number(i++) + QLatin1String(" Source Code"));
    auto spmgr = new QtStringPropertyManager();
    auto tef = new QtTextEditFactory();
    auto topItem6 = spmgr->addProperty("");
    topItem6->setSpanned(true);
    topItem6->setHeightHint(100);

    QtVariantEditorFactory* variantFactory = new QtVariantEditorFactory();
    QtTreePropertyBrowser* variantEditor = new QtTreePropertyBrowser();
    variantEditor->setFactoryForManager(variantManager, variantFactory);
    variantEditor->setFactoryForManager(enummgr, enumfct);
    variantEditor->setFactoryForManager(spmgr, tef);
    variantEditor->addProperty(topItem);
    variantEditor->addProperty(topItem2);
    variantEditor->addProperty(topItem4);
    variantEditor->addProperty(topItem5);
    variantEditor->addProperty(topItem6);
    variantEditor->addProperty(topItem3);
    variantEditor->setPropertiesWithoutValueMarked(true);
    variantEditor->setRootIsDecorated(false);
    variantEditor->show();

    item = variantManager->addProperty(QVariant::Color, QString::number(i++) + QLatin1String(" Color Property"));
    variantEditor->setPropertiesWithoutValueMarked(true);
    variantEditor->setRootIsDecorated(false);

    variantEditor->resize(400, 800);
    variantEditor->show();

    int ret = app.exec();

    delete variantManager;
    delete variantFactory;
    delete variantEditor;

    return ret;
}
