/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *exitAction;
    QAction *insertRowAction;
    QAction *removeRowAction;
    QAction *insertChildAction;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_10;
    QTabWidget *tabWidget_2;
    QWidget *tab_mapping;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *btn_parcourir_source;
    QTreeView *sourceView;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QPushButton *pushButton_2;
    QPushButton *btn_parcourir_target;
    QTreeView *targetView;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btn_save_mapping;
    QPushButton *btn_remove_mapping;
    QPushButton *btn_add_mapping;
    QPushButton *btn_upload_mapping;
    QTableView *tableView;
    QWidget *tab_transformation;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QPushButton *btn_upload_model_target;
    QTreeView *treeViewTarget;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_8;
    QToolButton *btn_add_input;
    QToolButton *btn_remove_input;
    QListView *list_input;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QLineEdit *lineEdit_mapping;
    QPushButton *btn_upload_mapping_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_transform;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *actionsMenu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(936, 500);
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        insertRowAction = new QAction(MainWindow);
        insertRowAction->setObjectName(QStringLiteral("insertRowAction"));
        removeRowAction = new QAction(MainWindow);
        removeRowAction->setObjectName(QStringLiteral("removeRowAction"));
        insertChildAction = new QAction(MainWindow);
        insertChildAction->setObjectName(QStringLiteral("insertChildAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setMinimumSize(QSize(400, 0));
        verticalLayout_10 = new QVBoxLayout(centralwidget);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        tabWidget_2 = new QTabWidget(centralwidget);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setMovable(true);
        tabWidget_2->setTabBarAutoHide(false);
        tab_mapping = new QWidget();
        tab_mapping->setObjectName(QStringLiteral("tab_mapping"));
        tab_mapping->setAcceptDrops(true);
        verticalLayout_6 = new QVBoxLayout(tab_mapping);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(tab_mapping);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        pushButton = new QPushButton(tab_mapping);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        btn_parcourir_source = new QPushButton(tab_mapping);
        btn_parcourir_source->setObjectName(QStringLiteral("btn_parcourir_source"));

        horizontalLayout->addWidget(btn_parcourir_source);


        verticalLayout_2->addLayout(horizontalLayout);

        sourceView = new QTreeView(tab_mapping);
        sourceView->setObjectName(QStringLiteral("sourceView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(16);
        sizePolicy.setVerticalStretch(16);
        sizePolicy.setHeightForWidth(sourceView->sizePolicy().hasHeightForWidth());
        sourceView->setSizePolicy(sizePolicy);
        sourceView->setMaximumSize(QSize(1697, 2000));
        sourceView->setAcceptDrops(true);
        sourceView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        sourceView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        sourceView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        sourceView->setDragEnabled(true);
        sourceView->setDragDropMode(QAbstractItemView::DragOnly);
        sourceView->setAlternatingRowColors(true);
        sourceView->setSelectionBehavior(QAbstractItemView::SelectItems);
        sourceView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        sourceView->setAnimated(false);
        sourceView->setAllColumnsShowFocus(true);
        sourceView->header()->setCascadingSectionResizes(true);
        sourceView->header()->setStretchLastSection(true);

        verticalLayout_2->addWidget(sourceView);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(tab_mapping);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        pushButton_2 = new QPushButton(tab_mapping);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        btn_parcourir_target = new QPushButton(tab_mapping);
        btn_parcourir_target->setObjectName(QStringLiteral("btn_parcourir_target"));

        horizontalLayout_2->addWidget(btn_parcourir_target);


        verticalLayout_3->addLayout(horizontalLayout_2);

        targetView = new QTreeView(tab_mapping);
        targetView->setObjectName(QStringLiteral("targetView"));
        targetView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        targetView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        targetView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        targetView->setAlternatingRowColors(true);
        targetView->setSelectionBehavior(QAbstractItemView::SelectItems);
        targetView->setAllColumnsShowFocus(true);
        targetView->header()->setCascadingSectionResizes(false);

        verticalLayout_3->addWidget(targetView);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout_8->addLayout(horizontalLayout_3);


        verticalLayout_6->addLayout(verticalLayout_8);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btn_save_mapping = new QPushButton(tab_mapping);
        btn_save_mapping->setObjectName(QStringLiteral("btn_save_mapping"));

        horizontalLayout_4->addWidget(btn_save_mapping);

        btn_remove_mapping = new QPushButton(tab_mapping);
        btn_remove_mapping->setObjectName(QStringLiteral("btn_remove_mapping"));

        horizontalLayout_4->addWidget(btn_remove_mapping);

        btn_add_mapping = new QPushButton(tab_mapping);
        btn_add_mapping->setObjectName(QStringLiteral("btn_add_mapping"));

        horizontalLayout_4->addWidget(btn_add_mapping);

        btn_upload_mapping = new QPushButton(tab_mapping);
        btn_upload_mapping->setObjectName(QStringLiteral("btn_upload_mapping"));

        horizontalLayout_4->addWidget(btn_upload_mapping);


        verticalLayout_4->addLayout(horizontalLayout_4);

        tableView = new QTableView(tab_mapping);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setShowGrid(true);
        tableView->setSortingEnabled(false);
        tableView->setWordWrap(true);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setStretchLastSection(false);

        verticalLayout_4->addWidget(tableView);


        verticalLayout_7->addLayout(verticalLayout_4);


        verticalLayout_6->addLayout(verticalLayout_7);

        tabWidget_2->addTab(tab_mapping, QString());
        tab_transformation = new QWidget();
        tab_transformation->setObjectName(QStringLiteral("tab_transformation"));
        tab_transformation->setAcceptDrops(true);
        verticalLayout_13 = new QVBoxLayout(tab_transformation);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_5 = new QLabel(tab_transformation);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_7->addWidget(label_5);

        btn_upload_model_target = new QPushButton(tab_transformation);
        btn_upload_model_target->setObjectName(QStringLiteral("btn_upload_model_target"));

        horizontalLayout_7->addWidget(btn_upload_model_target);


        verticalLayout_5->addLayout(horizontalLayout_7);

        treeViewTarget = new QTreeView(tab_transformation);
        treeViewTarget->setObjectName(QStringLiteral("treeViewTarget"));

        verticalLayout_5->addWidget(treeViewTarget);


        horizontalLayout_9->addLayout(verticalLayout_5);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(tab_transformation);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_5->addWidget(label_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        btn_add_input = new QToolButton(tab_transformation);
        btn_add_input->setObjectName(QStringLiteral("btn_add_input"));
        btn_add_input->setEnabled(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/inc/icons/inc/icons/add.png"), QSize(), QIcon::Selected, QIcon::On);
        btn_add_input->setIcon(icon);

        horizontalLayout_8->addWidget(btn_add_input);

        btn_remove_input = new QToolButton(tab_transformation);
        btn_remove_input->setObjectName(QStringLiteral("btn_remove_input"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/inc/icons/inc/icons/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_remove_input->setIcon(icon1);

        horizontalLayout_8->addWidget(btn_remove_input);


        horizontalLayout_5->addLayout(horizontalLayout_8);


        verticalLayout_9->addLayout(horizontalLayout_5);

        list_input = new QListView(tab_transformation);
        list_input->setObjectName(QStringLiteral("list_input"));
        list_input->setEnabled(true);

        verticalLayout_9->addWidget(list_input);


        verticalLayout_11->addLayout(verticalLayout_9);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label = new QLabel(tab_transformation);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_6->addWidget(label);

        lineEdit_mapping = new QLineEdit(tab_transformation);
        lineEdit_mapping->setObjectName(QStringLiteral("lineEdit_mapping"));

        horizontalLayout_6->addWidget(lineEdit_mapping);

        btn_upload_mapping_2 = new QPushButton(tab_transformation);
        btn_upload_mapping_2->setObjectName(QStringLiteral("btn_upload_mapping_2"));

        horizontalLayout_6->addWidget(btn_upload_mapping_2);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_11->addLayout(verticalLayout);


        horizontalLayout_9->addLayout(verticalLayout_11);


        verticalLayout_12->addLayout(horizontalLayout_9);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_12->addItem(horizontalSpacer);

        btn_transform = new QPushButton(tab_transformation);
        btn_transform->setObjectName(QStringLiteral("btn_transform"));
        btn_transform->setEnabled(true);

        verticalLayout_12->addWidget(btn_transform);


        verticalLayout_13->addLayout(verticalLayout_12);

        tabWidget_2->addTab(tab_transformation, QString());

        verticalLayout_10->addWidget(tabWidget_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 936, 22));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QStringLiteral("fileMenu"));
        actionsMenu = new QMenu(menubar);
        actionsMenu->setObjectName(QStringLiteral("actionsMenu"));
        MainWindow->setMenuBar(menubar);
        QWidget::setTabOrder(btn_parcourir_target, btn_parcourir_source);
        QWidget::setTabOrder(btn_parcourir_source, targetView);
        QWidget::setTabOrder(targetView, btn_upload_mapping);
        QWidget::setTabOrder(btn_upload_mapping, sourceView);
        QWidget::setTabOrder(sourceView, btn_save_mapping);
        QWidget::setTabOrder(btn_save_mapping, tableView);

        menubar->addAction(fileMenu->menuAction());
        menubar->addAction(actionsMenu->menuAction());
        fileMenu->addAction(exitAction);
        actionsMenu->addAction(insertRowAction);
        actionsMenu->addSeparator();
        actionsMenu->addAction(removeRowAction);
        actionsMenu->addSeparator();
        actionsMenu->addAction(insertChildAction);

        retranslateUi(MainWindow);

        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Efficiency MC - Transformateur de flux", 0));
        exitAction->setText(QApplication::translate("MainWindow", "E&xit", 0));
        exitAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        insertRowAction->setText(QApplication::translate("MainWindow", "Insert Row", 0));
        insertRowAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+I, R", 0));
        removeRowAction->setText(QApplication::translate("MainWindow", "Remove Row", 0));
        removeRowAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+R, R", 0));
        insertChildAction->setText(QApplication::translate("MainWindow", "Insert Child", 0));
        insertChildAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        label_3->setText(QApplication::translate("MainWindow", "Model source", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Save", 0));
        btn_parcourir_source->setText(QApplication::translate("MainWindow", "Upload", 0));
        label_4->setText(QApplication::translate("MainWindow", "Model cible", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Save", 0));
        btn_parcourir_target->setText(QApplication::translate("MainWindow", "Upload", 0));
        btn_save_mapping->setText(QApplication::translate("MainWindow", "Save", 0));
        btn_remove_mapping->setText(QApplication::translate("MainWindow", "Remove", 0));
        btn_add_mapping->setText(QApplication::translate("MainWindow", "Add", 0));
        btn_upload_mapping->setText(QApplication::translate("MainWindow", "Upload", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_mapping), QApplication::translate("MainWindow", "Mapping", 0));
        label_5->setText(QApplication::translate("MainWindow", "Model Cible", 0));
        btn_upload_model_target->setText(QApplication::translate("MainWindow", "Upload", 0));
        label_2->setText(QApplication::translate("MainWindow", "Input", 0));
        btn_add_input->setText(QApplication::translate("MainWindow", "...", 0));
        btn_remove_input->setText(QApplication::translate("MainWindow", "...", 0));
        label->setText(QApplication::translate("MainWindow", "Mapping", 0));
        btn_upload_mapping_2->setText(QApplication::translate("MainWindow", "Upload", 0));
        btn_transform->setText(QApplication::translate("MainWindow", "Transform", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_transformation), QApplication::translate("MainWindow", "Transformation", 0));
        fileMenu->setTitle(QApplication::translate("MainWindow", "&File", 0));
        actionsMenu->setTitle(QApplication::translate("MainWindow", "&Actions", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
