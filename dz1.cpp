//1.Main			11-264
//2.Platform.cpp	265-407
//3.PLatform.h		412-448
//4.Question.cpp	452-554
//5.Question.h		560-601
//6.Comment.cpp		607-720
//7.Comment.h		728-773
//8.Exception.h		780-800


#include "Platform.h"
#include "Exception.h"

#include <iostream>
#include "Exception.h"

using namespace std;

int main() {

	int c;
	string text, text1, text2;
	int tmp;

	Platform* pl = new Platform();

	pl->addQuestion("p1");
	pl->addQuestion("p2");
	pl->addQuestion("p3");

	pl->findQuestion("p1")->addAnswerByText("o1");
	pl->findQuestion("p1")->addAnswerByText("o2");
	pl->findQuestion("p1")->addAnswerByText("o3");
	pl->findQuestion("p1")->addAnswerByText("o4");

	pl->findAnswer("p1", "o1")->addComment("k1");
	pl->findAnswer("p1", "o2")->addComment("k2");
	pl->findAnswer("p1", "o2")->addComment("k3");
	pl->findAnswer("p1", "o2")->addComment("k4");
	pl->findAnswer("p1", "o3")->addComment("k5");
	pl->findAnswer("p1", "o4")->addComment("k6");

	pl->findAnswer("p1", "k1")->addComment("kk1");
	pl->findAnswer("p1", "k5")->addComment("kk2");
	pl->findAnswer("p1", "k5")->addComment("kk3");



	while (1) {

		cout << "Dobrodošli u platformu za postavljanje pitanja i komentara" << endl;
		cout << "Izaberite opciju unoseci redni broj zeljene stavke" << endl;
		cout << "2. Dodavanje novog pitanja" << endl;
		cout << "3. Dodavanje odgovora na neko pitanje ili odgovor" << endl;
		cout << "4. Pretraga pitanja" << endl;
		cout << "5. Pretraga odgovora" << endl;
		cout << "6. Povećanje ocene nekog odgovora" << endl;
		cout << "7. Uređivanje odgovora prema njihovoj oceni za sva pitanja" << endl;
		cout << "8. Ispis svih pitanja" << endl;
		cout << "9. Ispis pojedinačnog pitanja i njemu pridruženih odgovora i komentara" << endl;
		cout << "10. Brisanje odgovora ili komentara i svih njegovih potomaka" << endl;
		cout << "11. Brisanje pojedinačnog pitanja i svih povezanih odgovora" << endl;
		cout << "12. Pronalazak pitanja čiji odgovor ili komentar imaju najvišu ocenu" << endl;
		cout << "0. IZLAZ" << endl;

		cout << "Izaberite opciju unoseci redni broj zeljene stavke" << endl;
		try {
			cin >> c;

			if (c > 12 || c < 0) throw NeispravnoZadataOpcija("Nesipravno zadat broj zeljene opcije. Molim pokusajte ponovo.\n");
		}
		catch (NeispravnoZadataOpcija& e) {
			cout << e.what() << endl;
		}
		switch (c) {
		case 0:
		{
			exit(0);
			break;
		}
		case 2:

		{
			cout << "Unesite tekst pitanja:" << endl;

			cin >> text;
			pl->addQuestion(text);
			break;
		}

		case 3:
		{
			cout << "Ukoliko želite da unesete odgovor na pitanje unesite 1, ukoliko zelite da unesete odgovor na odgovor unesite 2 :" << endl;

			cin >> tmp;
			switch (tmp) {

			case 1: {
				cout << "Unesite tekst pitanja na koje zelite da postavite odgovor" << endl;
				cin >> text;
				cout << "Unesite odgovor koji zelite da postavite" << endl;
				cin >> text1;
				Comment* a = new Comment(text1);
				try {
					pl->findQuestion(text)->addAnswer(a);
					break;
				}
				catch (Neuspesno& e) {
					cout << e.what() << endl;

				}
				break;
			}
			case 2: {
				cout << "Unesite tekst odgovora na koje zelite da postavite odgovor:" << endl;
				cin >> text;
				cout << "Unesite tekst pitanja na koje je dat odgovor:" << endl;
				cin >> text1;
				cout << "Unesite tekst odgovora koje zelite da dodate:" << endl;
				cin >> text2;
				try {
					pl->findAnswer(text1, text)->addComment(text2);
				}
				catch (Neuspesno& e) {
					cout << e.what() << endl;
				}
				break;
			}

			}
			break;
		}

		case 4:
		{
			cout << "Unesite tekst pitanja koje zelite da pronadjete" << endl;
			cin >> text;
			try {
				pl->findQuestion(text);
			}
			catch (Neuspesno& e) {
				cout << e.what() << endl;
			}
			break;
		}
		case 5:
		{
			cout << "Unesite tekst odgovora koje zelite da pronadjete" << endl;
			cin >> text;
			cout << "Unesite tekst pitanja na koje je dat odgovor koji zelite da pronadjete" << endl;
			cin >> text1;
			try {
				pl->findAnswer(text1, text);
			}
			catch (Neuspesno& e) {
				cout << e.what() << endl;
			}

			break;
		}
		case 6:
		{
			cout << "Unesite tekst odgovora ciju ocenu zelite da uvecate" << endl;
			cin >> text;
			cout << "Unesite tekst pitanja na koje je dat odgovor ciju ocenu zelite da uvecate" << endl;
			cin >> text1;
			cout << "Unesite novu ocenu" << endl;
			cin >> tmp;
			try {
				pl->findAnswer(text1, text)->addMark(tmp);
			}
			catch (Neuspesno& e) {
				cout << e.what() << endl;
			}
			break;
		}
		case 7:
		{
			pl->sortAnswer();
			break;
		}
		case 8:
		{
			list<Question*> qList = pl->getRoots();
			if (qList.empty()) {
				cout << "Nema unetih pitanja" << endl;
				break;
			}
			for (auto it = qList.begin(); it != qList.end(); it++) {
				cout << (*it)->getText() << endl;;
			}
			break;
		}
		case 9:
		{
			cout << "Unesite pitanje cije odgovore i komentare zelite da ispisete" << endl;
			cin >> text;
			try {
				Question* q = pl->findQuestion(text);
				cout << q;
			}
			catch (Neuspesno& e) {
				cout << e.what() << endl;
			}
			break;
		}
		case 10:
		{
			cout << "Unesite odgovor ili komentar koji zelite da obrisete" << endl;
			cin >> text;
			cout << "unesite pitanje na koje je dat zeljeni odgovor ili komentar" << endl;
			cin >> text1;
			try {
				Comment* c = pl->findAnswer(text1, text);
				Question* q = pl->findQuestion(text1);
				q->deleteChild(c);
				c->deleteComment();
			}
			catch (Neuspesno& e) {
				cout << e.what() << endl;
			}
			break;
		}
		case 11:
		{
			cout << "Unesite pitanje koji zelite da obrisete" << endl;
			cin >> text;
			try {
				Question* q = pl->findQuestion(text);
				q->deleteQ();
				pl->deleteRoot(q);
			}
			catch (Neuspesno& e) {
				cout << e.what() << endl;
			}
			break;
		}
		case 12:
		{
			try {
				list<Question*> l = pl->findBestComment();
				if (l.size() > 1) {
					cout << "Pitanja ciji odgovor ili komentar imaju najvisu ocenu su: " << endl;
					while (!l.empty()) {
						cout << (l.back())->getText() << endl;
						l.pop_back();
					}
				}
				else {
					cout << "Pitanje ciji odgovor ili komentar imaju najvisu ocenu je: " << endl;
					cout << (l.back())->getText() << endl;
					l.pop_back();
				}
			}
			catch (Neuspesno& e) {
				cout << e.what() << endl;
			}
			break;
		}

		}

	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Platform.cpp

#include "Platform.h"



list<Question*> Platform::getRoots()
{
	return roots_;
}

void Platform::addQuestion(string text)
{
	Question* q = new Question(text);
	roots_.push_back(q);
}

Question* Platform::findQuestion(string text)
{
	list<Question*> ::iterator it;

	for (it = roots_.begin(); it != roots_.end(); it++) {
		if ((*it)->getText().compare(text) == 0) {
			return *it;
		}
	}
	throw Neuspesno("Uneli ste nepostojece pitanje");
	return nullptr;
}

Comment* Platform::findAnswer(string qText, string aText)
{
	Question* q = findQuestion(qText);
	if (q == nullptr) throw Neuspesno("Uneli ste nepostojece pitanje");
	stack<Comment*> s;

	Comment* tmp;

	for (int i = q->getChild().size() - 1; i >= 0; i--) {

		s.push((q->getChild()[i]));
	}

	while (!s.empty()) {
		tmp = s.top();
		s.pop();

		if (tmp->getText().compare(aText) == 0) {
			return tmp;
		}
		for (int i = tmp->getChild().size() - 1; i >= 0; i--) {
			s.push(tmp->getChild()[i]);
		}

	}
	throw Neuspesno("Uneli ste odgovor/komentar koji ne postoji u okviru zeljenog pitanja");
	return nullptr;
}

bool compareElem(Comment* first, Comment* second) {
	return first->getMark() > second->getMark();
}

void Platform::sortAnswer()
{
	stack<Comment*> s;
	Comment* tmp;
	list<Question*> ::iterator it;

	for (it = roots_.begin(); it != roots_.end(); it++) {

		vector<Comment*> tmpChild = (*it)->getChild();
		sort(tmpChild.begin(), tmpChild.end(), compareElem);
		(*it)->setChild(tmpChild);

		for (int i = (*it)->getChild().size() - 1; i >= 0; i--) {
			s.push((*it)->getChild()[i]);
		}

		while (!s.empty()) {
			tmp = s.top();
			s.pop();
			tmpChild = tmp->getChild();
			sort(tmpChild.begin(), tmpChild.end(), compareElem);
			tmp->setChild(tmpChild);

			for (int i = tmp->getChild().size() - 1; i >= 0; i--) {
				s.push(tmpChild[i]);
			}

		}
	}
}

void Platform::deleteRoot(Question* q)
{
	q->~Question();
	list<Question*> ::iterator it = roots_.begin();

	for (int i = 0; i <= roots_.size(); i++) {
		if ((*it) == q) {
			roots_.erase(it);
			return;
		}
		advance(it, 1);
	}
}

list<Question*> Platform::findBestComment()
{
	stack<Comment*> s;
	Comment* tmp;
	int bestMark = -1;
	list<Question*> bestQuestion;
	if (roots_.empty()) throw Neuspesno("Ne postoje pitanja na platformi");

	for (auto it = roots_.begin(); it != roots_.end(); it++) {

		for (int i = (*it)->getChild().size() - 1; i >= 0; i--) {
			s.push((*it)->getChild()[i]);
		}

		while (!s.empty()) {
			tmp = s.top();
			s.pop();

			if (tmp->getMark() >= bestMark) {
				bestQuestion.push_back(*it);
				bestMark = tmp->getMark();
			}
			vector<Comment*> tmpChild = tmp->getChild();
			for (int i = tmpChild.size() - 1; i >= 0; i--) {
				s.push(tmpChild[i]);
			}

		}
	}
	bestQuestion.unique();
	return bestQuestion;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Platform.h
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Question.cpp
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
	os << q->getText() << endl;

	stack<Comment*> s;
	Comment* tmp;


	for (int i = q->getChild().size() - 1; i >= 0; i--) {
		s.push(q->getChild()[i]);
	}

	while (!s.empty()) {
		tmp = s.top();
		s.pop();


		os << tmp << endl;
		for (int i = tmp->getChild().size() - 1; i >= 0; i--) {
			s.push(tmp->getChild()[i]);
		}

	}
	return os;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Question.h

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
	Question(string text) :text_(text), a_(), aMark_() {};

	void deleteQ();

	string getText();
	vector<Comment*> getChild();
	void setChild(vector<Comment*> newC);

	void deleteChild(Comment* c);

	void addAnswer(Comment* answer);
	void addAnswerByText(string text);


	friend ostream& operator<<(ostream& os, Question* q);

private:

	string text_;
	vector <Comment*> a_;
	vector <int> aMark_;

};

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Comment.cpp

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
	os << " (" << c->getMark() << ")" << endl;
	return os;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Comment.h

#ifndef COMMENT_H
#define COMMENT_H

#include <vector>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Comment {
public:
	Comment();
	~Comment();
	Comment(string text) : text_(text), mark_(0), c_(), cMark_() {};

	void deleteComment();

	void addComment(string textC);
	void addMark(int newMark);
	void addMarkOfChild(int newMark, Comment* child);

	string getText();
	int getMark();

	vector <Comment*> getChild();
	void setChild(vector <Comment*> newC);

	void setFather(Comment* c);
	Comment* getFather();

	void setLevel(int lvl);
	int getLevel();

	friend ostream& operator<<(ostream& os, Comment* c);

private:
	string text_;
	int mark_;
	vector <Comment*> c_;
	vector<int> cMark_;
	Comment* father;
	int level;
};

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Exception.h

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
using namespace std;

class NeispravnoZadataOpcija : public exception {
public:
	NeispravnoZadataOpcija(const char* msg) : exception(msg) {};
};

class Neuspesno : public exception {
public:
	Neuspesno(const char* msg) : exception(msg) {};
};

class Nepostojece : public exception {
public:
	Nepostojece(const char* msg) : exception(msg) {};
};
#endif