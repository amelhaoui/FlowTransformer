
#include "expat.h"
#include "inc/tinyxml2.h"
#include "emc_parser.cpp"
#include "treemodel.h"
#include "mainwindow.h"
#include "utility.h"
#include "treeitem.h"
#include "emc_parse_utility.h"
#include "itemtabledelegate.h"
#include <QtWidgets>
#include "treemodelcompleter.h"
#include <QFile>
#include "unordered_map"
#include "vector"
#include <QtCore>
#include <QFileDialog>
#include <QDebug>
#include <QStandardItemModel>
#include <QHash>


#define BUFFER_SIZE 100000
using namespace tinyxml2;
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    source_completer = new TreeModelCompleter(this);
    cible_completer = new TreeModelCompleter(this);

    //bind Model to the View
    model_files_input = new QStandardItemModel(this);
    list_input->setModel(model_files_input);

    sourceView->setModel(NULL);
    targetView->setModel(NULL);
    //view->setModel(model_target);
//    for (int column = 0; column < model->columnCount(); ++column)
//        view->resizeColumnToContents(column);



    //set the Model for the tableView and set the Item Delegate
    ItemTableDelegate* table_delegate = new ItemTableDelegate(source_completer, cible_completer, this);
    //need to bring a model to the table and fill it with data
    table_model = new QStandardItemModel(1,2,this);
    table_model->setHorizontalHeaderItem(0, new QStandardItem("Cible"));
    table_model->setHorizontalHeaderItem(1, new QStandardItem("Source"));

    tableView->setModel(table_model);
    tableView->setItemDelegate(table_delegate);
    targetView->setItemDelegateForColumn(1, table_delegate);

    //targetView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    //targetView->setDragEnabled(true);
    targetView->setAcceptDrops(true);
    targetView->setDropIndicatorShown(true);

    sourceView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    sourceView->setDragEnabled(true);
    //sourceView->setAcceptDrops(true);
    //sourceView->setDropIndicatorShown(true);

    QObject::connect(source_completer, SIGNAL(highlighted(QModelIndex)),
                     this, SLOT(highlight(QModelIndex)));
    QObject::connect(cible_completer, SIGNAL(highlighted(QModelIndex)),
                     this, SLOT(highlight(QModelIndex)));

    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(sourceView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,
                                    const QItemSelection &)),
            this, SLOT(updateActions()));
    connect(targetView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,
                                    const QItemSelection &)),
            this, SLOT(updateActions()));

    connect(actionsMenu, SIGNAL(aboutToShow()), this, SLOT(updateActions()));
    connect(insertRowAction, SIGNAL(triggered()), this, SLOT(insertRow()));
    connect(removeRowAction, SIGNAL(triggered()), this, SLOT(removeRow()));
    connect(insertChildAction, SIGNAL(triggered()), this, SLOT(insertChild()));

    updateActions();
}

void MainWindow::insertChild()
{
    //detect in which TreeWidget
    QWidget * fw = qApp->focusWidget();
    QTreeView* current_view = (QTreeView*) fw;

    QModelIndex index = current_view->selectionModel()->currentIndex();
    QAbstractItemModel *model = current_view->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
    }

    current_view->selectionModel()->setCurrentIndex(model->index(0, 0, index),
            QItemSelectionModel::ClearAndSelect);
    updateActions();
}

bool MainWindow::insertColumn(const QModelIndex &parent)
{
    //detect in which TreeWidget
    QWidget * fw = qApp->focusWidget();
    QTreeView* current_view = (QTreeView*) fw;

    QAbstractItemModel *model = current_view->model();
    int column = current_view->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1, parent);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);

    updateActions();

    return changed;
}

void MainWindow::insertRow()
{
    //detect in which TreeWidget
    QWidget * fw = qApp->focusWidget();
    QTreeView* current_view = (QTreeView*) fw;

    QModelIndex index = current_view->selectionModel()->currentIndex();
    QAbstractItemModel *model = current_view->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
    }
}

bool MainWindow::removeColumn(const QModelIndex &parent)
{
    QAbstractItemModel *model = sourceView->model();
    int column = sourceView->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    bool changed = model->removeColumn(column, parent);

    if (!parent.isValid() && changed)
        updateActions();

    return changed;
}

