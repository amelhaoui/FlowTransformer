#include "utility.h"
#include "treeitem.h"
#include <QModelIndex>

Utility::Utility()
{

}

QString Utility::findPath(QString &text, QModelIndex &index) {
    QModelIndex temp_index = index.parent();
    QString path = text;
    while (temp_index.isValid()) {
        path = temp_index.data().toString() + "." + path;
        temp_index = temp_index.parent();
    }
    return path;
}

QString Utility::findPath(QString &text, TreeItem* item) {
    QString path = text;
    while (item != NULL && item->data(0).toString().compare("Tag")) {
        path = item->data(0).toString() + "." + path;
        item = item->parent();
    }
    return path;
}

