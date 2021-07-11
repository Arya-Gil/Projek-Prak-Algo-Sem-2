
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>

using namespace std; 

class Penduduk{
public:
	string noKTP;
	string nama;
	string goldarah;
	string status;
};

Penduduk pendudukPublic[100];
int jumlahDataPublic=0;

void printMenu();
void backToMenu();

void saveData(string namaFile, Penduduk dataPenduduk[], int banyakData);
void loadData(string namaFile);

void inputData();
void tampilkanData();
void searchData();
void sortingData();
void transaksi();

void quickSort(Penduduk arr[], int low, int high);
int partition(Penduduk arr[], int low, int high);

int main(){
	int pilihan;

	do{
		printMenu();
		cin>>pilihan;fflush(stdin);
		switch(pilihan){
			case 1:inputData(); break;
			case 2:tampilkanData(); break;
			case 3:searchData(); break;
			case 4:sortingData(); break;
			case 5:transaksi(); break;
		}
	
	}while(pilihan != 6);

	return 0;
}

void printMenu(){
	system("cls");
	cout<<"========================="<<endl;
	cout<<" TUGAS PROJECT ALGO 2021	"<<endl;
	cout<<"========================="<<endl;
	cout<<"        1. INPUT DATA	"<<endl;
	cout<<"        2. TAMPILKAN DATA"<<endl;
	cout<<"        3. SEARCHING DATA"<<endl;
	cout<<"        4. SORTING DATA	"<<endl;
	cout<<"        5. TRANSAKSI		"<<endl;
	cout<<"        6. KELUAR		"<<endl;
	cout<<"========================="<<endl;
	cout<<"========================="<<endl;
	cout<<"Masukan Pilihan         = ";
}

void backToMenu(){
	string pilihan;
	cout<<"\nKembali Ke Menu Utama?\n"<<endl;
	cout<<"Y = Kembali"<<endl;
	cout<<"N = Keluar	"<<endl;
	cout<<"Masukan Pilihan         = ";
	getline(cin,pilihan);

	if(pilihan.compare("y") != 0 && pilihan.compare("Y") != 0){
		exit(0);
	}
}

void saveData(string namaFile, Penduduk dataPenduduk[], int banyakData){
	ofstream out(namaFile);
	for(int i=0; i < banyakData; i++){
		out <<dataPenduduk[i].noKTP+"#"+dataPenduduk[i].nama+"#"+dataPenduduk[i].status+"#"+dataPenduduk[i].goldarah+"\n";
	}
	out.close();
}

void loadData(string namaFile){
	string line;
	ifstream open(namaFile);
	jumlahDataPublic = 0;
	if(open.is_open()){
		
		while (getline(open,line)){
			stringstream check1(line);
			string intermediate;
			string dataGet[4];
			int i = 0;
			while(getline(check1, intermediate, '#')){
				dataGet[i] = intermediate;
				i++;
			}
			pendudukPublic[jumlahDataPublic].noKTP = dataGet[0];
			pendudukPublic[jumlahDataPublic].nama = dataGet[1];
			pendudukPublic[jumlahDataPublic].status = dataGet[2];
			pendudukPublic[jumlahDataPublic].goldarah = dataGet[3];
			jumlahDataPublic++;
		}
	}
	open.close();
}

void inputData(){
	string namaFile;
	int banyakData;
	Penduduk dataPenduduk[1000];

	system("cls");
	cout<<"========================="<<endl;
	cout<<" INPUT DATA KEPENDUDUKAN	"<<endl;
	cout<<"========================="<<endl;
	cout<<"Masukan nama file       = ";
	getline(cin,namaFile);
	cout<<"\nBanyaknya Data = ";
	cin>>banyakData;fflush(stdin);
	

	for(int i=0; i < banyakData; i++){
		cout<<"\tNomer KTP       = ";
		getline(cin,dataPenduduk[i].noKTP);
		cout<<"\tNama            = ";
		getline(cin,dataPenduduk[i].nama);
		cout<<"\tStatus          = ";
		getline(cin,dataPenduduk[i].status);
		cout<<"\tGolongan darah  = ";
		getline(cin,dataPenduduk[i].goldarah);
		cout<<endl;
	}

	saveData(namaFile, dataPenduduk, banyakData);

	backToMenu();
}

