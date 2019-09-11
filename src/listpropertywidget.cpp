#include "listpropertywidget.h"
#include "qtvariantproperty.h"
#include "qtlistpropertybrowser.h"
#include "collapsiblecontainer.h"

#include <QVBoxLayout>


ListPropertyWidget::ListPropertyWidget(QWidget* parent /*= nullptr*/)
    : ListPropertyWidget("", parent)
{

}

ListPropertyWidget::ListPropertyWidget(const QString& title, QWidget* parent /*= nullptr*/)
    : QWidget(parent)
    , manager_(new QtVariantPropertyManager)
    , factory_(new QtVariantEditorFactory)
    , browser_(new QtListPropertyBrowser)
    , layout_(new QVBoxLayout(this))
{
    auto container = new CollapsibleContainer(title, this);
    container->setObjectName("list-property-container");
    container->setCollapsible(false);
    container->setClosable(true);
    container->setCentralWidget(browser_);

    auto bl = new QVBoxLayout(browser_);
    bl->setMargin(8);

    layout_->setMargin(0);
    layout_->addWidget(container, 1);

    browser_->setFactoryForManager(manager_, factory_);
}

ListPropertyWidget::~ListPropertyWidget()
{
    manager_->deleteLater();
    factory_->deleteLater();
}

void ListPropertyWidget::setLabelWidth(int width)
{
    browser_->setLabelWidth(width);
}

QtVariantProperty* ListPropertyWidget::addGroupProperty(const QString& name)
{
    auto p = addProperty(nullptr, manager_->groupTypeId(), name);
    browser_->addProperty(p);
    return p;
}

QtVariantProperty* ListPropertyWidget::addProperty(QtVariantProperty* parent, int propertyType, const QString& name /*= QString()*/)
{
    auto p = manager_->addProperty(propertyType, name);
    if (parent) {
        parent->addSubProperty(p);
    }
    else {
        browser_->addProperty(p);
    }
    return p;
}
