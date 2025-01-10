#include <iomanip> 
#include <cstring> 
#include <stdlib.h>
#include <conio.h>
#include <stdio.h> 
#include <fstream>                  
#include <iostream>

using namespace std;

struct Telefon {
    char marka[100];
    char model[100];
    char serino[100];
    char bellek[100];
    char batarya[100];
    char fiyat[200];
};

Telefon telefoncu;

void TelefonEkle() {
    ofstream yaz("deneme.dat", ios::binary | ios::app);
    
    char secim;
    do {
    	system("cls");
        cout << "Telefonun Markasini Giriniz:\n";
        cin.ignore(); 
        cin.getline(telefoncu.marka, sizeof(telefoncu.marka));
        cout << "Telefonun Modelini Giriniz: \n";
        cin.getline(telefoncu.model, sizeof(telefoncu.model));
        cout << "Telefonun Seri No sunu Giriniz:\n";
        cin.getline(telefoncu.serino, sizeof(telefoncu.serino));
        cout << "Telefonun Bellek Kapasitesini Giriniz:\n";
        cin.getline(telefoncu.bellek, sizeof(telefoncu.bellek));
        cout << "Telefonun Batarya Bilgisini Giriniz:\n";
        cin.getline(telefoncu.batarya, sizeof(telefoncu.batarya));
        cout << "Telefonun Fiyat Bilgisini Giriniz:\n";
        cin.getline(telefoncu.fiyat, sizeof(telefoncu.fiyat));
        yaz.write((char*)&telefoncu, sizeof(telefoncu));
        cout << "Daha fazla ekleme yapacak misiniz? (E/e): ";
        secim = cin.get();
        cout << endl;
    } while (secim == 'e' || secim == 'E');
    
    yaz.close();
}
void TelefonListele() {
    ifstream oku("deneme.dat", ios::binary | ios::app); 
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(telefoncu);

    cout << "Toplam Kayit Sayisi: " << kayits << endl;

    if(kayits > 0) {
        for(int i = 0; i < kayits; i++) {
            oku.seekg(i * sizeof(telefoncu), ios::beg);
            oku.read((char*)&telefoncu, sizeof(telefoncu));	

            cout << i + 1 << ". Telefonun Bilgileri" << endl;
            cout << "Telefonun Markasi: " << telefoncu.marka << endl;
            cout << "Telefonun Modeli: " << telefoncu.model << endl;
            cout << "Telefonun Seri Nosu: " << telefoncu.serino << endl;
            cout << "Telefonun Bellek Bilgisi: " << telefoncu.bellek << " GB" << endl;
            cout << "Telefonun Batarya Bilgisi: " << telefoncu.batarya << " mAh" << endl;
            cout << "Telefonun Fiyati : " << telefoncu.fiyat << " TL" << endl;
        }
    } else {
        cout << "Kayit Bulunamadi..." << endl;
    }

    oku.close();
}

void TelefonAra() {
	ifstream oku("deneme.dat", ios::binary | ios::app); 
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(telefoncu);
    char aranan[10];
    cout << "Aranacak Telefonun Seri Nosunu giriniz:"<< endl;
    cin >> aranan;
    if(kayits > 0) {
        for(int i = 0; i < kayits; i++) {
            oku.seekg(i * sizeof(telefoncu), ios::beg);
            oku.read((char*)&telefoncu, sizeof(telefoncu));	
		if(strcmp(telefoncu.serino, aranan)==0){
            cout <<" Bulunan Telefonun Bilgileri" << endl;
            cout << "Telefonun Markasi: " << telefoncu.marka << endl;
            cout << "Telefonun Modeli: " << telefoncu.model << endl;
            cout << "Telefonun Seri Nosu: " << telefoncu.serino << endl;
            cout << "Telefonun Bellek Bilgisi: " << telefoncu.bellek << " GB" << endl;
            cout << "Telefonun Batarya Bilgisi: " << telefoncu.batarya << " mAh" << endl;
            cout << "Telefonun Fiyati : " << telefoncu.fiyat << " TL" << endl;
			}
        }
    } 
	else {
        cout << "Kayit Bulunamadi..." << endl;
    }

    oku.close();
    
}

void KayitSil() {
    ifstream oku("deneme.dat", ios::binary | ios::in);  
    ofstream y_yaz("Yedet.dat", ios::binary | ios::trunc);  
    char aranan[10];
    char secim;
    bool var = false;
    
    cout << "Silinecek Telefonun Seri Nosunu giriniz:"<< endl;
    cin >> aranan;
    
    if (oku) {
        while (oku.read((char*)&telefoncu, sizeof(telefoncu))) {  
            if (strcmp(telefoncu.serino, aranan) == 0) {  
                cout <<"Silinecek Telefonun Bilgileri" << endl;
                cout << "Telefonun Markasi: " << telefoncu.marka << endl;
                cout << "Telefonun Modeli: " << telefoncu.model << endl;
                cout << "Telefonun Seri Nosu: " << telefoncu.serino << endl;
                cout << "Telefonun Bellek Bilgisi: " << telefoncu.bellek << " GB" << endl;
                cout << "Telefonun Batarya Bilgisi: " << telefoncu.batarya << " mAh" << endl;
                cout << "Telefonun Fiyati : " << telefoncu.fiyat << " TL" << endl;
                cout << "Silinecek Telefon Bu Mu?(e/h)" << endl;
                cin >> secim;
                
                if (secim == 'e' || secim == 'E') {  
                    var = true;  
                    continue;  
                }
            }
            y_yaz.write((char*)&telefoncu, sizeof(telefoncu));  
        }

        oku.close();
        y_yaz.close();
        
        if (var) {
            remove("deneme.dat");  
            rename("Yedet.dat", "deneme.dat");  
            cout << "Kayit Silindi" << endl;
        } else {
            remove("Yedet.dat");  
            cout << "Kayit Bulunamadi!" << endl;
        }
    } else {
        cout << "Dosya okunamadý!" << endl;
    }
}


