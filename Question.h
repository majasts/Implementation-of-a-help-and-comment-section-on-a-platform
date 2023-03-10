#ifndef QUESTION_H
#define QUESTION_H

#include "Comment.h"

#include <vector>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

class Question {
public:
	Question();
	~Question();
	Question( string text) :text_(text), a_(), aMark_() {};

	void deleteQ();

	string getText();
	vector<Comment*> getChild();
	void setChild(vector<Comment*> newC);

	void deleteChild(Comment* c);

	void addAnswer( Comment* answer);
	void addAnswerByText(string text);
	
	
	friend ostream& operator<<(ostream& os, Question* q);

private:

	string text_;
	vector <Comment*> a_;
	vector <int> aMark_;

};

#endif
