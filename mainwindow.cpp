#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QProgressBar"
#include "sim.h"
#include "simthread.h"
#include "globals.h"
#include <fstream>
#include <QDebug>
#include <QFileDialog>
#include <sstream>
#include <math.h>

extern bool singleElim;
extern bool doubleElim;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    loadDecks();
    for (int i = 0; i < (int)deckNames.size(); i++){
        qDebug() << QString::fromStdString(deckNames[i]);
        ui->biasDeck1->addItem(QString::fromStdString(deckNames[i]));
        ui->biasDeck2->addItem(QString::fromStdString(deckNames[i]));
        ui->biasDeck3->addItem(QString::fromStdString(deckNames[i]));
        ui->wrBox1->addItem(QString::fromStdString(deckNames[i]));
        ui->wrBox2->addItem(QString::fromStdString(deckNames[i]));
        ui->scrubBox->setCheckState(Qt::Checked);
        ui->roundsLabel->setText(QString::number(rounds(tourneySize)));
        ui->topCutLabel->setText(QString::number(cut(tourneySize)));
    }
    connect(ui->chooseBias, SIGNAL(currentIndexChanged(int)), this, SLOT(biasChanged(int)));
}

MainWindow::~MainWindow(){
    delete ui;
}

//Slot implementation
void MainWindow::onNumberChanged(int Number){
    ui->progressBar->setValue(Number);
    if (Number != 1){
        int currentNum = 1 + ui->numTourneyLabel->text().toInt();
        ui->numTourneyLabel->setText(QString::number(currentNum));
    }
    //Debug() << curr+Number;
}

//When the chooseBias combo box index is changed.
void MainWindow::biasChanged(int i){
    if (ui->chooseBias->count() == 0 || bias.empty())
        return;
    ui->biasDeck1->setCurrentIndex(bias[i].decks[0].currentIndex());
    qDebug() << bias[i].decks[0].currentIndex();
    ui->biasDeck2->setCurrentIndex(bias[i].decks[1].currentIndex());
    ui->biasDeck3->setCurrentIndex(bias[i].decks[2].currentIndex());
    ui->biasSpin->setValue(bias[i].bias*100.0);
}

void MainWindow::updateResults(int num){
    ui->resultsTable->setRowCount((int)result.size());
    for (int row = 0; row < (int)result.size(); row++){
        ui->resultsTable->setVerticalHeaderItem(row, new QTableWidgetItem(QString::number(row+1)));
        //First we want to order the decks in results to make it look prettier.
        std::sort(std::begin(result[row].decks), std::end(result[row].decks));
        for (int col = 0; col < ui->resultsTable->columnCount(); col++){
            switch (col){
            case 0:
            case 1:
            case 2:
                ui->resultsTable->setItem(row, col, new QTableWidgetItem(QString::fromStdString(result[row].decks[col].name)));
                break;
            case 3:
                //qDebug() << QString::fromStdString(result[row].getTops());

                ui->resultsTable->setItem(row, col, new QTableWidgetItem(QString::fromStdString(result[row].getTops())));
                break;
            case 4:
                ui->resultsTable->setItem(row, col, new QTableWidgetItem(QString::number(result[row].wins)));
                break;
            case 5:
                ui->resultsTable->setItem(row, col, new QTableWidgetItem(QString::number(result[row].losses)));
                break;
            case 6:
                ui->resultsTable->setItem(row, col, new QTableWidgetItem(QString::number(100*(double)result[row].winRate())));
                break;
            case 7:
                ui->resultsTable->setItem(row, col, new QTableWidgetItem(QString::number((int)result[row].placings.size())));
                break;
            case 8:
                ui->resultsTable->setItem(row, col, new QTableWidgetItem(QString::number(100.0*(double)result[row].placings.size()/(double)result[row].occurrences)));
                break;
            case 9:
                ui->resultsTable->setItem(row, col, new QTableWidgetItem(QString::number((int)result[row].occurrences)));
                break;
            default:
                //Never reaches here due to for loop cap.
                break;
            }
        }
    }
    ui->SimulationProgressLabel->setText("Simulations Complete.");
    ui->RunSimButton->setEnabled(true);
    ui->numSimulations->setEnabled(true);
    ui->numPlayers->setEnabled(true);
    ui->clearResultsButton->setEnabled(true);
    ui->scrubBox->setEnabled(true);
    ui->addBias->setEnabled(true);
    ui->removeBias->setEnabled(true);
    ui->wrUpdate->setEnabled(true);
    ui->wrDefault->setEnabled(true);
    ui->defaultAllWR->setEnabled(true);
    ui->saveButton->setEnabled(true);
    ui->biasSave->setEnabled(true);
    ui->chooseBias->setEnabled(true);
    ui->addBias->setEnabled(true);
    ui->removeBias->setEnabled(true);
    ui->loadBias->setEnabled(true);
    ui->findBias->setEnabled(true);
    ui->wrSave->setEnabled(true);
    ui->wrLoad->setEnabled(true);

}

