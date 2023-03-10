#include "Answer.h"


string Answer::getText()
{
	return text_;
}

vector<Comment*> Answer::getChild()
{
	return c_;
}

void Answer::addComment(string textC)
{
	Comment* comment = new Comment(textC);
	c_.push_back(comment);
	cMark_.push_back(0);
}
