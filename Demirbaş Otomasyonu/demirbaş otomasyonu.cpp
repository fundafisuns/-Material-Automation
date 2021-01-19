//Demirbaþ otomasyonu
#include<iostream>
#include<cstring>
#include<fstream>
#include <cmath>
#include <sstream>
#include<stdio.h> 
#include <locale.h>
using namespace std;
//get set komutlarý
class demirbasBilgi{
	protected:
	string barkod;
	string esyaad;
	string alinisYil;
	string adet;
	public:
		void setBarkod(string k){
			barkod=k;
		}
		void setEsyaAd(string k){
			esyaad=k;
		}
		void setAlinisYili(string k){
			alinisYil=k;
		}
		void setAdet(string k){
			adet=k;
		}
		string getBarkod(){
			return barkod;
		}
		string getEsyaAd(){
			return esyaad;
		}
		string getAlinisYili(){
			return alinisYil;
		}
		string getAdet(){
			return adet;
		}
		string getFull(){
			return getBarkod()+"-"+getEsyaAd()+"-"+getAlinisYili()+"-"+getAdet();
		}
};
//yapýcý fonksiyonlar
demirbasBilgi dbGS(string satir);
void cikti(demirbasBilgi db);

demirbasBilgi dbGS(string satir){

	demirbasBilgi d;
	int sayac=0;
	string gecici="";
		for(int i=0;i<=satir.length();i++){
			if((satir[i]!='-'||i==(satir.length()-1))&&i!=satir.length()){
				gecici+=satir[i];
			}
			else{
				sayac++;
				if(sayac==1){
				d.setBarkod(gecici);
				}else if(sayac==2){
				d.setEsyaAd(gecici);
				}
				else if(sayac==3){
				d.setAlinisYili(gecici);
				}
				else if(sayac==4){
				d.setAdet(gecici);
				}
				gecici="";				
			}
		}
		return d;
};
//ara listele ekle classlarý
class ekleAraListele{
	public:
	void ekle(){
		demirbasBilgi db;
		char metin[50];
		cout<<"Demirbas Barkod: ";
		gets(metin);
		db.setBarkod(metin);
		cout<<"Esya Adi: ";
		gets(metin);
		db.setEsyaAd(metin);
		cout<<"Esya Alinis Yili: ";
		gets(metin);
		db.setAlinisYili(metin);
		cout<<"Esya Adet: ";
		gets(metin);
		db.setAdet(metin);
		ofstream dosya("Demirbas.txt",ios::app);
		dosya<<db.getFull()<<endl;
		dosya.close();
		
	}
	void ara(){
		char metin[50];
		cout<<"Ara: ";
		gets(metin);
			
		ifstream dosya("Demirbas.txt",ios::in);
		string satir;
		while(!dosya.eof()){
			getline(dosya,satir);
		if(satir.find(metin)!=string::npos){
			demirbasBilgi db=dbGS(satir);
			cikti(db);
			cout<<"-----------------------------"<<endl;
		}
		}
		dosya.close();		
	}
	void listele(){
		ifstream dosya("Demirbas.txt",ios::in);
		string satir;
		while(!dosya.eof()){
		
		getline(dosya,satir);
		if(satir.length()<2){
			break;
		}
		demirbasBilgi db=dbGS(satir);
		cikti(db);
		cout<<"-----------------------------"<<endl;
		}
		dosya.close();
	}

};
//sil güncelle classlarý
class silGuncelle{
	public:
		
		void guncelle(){
			char metin[50];
			cout<<"Guncellenecek Demirbasin Barkodu: ";
			gets(metin);
		ifstream dosya("Demirbas.txt",ios::in);
		string satir;
		while(!dosya.eof()){
			getline(dosya,satir);
			if(satir.length()<2){
				continue;
			}
			demirbasBilgi db=dbGS(satir);
			if(db.getBarkod()==metin){
				cout<<db.getFull()<<endl;
				cout<<"Guncel Esya Adi: ";
				gets(metin);
				if(strlen(metin)>0){
					db.setEsyaAd(metin);
				}
				cout<<"Guncel Alinis Yil: ";
				gets(metin);
				if(strlen(metin)>0){
					db.setAlinisYili(metin);
				}
				cout<<"Guncel Esya Adet: ";
				gets(metin);
				if(strlen(metin)>0){
					db.setAdet(metin);
				}
				ofstream dosyayedek("gecici.txt",ios::app);
				dosyayedek<<db.getFull()<<endl;
				dosyayedek.close();
			}else{
			ofstream dosyayedek("gecici.txt",ios::app);
			dosyayedek<<satir<<endl;
			dosyayedek.close();
				
			}
	}
	dosya.close();
	remove("Demirbas.txt");
	rename("gecici.txt","Demirbas.txt");
			
	}
	void sil(){
		char metin[50];
		cout<<"Silinecek Demirbas Barkodu: ";
		gets(metin);
		ifstream dosya("Demirbas.txt",ios::in);
		string satir;
		while(!dosya.eof()){
			getline(dosya,satir);
		if(satir.length()<2){
				continue;
		}
		demirbasBilgi db=dbGS(satir);
		if(db.getBarkod()==metin){
				
		}else{
			ofstream dosyagecici("gecici.txt",ios::app);
			dosyagecici<<satir<<endl;
			dosyagecici.close();
				
		}
		}
		dosya.close();
		remove("Demirbas.txt");
		rename("gecici.txt","Demirbas.txt");
	}
	
};
// Kalýtým alan class  ile public diye belirtilenlerden özellik alýyor.
class demirbasEkleme: public ekleAraListele,public silGuncelle{
	public: 
	demirbasEkleme(){
	    cout << "1) Esya Ekle\n";
	    cout << "2) Esyalari Goruntule\n";
	    cout << "3) Esya Bilgileri Sorgulama\n";
	    cout << "4) Esya Bilgilerini Guncelle\n";
	    cout << "5) Esya Sil\n";	  
	}
		
};



int main(){	
	
   	
	while(true){
	demirbasEkleme dbasEkleme;
	char islem;
	cout<<"Islem Seciniz: ";
	cin>>islem;
	cin.ignore();
	switch(islem){
		case '1':
			dbasEkleme.ekle();
			system("cls");	
			break;
		case '2':
			dbasEkleme.listele();
			break;
		case '3':
			dbasEkleme.ara();
			break;
		case '4':
			dbasEkleme.guncelle();
			system("cls");	
			break;
		case '5':
			dbasEkleme.sil();
			system("cls");	
			break;
	
	}
		
	}
	
	}

				
//aþýrý yüklenen fonksiyon
void cikti(demirbasBilgi db){
	cout<<"Demirbas Barkod No: "<<db.getBarkod()<<endl;
	cout<<"Esya Adi: "<<db.getEsyaAd()<<endl;
	cout<<"Esya Alinis Yili: "<<db.getAlinisYili()<<endl;
	cout<<"Esya Adedi: "<<db.getAdet()<<endl;
}


