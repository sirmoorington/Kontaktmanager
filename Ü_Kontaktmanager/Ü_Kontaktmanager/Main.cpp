#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

class Kontakt {
public:
	string sVorname;
	string sNachname;
	string sTelefonnummer;
	string sEmail;

	Kontakt(string v, string n, string t, string e) {
		sVorname = v;
		sNachname = n;
		sTelefonnummer = t;
		sEmail = e;
	}
	
	void anzeigen() {
		cout << "Name: " << sVorname << " " << sNachname << endl;
		cout << "Telefonnummer: " << sTelefonnummer << endl;
		cout << "Email: " << sEmail << endl;
		cout << endl;
	}
	
	void bearbeiten(int feld, string neuWert) {
		switch (feld) {
		case 1:
			sVorname = neuWert;
			break;
		case 2:
			sNachname = neuWert;
			break;
		case 3:
			sTelefonnummer = neuWert;
			break;
		case 4:
			sEmail = neuWert;
			break;
		default:
			cout << "Ungültige Auswahl" << endl;
		}
	}
};

class Kontaktmanager {
private:
	vector<Kontakt> vKontakte;

public:
	void kontaktHinzufuegen(string vorname, string nachname, string telefonnummer, string email) {
		vKontakte.push_back(Kontakt(vorname, nachname, telefonnummer, email));
		cout << endl;
		cout << "Kontakt hinzugefügt! " << endl;
		cout << endl;
		system("cls");
	}

	void kontaktAnzeigen() {
		system("cls");
		for (int i = 0; i < vKontakte.size(); i++) {
			cout << i + 1 << ". Kontakt:  " << endl;
			vKontakte[i].anzeigen();
			cout << "--------------------" << endl;
		}
	}


	void kontaktSuchen(string vorname) {
		system("cls");
		auto berechnung = find_if(vKontakte.begin(), vKontakte.end(), [vorname](const Kontakt& k) {
			return k.sVorname == vorname;

			});

		if (berechnung != vKontakte.end()) {
			berechnung->anzeigen();
		}
		else {
			cout << "Name wurde nicht gefunden..." << endl;
		}
	}

	void kontaktBearbeiten(string vornameS) {
		bool gefunden = false;
		for (int i = 0; i < vKontakte.size(); i++) {
			if (vKontakte[i].sVorname == vornameS) {
				gefunden = true;
				cout << "Kontakt gefunden: " << endl;
				vKontakte[i].anzeigen();

				int feld;
				cout << "Welches Feld möchtest du bearbeiten? " << endl;
				cout << "1. Vorname" << endl;
				cout << "2. Nachname" << endl;
				cout << "3. Telefonnummer" << endl;
				cout << "4. E-Mail" << endl;
				cout << "Gib die Nummer des Feldes ein: ";
				cin >> feld;

				string neuWert;
				cout << "Geben Sie den neuen Wert ein: ";
				cin >> neuWert;

				vKontakte[i].bearbeiten(feld, neuWert);
				cout << "Kontakt wurde aktualisiert" << endl;
				return;

			}
		}
		if (!gefunden) {
			cout << "Kontakt mit dem Vornamen " << vornameS << " wurde nicht gefunden..." << endl;
		}
	}

	void kontaktLoeschen(string vorname) {
		system("cls");
		auto berechnung = remove_if(vKontakte.begin(), vKontakte.end(), [vorname](const Kontakt& k) {
			return k.sVorname == vorname;

			});

		if (berechnung != vKontakte.end()) {
			char best;
			cout << "Möchten Sie den Kontakt wirklich löschen? ";
			cin >> best;
			if (best == 'j' || best == 'J') {
				vKontakte.erase(berechnung, vKontakte.end());
				cout << "Kontakt wurde gelöscht!";
			}
			else {
				cout << "Abgebrochen..." << endl;
			}
			
		}
		else {
			cout << "Name wurde nicht gefunden...";
		}

	};

	void kontakteSpeichern(string dateiName) {
		ofstream datei(dateiName);
		if (datei.is_open()) {
			for (auto& kontakt : vKontakte) {
				datei << kontakt.sVorname << " "
					<< kontakt.sNachname << " "
					<< kontakt.sTelefonnummer << " "
					<< kontakt.sEmail << endl;
			}
			datei.close();
			cout << "Kontakte wurden erfolgreich gespeichert" << endl;
		}
		else {
			cout << "Fehler beim Öffnen der Datei!" << endl;
		}
	}

	void kontakteLaden(string dateiName) {
		ifstream datei(dateiName);
		if (datei.is_open()) {
			string vorname, nachname, telefonnummer, email;
			while (datei >> vorname >> nachname >> telefonnummer >> email) {
				vKontakte.push_back(Kontakt(vorname, nachname, telefonnummer, email));
			}
			datei.close();
			cout << "Kontakte erfolgreich geladen!" << endl;
		}
		else {
			cout << "Fehler beim Öffnen oder Datei existiert nicht!" << endl;
		}
	}
};

	int main() {

		Kontaktmanager manager;
		string dateiName = "kontakte.txt";
		int iAuswahl;
		string sEingabe;

		manager.kontakteLaden(dateiName);

		do {

			cout << "Kontaktmanager" << endl;
			cout << "---------------------------" << endl;
			cout << "(1) Kontakte hinzufügen " << endl;
			cout << "(2) Kontakte anzeigen " << endl;
			cout << "(3) Kontakte nach Namen durchsuchen " << endl;
			cout << "(4) Kontakte bearbeiten " << endl;
			cout << "(5) Kontakte löschen " << endl;
			cout << "(6) Beenden" << endl;
			cout << "---------------------------" << endl;
			cin >> iAuswahl;

			if (iAuswahl == 1) {
				system("cls");
				string vorname, nachname, telefonnummer, email;
				cout << "Vorname: ";
				cin >> vorname;
				cout << "Nachname: ";
				cin >> nachname;
				cout << "Telefonnummer: ";
				cin >> telefonnummer;
				cout << "Email: ";
				cin >> email;
				manager.kontaktHinzufuegen(vorname, nachname, telefonnummer, email);
			}
			else if (iAuswahl == 2) {
				manager.kontaktAnzeigen();
			}
			else if (iAuswahl == 3) {
				cout << "Geben Sie den Namen des Kontaktes ein: ";
				cin >> sEingabe;
				manager.kontaktSuchen(sEingabe);
			}
			else if (iAuswahl == 4) {
				string vornameS;
				cout << "Geben Sie den Namen des Kontaktes ein: ";
				cin >> vornameS;
				manager.kontaktBearbeiten(vornameS);

			}
			else if (iAuswahl == 5) {
				cout << "Geben Sie den Namen des Kontaktes ein, den Sie löschen wollen: ";
				cin >> sEingabe;
				manager.kontaktLoeschen(sEingabe);
			} else if (iAuswahl == 6){
				manager.kontakteSpeichern(dateiName);
			}

		} while (iAuswahl != 6);


		return 0;
	}