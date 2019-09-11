#pragma once

#include <QWidget>

class QAction;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;

class CollapsibleContainer : public QWidget
{
    Q_OBJECT

public:
    CollapsibleContainer(QWidget* parent = nullptr);
    CollapsibleContainer(const QString& title, QWidget* parent = nullptr);
    ~CollapsibleContainer();

public:
    void setCollapsible(bool);
    void setClosable(bool);
    void setTitle(const QString& title);
    void setCentralWidget(QWidget*);
    void addAction(QAction*);
    QWidget* centralWidget() const;

    void expand();
    void collapse();
    bool isExpanded() const;

protected:
    bool eventFilter(QObject* watched, QEvent* event);

private:
    QLabel* titleLb_;
    QWidget* centralw_;
    bool collapsible_;
    bool closable_;
    QWidget* placeholder_;
    QVBoxLayout* layout_;
};

