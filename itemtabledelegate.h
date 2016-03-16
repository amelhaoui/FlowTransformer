#ifndef ITEMTABLEDELEGATE_H
#define ITEMTABLEDELEGATE_H

#include <QWidget>
#include <QStyledItemDelegate>

#include <QtWidgets>
#include "treemodelcompleter.h"
#include <QLineEdit>


class ItemTableDelegate : public QStyledItemDelegate
{

public:
    ItemTableDelegate(QObject * parent = 0);
    ItemTableDelegate(QCompleter* source_completer,QCompleter* cible_completer, QObject * parent = 0);
    QWidget* createEditor(QWidget *parent,
                          const QStyleOptionViewItem & option,
                          const QModelIndex & index) const;
    void setEditorData(QWidget *editor,
                                   const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    QString displayText(const QVariant &value, const QLocale &locale) const;

private:
    TreeModelCompleter* source_completer;
    TreeModelCompleter* cible_completer;


};

#endif // ITEMTABLEDELEGATE_H
