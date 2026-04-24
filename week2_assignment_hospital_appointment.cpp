#include <iostream> //Oğuzhan Göynük 1306240038 2.ödev veri yapıları
#include <string>//gerekli kütüphaneleri tanımlayıp istenen struct yapısını tanımladık ve node başlangıcını attık
using namespace std;

struct Appointment {
	string patientName;
	double time;
	int duration;
	Appointment* next;
};

void printAll(Appointment* head) { //tüm randevuların yazdırılmasını sağlayacak fonksiyon
	if (head == nullptr) {
		cout << "Sstemde Randevu Yok." << endl;
		return;
	}

	cout << endl << "Tüm Randevular:" << endl;
	Appointment* current = head;
	while (current != nullptr) {
		int saat = (int)current->time;
		int dakika = (int)((current->time - saat) * 100);
		cout << "İsim: " << current->patientName << endl;
		cout << "Saat: " << saat << ":" << dakika << endl;
		cout << "Süre: " << current->duration << endl;
		current = current->next;
	}
}


void printFromTime(Appointment* head, double time) { //belli bir saatten sonraki randevuları listeleyen fonksiyon
	int saat = (int)time;
	int dakika = (int)((time - saat) * 100);
	Appointment* current = head;
	while (current != nullptr) {
		if (current->time > time) {
			int s = (int)current->time;
			int d = (int)((current->time - s) * 100);

			cout << "İsim: " << current->patientName<< endl;
			cout << "Saat: " << s << d << ":" << endl;
			cout << "Sure: " << current->duration << " dk"<<endl;
		}
		current = current->next;
	}
}

double hesaplaBitisSaati(double baslangic, int sure) { //randevunun bitiş saatini hesaplayan fonksiyon
	int saat = (int)baslangic;
	int dakika = (int)((baslangic - saat) * 100);

	dakika += sure;
	saat += dakika / 60;
	dakika = dakika % 60;

	return saat + (dakika / 100.0);
}

bool cakismaVarMi(Appointment* head, double yeniSaat, int yeniSure) { //yeni randevu ekleneceği zaman o saatte başka randevu var mı diye kontrol eden fonksiyon
	double yeniBitis = hesaplaBitisSaati(yeniSaat, yeniSure);

	Appointment* current = head;
	while (current != nullptr) {
		double mevcutBitis = hesaplaBitisSaati(current->time, current->duration);

		if ((yeniSaat >= current->time && yeniSaat < mevcutBitis) ||
			(yeniBitis > current->time && yeniBitis <= mevcutBitis) ||
			(yeniSaat <= current->time && yeniBitis >= mevcutBitis)) {
			return true;
		}
		current = current->next;
	}
	return false;
}

void insertAppointment(Appointment*& head, string name, double time, int duration) { // randevu girişi yapılmasını sağlayan fonksiyon
	if (time < 9.0 || time >= 17.0) {
		cout << "Randevu saati 09:00 - 17:00 arasinda olmali!"<<endl; //giriş yapılırken o saat aralığında başka randevu var mı, ve randevu saatleri 9-17 arası mı diye kontrol ediliyor.
		return;
	}

	double bitis = hesaplaBitisSaati(time, duration);
	if (bitis > 17.0) {
		cout << "Randevu 17:00'yi asiyor!"<<endl;
		return;
	}

	if (cakismaVarMi(head, time, duration)) {
		cout << "Bu saat araliginda randevu var!;" << endl;
		return;
	}

	Appointment* yeni = new Appointment();
	yeni->patientName = name;
	yeni->time = time;
	yeni->duration = duration;
	yeni->next = nullptr;

	if (head == nullptr || head->time > time) {
		yeni->next = head;
		head = yeni;
		cout << "Randevu eklendi."<<endl;
		return;
	}

	Appointment* current = head;
	while (current->next != nullptr && current->next->time < time) {
		current = current->next;
	}

	yeni->next = current->next;
	current->next = yeni;
	cout << "Randevu eklendi."<<endl;
}


