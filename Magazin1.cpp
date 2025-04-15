#include <iostream>
#include <iomanip>
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
	string produse[100] = {};//lista de produse existente
	float pret_produse[100] = {};//pretul produselor 
	int numar_produse_diferite = 0;
	int numar_total_produse = 0;
	~Magazin()
	{

	}
	Magazin()//Constructor
	{
		cout << "Nume magazin: "; getline(cin,this->nume_magazin);
		cout << "Adresa magazin: "; getline(cin,this->adresa_magazin);
		cout << "Numar de contact: "; getline(cin,this->numar_de_contact_magazin);
	 	cout << "Adresa de email: "; getline(cin, this->adresa_email);
 	    cout << endl;
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
			cout << i << ": " << this->produse[i] << " Pret: " << fixed << setprecision(2) << this->pret_produse[i] <<  " RON" << endl;
		}
		cout << endl;
	}
	bool Verificare_email()
	{
		string email = this->adresa_email;
		for (int i = 0; i < email.size(); i++)
			if (adresa_email[i] == '@')
				return 1;
		return 0;
	}

	bool Verificare_numar_contact()
	{
		string nr = this->numar_de_contact_magazin;
		if (nr.size() != 10 || (nr[0] != '0' && nr[1] != '7'))
			return 0;
		return 1;
	}
	bool Verificare_date()
	{
		Magazin& s = *this;
		if (!s.Verificare_email())
			cout << "Adresa de email a magazinului " << s.nume_magazin << " nu este buna!" << endl;
		while (!s.Verificare_email() && s.adresa_email != "x" && s.adresa_email != "X")
		{
			cout << "Introduceti o adresa de email valida!" << endl
				<< "Daca nu introduceti o adresa de email valida magazinul nu poate fi creat!!" <<
				endl << "Pentru a opri citirea unei adrese de email valide introduceti x/X!!!" << endl;
			cout << "Adresa email: "; getline(cin, s.adresa_email);
		}
		if (s.adresa_email == "x" || s.adresa_email == "X")
			return 0;
		if (!s.Verificare_numar_contact())
			cout << "Numarul de contact al Magazinului " << s.nume_magazin << " nu este bun!" << endl;
		while (!s.Verificare_numar_contact() && s.numar_de_contact_magazin != "x" && s.numar_de_contact_magazin != "X")
		{
			cout << "Introduceti un numar de contact valid!" << endl << "Daca nu introduceti un numar de contact valid magazinul nu poate fi creat!!" <<
				endl << "Pentru a opri citirea unui numar de contact valid introduceti x/X!!!" << endl;
			cout << "Numar de contact: "; getline(cin, s.numar_de_contact_magazin);
		}
		if (s.numar_de_contact_magazin == "x" || s.numar_de_contact_magazin == "X")
			return 0;
		return 1;
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
	Magazin *shop;//Memorez in ce magazin a ajuns produsul
	bool Verificare_Data(string data)
	{
		bool ok = 0;
		int nr = 0;
		if (data.size() != 10)
		{
			cout << "Data trebuie sa fie de forma zz:ll:aaaa\nData: ";
			return 0;
		}
		if (data[2] == ':' && data[5] == ':')
			ok = 1;
		for (int i = 0; i < data.size(); i++)
		{
			if (isdigit(data[i]))
				nr++;
		}

		if (nr == 8 && ok)
			return 1;
		cout << "Data trebuie sa fie de forma zz:ll:aaaa\nData: ";
		return 0;
	}
	bool Corectitudine_Data(string data)
	{
		if (!Verificare_Data(data))
			return 0;

		string zz = {};
		zz += data[0];
		zz += data[1];

		string ll = {};
		ll += data[3];
		ll += data[4];

		string aaaa = {};
		aaaa += data[6];
		aaaa += data[7];
		aaaa += data[8];
		aaaa += data[9];

		int zi, luna, an;
		zi = stoi(zz);
		luna = stoi(ll);
		an = stoi(aaaa);

		if (an < 0)
		{
			cout << "Anul nu exista!" << endl;
			return 0;
		}
		if (zi < 0 || zi > 31)
		{
			cout << "Ziua nu exista!\n";
			return 0;
		}
		if (luna < 0 || luna > 12)
		{
			cout << "Luna nu exista\n";
			return 0;
		}

		bool ok = 1;
		switch (luna)
		{
		case 1:
			if (zi < 0 || zi > 31)
				ok = 0;
			break;
		case 2:
			if ((an % 4 == 0 && an % 100 != 0) xor (an % 400 == 0))
				if (zi < 0 || zi > 29)
					ok = 0;
			if (zi < 0 || zi > 28)
				ok = 0;
			break;
		case 3:
			if (zi < 0 || zi > 31)
				ok = 0;
		case 4:
			if (zi < 0 || zi > 30)
				ok = 0;
			break;
		case 5:
			if (zi < 0 || zi > 31)
				ok = 0;
			break;
		case 6:
			if (zi < 0 || zi > 30)
				ok = 0;
			break;
		case 7:
			if (zi < 0 || zi > 31)
				ok = 0;
			break;
		case 8:
			if (zi < 0 || zi > 31)
				ok = 0;
			break;
		case 9:
			if (zi < 0 || zi > 30)
				ok = 0;
			break;
		case 10:
			if (zi < 0 || zi > 31)
				ok = 0;
			break;
		case 11:
			if (zi < 0 || zi > 30)
				ok = 0;
			break;
		case 12:
			if (zi < 0 || zi > 31)
				ok = 0;
			break;
		}

		if (!ok)
		{
			cout << "Ziua introdusa nu exista!" << endl;
			return 0;
		}

		return 1;
	}
	bool Comparare_Date(string data1, string data2)
	{
		if (!Corectitudine_Data(data1) || !Corectitudine_Data(data2))
			return 0;

		string zz1 = {};
		zz1 += data1[0];
		zz1 += data1[1];

		string ll1 = {};
		ll1 += data1[3];
		ll1 += data1[4];

		string aaaa1 = {};
		aaaa1 += data1[6];
		aaaa1 += data1[7];
		aaaa1 += data1[8];
		aaaa1 += data1[9];

		int zi1, luna1, an1;
		zi1 = stoi(zz1);
		luna1 = stoi(ll1);
		an1 = stoi(aaaa1);

		string zz2 = {};
		zz2 += data2[0];
		zz2 += data2[1];

		string ll2 = {};
		ll2 += data2[3];
		ll2 += data2[4];

		string aaaa2 = {};
		aaaa2 += data2[6];
		aaaa2 += data2[7];
		aaaa2 += data2[8];
		aaaa2 += data2[9];

		int zi2, luna2, an2;
		zi2 = stoi(zz2);
		luna2 = stoi(ll2);
		an2 = stoi(aaaa2);

		if (an1 < an2)
			return 1;
		else
			if (an1 > an2)
				return 0;
		if (luna1 < luna2)
			return 1;
		else
			if (luna1 > luna2)
				return 0;
			else
				if (zi1 < zi2)
					return 1;
				else
					if (zi1 > zi2)
						return 0;
					else
						if (zi1 == zi2)
							return 1;
	}
	int Verificare_produs_in_stoc(string nume, string prod[], int nr)//caut in lista de produse daca exista produsl pe care il aduc acum
	{
		for (int i = 1; i <= nr; i++)
		{
			if (prod[i] == nume)//in momentul in care gasesc produsul in stoc returnez ca l-am gasit (adica 1/adevarat)
				return i;
		}
		return 0;//daca am ajuns la finalul liste insemna ca prdusul nu este deja in magazin si returnez 0 (false)
	}
	//constructor

	Produse(Magazin& s) : Magazin(s)//creaz un produs si il leg de un produs existent, -shop(s) memoreaza unde este produsul, Magazin(s) - sa nu imi mai ceara cand creez un magazin cand creez un produs
	{
		cout << "Nume produs: "; getline(cin,this->nume_produs);
		cout << "Pretul produs: "; cin >> this->pret;
		cout << "Cantitatea de produse: "; cin >> this->cantitate;
		cin.get();
		cout << "Data expirari acestui lot(zz:ll:aaaa): "; getline(cin,this->data_expiriare);
		while (Corectitudine_Data(this->data_expiriare) == 0)
		{
			getline(cin, this->data_expiriare);
		}
		cout << "Data primire lot(zz::ll:aaaa): "; getline(cin,this->data_primire);
		while (Corectitudine_Data(this->data_primire) == 0)
		{
			getline(cin, this->data_primire);
		}
		
		if (!Comparare_Date(this->data_primire, this->data_expiriare))
		{
			cout << endl;
			cout << "**************************************" << endl 
				 << "***** Produsul este expirat!! ********" << endl
				 << "********** Lot refuzat!! *************" << endl
				 << "**************************************" << endl;
			cout << endl;
			shop = NULL;
			
		}
		else
		{
			shop = &s;
			if (Verificare_produs_in_stoc(this->nume_produs, s.produse, s.numar_produse_diferite) == 0)
			{
				s.numar_produse_diferite++;
				s.produse[s.numar_produse_diferite] = this->nume_produs;//imi adauga produsul nou in lista de produse
			}
			s.pret_produse[Verificare_produs_in_stoc(this->nume_produs, s.produse, s.numar_produse_diferite)] = this->pret;//retin pretul produsului nou pe aceasi pozitie/index ca si numele 
			s.numar_total_produse += this->cantitate;//actualizez cantitatea totala de produse
		}
		cout << endl;
	}
	~Produse()
	{
	
	}
	void Informatii_produs()
	{
		if (shop != NULL) {
			cout << "Numele produsului este " << this->nume_produs << " acesta face parte din magazinul " << shop->nume_magazin << endl;
			cout << "Pretul: " << fixed << setprecision(2) << this->pret << " RON" << endl;
			cout << "Cantitate: " << this->cantitate << endl;
			cout << "Data expirari: " << this->data_expiriare << endl;
			cout << endl;
		}
		else
			cout << "Produsul " << this->nume_produs << " nu face parte dintr-un magazin!" << endl << endl;
	}
	bool operator<(const Produse& s) const
	{
		return this->pret < s.pret;
	}
	bool operator>(const Produse& s) const
	{
		return this->pret > s.pret;
	}

};

int main()
{
	Admin admin;
	Magazin M1;
	if (M1.Verificare_date() == 0)
	{
		cout << "Datele de contact nu sunt valide!";
		return 0;
	}
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

	if (P1 < P2)
		cout << P1.nume_produs << " este mai ieftin decat " << P2.nume_produs << endl;
	else if (P1 > P2)
		cout << P1.nume_produs << " este mai scump decat " << P2.nume_produs << endl;
	else
		cout << P1.nume_produs << " are acelasi pret cu " << P2.nume_produs << endl;

	return 0;
}