void MainWindow::on_RunSimButton_clicked(){

    ui->RunSimButton->setEnabled(false);
    ui->numSimulations->setEnabled(false);
    ui->numPlayers->setEnabled(false);
    ui->clearResultsButton->setEnabled(false);
    ui->scrubBox->setEnabled(false);
    ui->addBias->setEnabled(false);
    ui->removeBias->setEnabled(false);
    ui->wrUpdate->setEnabled(false);
    ui->wrDefault->setEnabled(false);
    ui->defaultAllWR->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->biasSave->setEnabled(false);
    ui->chooseBias->setEnabled(false);
    ui->addBias->setEnabled(false);
    ui->removeBias->setEnabled(false);
    ui->loadBias->setEnabled(false);
    ui->findBias->setEnabled(false);
    ui->wrSave->setEnabled(false);
    ui->wrLoad->setEnabled(false);

    QString numTourneysInput = ui->numSimulations->text();
    int numP = ui->numPlayers->text().toInt();
    if (numP < 2){
        ui->numPlayers->setValue(tourneySize);
    }
    else
        tourneySize = numP;


    int numSims;
    numSims = numTourneysInput.toInt();
    if (numSims < 1){
        numSims = 100;
        ui->numSimulations->setValue(100);
    }

    ui->SimulationProgressLabel->setText("Simulations Running.");

    //Call simthread
    simThread *sim = new simThread;

    sim->stop = false;
    sim->numSims = numSims;

    ui->progressBar->setRange(0,numSims);

    //Debug() << "Beginning connection.";
    connect(sim, SIGNAL(percentChanged(int)), this, SLOT(onNumberChanged(int)));
    connect(sim, SIGNAL(runComplete(int)), this, SLOT(updateResults(int)));
    //Debug() << "Connection complete.";
    sim->start();
    //Debug()<< "Simulations started.";
}

void MainWindow::on_clearResultsButton_clicked(){
    ui->clearResultsButton->setEnabled(false);
    ui->SimulationProgressLabel->setText("No Simulations Running.");
    ui->progressBar->setValue(0);
    ui->numPlayers->clear();
    ui->numSimulations->clear();
    ui->numTourneyLabel->setText(QString::number(0));
    for (int row = 0; row < (int)result.size(); row++)
        for (int col = 0; col < ui->resultsTable->columnCount(); col++)
            ui->resultsTable->setItem(row, col, new QTableWidgetItem(QString::fromStdString("")));
    result.clear();
    ui->resultsTable->viewport()->update();
    ui->clearResultsButton->setEnabled(true);
}

void MainWindow::on_scrubBox_clicked(){
    addScrubs = !addScrubs;
}

void MainWindow::on_addBias_clicked(){
    ui->addBias->setEnabled(false);
    QString line = ui->biasLine->text();
    if (line == ""){
        ui->biasErrorLabel->setText("You must enter a name.");
        ui->addBias->setEnabled(true);
        return;
    }
    player toBePushed;
    toBePushed.decks[0].name = ui->biasDeck1->currentText().toStdString();
    toBePushed.decks[1].name = ui->biasDeck2->currentText().toStdString();
    toBePushed.decks[2].name = ui->biasDeck3->currentText().toStdString();
    toBePushed.bias = ui->biasSpin->text().toDouble()/100.0;
    //Check if same class used twice.
    if (toBePushed.decks[0].sameClass(toBePushed.decks[1]) || toBePushed.decks[0].sameClass(toBePushed.decks[2]) || toBePushed.decks[2].sameClass(toBePushed.decks[1])){
        ui->biasErrorLabel->setText("Decks must be of different classes.");
        ui->addBias->setEnabled(true);
        return;
    }
    //Prevent duplicates of same name / combinations.
    toBePushed.name = line.toStdString();
    for (int i = 0; i < (int)bias.size(); i++)
        if (bias[i].name == toBePushed.name || bias[i].same(toBePushed)){
            ui->biasErrorLabel->setText("Duplicate player name or deck combination.");
            ui->addBias->setEnabled(true);
            return;
        }

    bias.push_back(toBePushed);
    ui->biasErrorLabel->clear();
    ui->chooseBias->addItem(line);
    ui->chooseBias->setCurrentIndex(ui->chooseBias->count()-1);
    ui->biasLine->clear();
    ui->removeBias->setEnabled(true);
    ui->addBias->setEnabled(true);
}

