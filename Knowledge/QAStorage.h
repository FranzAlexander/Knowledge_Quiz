#pragma once
#include <iostream>
#include <string>

using namespace std;
#ifndef _Q_A
#define _Q_A

class QAStorage
{
private:
	string answerText;
	string questionText;
	int order;

public:
	//Creating methods for the QAStorage.cpp to construct.
	QAStorage();
	void setAnswer(string tempAnswer);
	void setQuestion(string tempQuestion);
	void setOrder(int tempOrder);

		int getOrder();
	string getAnswer();
	string getQuestion();
};
#endif // !_Q_A