void tampilkanData(){
	string namaFile;
	string line;

	system("cls");
	cout<<"========================="<<endl;
	cout<<" INPUT DATA KEPENDUDUKAN	"<<endl;
	cout<<"========================="<<endl;
	cout<<"Masukan nama file       = ";
	getline(cin,namaFile);

	ifstream open(namaFile);

	if(open.is_open()){
		loadData(namaFile);
		cout<<"\n=============================================================================="<<endl;
		cout<<" Nomor KTP      Nama                            Gol. Darah  Status			 "<<endl;
		cout<<"=============================================================================="<<endl;
		for(int i = 0; i< jumlahDataPublic; i++){
			pendudukPublic[i].noKTP.resize(15,' ');
			pendudukPublic[i].nama.resize(32,' ');
			pendudukPublic[i].status.resize(12,' ');
			cout<<" "+pendudukPublic[i].noKTP+pendudukPublic[i].nama+pendudukPublic[i].status+pendudukPublic[i].goldarah+"\n";
		}
		cout<<"=============================================================================="<<endl;
		open.close();
	
	}else{
		cout<<"  File tidak ada atau gagal dibuka..."<<endl;
	}
	open.close();
	backToMenu();
}

void searchData(){
	string namaFile;
	string keyword;
	string choose;
	int pilihan;
	bool found = false;

	cout<<"\nMasukan nama file       = ";
	getline(cin,namaFile);

	ifstream open(namaFile);
	if(open.is_open()){
		loadData(namaFile);
		system("cls");
		cout<<"========================="<<endl;
		cout<<" CARI DATA KEPENDUDUKAN	"<<endl;
		cout<<"========================="<<endl;
		cout<<"        1. Sequential	"<<endl;
		cout<<"        2. Binary		"<<endl;
		cout<<"========================="<<endl;
		cout<<"Masukan Pilihan         =";
		cin>>pilihan;fflush(stdin);

		auto print_menu = [](string menu){
			system("cls");
			cout<<"============================="<<endl;
			cout<<" PENCARIAN DENGAN "<<menu<<endl;
			cout<<"============================="<<endl;
			cout<<"Masukan NIK = ";
		};

		switch(pilihan){
			case 1:
				do{
					found = false;
					print_menu("SEQUENSIAL");
					getline(cin,keyword);
					for(int i = 0; i < jumlahDataPublic; i++){
						if(pendudukPublic[i].noKTP == keyword){
							found = true;
							cout<<"\n        Nomor KTP       = "<<pendudukPublic[i].noKTP<<endl;
							cout<<"        Nama            = "<<pendudukPublic[i].nama<<endl;
							cout<<"        Status          = "<<pendudukPublic[i].status<<endl;
							cout<<"        Golongan Darah  = "<<pendudukPublic[i].goldarah<<endl;
						}
					}
					if(found==false)cout<<"Data Tidak Ditemukan"<<endl;

					cout<<"\nKembali ke Sequential Search?"<<endl;
					cout<<"Y = Kembali						 "<<endl;
					cout<<"N = Keluar						 "<<endl;
					cout<<"Masukan pilihan = ";
					getline(cin,choose);
				}while(choose.compare("y") == 0 || choose.compare("Y") == 0);

				break;
			case 2:
				do{
					found = false;
					print_menu("BINARY");
					getline(cin,keyword);

					int lower = 0;
					int upper = jumlahDataPublic - 1;
					while (lower <= upper) {
						int mid = lower + (upper - lower) / 2;
						int res = -1;
						if (keyword == (pendudukPublic[mid].noKTP))
							res = 0;
						if (res == 0){
							cout<<"\n        Nomor KTP       = "<<pendudukPublic[res].noKTP<<endl;
							cout<<"        Nama            = "<<pendudukPublic[res].nama<<endl;
							cout<<"        Status          = "<<pendudukPublic[res].status<<endl;
							cout<<"        Golongan Darah  = "<<pendudukPublic[res].goldarah<<endl;
							found = true;
						}	
						if (keyword > (pendudukPublic[mid].noKTP))
							lower = mid + 1;
						else
							upper = mid - 1;
					}
					if(found==false)cout<<"Data Tidak Ditemukan"<<endl;

					cout<<"\nKembali ke Binary Search?"<<endl;
					cout<<"Y = Kembali						 "<<endl;
					cout<<"N = Keluar						 "<<endl;
					cout<<"Masukan pilihan = ";
					getline(cin,choose);
				}while(choose.compare("y") == 0 || choose.compare("Y") == 0);
				break;
		}

	}else{
		cout<<"  File tidak ada atau gagal dibuka..."<<endl;
	}
	open.close();

	backToMenu();
}

int partition (Penduduk arr[], int low, int high){
    Penduduk pivot = arr[high];
	Penduduk temp;
    int i = (low - 1);
 
    for (int j = low; j <= high- 1; j++){
		if (arr[j].nama <= pivot.nama)
        {
            i++;
			temp = pendudukPublic[i];
			pendudukPublic[i] = pendudukPublic[j];
			pendudukPublic[j] = temp;
        }
    }
	temp = pendudukPublic[i+1];
	pendudukPublic[i+1] = pendudukPublic[high];
	pendudukPublic[high] = temp;
    return (i + 1);
}

