#include <iostream>
#include <string>
using namespace std;
//Sa se scrie un program in c++ pentru gestiunea unei gradinit zoologice folosind clase obiecte, derivate, vom avea o clasa animal din care vom deriva, de ex clasa pasari in care avem lungimea arimplor varsta, pt caine rasa 

class Animale {
	static int numar_animale;
public:
	void afisare_nr()
	{
		cout << numar_animale << endl;
	}
	Animale()
	{
		Animale::numar_animale = Animale::numar_animale + 1;
	}

};
int Animale::numar_animale = 0;
class Caini : public Animale
{
private:
	int varsta;
	string rasa;
	bool dresat;
public:
	Caini(int varsta, string rasa, bool dresat):Animale()
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
		cout << "\nNumarul de animale: ";
		afisare_nr();
		cout << endl;
	}

};

int main()
{
	Caini s(31, "Maidanez",1);
	Caini s2(21, "Bison", 1);
	s.afisare();
	return 0;
}