void MainWindow::removeRow()
{
    //detect in which TreeWidget
    QWidget * fw = qApp->focusWidget();
    QTreeView* current_view = (QTreeView*) fw;

    QModelIndex index = current_view->selectionModel()->currentIndex();
    QAbstractItemModel *model = current_view->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void MainWindow::updateActions()
{
    bool hasSelection = !(sourceView->selectionModel()->selection().isEmpty() ||
                          targetView->selectionModel()->selection().isEmpty());
    removeRowAction->setEnabled(hasSelection);

    bool hasCurrent = (sourceView->selectionModel()->currentIndex().isValid() ||
                       targetView->selectionModel()->currentIndex().isValid());
    insertRowAction->setEnabled(hasCurrent);

    //show which row you're selecting.
    /**if (hasCurrent) {
        view->closePersistentEditor(view->selectionModel()->currentIndex());

        int row = view->selectionModel()->currentIndex().row();
        int column = view->selectionModel()->currentIndex().column();
        if (view->selectionModel()->currentIndex().parent().isValid())
            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        else
            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    }**/
}

void MainWindow::on_btn_parcourir_source_clicked()
{

    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open a file"), "/", tr("File (*.xml *.pdf *.xls)"));

    char            buffer[BUFFER_SIZE];
    if (fileName.isEmpty())
        return;
    ModelXML* model_a = new ModelXML(NULL, "american");
    parse_xml(buffer, BUFFER_SIZE,  fileName.toStdString().c_str(), model_a, mapping);
    QStringList headers;
    headers << tr("Tag");
    model_source = new DragDropModel(headers, model_a->root);

    sourceView->setModel(model_source);
    source_completer->setModel(model_source);
    source_completer->setCaseSensitivity(Qt::CaseInsensitive);
    source_completer->setSeparator(QLatin1String("."));
    source_completer->setCompletionMode(QCompleter::PopupCompletion);

}

void MainWindow::on_btn_parcourir_target_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open a file"), "/", tr("File (*.xml *.pdf *.xls)"));

    char            buffer[BUFFER_SIZE];

    if (fileName.isEmpty())
        return;
    ModelXML* model_a = new ModelXML(NULL, "Vanilla");
    parse_xml(buffer, BUFFER_SIZE,  fileName.toStdString().c_str(), model_a, mapping);
    QStringList headers;
    headers << tr("Tag") << tr("Mapping");
    model_cible = new DragDropModel(headers, model_a->root);

    targetView->setModel(model_cible);
    cible_completer->setModel(model_cible);
    cible_completer->setCaseSensitivity(Qt::CaseInsensitive);
    cible_completer->setSeparator(QLatin1String("."));
    cible_completer->setCompletionMode(QCompleter::PopupCompletion);

}

