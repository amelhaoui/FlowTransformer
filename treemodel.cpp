#include <QtWidgets>

#include "treeitem.h"
#include "treemodel.h"
#include <iostream>


TreeModel::TreeModel(const QStringList &headers, const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    rootItem = new TreeItem(rootData);
    setupModelData(data.split(QString("\n")), rootItem);
}
TreeModel::TreeModel(const QStringList &headers, Node *root, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    rootItem = new TreeItem(rootData); // this root serves as header
    QVariant data = QString::fromStdString(root->getTag());
    rootItem->insertChildren(0,0, data); // root of the tree
    setupModelData(root);
}

TreeModel::TreeModel(TreeItem *root, QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = root;
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DecorationRole && index.column() == 0) {
        //get type (attribute or tag) ??
        QPixmap pixmap(10,10);
        QColor color;
        QString data = index.data().toString();
        QString data_parent = index.parent().data().toString();

        if (data.compare("Attributes") == 0 || data_parent.compare("Attributes") == 0)
            color.setRgb(200,100,100);
        else
            color.setRgb(0, 0, 0);

        pixmap.fill(color);
        return pixmap;
    } else if (role == Qt::DisplayRole || role == Qt::EditRole ) {
        // you will have *both* text and image displayed.
        TreeItem *item = getItem(index);
        return item->data(index.column());
    } else {
        return QVariant();
    }

}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    TreeItem *parentItem = getItem(parent);

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *root)
{
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << root;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].mid(position, 1) != " ")
                break;
            ++position;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            TreeItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        }

        ++number;
    }
}

/* transfer Node structure to TreeNode structure */
void TreeModel::setupModelData(Node *root)
{
    if (root->childs == NULL)
        return;

    QStack<Node*> nodes_source;
    nodes_source.push(root);

    QStack<TreeItem*> nodes_target;
    nodes_target.push(rootItem->child(0));

    while (!nodes_source.empty()) {
        TreeItem* top_item = nodes_target.top();
        Node* top_node = nodes_source.top();
        nodes_source.pop();
        nodes_target.pop();

        int f_index = 0;
        QVariant tag = "Attributes";
        top_item->insertChildren(f_index, 2, tag);

        // at least one attribute correspond to the value of the tag
        QVariant qv("value");
        top_item->child(f_index)->insertChildren(0, 2, qv);

        // check if node has other attributes
        if (top_node->attributes->size() > 0) {
            for (int i = 0; i < top_node->attributes->size(); ++i) {
                Attribut* current_attribut = (top_node->attributes->at(i));
                QVariant attribut = QString::fromStdString(current_attribut->name);
                top_item->child(f_index)->insertChildren(i + 1, 2, attribut);
            }
            ++f_index;
        }

        for (int index = 0, f_index = 0; index < top_node->childs->size(); ++index, ++f_index) {
            nodes_source.push(top_node->childs->at(f_index));
            QVariant columns;
            columns = QString::fromStdString(nodes_source.top()->getTag());
            top_item->insertChildren(f_index, 2, columns);
            nodes_target.push(top_item->child(f_index));
        }
    }
}
