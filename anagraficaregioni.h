#ifndef ANAGRAFICAREGIONI_H
#define ANAGRAFICAREGIONI_H

#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QMap>
#include <QStringList>
#include <QVector>

namespace Ui {
class AnagraficaRegioni;
}

class AnagraficaRegioni : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnagraficaRegioni(QWidget *parent = 0);
    ~AnagraficaRegioni();

    struct fasciaR {

        QString fascia;
        int numU;
        int numD;
        double perU;
        double perD;

        fasciaR(){}

        fasciaR(QString f, int u, int d, double mu, double md){
            fascia = f;
            numU = u;
            numD = d;
            perU = mu;
            perD = md;
        }

        ~fasciaR(){}
    };

    QMap<QString, QVector<AnagraficaRegioni::fasciaR>> dict;


private slots:

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_tastoConferma_clicked();

private:
    Ui::AnagraficaRegioni *ui;

};

#endif // ANAGRAFICAREGIONI_H
