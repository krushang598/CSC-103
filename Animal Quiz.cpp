#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
using namespace std;

//string input function
string Input(){
    string input, format;

    while(getline(cin, input)){
        format += input;
        if(!getline(cin, input)){
            break;
        }
        format += input;
        if(input.empty()){
            break;
        }
    }
    return format;
}

//function to split strings into individual words and push it into vector
vector<string> Split(const string& text, const string& delims){
    vector<string> animalNames;
    size_t start = text.find_first_not_of(delims), end = 0;
    while((end = text.find_first_of(delims, start)) != string::npos){
        animalNames.push_back(text.substr(start, end - start));
        start = text.find_first_not_of(delims, end);
    }
    if(start != string::npos){
        animalNames.push_back(text.substr(start));
    }
    return animalNames;
}


//function to display the list of vectors
void DisplayList(vector<string> initialNames){
    for(int i = 0; i < initialNames.size(); i++){
        cout << i << ": " << initialNames[i] << endl;
    }
}

//function to generate a random number
int Pick(){
    int r = rand() % 3 + 1;
    return r;
}

//function that removes a letter and replaces it with a '_'
void RandomStrikeOut(string& s, int num) {
	unsigned temp = num;
	while (temp > 0 && num - temp != s.size()) { // if number of strike-out > length of string, the loop will strike-out chars equal to the length of the string
		int random = rand() % s.size();
		if (s[random] != '_') {
			s[random] = '_';
			temp--;
		}
	}
}

//main function
int main(){
    int pickUps = 0, gotRight = 0, consecutiveSuccess = 0, strikeOut =0;
    string initialInput, userInput, shuffledStr;
    vector<string> animalNames, shuffleNames, shuffledPicks, userGuess;

    cout << "Enter at least five animal names, e.g., cat, dog, etc...\n";

    //calls Input function
    initialInput = Input();

    //calls Split function
    animalNames = Split(initialInput, " ");

    //calls DisplayList function
    DisplayList(animalNames);
    cout << endl;


    while(true){
        for(int i = 0; i < animalNames.size(); i++){
            shuffleNames.push_back(animalNames[i]);
        }
        random_shuffle(shuffleNames.begin(), shuffleNames.end());
        pickUps = Pick();

        for(int i = 0; i < pickUps; i++){
            shuffledPicks.push_back(shuffleNames[i]);
        }
        for(int i = 0; i < shuffledPicks.size(); i++){
            shuffledStr += shuffledPicks[i];
        }
        random_shuffle(shuffledStr.begin(), shuffledStr.end());

        //calls the RandomStrikeOut function
        RandomStrikeOut(shuffledStr, strikeOut);

        if(pickUps == 1){
            cout << "What is " << pickUps << " animal in \"" << shuffledStr << "\"? ";
            loop1: getline(cin, userInput);
            if(userInput == "?"){
                DisplayList(animalNames);
                cout << "Enter again: ";
                goto loop1;
            }
            else if(userInput == "quit"){
                break;
            }
            else{
                userGuess = Split(userInput, " ");
            }
        }
        else{
            cout << "What are " << pickUps << " animals in \"" << shuffledStr << "\"? ";
            loop2: getline(cin, userInput);
            if(userInput == "?"){
                DisplayList(animalNames);
                cout << "Enter again: ";
                goto loop2;
            }
            else if(userInput == "quit"){
                break;
            }
            else{
                userGuess = Split(userInput, " ");
            }
        }
        //checks if userGuess is right
        for(int i = 0; i < shuffledPicks.size(); i++){
            if(find(shuffledPicks.begin(), shuffledPicks.end(), userGuess[i]) != shuffledPicks.end()){
                gotRight += 1;
            }
        }
        if(gotRight < shuffledPicks.size()){
            cout << "Your number of input is incorrect. Enter again: ";//NOT WORKING PLEASE CHECK WHATS WRONG
            if(gotRight == 1){
                userGuess.clear();
                goto loop1;
            }
            else{
                userGuess.clear();
                goto loop2;
            }
        }
        else if(gotRight == shuffledPicks.size()){
            cout << "Yes!" << endl;
            if(consecutiveSuccess <= 0){
                consecutiveSuccess = 1;
            }
            else{
                strikeOut++;
                consecutiveSuccess = 0;
                cout << "Succeeded two consecutive times, challenge goes up!" << endl;
            }
        }
        else{
            cout << "Nope!" << endl;
            if(consecutiveSuccess >= 0){
                consecutiveSuccess = -1;
            }
            else{
                if(strikeOut > 0){
                    strikeOut--;
                }
                consecutiveSuccess = 0;
                cout << "Missed two consecutive times, challenge goes down!" << endl;
            }
        }
        shuffleNames.clear();
        shuffledPicks.clear();
        userGuess.clear();
        userInput = "";
        shuffledStr = "";
        pickUps = 0;
        gotRight =0;
    }
    cout << "Bye...";
}