void deleteAppointment(Appointment*& head, double time) { //randevu silmeyi sağlayan fonksiyon
	if (head == nullptr) {
		cout << "Sistemde randevu yok."<<endl;
		return;
	}

	if (head->time == time) {
		Appointment* temp = head;
		head = head->next;
		delete temp;
		cout << "Randevu silindi."<<endl;
		return;
	}

	Appointment* current = head;
	while (current->next != nullptr) {
		if (current->next->time == time) {
			Appointment* temp = current->next;
			current->next = current->next->next;
			delete temp;
			cout << "Randevu silindi."<<endl;
			return;
		}
		current = current->next;
	}

	cout << "Bu saatte randevu bulunamadi."<<endl;
}



int totalBusyMinutes(Appointment* head) { //total meşgul süreyi yani total randevu süresini hesaplayan fonksiyon
	int toplam = 0;
	Appointment* current = head;

	while (current != nullptr) {
		toplam += current->duration;
		current = current->next;
	}

	return toplam;
}

double suggestNextAvailable(Appointment* head, double startTime) { //bir sonraki en yakın boş zamanı söyleyen fonksiyon
	if (startTime < 9.0) startTime = 9.0;
	if (startTime >= 17.0) {
		cout << "Mesai saatleri disinda." << endl;
		return -1;
	}

	double onerilenSaat = startTime;
	Appointment* current = head;

	while (current != nullptr) {
		double mevcutBitis = hesaplaBitisSaati(current->time, current->duration);

		if (onerilenSaat >= current->time && onerilenSaat < mevcutBitis) {
			onerilenSaat = mevcutBitis;
		}

		current = current->next;
	}

	if (onerilenSaat >= 17.0) {
		cout << "Bugun icin uygun zaman yok." << endl;
		return -1;
	}

	return onerilenSaat;
}

int main() {
	Appointment* head = nullptr; //main fonksiyonumuzda kullanıcı arayüzü oluşturuldu ve tüm işlevler listelendi bunlara uygun fonksiyonlar çağırıldı.
	int secim;

	do {
		cout << endl << "RANDEVU PLANLAMA" << endl;
		cout << "1. Tum randevulari listele" << endl;
		cout << "2. Belirli bir saatten sonraki randevulari goster" << endl;
		cout << "3. Yeni randevu ekle" << endl;
		cout << "4. Randevu sil" << endl;
		cout << "5. Toplam dolu sureyi hesapla" << endl;
		cout << "6. Ilk uygun zamani oner" << endl;
		cout << "0. Cikis" << endl;
		cout << "Seciminiz: ";
		cin >> secim;

		if (secim == 1) {
			printAll(head);
		}
		else if (secim == 2) {
			double saat;
			cout << "Saat giriniz : ";
			cin >> saat;
			printFromTime(head, saat);
		}
		else if (secim == 3) {
			string isim;
			double saat;
			int sure;

			cout << "Hasta adi: ";
			cin.ignore();
			getline(cin, isim);
			cout << "Randevu saati : ";
			cin >> saat;
			cout << "Sure (dakika): ";
			cin >> sure;

			insertAppointment(head, isim, saat, sure);
		}
		else if (secim == 4) {
			double saat;
			cout << "Silinecek randevu saati: ";
			cin >> saat;
			deleteAppointment(head, saat);
		}
		else if (secim == 5) {
			int toplam = totalBusyMinutes(head);
			cout << "Toplam dolu sure: " << toplam << " dakika" << endl;
			cout << "(" << toplam / 60 << " saat " << toplam % 60 << " dakika)" << endl;
		}
		else if (secim == 6) {
			double baslangic;
			cout << "Baslangic saati : ";
			cin >> baslangic;

			double onerilen = suggestNextAvailable(head, baslangic);
			if (onerilen != -1) {
				int s = (int)onerilen;
				int d = (int)((onerilen - s) * 100);
				cout << "Onerilen saat: " << s << ":";
				if (d < 10) cout << "0";
				cout << d << endl;
			}
		}
		else if (secim == 0) {
			cout << "Cikis yapiliyor..." << endl;
		}
		else {
			cout << "Gecersiz secim!" << endl;
		}

	} while (secim != 0);

	while (head != nullptr) { //yuakrdaki while döngüsünden 0'a basılarak çıkılınca tüm veriyi silmeye yarıyor
		Appointment* temp = head;
		head = head->next;
		delete temp;
	}

	return 0;
}
	
