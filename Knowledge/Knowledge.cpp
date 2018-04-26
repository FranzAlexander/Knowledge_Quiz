// Knowledge.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "QAStorage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <array>

using namespace std;

//Method that reads the text file.
template<class T>
void readingFile(T &unsortedArr)
{
	int index = 0;
	int count = 0;
	string line;
	//Reading the text file Answer.txt and storing it in answerFile
	ifstream answerFile("QAFile.txt");
	//Will do any of the reading code while the text file is open and checked by an if statement.
	if (answerFile.is_open())
	{
		while (getline(answerFile, line)) //Saving characters into line
		{
			if (line[0] == 'Q') //Seeing if the first character of the line is Q.
			{
				if (index < 10) //Will only continue if index is less or equal to 20. 
				{
					unsortedArr[0][index].setQuestion(line); //Sets the question on that line into the class. Also puts it into the first row(0) and in an column that is incremented each line.
					unsortedArr[0][index].setOrder(index); //Sets the order of the question using the index variable.
					index++; // Index is increased by 1.
				}
			}
			if(line[0] == 'A') //Seeing if the first charater of the line is A.
			{
				if (count < 10)//Will only continue if index is less or equal to 20. 
				{
					unsortedArr[1][count].setAnswer(line);//Sets the answer on the line into the class. Also puts it into the second row(1) and in an column that is incremented each line.
					unsortedArr[1][count].setOrder(count);//Sets the order of the answer using the index variable.
					count++;
				}

			}
			if (line[0] != 'A' && line[0] != 'Q' && line[0] != ' ')
			{
				cout << "There was an error reading the line in the txt file please make sure that ANSWER Starts A and QUESTIONS Starts with Q" << endl;
			}
			
		}
		answerFile.close(); //Closes the file.
	}
	else //Prints out message if the file is unreadable.
	{
		cout << "Not able to read file"; //Prints a message to the user saying that the file was not found.
	}

}



void someThingRandom() //A method that reads from a text file using binary.
{
	string line;
	string exitOption;
	int input;
	bool stop = false;

	cout << "Please enter a random number" << endl;


	while (stop == false)
	{
		ifstream file("QAFile.txt", ios::binary); //Creating a ifstream that looks for QAFile.txt and uses binary.

		if (file.is_open()) //Makes sure the file is open.
		{
			cin >> input; //Getting user input
			file.seekg(input, ios::beg); //Puts the pointer to the postion that the user has put in. Pointer will be placed depending on how many positions from the start of file.
			getline(file, line); //Gets the rest of the line.
			cout << line << endl;

			cout << endl << "Enter Stop/stop to go back to options" << endl;
			cout << "If you want to contuine enter no" << endl;

			cin >> exitOption;
		}
		if (exitOption == "Stop" || exitOption == "stop")//Seeing if the user has entered Stop/stop to exit this option.
		{
			stop = true;
		}
		if (exitOption != "Stop" || exitOption != "stop")//Making sure the program doesnt flip out if user puts something else in.
		{
			cout << "If you would like to exit enter Stop or stop" << endl;
			return;
		}
	}
	return;
}

template <class T, class AT>
void splitArray(AT &unsortedArr, T &questionArr, T &answerArr) //This method splits the two rows of the 2d array into 2 1d arrays.
{
	for (int index = 0; index <= 9; index++) //Loop that 
	{
		questionArr[index] = unsortedArr[0][index]; //Puts contents of unsortedArr row 0 into questionArr.
		answerArr[index] = unsortedArr[1][index];//Puts the contents of unsortedArr row 1 into answerArr.
	}
}

template<class T, class AT>
void SortingArrs(AT &questionArr, T &answerArr, T &sortedArr)//Method that sorts the two arrays into one using merge sort.
{
	int index = 0;
	int count = 0;
	int check = 0;
	int checkB = 0;
	int totalArraySize = sizeof(questionArr) / sizeof(questionArr[0]); //Gets size of array.

	while (index < totalArraySize && count < totalArraySize) //While index and count are both less than the array size.
	{
		if (questionArr[index].getOrder() <= answerArr[count].getOrder())//Seeing if the question array order number is less than answers order number.
		{

			sortedArr[check].setQuestion(questionArr[index].getQuestion());
			sortedArr[check].setOrder(questionArr[index].getOrder());//Puts
			index++;
			check++;
		}

		else
		{
			sortedArr[checkB].setAnswer(answerArr[count].getAnswer());
			sortedArr[checkB].setOrder(answerArr[count].getOrder());
			count++;
			checkB++;
		}
	}
	while (checkB < check)
	{
		sortedArr[checkB].setAnswer(answerArr[count].getAnswer());
		sortedArr[checkB].setOrder(answerArr[count].getOrder());
		count++;
		checkB++;
	}
	while (check < checkB)
	{
		sortedArr[check].setQuestion(questionArr[index].getQuestion());
		sortedArr[check].setOrder(questionArr[index].getOrder());
		index++;
		check++;
	}
	return;

}
template <class T, class AT>
void writeNSortSelectedToFile(T &tempOrderArr, AT &tempAnsArr)
{
	int count = 0;

	std::sort(tempOrderArr.begin(), tempOrderArr.end());

	ofstream selectedAnfile("SelectedAnswers.txt");



	for (int i = 0; i < tempOrderArr.size(); i++)
	{
		if (tempOrderArr[i] != 0)
		{
			selectedAnfile << "What you entered" << endl;
			selectedAnfile << tempOrderArr[i] << endl;
			selectedAnfile << "Answer: " << endl;
			selectedAnfile << tempAnsArr[count] << endl;
			selectedAnfile << endl;
			count++;
		}
	}
}

