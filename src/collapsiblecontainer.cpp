#include "collapsiblecontainer.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>


CollapsibleContainer::CollapsibleContainer(QWidget* parent /*= nullptr*/)
    : QWidget(parent)
    , titleLb_(new QLabel(this))
    , centralw_(nullptr)
    , collapsible_(true)
    , closable_(false)
    , placeholder_(new QWidget)
    , layout_(new QVBoxLayout(this))
{
    auto titlel_ = new QHBoxLayout;
    titlel_->setMargin(5);
    titlel_->addWidget(titleLb_, 1);

    auto titlew = new QFrame(this);
    titlew->setObjectName("title-c");
    titlew->setStyleSheet("QFrame#title-c{background-color:#f0f0f0;border:0;border-bottom:1px solid #ccc;}");
    titlew->setLayout(titlel_);
    titlew->installEventFilter(this);

    layout_->setMargin(0);
    layout_->setSpacing(0);
    layout_->addWidget(titlew);
    layout_->addWidget(placeholder_, 1);
}

CollapsibleContainer::CollapsibleContainer(const QString& title, QWidget* parent /*= nullptr*/)
    : CollapsibleContainer(parent)
{
    setTitle(title);
}

CollapsibleContainer::~CollapsibleContainer()
{

}

void CollapsibleContainer::setCollapsible(bool on)
{
    collapsible_ = on;
}

void CollapsibleContainer::setClosable(bool on)
{
    closable_ = on;
}

void CollapsibleContainer::setTitle(const QString& title)
{
    titleLb_->setText(title);
}

void CollapsibleContainer::setCentralWidget(QWidget* central)
{
    if (central == nullptr) {
        layout_->replaceWidget(centralw_, placeholder_);
        placeholder_->show();
    }
    else {
        layout_->replaceWidget(placeholder_, central);
        placeholder_->hide();
    }

    centralw_ = central;
}

void CollapsibleContainer::addAction(QAction* a)
{

}

QWidget* CollapsibleContainer::centralWidget() const
{
    return centralw_;
}

void CollapsibleContainer::expand()
{
    centralw_->show();
}

void CollapsibleContainer::collapse()
{
    centralw_->hide();
}

bool CollapsibleContainer::isExpanded() const
{
    return centralw_->isVisible();
}

// @override
bool CollapsibleContainer::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == titleLb_->parent() && event->type() == QEvent::MouseButtonDblClick && collapsible_) {
        if (static_cast<QMouseEvent*>(event)->buttons().testFlag(Qt::LeftButton)) {
            if (isExpanded()) {
                collapse();
            }
            else {
                expand();
            }
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}
