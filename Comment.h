#ifndef COMMENT_H
#define COMMENT_H

#include <vector>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Comment  {
public:
	Comment();
	~Comment();
	Comment(string text) : text_(text),mark_(0), c_(), cMark_(){};

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
