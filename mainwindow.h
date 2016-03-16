#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "treemodel.h"
#include "treemodelcompleter.h"
#include "dragdropmodel.h"

#include <QMainWindow>
#include <QModelIndex>
#include <QStandardItemModel>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void updateActions();

private slots:
    void insertChild();
    bool insertColumn(const QModelIndex &parent = QModelIndex());
    void insertRow();
    bool removeColumn(const QModelIndex &parent = QModelIndex());
    void removeRow();
    void highlight(const QModelIndex&);

    void on_btn_parcourir_source_clicked();
    void on_btn_parcourir_target_clicked();

    void on_btn_add_mapping_clicked();

    void on_btn_save_mapping_clicked();

    void on_btn_upload_mapping_clicked();

    void on_btn_upload_mapping_2_clicked();

    void on_btn_transform_clicked();

    void on_btn_remove_mapping_clicked();

    void on_btn_add_input_clicked();

    void on_btn_remove_input_clicked();

private:
    DragDropModel* model_cible;
    DragDropModel* model_source;
    TreeModelCompleter *source_completer;
    TreeModelCompleter *cible_completer;
    QStandardItemModel* model_files_input;
    QStandardItemModel* table_model;
    QHash<QString, QString> mapping;

};

#endif // MAINWINDOW_H
