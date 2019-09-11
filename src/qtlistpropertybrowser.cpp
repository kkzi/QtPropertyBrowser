#include "qtlistpropertybrowser.h"
#include "qtvariantproperty.h"
#include "collapsiblecontainer.h"

#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QList>
#include <QMap>
#include <QTimer>
#include <QSpacerItem>


#if QT_VERSION >= 0x040400
QT_BEGIN_NAMESPACE
#endif


class QtListPropertyBrowserPrivate
{
    QtListPropertyBrowser* q_ptr;
    Q_DECLARE_PUBLIC(QtListPropertyBrowser)

public:
    struct WidgetItem
    {
        QtProperty* property = nullptr;

        CollapsibleContainer* container = nullptr;

        QLabel* label = nullptr;
        QWidget* editor = nullptr;
    };

public:
    void propertyInserted(QtBrowserItem* index, QtBrowserItem* afterIndex);
    void propertyRemoved(QtBrowserItem* index);
    void propertyChanged(QtBrowserItem* index);
    void slotEditorDestroyed();
    void slotUpdate();

private:
    CollapsibleContainer* createContainer(QtProperty*);
    void updateLater();
    void updateItem(WidgetItem* item);
    void removeRow(QBoxLayout* layout, int row) const;
    QLabel* createLabel(QtProperty* property, QWidget* parent);

private:
    int labelWidth_;
    QMap<QtBrowserItem*, CollapsibleContainer*> indexToContainer_;

    QMap<WidgetItem*, QtBrowserItem*> itemToIndex_;
    QMap<QWidget*, WidgetItem*> widgetToItem_;
    QVBoxLayout* mainLayout_;
    QList<WidgetItem*> children_;
    QList<WidgetItem*> recreateQueue_;
};


void QtListPropertyBrowserPrivate::propertyInserted(QtBrowserItem* index, QtBrowserItem* afterIndex)
{
    auto item = new WidgetItem;
    item->property = index->property();
    if (index->parent() == nullptr) {
        auto w = createContainer(item->property);
        mainLayout_->insertWidget(mainLayout_->count() - 1, w);
        indexToContainer_[index] = w;

        item->container = w;
    }
    else {
        auto par = indexToContainer_.value(index->parent());
        Q_CHECK_PTR(par);

        item->label = createLabel(item->property, nullptr);
        item->editor = q_ptr->createEditor(item->property, nullptr);

        auto row = new QWidget;
        auto hl = new QHBoxLayout(row);
        hl->setMargin(0);
        if (item->label) {
            item->label->setFixedWidth(labelWidth_);
            hl->addWidget(item->label);
        }
        if (item->editor == nullptr) {
            item->editor = new QLabel(item->property->propertyName(), q_ptr);
        }
        hl->addWidget(item->editor, 1);
        par->centralWidget()->layout()->addWidget(row);
    }
    updateItem(item);
}

void QtListPropertyBrowserPrivate::propertyRemoved(QtBrowserItem* index)
{
    //WidgetItem* item = indexToItem_.value(index);

    //indexToItem_.remove(index);
    //itemToIndex_.remove(item);

    //WidgetItem* parentItem = item->parent;

    //int row = -1;

    //if (parentItem) {
    //    row = parentItem->children.indexOf(item);
    //    parentItem->children.removeAt(row);
    //    if (hasHeader(parentItem))
    //        row += 2;
    //}
    //else {
    //    row = children_.indexOf(item);
    //    children_.removeAt(row);
    //}

    //if (item->widget)
    //    delete item->widget;
    //if (item->label)
    //    delete item->label;
    //if (item->widgetLabel)
    //    delete item->widgetLabel;
    //if (item->container)
    //    delete item->container;

    //if (!parentItem) {
    //    removeRow(mainLayout_, row);
    //}
    //else if (parentItem->children.count() != 0) {
    //    removeRow(parentItem->layout, row);
    //}
    //else {
    //    WidgetItem* par = parentItem->parent;
    //    QBoxLayout* l = 0;
    //    int oldRow = -1;
    //    if (!par) {
    //        l = mainLayout_;
    //        oldRow = children_.indexOf(parentItem);
    //    }
    //    else {
    //        l = par->layout;
    //        oldRow = par->children.indexOf(parentItem);
    //        if (hasHeader(par))
    //            oldRow += 2;
    //    }

    //    if (parentItem->widget) {
    //        parentItem->widget->hide();
    //        parentItem->widget->setParent(0);
    //    }
    //    else if (parentItem->widgetLabel) {
    //        parentItem->widgetLabel->hide();
    //        parentItem->widgetLabel->setParent(0);
    //    }
    //    else {
    //        //parentItem->widgetLabel = new QLabel(w);
    //    }
    //    l->removeWidget(parentItem->container);
    //    delete parentItem->container;
    //    parentItem->container = 0;
    //    parentItem->line = 0;
    //    parentItem->layout = 0;
    //    if (!recreateQueue_.contains(parentItem))
    //        recreateQueue_.append(parentItem);
    //    updateLater();
    //}
    //recreateQueue_.removeAll(item);

    //delete item;
}

void QtListPropertyBrowserPrivate::propertyChanged(QtBrowserItem* index)
{
    //WidgetItem* item = indexToItem_.value(index);
    //updateItem(item);
}

void QtListPropertyBrowserPrivate::slotEditorDestroyed()
{
    //QWidget* editor = qobject_cast<QWidget*>(q_ptr->sender());
    //if (!editor)
    //    return;
    //if (!widgetToItem_.contains(editor))
    //    return;
    //widgetToItem_[editor]->widget = 0;
    //widgetToItem_.remove(editor);
}

