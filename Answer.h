#ifndef ANSWER_H
#define ANSWER_H


#include "Comment.h"
#include <map>
#include <string>
using namespace std;

class Answer :public Comment{
public:
	Answer() : mark_(0) {};
	Answer(string text) : text_(text), mark_(0){};

	string getText();
	vector <Comment*> getChild();
	void addComment(string textC);

private:
	string text_;
	vector <Comment*> c_;
	vector <int> cMark_;
	int mark_;
};

#endif
