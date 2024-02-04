#include <QRegularExpression>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Tarkista, että käyttäjä antaa tiedoston nimen komentoriviparametrina
    // if (argc != 2) {
    //     qDebug() << "Käytä: WordFrequencyCounter <tiedostonimi>";
    //     return 1;
    // }

    // Avaa tiedosto
    QString tiedostonimi = QString::fromUtf8(argv[1]);
    QFile tiedosto("c:/temp/bowie.txt");

    if (!tiedosto.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Tiedoston avaaminen epäonnistui:" << tiedosto.errorString();
        return 1;
    }

    // Luodaan QMap tallentamaan sanojen frekvenssit
    QMap<QString, int> sanatFrekvenssit;

    // Luetaan tiedoston sisältö
    QTextStream virta(&tiedosto);
    while (!virta.atEnd()) {
        QString rivi = virta.readLine();
        QStringList sanat = rivi.split(QRegularExpression("\\W+"), Qt::SkipEmptyParts);

        // Päivitetään sanan frekvenssiä
        for (const QString &sana : sanat) {
            sanatFrekvenssit[sana.toLower()]++;
        }
    }

    // Sulje tiedosto
    tiedosto.close();

    // Tulosta sanojen frekvenssit
    qDebug() << "Sanojen frekvenssit tiedostossa" << tiedostonimi << ":";
    for (auto it = sanatFrekvenssit.begin(); it != sanatFrekvenssit.end(); ++it) {
        qDebug() << it.key() << ":" << it.value();
    }

    return 0;
}
