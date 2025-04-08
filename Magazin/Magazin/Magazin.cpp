#include <iostream>
#include <string>
using namespace std;

class Magazin {
private:
	int numar_mediu_de_clienti = 0;//media pe zi de clienti
	int numar_de_clienti = 0;//nr total de clienti
public:
	string nume_magazin;
	string adresa_magazin;
	string numar_de_contact_magazin;
	string adresa_email;
	string produse[1000] = {};//lista de produse existente
	int pret_produse[1000] = {};//pretul produselor 
	int numar_produse_diferite = 0;
	int numar_total_produse = 0;
	Magazin()//Constructor
	{
		cout << "Nume magazin: "; getline(cin,this->nume_magazin);
		cout << "Adresa magazin: "; getline(cin,this->adresa_magazin);
		cout << "Numar de contact: "; getline(cin,this->numar_de_contact_magazin);
		cout << "Adresa de email: "; getline(cin, this->adresa_email);
		cout << endl;
	}
	~Magazin()
	{

	}
	void denumire()
	{
		cout << "Nume magazin: " << this->nume_magazin << endl;
		cout << endl;
	}
	void adresa()
	{
		cout << "Adresa magazinului: " << this->nume_magazin << " este " << this->adresa_magazin << endl;
		cout << endl;
	}
	void date_de_contact()
	{
		cout << "Numarul de contact al magazinului " << this->nume_magazin << " este " << this->numar_de_contact_magazin << 
			" si email-ul este " << this->adresa_email << endl;
		cout << endl;
	}
	void Afisare_produse()
	{
		for (int i = 1; i <= numar_produse_diferite; i++)//ma plimb prin lista de produse si afisez si pretul produsului
		{
			cout << i << ": " << this->produse[i] << " Pret: " << this->pret_produse[i] << endl;
		}
		cout << endl;
	}
	friend class Admin;//clasa prietena
	friend void Informatii_magazin(Magazin& s);//functie prietena, specific pentru ce magazin afisez informatiile
};

class Admin {
public:
	void afisare_informatii(const Magazin& s)//am folosit & pentru a nu crea in memorie o copie a magazinului
	{
		cout << "--------------------------ADMIN--------------------------" << endl;
		cout << "Nume magazin: " << s.nume_magazin << endl;
		cout << "Informatii: " << endl;
		cout << "Numar de produse diferite: " << s.numar_produse_diferite << endl;
		cout << "Cantitatea totala de produse din magazin este: " << s.numar_total_produse << endl;
		cout << "Numar mediu de clienti: " << s.numar_mediu_de_clienti << endl;
		cout << "Numar de clienti care au intrat in magazin: " << s.numar_de_clienti << endl;
		cout << "---------------------------------------------------------" << endl;
		cout << endl;
	}
};
void Informatii_magazin(Magazin& s)//
{
	cout << "Nume magazin: " << s.nume_magazin << endl;
	cout << "Adresa magazin: " << s.adresa_magazin << endl;
	cout << "Numar de contact: " << s.numar_de_contact_magazin << endl;
	cout << "Adresa de email: " << s.adresa_email << endl;
	cout << endl;
}

class Produse : public Magazin {//clasa produse este derivata din magazin
public:
	string nume_produs;
	float pret;
	int cantitate;
	string data_expiriare;
	string data_primire;
	Magazin& shop;//Memorez in ce magazin a ajuns produsul
	bool Verificare_produs_in_stoc(string nume, string prod[], int nr)//caut in lista de produse daca exista produsl pe care il aduc acum
	{
		for (int i = 1; i <= nr; i++)
		{
			if (prod[i] == nume)//in momentul in care gasesc produsul in stoc returnez ca l-am gasit (adica 1/adevarat)
				return 1;
		}
		return 0;//daca am ajuns la finalul liste insemna ca prdusul nu este deja in magazin si returnez 0 (false)
	}
	//constructor
	Produse(Magazin& s) : shop(s), Magazin(s)//creaz un produs si il leg de un produs existent, -shop(s) memoreaza unde este produsul, Magazin(s) - sa nu imi mai ceara cand creez un magazin cand creez un produs
	{
		cout << "Nume produs: "; getline(cin,this->nume_produs);
		cout << "Pretul produs: "; cin >> this->pret;
		cout << "Cantitatea de produse: "; cin >> this->cantitate;
		cin.get();
		cout << "Data expirari acestui lot: "; getline(cin,this->data_expiriare);
		cout << "Data primiri lotului: "; getline(cin,this->data_primire);
		if (Verificare_produs_in_stoc(this->nume_produs, s.produse, s.numar_produse_diferite) == 0)
		{
			s.numar_produse_diferite++;
			s.produse[s.numar_produse_diferite] = this->nume_produs;//imi adauga produsul nou in lista de produse
			s.pret_produse[s.numar_produse_diferite] = this->pret;//retin pretul produsului nou pe aceasi pozitie/index ca si numele 
		}
		s.numar_total_produse += this->cantitate;//actualizez cantitatea totala de produse
		cout << endl;
	}
	~Produse()
	{

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

	Produse P1(M1);

	P1.Informatii_produs();

	admin.afisare_informatii(M1);

	M1.Afisare_produse();

	Produse P2(M1);
	admin.afisare_informatii(M1);
	M1.Afisare_produse();

	return 0;
}