void quickSort(Penduduk arr[], int low, int high){
    if (low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void sortingData(){
	string namaFile;
	int pilihan;
	string choose;
	Penduduk temp;

	cout<<"\nMasukan nama file       = ";
	getline(cin,namaFile);

	ifstream open(namaFile);
	auto print_header = [](string sort){
		system("cls");
		cout<<"========================="<<endl;
		cout<<" PENGURUTAN DATA "<<sort<<endl;
		cout<<"========================="<<endl;
		cout<<"Pengurutan berdasarkan Nama secara Ascending [A-Z]"<<endl;
	};
	auto print_menu = [](){
		cout<<"\n=============================================================================="<<endl;
		cout<<" Nomor KTP      Nama                            Gol. Darah  Status			 "<<endl;
		cout<<"=============================================================================="<<endl;
		for(int i = 0; i< jumlahDataPublic; i++){
			pendudukPublic[i].noKTP.resize(15,' ');
			pendudukPublic[i].nama.resize(32,' ');
			pendudukPublic[i].status.resize(12,' ');
			cout<<" "+pendudukPublic[i].noKTP+pendudukPublic[i].nama+pendudukPublic[i].status+pendudukPublic[i].goldarah+"\n";
		}
		cout<<"=============================================================================="<<endl;
		cout<<"\nKembali ke menu Sorting?"<<endl;
		cout<<"Y = Kembali						 "<<endl;
		cout<<"N = Keluar						 "<<endl;
		cout<<"Masukan pilihan = ";
	};

	if(open.is_open()){
		do{
			loadData(namaFile);
			system("cls");
			cout<<"========================="<<endl;
			cout<<" PENGURUTAN DATA PENDUDUK"<<endl;
			cout<<"========================="<<endl;
			cout<<"1. Bubble Sort			"<<endl;
			cout<<"2. Selection Sort		"<<endl;
			cout<<"3. Insertion Sort		"<<endl;
			cout<<"4. Shell Sort			"<<endl;
			cout<<"5. Quick Sort			"<<endl;
			cout<<"Masukan Pilihan : ";
			cin>>pilihan;fflush(stdin);
			switch(pilihan){
				case 1:
					print_header("BUBBLE");
					for (int j=0; j<jumlahDataPublic; j++){
						for (int i=j+1; i<jumlahDataPublic; i++){
							if (pendudukPublic[j].nama > pendudukPublic[i].nama){
								temp = pendudukPublic[j];
								pendudukPublic[j] = pendudukPublic[i];
								pendudukPublic[i] = temp;
							}
						}
					}
					saveData(namaFile, pendudukPublic, jumlahDataPublic);
					print_menu();
					getline(cin,choose);
					break;
				case 2:
					print_header("SELECTION");
					int min_idx;
					for (int j=0; j<jumlahDataPublic; j++){
						min_idx = j;
						for (int i=j+1; i<jumlahDataPublic; i++){
							if (pendudukPublic[j].nama > pendudukPublic[i].nama)
								min_idx = i;
						}		
						temp = pendudukPublic[min_idx];
						pendudukPublic[min_idx] = pendudukPublic[j];
						pendudukPublic[j] = temp;
					}
					saveData(namaFile, pendudukPublic, jumlahDataPublic);
					print_menu();
					getline(cin,choose);
					break;
				case 3:
					print_header("INSERTION");
					int i, j;
					for (i = 1; i < jumlahDataPublic; i++){
						temp = pendudukPublic[i];
						j = i - 1;

						while (j >= 0 && pendudukPublic[j].nama > temp.nama){
							pendudukPublic[j + 1] = pendudukPublic[j];
							j = j - 1;
						}
						pendudukPublic[j + 1] = temp;
					}
					saveData(namaFile, pendudukPublic, jumlahDataPublic);
					print_menu();
					getline(cin,choose);
					break;
				case 4:
					print_header("SHELL");
					for (int gap = jumlahDataPublic/2; gap > 0; gap /= 2){
						for (int i = gap; i < jumlahDataPublic; i += 1)
						{
							temp = pendudukPublic[i];
							int j;           
							for (j = i; j >= gap && pendudukPublic[j - gap].nama > temp.nama; j -= gap)
								pendudukPublic[j] = pendudukPublic[j - gap];

							pendudukPublic[j] = temp;
						}
					}
					saveData(namaFile, pendudukPublic, jumlahDataPublic);
					print_menu();
					getline(cin,choose);
					break;
				case 5:
					print_header("QUICK");
					quickSort(pendudukPublic,0,jumlahDataPublic-1);
					saveData(namaFile, pendudukPublic, jumlahDataPublic);
					print_menu();
					getline(cin,choose);
					break;
			}
		}while(choose.compare("y") == 0 || choose.compare("Y") == 0);
	}
	open.close();
	backToMenu();
}

void transaksi(){
	Penduduk mergedData[100];
	Penduduk temp;
	string file1,file2,fileBaru;
	int pilihan, mergedTotal = 0;
	string choose;
	auto print_data = [](){
		cout<<"\n=============================================================================="<<endl;
		cout<<" Nomor KTP      Nama                            Gol. Darah  Status			 "<<endl;
		cout<<"=============================================================================="<<endl;
		for(int i = 0; i< jumlahDataPublic; i++){
			pendudukPublic[i].noKTP.resize(15,' ');
			pendudukPublic[i].nama.resize(32,' ');
			pendudukPublic[i].status.resize(12,' ');
			cout<<" "+pendudukPublic[i].noKTP+pendudukPublic[i].nama+pendudukPublic[i].status+pendudukPublic[i].goldarah+"\n";
		}
		cout<<"=============================================================================="<<endl;
	};
	do{
		system("cls");
		cout<<"========================="<<endl;
		cout<<" TRANSAKSI				"<<endl;
		cout<<"========================="<<endl;
		cout<<"1. Merging Sambung		"<<endl;
		cout<<"2. Merging Urut			"<<endl;
		cout<<"Masukan Pilihan : ";
		cin>>pilihan;fflush(stdin);
		switch(pilihan){
			case 1:
				do{
					system("cls");
					cout<<"=================="<<endl;
					cout<<" MERGING SAMBUNG	 "<<endl;
					cout<<"=================="<<endl;
					cout<<"Nama File Pertama       = ";
					getline(cin,file1);
					loadData(file1);
					mergedTotal += jumlahDataPublic;
					for(int i = 0 ; i < jumlahDataPublic ; i++){
						mergedData[i] = pendudukPublic[i];
					}
					print_data();
					cout<<"Nama File Kedua       = ";
					getline(cin,file2);
					loadData(file2);
					for(int i = 0 ; i < jumlahDataPublic ; i++){
						mergedData[i+jumlahDataPublic] = pendudukPublic[i];
					}
					mergedTotal += jumlahDataPublic;
					print_data();
					cout<<"Masukan nama file hasil merging sambung = ";
					getline(cin,fileBaru);
					saveData(fileBaru,mergedData,mergedTotal);
					cout<<"\n\nMerging Sambung Berhasil,lihat file hasil kembali ke menu utama"<<endl;
					cout<<"\nUlangi?\n"<<endl; 
					cout<<"Y = Ulangi "<<endl;
					cout<<"N = Keluar "<<endl;
					cout<<"Masukan Pilihan =";
					getline(cin,choose);
				}while(choose.compare("y") == 0 || choose.compare("Y") == 0);
				break;
			case 2:
				do{
					system("cls");
					cout<<"=================="<<endl;
					cout<<" MERGING URUT	 "<<endl;
					cout<<"=================="<<endl;
					cout<<"Nama File Pertama       = ";
					getline(cin,file1);
					loadData(file1);
					mergedTotal += jumlahDataPublic;
					for(int i = 0 ; i < jumlahDataPublic ; i++){
						mergedData[i] = pendudukPublic[i];
					}
					print_data();
					cout<<"Nama File Kedua       = ";
					getline(cin,file2);
					loadData(file2);
					for(int i = 0 ; i < jumlahDataPublic ; i++){
						mergedData[i+jumlahDataPublic] = pendudukPublic[i];
					}
					mergedTotal += jumlahDataPublic;
					print_data();
					cout<<"Masukan nama file hasil merging urut = ";
					getline(cin,fileBaru);
					for (int j=0; j<mergedTotal; j++){
						for (int i=j+1; i<mergedTotal; i++){
							if (mergedData[j].nama > mergedData[i].nama){
								temp = mergedData[j];
								mergedData[j] = mergedData[i];
								mergedData[i] = temp;
							}
						}
					}
					saveData(fileBaru,mergedData,mergedTotal);
					cout<<"\n\nMerging Urut Berhasil,lihat file hasil kembali ke menu utama"<<endl;
					cout<<"\nUlangi?\n"<<endl; 
					cout<<"Y = Ulangi "<<endl;
					cout<<"N = Keluar "<<endl;
					cout<<"Masukan Pilihan =";
					getline(cin,choose);
				}while(choose.compare("y") == 0 || choose.compare("Y") == 0);
				break;
		}
	}while(choose.compare("y") == 0 || choose.compare("Y") == 0);
	backToMenu();
}