void MainWindow::on_removeBias_clicked(){
    ui->biasLine->clear();
    ui->biasErrorLabel->clear();
    bias.erase(bias.begin() + ui->chooseBias->currentIndex());
    if (ui->chooseBias->count() == 0 )//|| bias.empty())
        return;
    ui->chooseBias->removeItem(ui->chooseBias->currentIndex());
    if (ui->chooseBias->count() == 0){
        ui->removeBias->setEnabled(false);
    }
}

void MainWindow::on_wrUpdate_clicked(){
    QString deckA = ui->wrBox1->currentText();
    QString deckB = ui->wrBox2->currentText();

    //Mirror matches are even.
    if (deckA == deckB){
        ui->wrSpinBox->setValue(50);
        return;
    }
    setWR(deckA, deckB, ui->wrSpinBox->value()/100.0);
}


void MainWindow::on_wrBox1_currentIndexChanged(int index){
    //Deck A has been changed.
    ui->wrSpinBox->setValue(100*wins(ui->wrBox1->currentText().toStdString(), ui->wrBox2->currentText().toStdString()));
}


void MainWindow::on_wrBox2_currentIndexChanged(int index){
    ui->wrSpinBox->setValue(100*wins(ui->wrBox1->currentText().toStdString(), ui->wrBox2->currentText().toStdString()));
}

void MainWindow::on_defaultAllWR_clicked(){
    for (int i = 0; i < (int)possibleDecks.size(); i++){
        for (int j = 0; j < (int)possibleDecks.size(); j++){
            setWRDefault(QString::fromStdString(possibleDecks[i].name), QString::fromStdString(possibleDecks[j].name));
        }
    }
    ui->wrSpinBox->setValue(100*wins(ui->wrBox1->currentText().toStdString(), ui->wrBox2->currentText().toStdString()));
}

void MainWindow::on_wrDefault_clicked(){
    QString deckA = ui->wrBox1->currentText();
    QString deckB = ui->wrBox2->currentText();

    //Mirror matches are even.
    if (deckA == deckB){
        ui->wrSpinBox->setValue(50);
        return;
    }
    setWRDefault(deckA, deckB);
    ui->wrSpinBox->setValue(100*wins(ui->wrBox1->currentText().toStdString(), ui->wrBox2->currentText().toStdString()));
}

void MainWindow::on_numPlayers_valueChanged(int num){
    if (ui->elim1->isChecked()){
        ui->roundsLabel->setText(QString::number(ceil(log2(ui->numPlayers->value()))));
        return;
    }

    if (ui->elim2->isChecked()){
        ui->roundsLabel->setText(QString::number(ceil(log2(ui->numPlayers->value()))+ceil(log2(log2(ui->numPlayers->value())))));
        return;
    }

    //We update the rounds label and the top cut label.
    ui->roundsLabel->setText(QString::number(rounds(num)));
    ui->topCutLabel->setText(QString::number(cut(num)));
}