void MainWindow::highlight(const QModelIndex &index)
{
    // detects who sent the signal
    TreeModelCompleter* completer = qobject_cast<TreeModelCompleter*> (this->sender());

    QTreeView* view;
    if (index.column() == 0)
        view = this->targetView;
    else
        view = this->sourceView;

    QAbstractItemModel *completionModel = completer->completionModel();
    QAbstractProxyModel *proxy = qobject_cast<QAbstractProxyModel *>(completionModel);
    if (!proxy)
        return;
    QModelIndex sourceIndex = proxy->mapToSource(index);
    view->selectionModel()->select(sourceIndex, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
    view->scrollTo(index);


}

void MainWindow::on_btn_add_mapping_clicked()
{
    QModelIndex source_index = sourceView->selectionModel()->currentIndex();
    QModelIndex target_index = targetView->selectionModel()->currentIndex();

    QString source = source_index.data().toString()
            , target = target_index.data().toString();
    if (source_index.isValid() && target_index.isValid()) {
        source = Utility::findPath(source, source_index);
        target = Utility::findPath(target, target_index);
        
        QStandardItemModel* model_table = qobject_cast<QStandardItemModel*>(tableView->model());
        QList<QStandardItem*> row;
        row.append(new QStandardItem(source));
        row.append(new QStandardItem(target));
        model_table->appendRow(row);
    }
    
}

void MainWindow::on_btn_save_mapping_clicked()
{
    // the use choose to save mapping from drag and drop or from table
    // can't mix both
    QMessageBox msgBox;
    msgBox.setText(tr("Save Mapping"));
    msgBox.setInformativeText(tr("Would you like to save them using:"));
    QPushButton* tree_view = msgBox.addButton(tr("Tree View"), QMessageBox::ActionRole);
    QPushButton* table_view = msgBox.addButton(tr("Table View"), QMessageBox::ActionRole);
    msgBox.exec();

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                    tr("Text files (*.txt)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly))
        return;

    QDataStream out(&file);

    // check which button was clicked
    if (msgBox.clickedButton() == tree_view) {
        TreeModel* target_model = qobject_cast<TreeModel *> (targetView->model());
        TreeItem* root = target_model->getRoot(); // fake root represent the header
        if (root != NULL && root->childCount() > 0)
            root = root->child(0);
        else
            return;

        // we are at the top element
        // we nedd to trarverse the tree using a stack
        // each time we visit an element we check if it has a mapping
        // if yes we save it
        QStack<TreeItem*> s;
        s.push(root);

        while(!s.empty()) {
            TreeItem* current = s.top(); s.pop();
            if (!current->data(1).toString().isEmpty()) {
                QString element = current->data(0).toString();
                element = Utility::findPath(element, current->parent());
                // to check: serialize to string is necessary ?? for deserialize ??
                out << element << current->data(1).toString();
            }

            for (int i = 0; i < current->childCount(); ++i) {
                s.push(current->child(i));
            }
        }
    } else if (msgBox.clickedButton() == table_view) {
        /** save using the table **/
        QStandardItemModel* model_table = qobject_cast<QStandardItemModel *> (tableView->model());
        int num_row = model_table->rowCount();

        // fixs saving if user did not finish editing
        tableView->setDisabled(true);
        tableView->setDisabled(false);

        for (int i = 0; i < num_row; ++i) {
            QStandardItem* item1 =  model_table->item(i, 0);
            QStandardItem* item2 =  model_table->item(i, 1);

            // A validate transformation -> both items !empty
            if (!item1->text().isEmpty() && !item2->text().isEmpty())
                out << item1->text() << item2->text();
        }
        /** end of save **/
    }

    file.flush();
    file.close();



//    // add the target model into the mapping
//    TreeModel* target_model = qobject_cast<TreeModel *> (treeView->model());
//    if (target_model == NULL)
//        return;
//    TreeItem* fake_root = target_model->getRoot();
//    TreeItem root = fake_root->child(0);

//    QStack<TreeItem*> s;
//    int space = 0;
//    s.push(root);

//    while (!s.empty()) {
//        TreeItem* top = s.top(); s.pop();
//        // common treatment
//        out << top->data(0);
//        int num_child = top->childCount();

//        for (int i = 0; i < num_child; ++i) {
//            s.push(top->child(i));
//        }
//    }


}

void MainWindow::on_btn_upload_mapping_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open a file"), "/", tr("File (*.xml *.pdf *.txt)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
        return;
    QDataStream in(&file);

    QStandardItemModel* model_table = qobject_cast<QStandardItemModel *> (tableView->model());
    //int nb_row = model_table->rowCount();
    int row = 0;
    while (!in.atEnd()) {
        //model_table->appendRow(new QStandardItem(1));
        QString col1, col2;
        in >> col1 >> col2;
        model_table->setItem(row, new QStandardItem(col1));
        model_table->setItem(row, 1, new QStandardItem(col2));
        ++row;
    }

    tableView->setDisabled(false);
    file.close();

}

void MainWindow::on_btn_upload_mapping_2_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Load a mapping"), "/", tr("File (*.xml *.txt)"));
    lineEdit_mapping->setText(fileName);
}



