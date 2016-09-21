#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QCloseEvent;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpenFile_triggered();
    void openRecent();
    void drawInfoInStatusBar(int x);
    void closeEvent(QCloseEvent *event);

private:
    void readWindowSettings();

    Ui::MainWindow *ui;

    struct Pimpl;
    Pimpl * _impl;
};
