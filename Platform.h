#ifndef PLATFORM_H
#define PLATFORM_H

#include "Exception.h"
#include "Question.h"

#include <algorithm>
#include <vector>
#include <list>
#include <stack>

using namespace std;

class Platform {
public:
	Platform() : roots_() {};

	list <Question*> getRoots();

	void addQuestion(string text);

	Question* findQuestion(string text);

	Comment* findAnswer(string qText, string aText);

	void sortAnswer();

	void deleteRoot(Question* q);

	list<Question*> findBestComment();

private:
	list <Question*> roots_;
};

#endif
