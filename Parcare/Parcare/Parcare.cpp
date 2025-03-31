#include <iostream>
#include <string>
using namespace std;


//Creare clasa parcare in care retinem numarul de locuri disponiile numarul de locuri ocupate si numarul de locuri totale
class Parcare {
public:
	const int nr = 30;
	static int nr_locuri_disponibile;
	static int nr_locuri_parcare;
	static int nr_locuri_ocupate;
	static bool locuri_ocupate[30];//cream un vector de frecventa pentru a vedea ce locuri de parcare sunt disponibile
	static string Pret_ora;
	int loc_ocupat;
	void cautare_loc_p(const int s, bool v[])//cream aceasta functie pentru a parcurge fiecare loc de parcare si sa gasim primul loc liber
	{
		for (int i = 0; i < s; i++)
			if (v[i] == 0)
			{
				v[i] = 1;
				loc_ocupat = i + 1;
				return;//in momentul in care am gasit un loc liber il marchez ca ocupat si inchid functia
			}
	}
	Parcare()//constructor
	{
		nr_locuri_ocupate++;
		nr_locuri_disponibile--;
		cautare_loc_p(nr, locuri_ocupate);
	}
	friend void locuri_libere();
	friend void status_parcare();

};

void status_parcare()
{
	cout << "Numarul de locuri:" << endl;
	cout << "                  --------->Total:" << Parcare::nr_locuri_parcare << endl;
	cout << "                  --------->Disponibile: " << Parcare::nr_locuri_disponibile << endl;
	cout << "                  --------->Ocupate: " << Parcare::nr_locuri_ocupate << endl;
}

void locuri_libere()
{
		cout << "Numarul de locuri de parcare disponibile: " << Parcare::nr_locuri_disponibile << endl;
}

int Parcare::nr_locuri_parcare = 30;
int Parcare::nr_locuri_ocupate = 0;
int Parcare::nr_locuri_disponibile = 30;
string Parcare::Pret_ora = "2 RON";
bool Parcare::locuri_ocupate[30] = {};
//cream o clasa derivata din clasa parcare in care retinem datele pentru o masina parcata
class Informatii_masini_parcate : public Parcare {
private:
	string nr_inmatriculare;
	string ora_s;
	friend class Admin;
public:
	Informatii_masini_parcate(string nr_inmatriculare, string ora):Parcare()//constructor
	{
		this->nr_inmatriculare = nr_inmatriculare;
		this->ora_s = ora;
	}
	void afisare_loc_ocupat() //afisam ce loc ocupa masina x
	{
		cout <<  "Locul ocupat este: " <<  this->loc_ocupat << endl;
	}
	~Informatii_masini_parcate() {};//destructor
	friend void total_tarif(Informatii_masini_parcate& s);
};
void total_tarif(Informatii_masini_parcate& s)//in acesta functie socotim diferenta dintre ora de plecare si ora de sosire afisand la final totalul de plata
{
	Parcare::locuri_ocupate[s.loc_ocupat - 1] = 0;//marcam la liber locul ocupat de masina x
	Parcare::nr_locuri_disponibile++;
	Parcare::nr_locuri_ocupate--;
	cout << "Introdu ora plecarii pentru masina cu numarul " << s.nr_inmatriculare << ' ';
	string orap;
	getline(cin, orap);
	string oras = s.ora_s;
	int ora_s, min_s, ora_p, min_p, t;
	string tarif = {};
	string moneda = {};
	bool ok = 0;
	for (int i = 0; i < Parcare::Pret_ora.size(); i++)
	{
		if (!isdigit(Parcare::Pret_ora[i]))
			ok = 1;
		if (!ok)tarif += Parcare::Pret_ora[i];
		else
			moneda += Parcare::Pret_ora[i];
	}
	t = stoi(tarif);
	string sora = {};
	string smin = {};
	string pora = {};
	string pmin = {};
	ok = 0;
	for (int i = 0; i < oras.size(); i++)
	{
		if (!isdigit(oras[i]))
			ok = 1, i++;
		if (!ok)
			sora += oras[i];
		else
			smin += oras[i];
	}
	ok = 0;
	for (int i = 0; i < orap.size(); i++)
	{
		if (!isdigit(orap[i]))
			ok = 1, i++;
		if (!ok)
			pora += orap[i];
		else
			pmin += orap[i];
	}
	ora_s = stoi(sora);
	min_s = stoi(smin);
	ora_p = stoi(pora);
	min_p = stoi(pmin);
	int total_start = ora_s * 60 + min_s;
	int total_final = ora_p * 60 + min_p;
	int difm = total_final - total_start;
	if (difm < 0)
		difm += 24 * 60;
	int difo = difm / 60;
	int minr = difm % 60;
	if (minr > 0)
		difo++;
	cout << "Totalul de plata este: " << difo*t << ' ' << moneda << endl;
	
}
//cream o clasa admin prietena a clasei informatii masini parcate pentru a avea acces la toate datele legate de masinile din parcare
class Admin
{
public:
	void afisare_date_masina(const Informatii_masini_parcate& s)
	{
		cout << "Admin -> Numar de inmatriculare: " << s.nr_inmatriculare << " Ora de sosire: " << s.ora_s << " Masina este parcata pe locul: " << s.loc_ocupat << endl;
	}
};


int main()
{
	Admin admin;

	int n;
	cout << "Introdu numarul de masini care intra in parcare:"; cin >> n;
	cin.get();

	Informatii_masini_parcate** masini = new Informatii_masini_parcate * [n];
	for (int i = 0; i < n; i++)
	{
		string nri;
		string ora;
		cout << "Introdu numarul de inmatriculare al masini: "; 
		getline(cin, nri);
		cout << "Introdu ora sosiri in parcare: "; 
		getline(cin, ora);
		masini[i] = new Informatii_masini_parcate(nri, ora);
	}

	for (int i = 0; i < n; i++)
		admin.afisare_date_masina(*masini[i]);

	status_parcare();
	total_tarif(*masini[0]);
	status_parcare();
	string nri;
	string ora;
	cout << "Introdu numarul de inmatriculare al masini: ";
	getline(cin, nri);
	cout << "Introdu ora sosiri in parcare: ";
	getline(cin, ora);
	Informatii_masini_parcate masina_noua(nri, ora);

	admin.afisare_date_masina(masina_noua);

	return 0;
}