#pragma once

#include "qtpropertybrowser.h"


#if QT_VERSION >= 0x040400
QT_BEGIN_NAMESPACE
#endif

class QtListPropertyBrowserPrivate;
class QtVariantProperty;

class QT_QTPROPERTYBROWSER_EXPORT QtListPropertyBrowser : public QtAbstractPropertyBrowser
{
    Q_OBJECT

public:
    QtListPropertyBrowser(QWidget* parent = 0);
    ~QtListPropertyBrowser();

public:
    void setLabelWidth(int width);

protected:
    void itemInserted(QtBrowserItem* item, QtBrowserItem* afterItem) override;
    void itemRemoved(QtBrowserItem* item) override;
    void itemChanged(QtBrowserItem* item) override;

private:
    QtListPropertyBrowserPrivate* d_ptr;
    Q_DECLARE_PRIVATE(QtListPropertyBrowser)
    Q_DISABLE_COPY(QtListPropertyBrowser)
    Q_PRIVATE_SLOT(d_func(), void slotUpdate())
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed())
};


#if QT_VERSION >= 0x040400
QT_END_NAMESPACE
#endif
