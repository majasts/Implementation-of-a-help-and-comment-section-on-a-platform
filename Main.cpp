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

		cout<< "Izaberite opciju unoseci redni broj zeljene stavke" << endl;
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
				catch (Neuspesno & e) {
					cout << e.what()<<endl;

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
					cout << e.what()<<endl;
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
				cout << e.what()<<endl;
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
				cout << e.what()<<endl;
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
				cout << e.what()<<endl;
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
				cout << "Nema unetih pitanja"<<endl;
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
				cout << e.what()<<endl;
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
				cout << e.what()<<endl;
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
				cout << e.what()<<endl;
			}
			break;
		}
		
		}
		
	}
}