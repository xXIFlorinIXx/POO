#include <iostream>
#include <string>
using namespace std;
//Private: Datele sunt accesibile in aceeasi clasa
//Protected: Datele sunt accesible in aceasi clasa si in clasele derivate
//Public: Datele sunt accesible in aceeasi clasa
//in clasele derivate (mostenite) si in exterior
//Sa se scrie un program in c__ pentru gestiunea unei gradinit zoologice folosind clase obiecte, derivate, vom avea o clasa animal din care vom deriva, de ex clasa pasari in care avem lungimea arimplor varsta, pt caine rasa , dresat
class Persoana {
protected:
	string nume;
	int varsta;
public:
	//Cream un constructor
	Persoana(string nume, int varsta)
	{
		this->nume = nume;
		this->varsta = varsta;
	}
	void afisare_detalii()
	{
		cout << "Nume: " << nume << ' ' << "Varsta: " << varsta << endl;
	}

};
//Derivam o  clasa derivata/mostenita din clasa persoana
class Student : public Persoana {
private:
	float medie;
public:
	//Constructor
	Student(string nume, int varsta, float medie) :Persoana(nume, varsta) 
	{
		this->medie = medie;
	}

	void afisare_informatii()
	{
		cout << "Nume: " << nume << " Varsta: " << varsta << " Media: " << medie << endl;
	}
};

int main()
{
	Student s("Ion", 21, 10);
	s.afisare_informatii();
	float mediam = 0;
	int n;
	cout << "Introduceti numarul de studenti: "; cin >> n;
	Student** studenti = new Student * [n];

	for (int i = 0; i < n; i++)
	{
		string nume;
		int varsta;
		float medie;
		cout << "Nume: "; cin >> nume;
		cout << "Varsta: "; cin >> varsta;
		cout << "Medie: "; cin >> medie;
		mediam += medie;
		studenti[i] = new Student(nume, varsta, medie);
	}

	for (int i = 0; i < n; i++)
		studenti[i]->afisare_informatii();

	cout << "Media studentiilor este: " << mediam/n << endl;

	return 0;
}