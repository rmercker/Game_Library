#include "stdafx.h"
#include "HighScore.h"

HighScore::HighScore() {
	high_Score = new std::string*[10];		//use this to setup a 2d array
	for (int i = 0; i < 10; i++) {
		high_Score[i] = new std::string[2];
	}

	std::fstream file("HighScore/highScore.txt");				//will read the text file and place values
	if (file.is_open()) {						//in the appropriate array position
		while (file) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 2; j++) {
					file >> high_Score[i][j];
				}
			}
		}
	}
	if (!file.is_open()) {
		std::cout << "Error reading High Score file." << std::endl;
		abort();
	}
	file.close();								//closes the file once read
}

void HighScore::highScore() {
	std::fstream fileWrite("HighScore/highScore.txt");			//Rewrite the updated array back to the txt file
	if (fileWrite.is_open()) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 2; j++) {
				fileWrite << high_Score[i][j] << std::endl;
			}
		}
	}
	if (!fileWrite.is_open()) {
		std::cout << "Error reading High Score file." << std::endl;
	}
	fileWrite.close();
}

std::string HighScore::printHigh(int i, int j) {
	//for (int i = 0; i < 10; i++) {				//Simple loop used to print the array
		//for (int j = 0; j < 1; j++) {
	return high_Score[i][j];
		//}
	//}
}

bool HighScore::determineHigh(int score) { // did the player get a high score
	std::string temp = high_Score[9][1];
	int tempscore = 0;
	for (int i = temp.length() - 1; i >= 0; i--) {
		tempscore += (temp[i] - '0') * pow(10, temp.length() - 1 - i);
	}

	if (tempscore < score) {
		return true;
	}

	return false;
}

void HighScore::newHigh(std::string name, int score) {
	std::string oldscore = "";  
	for (int i = 0; i < 10; i++) {				//cycle through array to compare the scores
		oldscore.assign(high_Score[i][1]);
		int tempscore = 0;
		for (int r = oldscore.length() - 1; r >= 0; r--) {
			tempscore += (oldscore[r] - '0') * pow(10, oldscore.length() - 1 - r);
		}
		if (tempscore < score) {				//if the new score belongs on list, shift everything in the array down to make room
			for (int j = 9; j > i; j--) {
				for (int k = 0; k < 2; k++) {
					high_Score[j][k] = high_Score[j - 1][k];

				}
			}
			//std::string newString = std::to_string(score);
			//std::string newName;
			//std::cout << "Initials(3 letters/no spaces): ";	//ask the player for his intials
			//std::cin >> name;
			name = name.substr(0, 3);		//limit to three characters
			high_Score[i][0] = name;			//place to new spot in the array
			high_Score[i][1] = std::to_string(score);
			break;
		}

	}
}
