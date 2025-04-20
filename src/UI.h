//
// Created by Jennifer Moloney on 4/8/25.
//

#ifndef SENTIMENTANALYSIS_UI_H
#define SENTIMENTANALYSIS_UI_H


#include <QMainWindow>
#include <QString>
#include "hashmap.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QGroupBox;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void analyzeText();
    void selectOpenAddressing();
    void selectSeparateChaining();

private:
    // UI components
    QLabel *titleLabel;
    QLineEdit *inputEdit;
    QPushButton *goButton;

    QPushButton *openAddressingButton;
    QPushButton *separateChainingButton;

    QLabel *sentimentResultLabel;
    QLabel *sentimentExplanationLabel;
    QGroupBox *metricsGroup;
    QLabel *metricsLabel;

    QString currentAlgorithm;
    HM_separateChaining m_separateMap;
    HM_linearProbing  m_openMap;
    long long insertionTimeLP = 0;
    long long insertionTimeSC= 0;
    long long searchTimeLP = 0;
    long long searchTimeSC = 0;
    float computeScore(const QString &text);
    void updateMetricsDisplay();
};

#endif //SENTIMENTANALYSIS_UI_H
