#include <iostream>
#include <string>
using namespace std;
//Sa se scrie un program in c++ pentru gestiunea unei gradinit zoologice folosind clase obiecte, derivate, vom avea o clasa animal din care vom deriva, de ex clasa pasari in care avem lungimea arimplor varsta, pt caine rasa 

class Animale {
private:
	int numar_animale;
public:
	void afisare_nr()
	{
		cout << numar_animale << endl;
	}
	Animale(int nr)
	{
		this->numar_animale = nr;
	}

};

class Caini : public Animale
{
private:
	int varsta;
	string rasa;
	bool dresat;
public:
	Caini(int nr, int varsta, string rasa, bool dresat):Animale(nr)
	{
		this->varsta = varsta;
		this->rasa = rasa;
		this->dresat = dresat;
	}
	void afisare()
	{
		cout << varsta << ' ' << rasa << ' ' << "Dresat->";
		if (dresat)
			cout << " DA ";
		else
			cout << " NU ";
		cout << "\nNumarul de animale asemanatoare: ";
		afisare_nr();
		cout << endl;
	}

};

int main()
{
	Caini s(3, 31, "Maidanez", 1);
	s.afisare();
	return 0;
}