void QtListPropertyBrowserPrivate::slotUpdate()
{
    //QListIterator<WidgetItem*> itItem(recreateQueue_);
    //while (itItem.hasNext()) {
    //    WidgetItem* item = itItem.next();

    //    WidgetItem* par = item->parent;
    //    QWidget* w = 0;
    //    QBoxLayout* l = 0;
    //    int oldRow = -1;
    //    if (!par) {
    //        w = q_ptr;
    //        l = mainLayout_;
    //        oldRow = children_.indexOf(item);
    //    }
    //    else {
    //        w = par->container;
    //        l = par->layout;
    //        oldRow = par->children.indexOf(item);
    //        if (hasHeader(par))
    //            oldRow += 2;
    //    }

    //    QtProperty* p = itemToIndex_[item]->property();
    //    item->label = q_ptr->createLabel(p, w);

    //    if (item->widget) {
    //        item->widget->setParent(w);
    //    }
    //    else if (item->widgetLabel) {
    //        item->widgetLabel->setParent(w);
    //    }
    //    else {
    //        item->widgetLabel = new QLabel(w);
    //        item->widgetLabel->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed));
    //        item->widgetLabel->setTextFormat(Qt::PlainText);
    //    }

    //    item->layout = new QHBoxLayout;
    //    if (item->label) {
    //        item->layout->addWidget(item->label);
    //    }
    //    if (item->widget) {
    //        item->layout->addWidget(item->widget, 1);
    //    }
    //    else if (item->widgetLabel) {
    //        item->layout->addWidget(item->widgetLabel, 1);
    //    }
    //    else {
    //        Q_ASSERT(false);
    //    }

    //    updateItem(item);
    //}
    //recreateQueue_.clear();
}

CollapsibleContainer* QtListPropertyBrowserPrivate::createContainer(QtProperty* p)
{
    Q_CHECK_PTR(p);

    auto cw = new QWidget;
    auto vl = new QVBoxLayout(cw);
    vl->setMargin(8);
    //for (const auto& p : p->subProperties()) {
    //    vl->addWidget(createWidgetItem(p));
    //}
    auto cc = new CollapsibleContainer(p->propertyName(), q_ptr);
    cc->setCentralWidget(cw);
    return cc;
}

void QtListPropertyBrowserPrivate::updateLater()
{
    QTimer::singleShot(0, q_ptr, SLOT(slotUpdate()));
}

void QtListPropertyBrowserPrivate::updateItem(QtListPropertyBrowserPrivate::WidgetItem* item)
{
    QtProperty* property = item->property;
    if (item->container) {
        QFont font = item->container->font();
        font.setUnderline(property->isModified());
        item->container->setFont(font);
        item->container->setTitle(property->propertyName());
        item->container->setToolTip(property->toolTip());
        item->container->setStatusTip(property->statusTip());
        item->container->setWhatsThis(property->whatsThis());
        item->container->setEnabled(property->isEnabled());
    }
    if (item->label) {
        QFont font = item->label->font();
        font.setUnderline(property->isModified());
        item->label->setFont(font);
        item->label->setText(property->propertyName());
        item->label->setToolTip(property->toolTip());
        item->label->setStatusTip(property->statusTip());
        item->label->setWhatsThis(property->whatsThis());
        item->label->setEnabled(property->isEnabled());
    }
    //item->setIcon(1, property->valueIcon());
}

void QtListPropertyBrowserPrivate::removeRow(QBoxLayout* layout, int row) const
{
    //auto item = layout->takeAt(row);
    //item->widget()->deleteLater();
    //delete item;
}

QLabel* QtListPropertyBrowserPrivate::createLabel(QtProperty* property, QWidget* parent)
{
    if (property == nullptr || property->propertyName().isEmpty()) return nullptr;
    auto label = new QLabel(parent);
    label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    return label;
}







QtListPropertyBrowser::QtListPropertyBrowser(QWidget* parent /*= 0*/)
    : QtAbstractPropertyBrowser(parent)
    , d_ptr(new QtListPropertyBrowserPrivate)
{
    d_ptr->q_ptr = this;
    d_ptr->mainLayout_ = new QVBoxLayout(this);
    d_ptr->mainLayout_->setMargin(0);
    d_ptr->mainLayout_->setSpacing(0);
    d_ptr->mainLayout_->addStretch(1);

    setStyleSheet("QtListPropertyBrowser{border:1px solid blue; background-color:#fff;}");
    setLabelWidth(80);
}

QtListPropertyBrowser::~QtListPropertyBrowser()
{
    for (auto it = d_ptr->itemToIndex_.constBegin(); it != d_ptr->itemToIndex_.constEnd(); ++it)
        delete it.key();
    delete d_ptr;
}

void QtListPropertyBrowser::setLabelWidth(int width)
{
    d_ptr->labelWidth_ = width;
}

void QtListPropertyBrowser::itemInserted(QtBrowserItem* item, QtBrowserItem* afterItem)
{
    d_ptr->propertyInserted(item, afterItem);
}

void QtListPropertyBrowser::itemRemoved(QtBrowserItem* item)
{
    d_ptr->propertyRemoved(item);
}

void QtListPropertyBrowser::itemChanged(QtBrowserItem* item)
{
    d_ptr->propertyChanged(item);
}


#if QT_VERSION >= 0x040400
QT_END_NAMESPACE
#endif

#include "moc_qtlistpropertybrowser.cpp"