void print_to_xml_Helper (TreeItem* root, XMLElement* parent, XMLDocument& xmlDoc,
                          unordered_map<string, unordered_map<int, string>> &values_target,
                          unordered_map<string, int> &occurences, QHash<QString, QString>& mapping,
                          QString root_path) {

    QString root_data = root->data(0).toString();
    // find if available the correspand item in input MODEL
    QString mapped = mapping[root_path];
    // check how many copies of this tag we have in input FILE
    int occurences_input = 1;
    // in case there is no associated mapping, we suppose that there is only one element
    // if this element has attributes || childs, we print it. Otherwise NO !
    // you could force that by changing "bool forcePrint = true";
    if (!mapped.isEmpty())
        occurences_input = occurences[mapped.toStdString()];

    for (int occurence = 0; occurence < occurences_input; ++occurence) {
        XMLElement * pElement = xmlDoc.NewElement(root_data.toStdString().c_str());

        if (strcmp(pElement->Value(), "variable") == 0)
            cout << "";

        int count = root->childCount();
        // help determine if node is leaf
        bool valueAsAttribute = false;

        // look for attributes if any
        // attribute are located at the last child of each TreeItem
        for (int position = count - 1; position >= 0; --position) {
            TreeItem* current_child = root->child(position);
            QString current_child_data = current_child->data(0).toString();
            QString child_path = root_path + "." + current_child_data;

            if (current_child_data.compare("Attributes") == 0) {
                // attributes of current pElement
                QString attributes_path = child_path;
                // start at 0 and do personalized treatment for attribute value
                for (int i = 0; i < current_child->childCount(); ++i) {
                    TreeItem* attribute = current_child->child(i);
                    // check for each attribute if there is an associated mapping
                    // try to use a function QString checkMapping(QString)
                    QString path = attributes_path;
                    path = path + "." + attribute->data(0).toString();
                    QString mapped = mapping[path];
                    string value;
                    if (!mapped.isEmpty()) {
                        // there is a mapping but is there a value in this input file ?
                        unordered_map<int, string> test_map = values_target[mapped.toStdString()];
                        value = test_map[occurence];
                    }

                    string att_value;
                    //if (values.is() > 0 && occurence < values.size())
                      //  att_value = values.at(occurence);
                    //else
                        att_value = value; // not needed

                    //add attribute
                    string att_name = (attribute->data(0)).toString().toStdString();

                    if (att_name.compare("value") != 0 || (att_name.compare("value") == 0 && valueAsAttribute))
                        pElement->SetAttribute(att_name.c_str(), att_value.c_str());
                    else
                        pElement->SetText(att_value.c_str());
                }

            } else {
                // children of current element
                // call the Helper function here
                print_to_xml_Helper(current_child, pElement, xmlDoc, values_target, occurences, mapping, child_path);
            }
        }

        // check if this element is leaf and if it has a value
        /** removed after the bug
        QString mapped = mapping[]
        if (count == 1 && hasAttributes && !mapped.isEmpty()) {
            // this item is a leaf
            // its mapped and may has a value
            vector<string> values = values_target[mapped.toStdString()];
            if (values.size() > 0)
                pElement->SetText(values.at(occurence).c_str());
        }
        **/

        // bind it to the parent element
        parent->InsertEndChild(pElement);
    }


}



/*
* Print to xml cible based on a source model filled with data
*
*/
void
print_to_xml (XMLDocument& xmlDoc, TreeModel* m_target, QHash<QString, QString>& mapping,
              unordered_map<string, unordered_map<int, string>>& values_target, unordered_map<string, int> &occurence) {

    // we are doing a tree traversal of our structure using a stack
    stack<TreeItem*> s;
    // root of target model
    TreeItem* root = m_target->getRoot();

    if (root->childCount() > 0)
        root = root->child(0); // replace fake root with the real one
    else
        return;

    // init stack with the root element
    s.push(root);

    // create an XML Doc
    QString root_data = root->data(0).toString();
    // insert root node
    XMLNode * pRoot = xmlDoc.NewElement(root_data.toStdString().c_str());
    xmlDoc.InsertEndChild(pRoot);


    QString path = root_data; // path used in mapping
    // print using a helper function
    for (int i = root->childCount() - 1; i > 0; --i) { // -1 because the last one is "Attributes"
        QString child_tag = root->child(i)->data(0).toString();
        QString child_path = path + "." + child_tag;
        print_to_xml_Helper(root->child(i), pRoot->ToElement(), xmlDoc, values_target, occurence, mapping, child_path);
    }

}

void saveFile(XMLDocument& xmlDoc, MainWindow* mainWindow) {
    /* prepare and save the file */
    string filename = QFileDialog::getSaveFileName(mainWindow, "Save File",
                                   QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                                          "XML (*.xml)").toStdString();
    XMLError e = xmlDoc.SaveFile(filename.c_str());
}

