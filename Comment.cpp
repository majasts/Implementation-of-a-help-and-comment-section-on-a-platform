#include "Comment.h"

Comment::Comment()
{
}

Comment::~Comment()
{
	while (!c_.empty()) {
		c_.pop_back();
		
	}
	c_.clear();
	delete father;
}

void Comment::addComment(string textC)
{
	Comment* comment = new Comment(textC);
	comment->setFather(this);
	comment->setLevel(this->getLevel() + 1);
	c_.push_back(comment);
	cMark_.push_back(0);
}

void Comment::addMark(int newMark)
{
	mark_ = newMark;
	if (this->getFather() != nullptr) {
		this->getFather()->addMarkOfChild(newMark, this);
	}

}

void Comment::addMarkOfChild(int newMark, Comment* child)
{
	for (int i = 0; i < this->getChild().size(); i++) {
		if (this->getChild()[i] == child) {
			this->cMark_[i] = newMark;
		}
	}
}

string Comment::getText()
{
	return text_;
}

int Comment::getMark()
{
	return mark_;
}

vector<Comment*> Comment::getChild()
{
	return c_;
}

void Comment::setChild(vector<Comment*> newC)
{
	c_ = newC;
}

void Comment::setFather(Comment* c)
{
	father = c;
}

Comment* Comment::getFather()
{
	return father;
}

void Comment::setLevel(int lvl)
{
	level = lvl;
}

int Comment::getLevel()
{
	return level;
}

void Comment::deleteComment()
{
	stack<Comment*> s;
	Comment* tmp;

	s.push(this);
	
	this->getFather();

	while (!s.empty()) {
		tmp = s.top();
		s.pop();


		
		for (int i = tmp->getChild().size() - 1; i >= 0; i--) {
			s.push(tmp->getChild()[i]);
		}
		delete tmp;
	}
	
}

ostream& operator<<(ostream& os, Comment* c)
{
	for (int i = 1; i <= c->getLevel(); i++) {
		cout << "  ";
	}
	os << c->getText();
	os<< " (" << c->getMark() << ")" << endl;
	return os;
}
