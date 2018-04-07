#include "anagraficaregioni.h"
#include "ui_anagraficaregioni.h"
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QMap>
#include <QStringList>
#include <QVector>

QString readFileData(QString Filename){
    QFile mFile(Filename);
    if (mFile.exists()){
        mFile.open(QFile::ReadOnly | QFile::Text);
        if(!mFile.isOpen()){
            //qDebug() << "File could not be opened in Read mode!";
            return "error";
        }
        QTextStream in(&mFile);
        QString mText = in.readAll();
        mFile.close();
        return mText;
    }
    return "error";
}

void parseData(QString in, QMap<QString, QVector<AnagraficaRegioni::fasciaR>> &anagrafica){
    QVector<AnagraficaRegioni::fasciaR> abruzzo;
    QVector<AnagraficaRegioni::fasciaR> emilia;
    QVector<AnagraficaRegioni::fasciaR> lombardia;
    QVector<AnagraficaRegioni::fasciaR> toscana;
    QStringList list = in.split("\n", QString::SplitBehavior::SkipEmptyParts);
    list.removeLast();
    foreach(const QString &str, list){
        QStringList record = str.split(" ", QString::SplitBehavior::SkipEmptyParts);
        QString id = record[0];
        QString f = record[1];
        int u = (record[2]).toInt();
        int d = (record[3]).toInt();
        double mU = ((double)u/(u+d))*100;
        double mD = 100 - mU;
        AnagraficaRegioni::fasciaR parsed(f,u,d,mU,mD);
        //qDebug() <<  id << f <<  u <<  d <<  mU <<  mD;
        if(id == "Abruzzo"){
            abruzzo.push_back(parsed);
        }
        else if(id == "Emilia-Romagna"){
            emilia.push_back(parsed);
        }
        else if(id == "Lombardia"){
            lombardia.push_back(parsed);
        }
        else if(id == "Toscana"){
            toscana.push_back(parsed);
        }
    }
    anagrafica.insert("Abruzzo", abruzzo);
    anagrafica.insert("Emilia-Romagna", emilia);
    anagrafica.insert("Lombardia", lombardia);
    anagrafica.insert("Toscana", toscana);
    /*
    for(int i=0; i<anagrafica->value("Abruzzo").count(); i++){
        qDebug() <<anagrafica->value("Abruzzo")[i].fascia;
    };
    */
    //qDebug() << anagrafica->value("Abruzzo").count();

}

AnagraficaRegioni::AnagraficaRegioni(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnagraficaRegioni)
{

    ui->setupUi(this);
    ui->Risultati->setSortingEnabled(false);

}

AnagraficaRegioni::~AnagraficaRegioni()
{
    delete ui;
}


void AnagraficaRegioni::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->SelRegion->setText(arg1);
    //qDebug() << arg1;

    QVector<AnagraficaRegioni::fasciaR> regione = dict.value(arg1);
    int rows = regione.count();
    ui->Risultati->setRowCount(rows);
    ui->Risultati->setColumnCount(5);
    for(int r=0; r<rows; r++){
        ui->Risultati->setItem(r,0,new QTableWidgetItem(regione[r].fascia));
        ui->Risultati->setItem(r,1,new QTableWidgetItem(QString::number(regione[r].numU)));
        ui->Risultati->setItem(r,2,new QTableWidgetItem(QString::number(regione[r].perU)));
        ui->Risultati->setItem(r,3,new QTableWidgetItem(QString::number(regione[r].numD)));
        ui->Risultati->setItem(r,4,new QTableWidgetItem(QString::number(regione[r].perD)));
    }
}

void AnagraficaRegioni::on_tastoConferma_clicked()
{
    QString filename = ui->percorsoFile->toPlainText();
    if(filename == ""){
        ui->percorsoFile->clear();
        ui->percorsoFile->appendPlainText("Errore, nessun percorso fornito!");
    }
    else{
        QString mText = readFileData(filename);
        if(mText != "error"){
            parseData(mText, dict);
            ui->comboBox->clear();
            ui->comboBox->addItems(dict.keys());
            ui->percorsoFile->clear();
            ui->percorsoFile->setVisible(false);
            ui->tastoConferma->setVisible(false);
            ui->istruzioni->clear();
            ui->istruzioni->setText("Il file\n" + filename + "\nè stato caricato correttamente.");
        }
        ui->percorsoFile->clear();
        ui->percorsoFile->appendPlainText("Errore, controllare il percorso fornito!");
    }
}
