#pragma once

#include <QWidget>

class QtVariantProperty;
class QtVariantPropertyManager;
class QtVariantEditorFactory;
class QtListPropertyBrowser;
class QVBoxLayout;

class ListPropertyWidget : public QWidget
{
	Q_OBJECT

public:
	ListPropertyWidget(QWidget* parent = nullptr);
	ListPropertyWidget(const QString& title, QWidget* parent = nullptr);
	~ListPropertyWidget();

public:
	void setLabelWidth(int width);
	QtVariantProperty* addGroupProperty(const QString& name);
	QtVariantProperty* addProperty(QtVariantProperty* parent, int propertyType, const QString& name = QString());

	QtListPropertyBrowser* browser() const;
	QtVariantPropertyManager* manager() const;
	QtVariantEditorFactory* factory() const;

private:
	QtVariantPropertyManager* manager_;
	QtVariantEditorFactory* factory_;
	QtListPropertyBrowser* browser_;
	QVBoxLayout* layout_;
};