void MainWindow::on_saveButton_clicked(){
    ui->saveButton->setEnabled(false);
    //QFile file("somefile.csv");
    std::fstream outfile;
    std::string filename = QFileDialog::getSaveFileName(this, tr("CSV file"), qApp->applicationDirPath (),tr("CSV File (*.csv)")).toStdString();
    if (filename.empty())
        return;

    outfile.open(filename, std::fstream:: in | std::fstream::out | std::fstream::app);
    if (true) {
        //QDataStream stream(&file);
        //qint32 n(ui->resultsTable->rowCount()), m(ui->resultsTable->columnCount());
        //stream << n << m;

        for (int i = 0; i < (int)ui->resultsTable->rowCount(); i++){
            for (int j = 0; j < (int)ui->resultsTable->columnCount(); j++){
                QString temp = ui->resultsTable->item(i,j)->text();
                if (j == 3){
                    //Printing out the vector of tops.
                    temp.insert(0, '"');
                    temp.append('"');
                }
                if (j + 1 != (int)ui->resultsTable->columnCount()){
                    temp.append(',');
                }
                else
                    temp.append('\n');
                outfile << temp.toStdString();
            }
        }

        //for (int i=0; i<n; ++i)
          //  for (int j=0; j<m; j++)
            //    ui->resultsTable->item(i,j)->write(stream);

        outfile.close();
    }
    ui->saveButton->setEnabled(true);
}

void MainWindow::on_biasSave_clicked(){

    std::fstream outfile;
    std::string filename = QFileDialog::getSaveFileName(this, tr("CSV file"), qApp->applicationDirPath (),tr("CSV File (*.csv)")).toStdString();
    if (filename.empty())
        return;
    ui->biasSave->setEnabled(false);
    ui->chooseBias->setEnabled(false);
    ui->addBias->setEnabled(false);
    ui->removeBias->setEnabled(false);
    ui->loadBias->setEnabled(false);
    ui->findBias->setEnabled(false);
    outfile.open(filename, std::fstream:: in | std::fstream::out | std::fstream::app);
    if (true) {
        //QDataStream stream(&file);
        //qint32 n(ui->resultsTable->rowCount()), m(ui->resultsTable->columnCount());
        //stream << n << m;

        for (int i = 0; i < (int)ui->chooseBias->count(); i++){
            //We loop through each index.
            QString biasName = ui->chooseBias->itemText(i);
            ui->chooseBias->setCurrentIndex(i);
            QString deck1 = ui->biasDeck1->currentText();
            QString deck2 = ui->biasDeck2->currentText();
            QString deck3 = ui->biasDeck3->currentText();
            double biasPercent = ui->biasSpin->value()/100.0;
            outfile << biasName.toStdString() << ", " << deck1.toStdString() << ", " << deck2.toStdString() << ", " << deck3.toStdString() << ", " << biasPercent << endl;
        }

        //for (int i=0; i<n; ++i)
          //  for (int j=0; j<m; j++)
            //    ui->resultsTable->item(i,j)->write(stream);


        ui->biasSave->setEnabled(true);
        ui->chooseBias->setEnabled(true);
        ui->addBias->setEnabled(true);
        ui->removeBias->setEnabled(true);
        ui->loadBias->setEnabled(true);
        ui->findBias->setEnabled(true);
        outfile.close();
    }
}

void MainWindow::on_loadBias_clicked(){
    ui->biasSave->setEnabled(false);
    ui->chooseBias->setEnabled(false);
    ui->addBias->setEnabled(false);
    ui->removeBias->setEnabled(false);
    ui->loadBias->setEnabled(false);
    ui->findBias->setEnabled(false);

    std::fstream infile;
    std::string filename = QFileDialog::getOpenFileName(this, tr("CSV file"), qApp->applicationDirPath (),tr("CSV File (*.csv)")).toStdString();
    if (filename.empty())
        return;

    infile.open(filename, std::fstream:: in | std::fstream::out | std::fstream::app);
    if (true) {
        //QDataStream stream(&file);
        //qint32 n(ui->resultsTable->rowCount()), m(ui->resultsTable->columnCount());
        //stream << n << m;


        ui->chooseBias->clear();
        bias.clear();
        for (std::string line; getline( infile, line );){
            //qDebug() << QString::fromStdString(line);

            //We loop through each index.
            std::istringstream ss(line);
            std::string token;
            vector<std::string> record;
            while(std::getline(ss, token, ',')) {
                record.push_back(token);
               //qDebug() () << QString::fromStdString(token);
            }
            player temp;
           //qDebug() () << 1;
            QString namae = QString::fromStdString(record[0]);
           //qDebug() () << namae;
            ui->chooseBias->addItem(namae);
           //qDebug() () << namae;
            QString d1 = QString::fromStdString(record[1]);
            QString d2 = QString::fromStdString(record[2]);
            QString d3 = QString::fromStdString(record[3]);
            QString num = QString::fromStdString(record[4]);
            d1.remove(0,1);
            d2.remove(0,1);
            d3.remove(0,1);
            num.remove(0,1);
            double d = num.toDouble();
            temp.decks[0].name = d1.toStdString();
            temp.decks[1].name = d2.toStdString();
            temp.decks[2].name = d3.toStdString();
            temp.bias = d;
            bias.push_back(temp);
        }


        //for (int i=0; i<n; ++i)
          //  for (int j=0; j<m; j++)
            //    ui->resultsTable->item(i,j)->write(stream);

        infile.close();
    }
    ui->chooseBias->setCurrentIndex(0);


    ui->biasSave->setEnabled(true);
    ui->chooseBias->setEnabled(true);
    ui->addBias->setEnabled(true);
    ui->removeBias->setEnabled(true);
    ui->loadBias->setEnabled(true);
    ui->findBias->setEnabled(true);
}

