#include "itemtabledelegate.h"
#include <QDebug>

ItemTableDelegate::ItemTableDelegate(QObject * parent) : QStyledItemDelegate(parent) {}

ItemTableDelegate:: ItemTableDelegate(QCompleter* source_completer,QCompleter* cible_completer, QObject * parent)
    : QStyledItemDelegate(parent) {
    this->source_completer = (TreeModelCompleter*) source_completer;
    this->cible_completer = (TreeModelCompleter*) cible_completer;

}

QString ItemTableDelegate::displayText(const QVariant &value, const QLocale &locale) const {
    // represent one or many paths
    QString names = value.toString();
    // paths are separated by a separator. We shall say it's "," or "+"
    int sep_index = names.indexOf('+');
    // index of . separator
    int last_dot_index = 0;

    // case : 1 element
    if (sep_index == -1) {
        // only one value
        last_dot_index = names.lastIndexOf('.');
        if (last_dot_index != -1)
            return names.mid(last_dot_index + 1);
        else
            return names;
    }

    // value to display
    QString values = "";

    // we have multiple items
    while (sep_index != -1 ) {
        // parse by '+'
        int n = sep_index - last_dot_index;
        QString current_value = names.mid(last_dot_index, n);

        // get the last word after the .
        int index = current_value.lastIndexOf('.');
        if (index != -1)
            current_value = current_value.mid (index+1);

        // append to values
        if (values.isEmpty())
            values = current_value;
        else
            values = values + ", " + current_value;

        // iterate
        last_dot_index = sep_index + 1;
        sep_index = names.indexOf('+', last_dot_index);
    }

    // case only 2 string
    if (last_dot_index < names.size()) {
        int start = last_dot_index;
        QString last_tag = names.mid(start);
        last_dot_index = last_tag.lastIndexOf('.');
        if (last_dot_index != -1)
            values = values + ", " + last_tag.mid(last_dot_index + 1);
        else
            values = values + ", " + last_tag;
    }

    return values;
}
QWidget* ItemTableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & option,
        const QModelIndex & index ) const
{
    QLineEdit *widget = 0;
    if (index.isValid()) {
        widget = new QLineEdit(parent);
        if (index.column() == 0)
            widget->setCompleter(cible_completer);
        else
            widget->setCompleter(source_completer);
    }
    return widget;
}

// Then, we set the Editor
// Gets the data from Model and feeds the data to Editor
void ItemTableDelegate::setEditorData(QWidget *editor,
                                      const QModelIndex &index) const
{
    // Get the value via index of the Model
    QString value = index.model()->data(index, Qt::EditRole).toString();

    // Put the value into the SpinBox
    QLineEdit *line_edit = static_cast<QLineEdit*>(editor);
    line_edit->setText(value);
}

void ItemTableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {

    QLineEdit *line_edit = static_cast<QLineEdit*>(editor);
    QString value = line_edit->text();
    model->setData(index, value, Qt::EditRole);
}
