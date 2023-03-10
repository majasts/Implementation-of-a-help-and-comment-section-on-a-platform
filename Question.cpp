#include "Question.h"

Question::~Question()
{
	while (!a_.empty()) {
		a_.pop_back();

	}
	a_.clear();

	
}

string Question::getText()
{
	return text_;
}

vector<Comment*> Question::getChild()
{
	return a_;
}

void Question::setChild(vector<Comment*> newC)
{
	a_ = newC;
}

void Question::deleteChild(Comment* c)
{
	vector<Comment*> qChild = this->getChild();
	for (int i = 0; i < qChild.size(); i++) {
		if (qChild[i] == c) {
			qChild.erase(qChild.begin() + i);
		}
	}
	this->setChild(qChild);
}

void Question::addAnswer(Comment* answer)
{
	
	answer->setFather(nullptr); //nullptr oznacava da je otac PITANJE a ne ODGOVOR/KOMENTAR
	answer->setLevel(1);
	a_.push_back(answer);
	aMark_.push_back(0);
}

void Question::addAnswerByText(string text)
{
	Comment* c = new Comment(text);
	a_.push_back(c);
	aMark_.push_back(0);

}

void Question::deleteQ()
{
	stack<Comment*> s;
	Comment* tmp;

	for (int i = this->getChild().size() - 1; i >= 0; i--) {
		s.push(this->getChild()[i]);
	}
	

	while (!s.empty()) {
		tmp = s.top();
		s.pop();

		for (int i = tmp->getChild().size() - 1; i >= 0; i--) {
			s.push(tmp->getChild()[i]);
		}
		delete tmp;
	}
}


ostream& operator<<(ostream& os, Question* q)
{
	os << q->getText()<<endl;

	stack<Comment*> s;
	Comment* tmp;
	

	for (int i = q->getChild().size()-1; i >= 0; i--) {
		s.push(q->getChild()[i]);
	}

	while (!s.empty()) {
		tmp = s.top();
		s.pop();

		
		os << tmp<<endl;
		for (int i = tmp->getChild().size()-1; i >=0; i--) {
			s.push(tmp->getChild()[i]);
		}

	}
	return os;
}