void MainWindow::on_findBias_clicked(){
    string deck1 = ui->biasDeck1->currentText().toStdString();
    string deck2 = ui->biasDeck2->currentText().toStdString();
    string deck3 = ui->biasDeck3->currentText().toStdString();
    vector<string> v;
    v.push_back(deck1);
    v.push_back(deck2);
    v.push_back(deck3);
    sort(v.begin(), v.end());

    for (int i = 0; i < (int)result.size(); i++){

        if (result[i].decks[0].name == v[0])
            if (result[i].decks[1].name == v[1])
                if (result[i].decks[2].name == v[2]){
                    ui->resultsTable->selectRow(i);
                }

    }
}

void MainWindow::on_wrSave_clicked(){
    std::fstream outfile;
    std::string filename = QFileDialog::getSaveFileName(this, tr("Match Ups"), qApp->applicationDirPath (),tr("MU File (*.mu)")).toStdString();
    if (filename.empty())
        return;

    outfile.open(filename, std::fstream:: in | std::fstream::out | std::fstream::app);
    if (true) {
        //QDataStream stream(&file);
        //qint32 n(ui->resultsTable->rowCount()), m(ui->resultsTable->columnCount());
        //stream << n << m;

        loadDecks();
        for (int i = 0;  i < (int)possibleDecks.size(); i++){
            for (int j = 0; j < (int)possibleDecks.size(); j++){
                if (possibleDecks[i].name == possibleDecks[j].name)
                    continue;
                outfile << wins(possibleDecks[i],possibleDecks[j]) << endl;
            }
        }
    }
    outfile.close();
}

void MainWindow::on_wrLoad_clicked(){
    std::fstream infile;
    std::string filename = QFileDialog::getOpenFileName(this, tr("Match Ups"), qApp->applicationDirPath (),tr("MU File (*.mu)")).toStdString();
    if (filename.empty())
        return;

    infile.open(filename, std::fstream:: in | std::fstream::out | std::fstream::app);

    for (int i = 0;  i < (int)possibleDecks.size(); i++){
        for (int j = 0; j < (int)possibleDecks.size(); j++){
            if (possibleDecks[i].name == possibleDecks[j].name)
                continue;
            std::string line;
            getline( infile, line);
            double rate = QString::fromStdString(line).toDouble();
            setWR(QString::fromStdString(possibleDecks[i].name), QString::fromStdString(possibleDecks[j].name), rate);
        }
    }

    infile.close();
    ui->wrBox1->setCurrentIndex(0);
    ui->wrBox2->setCurrentIndex(0);
}

void MainWindow::on_elim1_clicked(){
    ui->elim2->setChecked(false);
    ui->roundsLabel->setText(QString::number(ceil(log2(ui->numPlayers->value()))));
    ui->topCutLabel->setText("NA");

    singleElim = ui->elim1->isChecked();
    doubleElim = ui->elim2->isChecked();
}

void MainWindow::on_elim2_clicked(){
    ui->elim1->setChecked(false);
    ui->roundsLabel->setText(QString::number(ceil(log2(ui->numPlayers->value()))+ceil(log2(log2(ui->numPlayers->value())))));
    ui->topCutLabel->setText("NA");

    singleElim = ui->elim1->isChecked();
    doubleElim = ui->elim2->isChecked();
}
