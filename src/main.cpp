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

	HM_separateChaining first_map;
	ProcessInputReturn("fileData/movies.csv", first_map);
	return app.exec();

	//HM_separateChaining first_map;
	// just testing with this "datita.csv" file since it is WAY smaller than the actual dataset
	// feel free to add a new .csv file into \cmake-build-debug\fileData folder to test a different input
	// ParseDataFile("fileData/datita.csv", first_map);


	//ParseMovieDataFile("fileData/movies.csv", first_map);


	std::string user_input_message;
	std::getline(std::cin, user_input_message);
	ProcessInput(user_input_message, first_map);

	//ParseDataFile("file_datita/training.1600000.processed.noemoticon.csv");

}
