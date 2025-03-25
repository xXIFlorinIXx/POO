#include <iostream>
#include <string>
using namespace std;

class persoana {
protected:
	string nume;
	int varsta;
public:
	persoana(string nume, int varsta)
	{
		this->nume = nume;
		this->varsta = varsta;
	}
	void afisarinf()
	{
		cout << "Nume: " << nume << " Varsta: " << varsta << endl;
	}

	string Getnume() const {
		return nume;
	}

	int GetVarsta() const {
		return varsta;
	}
};

class student : public persoana {
private:
	float medie;
	friend class Admin;
public:
	student(string nume, int varsta, float medie) : persoana(nume, varsta)
	{
		this->medie = medie;
	}
	void afisare()
	{
		cout << "Nume: " << nume << " Varsta: " << varsta << " Medie: " << medie << endl;
	}
	//suprascirerea operatorului >
	bool operator>(const student& celalalt_obiect) const {
		return this->medie > celalalt_obiect.medie;
	}

};

class Admin {
public:
	void modifica_medie(student& s, float mouamedie)
	{
		cout << "Modific media pentru " << s.nume << " de la " << s.medie << " la " << mouamedie << endl;
		s.medie = mouamedie;
	}
	void afiseazaDetaliistudent(const student& s) {
		cout << "ADMIN -> Student: " << s.nume << " Varsta: " << s.varsta << " Medie: " << s.medie << endl;
	}
};

int main()
{
	student s1("Mihai", 20, 7.5);
	student s2("Victor", 21, 10);
	s1.afisare();
	s2.afisare();

	Admin admin;
	admin.modifica_medie(s2, 5);
	admin.modifica_medie(s1, 10);

	admin.afiseazaDetaliistudent(s1);
	admin.afiseazaDetaliistudent(s2);

	if (s1 > s2)
		cout << s1.Getnume() << " are media mai mare decat " << s2.Getnume() << endl;
	else
		cout << s2.Getnume() << " are media mai mare decat " << s1.Getnume() << endl;

	return 0;
}