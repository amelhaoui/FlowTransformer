#include <QtGui>

#include "dragdropmodel.h"

DragDropModel::DragDropModel(const QStringList &header, Node* root, QObject *parent)
    : TreeModel(header, root, parent)
{
}

bool DragDropModel::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat("text/plain"))
        return false;

    int beginRow;

    if (row != -1)
        beginRow = row;
    else if (parent.isValid())
        beginRow = 0;
    else
        beginRow = rowCount(QModelIndex());

    QByteArray encodedData = data->data("text/plain");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QString newItem;
    // we suppose we pass only one item
    while (!stream.atEnd())
        stream >> newItem;
   // we modify the current element
    if (!parent.data().toString().isEmpty())
        newItem = newItem + " + " + parent.data().toString();
    setData(parent, newItem);




    return true;
}

Qt::ItemFlags DragDropModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = TreeModel::flags(index);

    if (index.isValid() && index.column() == 0)
        return Qt::ItemIsDragEnabled | defaultFlags;
    else if (index.column() == 1)
        return Qt::ItemIsDropEnabled | defaultFlags;
}

QMimeData *DragDropModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            // retrieve path to this element
            QString text = data(index, Qt::DisplayRole).toString();
            text = findPath(text, index);
            //stream << index.internalId() << index.row() << index.column() << text;
            stream << text;
        }
    }

    mimeData->setData("text/plain", encodedData);
    return mimeData;
}

QStringList DragDropModel::mimeTypes() const
{
    QStringList types;
    types << "text/plain";
    return types;
}

Qt::DropActions DragDropModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

QString DragDropModel::findPath(QString text, QModelIndex &index) const{
    QModelIndex temp_index = index.parent();
    QString path = text;
    while (temp_index.isValid()) {
        path = temp_index.data().toString() + "." + path;
        temp_index = temp_index.parent();
    }
    return path;
}