void MainWindow::on_btn_transform_clicked()
{
    btn_transform->setDisabled(true);
    // the Magic happens here !!

    QString fileName = lineEdit_mapping->text();

    // load mapping
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
        return;
    QDataStream in(&file);

    while (!in.atEnd()) {
        QString key, value;
        in >> key >> value;
        // key and value as key in HashMap to allow reverse mapping
        mapping[key] = value;
        mapping[value] = key;

    }

    // load target cible
    TreeModel* target_model = qobject_cast<TreeModel *> (treeViewTarget->model());

    XMLDocument xmlDoc;

    // load xml input
    char            buffer[BUFFER_SIZE];

    int num_row = model_files_input->rowCount();
    for (int i = 0; i < num_row; ++i) {
        ModelXML* model_a = new ModelXML(NULL, "Vanilla");
        QString input = model_files_input->item(i)->text();
        parse_xml(buffer, BUFFER_SIZE,  input.toStdString().c_str(), model_a, mapping);

        //transform
        print_to_xml(xmlDoc, target_model,mapping, model_a->elements, model_a->occurence);
    }

    // save
    saveFile(xmlDoc, this);
    btn_transform->setDisabled(false);
}



void MainWindow::on_btn_remove_mapping_clicked()
{
    int row = tableView->currentIndex().row();
    qDebug() << row;
    table_model->removeRow(row);
}

void MainWindow::on_btn_add_input_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Load your input"), "/", tr("File (*.xml *.xls)"));
    //lineEdit_input->setText(fileName);
    model_files_input->appendRow(new QStandardItem(fileName));
}

void MainWindow::on_btn_remove_input_clicked()
{
    int row = list_input->currentIndex().row();
    model_files_input->removeRow(row);
}

void MainWindow::on_btn_upload_model_target_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Load your mapping"), "/", tr("File (*.txt)"));

    //    char            buffer[BUFFER_SIZE];
    //    ModelXML* model_a = new ModelXML(NULL, "american");
    //    parse_xml(buffer, BUFFER_SIZE,  fileName.toStdString().c_str(), model_a, mapping);
    //    // use target model if available
    //    if (model_cible != NULL)
    //        model_target = qobject_cast<TreeModel*> (model_source);
    //    else

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
        return;
    QDataStream in(&file);

    // todo : check if file data is valid
    QStack<pair<TreeItem*, int>*> s;
    QVector<QVariant> data;
    int num;
    QVariant var;
    in >> var >> num;
    data << "Tag";
    TreeItem* root = new TreeItem(data);
    root->insertChildren(0, 1, var);
    s.push(new pair<TreeItem*, int>(root->child(0), num));
    // now we have created our root and know how many childs it has

    deserializeModel(in, s);

    model_target = new TreeModel(root);
    treeViewTarget->setModel(model_target);
}
void MainWindow::deserializeModel(QDataStream &in, QStack<pair<TreeItem*, int>*>& s) {
    if (s.empty())
        return;

    TreeItem* current = s.top()->first;
    int num_childs = s.top()->second;
    s.pop();

    QVariant var;
    int num;

    for (int i = 0; i < num_childs; ++i) { // until - 1 because the last element is Attributes
        in >> var >> num;
        current->insertChildren(i, 1, var);
        s.push(new pair<TreeItem*, int>(current->child(i), num));
        // before we continue
        deserializeModel(in, s);
    }
}

void MainWindow::on_pushButton_clicked()
{
    TreeModel* source_model = qobject_cast<TreeModel*> (sourceView->model());
    serializeModel(source_model, this);
}

void MainWindow::serializeModel(TreeModel* model, MainWindow* mainWindow)
{
    // serialize model into a file
    if (model == NULL)
        return;
    // fake root is the header, child(0) represent the tree root
    TreeItem* root = model->getRoot();
    if (root == NULL)
        return;
    root = root->child(0);

    // we suppose it's not an empty tree, checked that at beggining
    QString fileName = QFileDialog::getSaveFileName(mainWindow, "Save Mapping",
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                    "Text files (*.txt)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly))
        return;

    QDataStream out(&file);

    // we use a stack to traverse the structure and serialize it's content
    QStack<TreeItem*> s;
    // initialise it with root element
    s.push(root);

    while (!s.empty()) {
        // process each element
        TreeItem* current = s.top(); s.pop();
        // we need data but also how many childs it has to deserialize it later
        out << current->data(0) << current->childCount();
        // add childrens to stack
        for (int i = 0; i < current->childCount(); ++i) {
            s.push(current->child(i));
        }
    }

    // push to the file
    file.flush();
    file.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    TreeModel* target_model = qobject_cast<TreeModel*> (targetView->model());
    serializeModel(target_model, this);
}
