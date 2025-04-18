//
// Created by Jennifer Moloney on 4/8/25.
//
#include <QApplication>
#include "UI.h"
#include "hashmap.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

	return app.exec();

	// HM_separateChaining first_map;
	// ParseDataFileSC("fileData/datita.csv", first_map);


	//ParseMovieDataFile("fileData/movies.csv", first_map);

	//ParseDataFile("file_datita/training.1600000.processed.noemoticon.csv");

}
