#include "stdafx.h"
#include "QAStorage.h"
#include <iostream>
#include <string>


using namespace std;

QAStorage::QAStorage()
{
	string answerText = "";
	string questionText = "";
	int order = 0;

}
//First Three methods are set methods which just set the variables to what ever the user has inputed.
void QAStorage::setAnswer(string tempAnswer)
{
	answerText = tempAnswer;
}

void QAStorage::setQuestion(string tempQuestion)
{
	questionText = tempQuestion;
}

void QAStorage::setOrder(int tempOrder)
{
	order = tempOrder;
}
//The next three methods return the variables that the user wants.
int QAStorage::getOrder()
{
	return order;
}

string QAStorage::getAnswer()
{
	return answerText;
}

string QAStorage::getQuestion()
{
	return questionText;
}
