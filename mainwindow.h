#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simthread.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_RunSimButton_clicked();

    void on_clearResultsButton_clicked();

    void on_scrubBox_clicked();

    void on_addBias_clicked();

    void on_removeBias_clicked();

    void on_wrUpdate_clicked();

    void on_wrBox1_currentIndexChanged(int index);

    void on_wrBox2_currentIndexChanged(int index);

    void on_defaultAllWR_clicked();

    void on_wrDefault_clicked();

    void on_numPlayers_valueChanged(int arg1);

    void on_saveButton_clicked();

    void on_biasSave_clicked();

    void on_loadBias_clicked();

    void on_findBias_clicked();

    void on_wrSave_clicked();

    void on_wrLoad_clicked();

    void on_elim1_clicked();

    void on_elim2_clicked();

private:
    Ui::MainWindow *ui;

public slots:
    void onNumberChanged(int);
    void updateResults(int);
    void biasChanged(int);
};

int getNumTourneys();

#endif // MAINWINDOW_H