void TelefonDuzenle() {
    ifstream oku("deneme.dat", ios::binary | ios::in);  
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(telefoncu);
    char aranan[10];
    char secim;
    bool var = false;
    
    cout << "Duzenlenecek Telefonun Seri Nosunu giriniz:" << endl;
    cin >> aranan;

    
    ofstream y_yaz("Yedet.dat", ios::binary | ios::trunc);  

    if (y_yaz) {
        for (int i = 0; i < kayits; i++) {
            oku.seekg(i * sizeof(telefoncu), ios::beg);
            oku.read((char*)&telefoncu, sizeof(telefoncu));

            if (strcmp(telefoncu.serino, aranan) == 0) {
                cout << "Duzeltilecek Telefonun Bilgileri" << endl;
                cout << "Telefonun Markasi: " << telefoncu.marka << endl;
                cout << "Telefonun Modeli: " << telefoncu.model << endl;
                cout << "Telefonun Seri Nosu: " << telefoncu.serino << endl;
                cout << "Telefonun Bellek Bilgisi: " << telefoncu.bellek << " GB" << endl;
                cout << "Telefonun Batarya Bilgisi: " << telefoncu.batarya << " mAh" << endl;
                cout << "Telefonun Fiyati : " << telefoncu.fiyat << " TL" << endl;
                cout << "Duzeltilecek Telefon Bu Mu? (e/h)" << endl;
                cin >> secim;

                if (secim == 'h' || secim == 'H') {
                    
                    y_yaz.write((char*)&telefoncu, sizeof(telefoncu));
                } else if (secim == 'e' || secim == 'E') {
                   
                    var = true;
                    cout << "Telefonun Markasini Giriniz:\n";
                    cin.ignore(); 
                    cin.getline(telefoncu.marka, sizeof(telefoncu.marka));
                    cout << "Telefonun Modelini Giriniz: \n";
                    cin.getline(telefoncu.model, sizeof(telefoncu.model));
                    cout << "Telefonun Seri No sunu Giriniz:\n";
                    cin.getline(telefoncu.serino, sizeof(telefoncu.serino));
                    cout << "Telefonun Bellek Kapasitesini Giriniz:\n";
                    cin.getline(telefoncu.bellek, sizeof(telefoncu.bellek));
                    cout << "Telefonun Batarya Bilgisini Giriniz:\n";
                    cin.getline(telefoncu.batarya, sizeof(telefoncu.batarya));
                    cout << "Telefonun Fiyat Bilgisini Giriniz:\n";
                    cin.getline(telefoncu.fiyat, sizeof(telefoncu.fiyat));
                    y_yaz.write((char*)&telefoncu, sizeof(telefoncu));  
                } else {
                    
                    y_yaz.write((char*)&telefoncu, sizeof(telefoncu));
                }
            } else {
                
                y_yaz.write((char*)&telefoncu, sizeof(telefoncu));
            }
        }

        oku.close();
        y_yaz.close();

        if (var) {
            remove("deneme.dat");
            rename("Yedet.dat", "deneme.dat");
            cout << "Veri Guncellendi" << endl;
        } else {
            remove("Yedet.dat");
            cout << "Kayit Bulunamadi!" << endl;
        }
    } else {
        cout << "Yedek dosyasý açýlmadý!" << endl;
    }
}


int main() {
    char anamenu;
    char secim;
    do {
        system("cls");

        cout << "|-------Hosgeldiniz------|" << endl;
        cout << "|      Secim Yapiniz     |" << endl;
        cout << "|   1- Telefon Ekleme    |" << endl;
        cout << "|   2- Telefon Listeleme |" << endl;
        cout << "|   3- Telefon Ara       |" << endl;
        cout << "|   4- Telefon Duzenle   |" << endl;
        cout << "|   5- Telefon Kayit Sil |" << endl;
        cout << "|   6- Cikis 			  |" << endl;
        cout << "|------------------------|" << endl;
        cout << "Seciminizi yapiniz: ";
        cin >> secim;

        switch(secim) {
            case '1':
                TelefonEkle();
                break;
            case '2':
                TelefonListele();
                break;
            case '3':
                TelefonAra();
                break;
            case '4':
                TelefonDuzenle();
                break;
            case '5':
                KayitSil();
                break;
            case '6':
            	cout << "Cikis Yapildi!" << endl;
            	exit(0);
            	break;
            default:
                cout << "Gecersiz secim!\n";
        }

        cout << "Ana menuye donmek icin A/a'ya tiklayiniz. Cikmak icin herhangi bir tusa basiniz.";
        anamenu = getche();

    } while (anamenu == 'A' || anamenu == 'a');

    return 0;
}