template <class T>
void getSwitchCase(int userInput, T &sortedArr)
{
	cout << "\n" << "Answer!!!- " << sortedArr[userInput - 1].getAnswer() << endl;
}

template <class T>
void chooseAnswer(T &sortedArr) //Method that checks user input to see what should be outputed.
{
	int userInput;
	string print;
	int index = 0;
	array<int, 20> tempOrderArr = { 0 };
	array<string, 20> tempAnsArr;

	bool exit = false;

	cout << endl << "To exit at anytime press 0" << endl;
	cout << "Put any number between 1-10 to get the answers for the question" << endl;

	while (exit != true) //Being do while loop.
	{
		cin >> userInput;
		if (userInput < sortedArr.size() && userInput != 0) //Will only continue if what the user inputs is less than the array size and isnt 0.
		{
			getSwitchCase(userInput,sortedArr);
			tempOrderArr[index] = userInput; //Putting what ever is in the postion that the user has entered into an temp array.
			tempAnsArr[index] = sortedArr[userInput - 1].getAnswer();
			index++;
		}
		else if (userInput == 0) //If the user types 10 then it will ask if you would like to save the answers into atext file.
		{
			cout << "Would you like to save the answers that you have chosen to a text file." << endl;
			cin >> print;
			if (print == "Yes" || print == "yes")
			{
				writeNSortSelectedToFile(tempOrderArr, tempAnsArr); //Call method.
			}
			exit = true;
			break;
		}
		if (userInput > 11)
		{
			cout << "You have selected over the limit (21)" << endl;
			cout << "Please put 1-10 or press 0 to go back to selection" << endl;
		}
	}
}

void searchUI()//Just a method for some UI.
{
	cout << "You are searching buy question number" << endl;
	cout << "Enter 0 to get (question and answer 1) and so on" << endl;
	cout << "To exit this option type in exit when promted" << endl;
}

template <class T>
void searchArray(T &sortedArr) //Searching the array using binary method.
{
	searchUI();
	int lower = 0;
	int higher = sortedArr.size() - 1;
	int lookFor;
	bool notFound = true;
	int exit;


	cout << "Enter 100 to go back to main" << endl;

		cin >> lookFor;

		while (lower <= higher && notFound ) //While lowe is less than or equal to higher && notFound is still equal to false.
		{	
		

			int middle = (higher + lower) / 2; //Middle is equal to higher(ArraySize(10)) plus lower 0, divide by 2.

			if (lookFor < sortedArr[middle].getOrder()) //If lookFor(User input) is less than sorted array at the poition that the number middle is.
			{
				higher = middle - 1; //Move to the left;
			}
			else if (lookFor > sortedArr[middle].getOrder()) //The oppasite of above so if lookFor is greater than sortedArr middle
			{
				lower = middle + 1; //Move to the right;
			}
			else
			{
				cout << sortedArr[middle].getQuestion() << endl;
				cout << sortedArr[middle].getAnswer() << endl;
				cin >> exit;
				if (exit == 100)
				{
					notFound = false;
				}
				else
				{
					cin >> lookFor;
					lower = 0;
					higher = sortedArr.size() - 1;
				}
			}
			

		}
}

template <class T>
void userInter(T &sortedArr)// Just displays the questions by looping through the sortedArr and getting the question from the object.
{
	for (int counter = 0; counter < sortedArr.size(); counter++)
	{
		cout << sortedArr[counter].getQuestion() << endl;
	}
	cout << endl;
}

template <class T>
void searchOrSelect(T &sortedArr) //This is the method where the user chooses what they would like to do.
{
	string option;
	string exitApp;
	bool exit = false;

	cout << "Type Search to search by character" << endl;
	cout << endl;
	cout << "Type Select to choose the question" << endl;
	cout << endl;
	cout << "If you would like to see something random then enter random" << endl;
	cout << endl;

	//Below are if statements which check to see if what the user has inputed is equal to what is need to contuine that option.
	do
	{
		cout << "Type What you would like to do" << endl;
		cin >> option;

		if (option == "Search" || option == "search")
		{
			searchArray(sortedArr);
		}
		if (option == "Select" || option == "select")
		{
			chooseAnswer(sortedArr);
		}
		if (option == "Random" || option == "random")
		{
			someThingRandom();
		}
		cout << endl << "You are back at option select" << endl;
		cout << "Would you like to quit type Yes or No" << endl;
		cin >> exitApp;
		if (exitApp == "Yes" || exitApp == "yes")
		{
			exit = true;
		}
	} while (exit == false);
}

//The main method and in the application its method is to call other methods.
void main()
{
	//Below it declaring the Object class arrays.
	array<QAStorage, 10> answerArr;
	array<QAStorage, 10> questionArr;
	array<array<QAStorage, 10>, 2> unsortedArr;
	array<QAStorage, 10> sortedArr;

	//Below are calling methods.
	readingFile(unsortedArr);
	splitArray(unsortedArr, questionArr, answerArr);
	SortingArrs(questionArr, answerArr, sortedArr);
	userInter(sortedArr);
	searchOrSelect(sortedArr);
}
