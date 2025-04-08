#include <iostream>
#include <string>
using namespace std;

class Magazin {
private:
	int numar_mediu_de_clienti = 0;
	int numar_de_clienti = 0;
public:
	string nume_magazin;
	string adresa_magazin;
	string numar_de_contact_magazin;
	string adresa_email;
	string produse[1000] = {};
	int pret_produse[1000] = {};
	int numar_produse_diferite = 0;
	int numar_total_produse = 0;
	Magazin() 
	{
		cout << "Introdu numele magazinului: "; getline(cin,this->nume_magazin);
		cout << "Introdu adresa magazinului: "; getline(cin,this->adresa_magazin);
		cout << "Introdu numarul de contact al magazinului: "; getline(cin,this->numar_de_contact_magazin);
		cout << "Introdu adresa de email: "; getline(cin, this->adresa_email);
	}
	void denumire()
	{
		cout << "Nume magazin: " << this->nume_magazin << endl;
	}
	void adresa()
	{
		cout << "Adresa magazinului: " << this->nume_magazin << " este " << this->adresa_magazin << endl;
	}
	void date_de_contact()
	{
		cout << "Numarul de contact al magazinului " << this->nume_magazin << " este " << this->numar_de_contact_magazin << 
			" si email-ul este " << this->adresa_email << endl;
	}
	void Afisare_produse()
	{
		for (int i = 1; i <= numar_produse_diferite; i++)
		{
			cout << i << ": " << this->produse[i] << " Pret: " << this->pret_produse[i] << endl;
		}
	}
	friend void Informatii_magazin(Magazin& s);
	friend class Admin;
};

class Admin {
public:
	void afisare_informatii(const Magazin& s)
	{
		cout << "--------------------------ADMIN--------------------------" << endl;
		cout << "Nume magazin: " << s.nume_magazin << endl;
		cout << "Informatii: " << endl;
		cout << "Numar de produse diferite: " << s.numar_produse_diferite << endl;
		cout << "Cantitatea totala de produse din magazin este: " << s.numar_total_produse << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << endl;
	}
};
void Informatii_magazin(Magazin& s)
{
	cout << "Nume magazin: " << s.nume_magazin << endl;
	cout << "Adresa magazin: " << s.adresa_magazin << endl;
	cout << "Numar de contact: " << s.numar_de_contact_magazin << endl;
	cout << "Adresa de email: " << s.adresa_email << endl;
	cout << endl;
}

class Produse : public Magazin {
public:
	string nume_produs;
	float pret;
	int cantitate;
	string data_expiriare;
	string data_primire;
	Magazin& shop;
	bool Verificare_produs_in_stock(string nume, string prod[], int nr)
	{
		for (int i = 1; i <= nr; i++)
		{
			if (prod[i] == nume)
				return 1;
		}
		return 0;
	}
	Produse(Magazin& s) : shop(s), Magazin(s)
	{
		cout << "Nume produs: "; getline(cin,this->nume_produs);
		cout << "Pretul produs: "; cin >> this->pret;
		cout << "Cantitatea de produse: "; cin >> this->cantitate;
		cin.get();
		cout << "Data expirari acestui lot: "; getline(cin,this->data_expiriare);
		cout << "Data primiri lotului: "; getline(cin,this->data_primire);
		if (Verificare_produs_in_stock(this->nume_produs, s.produse, s.numar_produse_diferite) == 0)
		{
			s.numar_produse_diferite++;
			s.produse[s.numar_produse_diferite] = this->nume_produs;
			s.pret_produse[s.numar_produse_diferite] = this->pret;
		}
		s.numar_total_produse += this->cantitate;
	}
	void Informatii_produs()
	{
		cout << "Numele produsului este " << this->nume_produs << " acesta face parte din magazinul " << shop.nume_magazin << endl;
		cout << "Pretul: " << this->pret << " RON" << endl;
		cout << "Cantitate: " << this->cantitate << endl;
		cout << "Data expirari: " << this->data_expiriare << endl;
		cout << endl;
	}


};


int main()
{
	Admin admin;
	Magazin M1;
	Informatii_magazin(M1);
	M1.date_de_contact();
	M1.adresa();
	M1.denumire();
	M1.date_de_contact();

	Produse P1(M1);

	P1.Informatii_produs();

	admin.afisare_informatii(M1);

	M1.Afisare_produse();

	Produse P2(M1);
	admin.afisare_informatii(M1);
	M1.Afisare_produse();

	/*
	De adaugat endl dupa fiecare functie de citire/afisare
	Sa verific daca merg toate functiile
	Verificare text si logica
	*/
	return 0;
}