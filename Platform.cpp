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
	Question* q=findQuestion(qText);
	if (q == nullptr) throw Neuspesno("Uneli ste nepostojece pitanje");
	stack<Comment*> s;
	
	Comment* tmp;

	for (int i = q->getChild().size()-1; i >= 0; i--) {
		
		s.push((q->getChild()[i]));
	}
	
	while (!s.empty()) {
		tmp = s.top();
		s.pop();

		if (tmp->getText().compare(aText) == 0) {
			return tmp;
		}
		for (int i = tmp->getChild().size()-1; i >=0; i--) {
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

		for (int i = (*it)->getChild().size()-1; i >= 0; i--) {
			s.push((*it)->getChild()[i]);
		}

		while (!s.empty()) {
			tmp = s.top();
			s.pop();
			tmpChild = tmp->getChild();
			sort(tmpChild.begin(), tmpChild.end(), compareElem);
			tmp->setChild(tmpChild);

			for (int i = tmp->getChild().size()-1; i >=0; i--) {
				s.push(tmpChild[i]);
			}

		}
	}
}

void Platform::deleteRoot(Question* q)
{
	q->~Question();
	list<Question*> ::iterator it = roots_.begin();

	for (int i = 0; i <= roots_.size();i++) {
		if ((*it)==q){
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
