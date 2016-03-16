#include "mainwindow.h"
#include "expat.h"
#include <QApplication>
#include "emc_parse_utility.h"
#include <QTreeView>


#define BUFFER_SIZE 100000

int main(int argc, char *argv[])
{

//    char            buffer[BUFFER_SIZE];
//    Model_XML* model_a = new Model_XML(&root, "americain");
//    Model_XML* model_b = new Model_XML(&root, "vanilla");
//    model_a = parse_xml(buffer, BUFFER_SIZE,  "/Users/Abderrahmane/Documents/Efficiency\ MC/StaticData/StaticData/StaticData/americain.xml", model_a);
//    model_b = parse_xml(buffer, BUFFER_SIZE,  "/Users/Abderrahmane/Downloads/reneedanxmlexampletoteston/EQD\ Index\ Option\ Vanilla\ 564001587.xml", model_b);
//    print_to_xml(model_a, model_b);

    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();


}
