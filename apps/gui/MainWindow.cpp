#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "DataParser.h"

#include <QDir>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text file (*.txt)"));
    if (!fileName.isEmpty()) {
        DataParser parser(fileName);
        auto data = parser.getData();

        QHashIterator<QString, int> i(data);
        while (i.hasNext()) {
            i.next();
            qDebug() << i.key() << ": " << i.value();
        }
    }

}
