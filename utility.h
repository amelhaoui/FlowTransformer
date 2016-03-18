#ifndef UTILITY_H
#define UTILITY_H

#include "treeitem.h"

#include <QString>
#include <QModelIndex>

class Utility
{
public:
    Utility();
    static QString findPath(QString& text, QModelIndex &index);
    static QString findPath(QString& text, TreeItem* parent);

};

#endif // UTILITY_H
