#include "UI.h"
#include "hashmap.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>
#include <QSpacerItem>
#include <QSizePolicy>
#include <iomanip>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    titleLabel = new QLabel("Analyze the Sentiment of your Message", this);
    titleLabel->setStyleSheet(
            "QLabel {"
            "   color: #6A5ACD;"
            "   font-size: 35pt;"
            "   font-weight: bold;"
            "}"
    );
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputEdit = new QLineEdit(this);
    inputEdit->setPlaceholderText("Enter your message here...");
    inputEdit->setStyleSheet(
            "QLineEdit {"
            "   border: 2px solid #FFC0CB;"
            "   border-radius: 12px;"
            "   padding: 6px;"
            "   font-size: 20pt;"
            "}"
    );
    goButton = new QPushButton("Go!", this);
    goButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #FFB6C1;"
            "   border: 1px solid #ff9aa2;"
            "   border-radius: 12px;"
            "   padding: 8px 16px;"
            "   font-size: 20pt;"
            "}"
            "QPushButton:hover {"
            "   background-color: #FFA6B2;"
            "}"
    );
    inputLayout->addWidget(inputEdit);
    inputLayout->addWidget(goButton);
    mainLayout->addLayout(inputLayout);

    QVBoxLayout *sentimentLabelsLayout = new QVBoxLayout();
    sentimentLabelsLayout->setAlignment(Qt::AlignCenter);

    sentimentResultLabel = new QLabel("", this);
    sentimentResultLabel->setAlignment(Qt::AlignCenter);
    sentimentResultLabel->setVisible(false);
    sentimentResultLabel->setStyleSheet(
            "QLabel {"
            "   font-size: 28pt;"
            "   font-weight: bold;"
            "   color: #4B0082;"
            "}"
    );

    sentimentExplanationLabel = new QLabel("", this);
    sentimentExplanationLabel->setAlignment(Qt::AlignCenter);
    sentimentExplanationLabel->setVisible(false);
    sentimentExplanationLabel->setStyleSheet(
            "QLabel {"
            "   font-size: 28pt;"
            "   font-weight: bold;"
            "   color: #4B0082;"
            "}"
    );

    sentimentLabelsLayout->addWidget(sentimentResultLabel);
    sentimentLabelsLayout->addWidget(sentimentExplanationLabel);

    mainLayout->addLayout(sentimentLabelsLayout);


    mainLayout->addStretch();

    QHBoxLayout *bottomLayout = new QHBoxLayout();


    QVBoxLayout *leftColumn = new QVBoxLayout();
    openAddressingButton = new QPushButton("Open Addressing", this);
    openAddressingButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #FFB6C1;"
            "   border: 1px solid #ff9aa2;"
            "   border-radius: 10px;"
            "   padding: 8px 16px;"
            "   font-size: 20pt;"
            "}"
            "QPushButton:hover {"
            "   background-color: #FFA6B2;"
            "}"
    );
    separateChainingButton = new QPushButton("Separate Chaining", this);
    separateChainingButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #FFB6C1;"
            "   border: 1px solid #ff9aa2;"
            "   border-radius: 10px;"
            "   padding: 8px 16px;"
            "   font-size: 20pt;"
            "}"
            "QPushButton:hover {"
            "   background-color: #FFA6B2;"
            "}"
    );
    leftColumn->addWidget(openAddressingButton);
    leftColumn->addWidget(separateChainingButton);
    bottomLayout->addLayout(leftColumn);

    QVBoxLayout *rightColumn = new QVBoxLayout();
    metricsGroup = new QGroupBox("Metrics", this);
    QVBoxLayout *metricsLayout = new QVBoxLayout(metricsGroup);
    metricsLabel = new QLabel("", this);
    metricsLabel->setStyleSheet("font-size: 20pt;");
    metricsLayout->addWidget(metricsLabel);
    metricsGroup->setLayout(metricsLayout);
    metricsGroup->setVisible(false);
    rightColumn->addWidget(metricsGroup);
    bottomLayout->addLayout(rightColumn);

    bottomLayout->addStretch();
    mainLayout->addLayout(bottomLayout);

    //Doesnt really do anything right now
    connect(goButton, &QPushButton::clicked, this, &MainWindow::analyzeText);
    connect(openAddressingButton, &QPushButton::clicked, this, &MainWindow::selectOpenAddressing);
    connect(separateChainingButton, &QPushButton::clicked, this, &MainWindow::selectSeparateChaining);

    currentAlgorithm = "Open Addressing";
    //change when we add our real data set
    ParseDataFileSC("../src/tweetsubset_quoted.csv", m_separateMap);
    ParseDataFileLP("../src/tweetsubset_quoted.csv", m_openMap);

    setMinimumSize(500, 500);
}


float MainWindow::computeScore(const QString &text) {
    std::string tweet = text.toStdString();
    if (currentAlgorithm == "Open Addressing") {
        return ProcessInputReturnLP(tweet, m_openMap);
    } else {
        return ProcessInputReturnSC(tweet, m_separateMap);
    }
}

void MainWindow::analyzeText()
{
    QString userText = inputEdit->text();
    float rawScore = computeScore(userText);
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << rawScore;
    QString rawScoreStr = QString::fromStdString(oss.str());
    int displayScore = static_cast<int>(std::round(rawScore));

    QString explanation;
    switch (displayScore) {
        case 1: explanation = "very negative"; break;
        case 2: explanation = "negative";      break;
        case 3: explanation = "neutral";       break;
        case 4: explanation = "positive";      break;
        case 5: explanation = "very positive"; break;
        default: explanation = "unknown";      break;
    }
    sentimentResultLabel->setText(QString("The sentiment of your message is: %1").arg(rawScoreStr));
    sentimentResultLabel->setVisible(true);
    sentimentExplanationLabel->setText(QString("Your text is %1").arg(explanation));
    sentimentExplanationLabel->setVisible(true);

    updateMetricsDisplay();
}


void MainWindow::selectOpenAddressing()
{
    currentAlgorithm = "Open Addressing";
    if (metricsGroup->isVisible())
        updateMetricsDisplay();
}

void MainWindow::selectSeparateChaining()
{
    currentAlgorithm = "Separate Chaining";
    if (metricsGroup->isVisible())
        updateMetricsDisplay();
}

void MainWindow::updateMetricsDisplay() {
    QString metricsText;

    if (currentAlgorithm == "Open Addressing") {
        int collisions = m_openMap.get_collision_count();
        metricsText = QString(
                "Open Addressing Metrics:\n"
                "- Time complexity for insertion & search: O(1)\n"
                "- Space Complexity for insertion & search: O(1)\n "
                "- Collisions: %1"
        ).arg(collisions);
    }
    else {
        int collisions = m_separateMap.get_collision_count();
        metricsText = QString(
                "Separate Chaining Metrics:\n"
                "- Time complexity for search: O(n)\n"
                "- Space complexity: ___\n"
                "- Collisions: %1"
        ).arg(collisions);
    }
    metricsLabel->setText(metricsText);
    metricsGroup->setVisible(true);
}