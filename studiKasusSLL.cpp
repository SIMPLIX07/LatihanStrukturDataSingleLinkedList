#include <iostream>
using namespace std;

#define nil NULL

struct pekerja {
    string nama;
    string id;
    int gaji;
};

typedef pekerja infotype;
typedef struct elmlist *address;

struct elmlist {
    infotype info;
    address next;
};

struct list {
    address first;
};


void createList(list &L);
address createElmtlist(infotype data);
void insertFirst(list &L, address &P);
void insertAfter(list &L, address &P, string id);
void insertLast(list &L, address &P);
void deleteFirst(list &L);
void deleteLast(list &L);
void deleteById(list &L, string id);
void searchByName(list &L, string nama);
void totalPengeluaranGaji(list &L);
void menampilkanGajiTertinggiDanTerendah(list &L);
void hapusPekerjaDenganGajiTertentu(list &L, int gaji);
void printList(list L);
void printMenu();

void createList(list &L) {
    L.first = nil;
}

address createElmtlist(infotype data) {
    address P = new elmlist;
    P->info = data;
    P->next = nil;
    return P;
}

void insertFirst(list &L, address &P) {
    P->next = L.first;
    L.first = P;
}

void insertAfter(list &L, address &P, string id) {
    address q = L.first;
    while (q != nil) {
        if (q->info.id == id) {
            P->next = q->next;
            q->next = P;
            return;
        }
        q = q->next;
    }
}

void insertLast(list &L, address &P) {
    if (L.first == nil) {
        L.first = P;
        return;
    }
    address q = L.first;
    while (q->next != nil) {
        q = q->next;
    }
    q->next = P;
}

void deleteFirst(list &L) {
    if (L.first != nil) {
        address P = L.first;
        L.first = P->next;
        delete P;
    } else {
        cout << "List Kosong" << endl;
    }
}

void deleteLast(list &L) {
    if (L.first == nil) {
        cout << "List Kosong" << endl;
        return;
    }

    if (L.first->next == nil) {
        delete L.first;
        L.first = nil;
        return;
    }

    address q = L.first;
    while (q->next->next != nil) {
        q = q->next;
    }
    address r = q->next;
    q->next = nil;
    delete r;
}

void deleteById(list &L, string id) {
    if (L.first == nil) return;
    if (L.first->info.id == id) {
        deleteFirst(L);
        return;
    }

    address q = L.first;
    while (q->next != nil && q->next->info.id != id) {
        q = q->next;
    }
    if (q->next != nil) {
        address r = q->next;
        q->next = r->next;
        delete r;
        cout <<  "Pekerja berhasil dihapus" << endl;
    }else{
        cout << "Pekerja dengan ID " << id << " tidak ditemukan" << endl;
    }
}

void searchByName(list &L, string nama) {
    address q = L.first;
    while (q != nil && q->info.nama != nama) {
        q = q->next;
    }
    if (q != nil) {
        cout << "Data ditemukan\nNama: " << q->info.nama
        << "\nID: " << q->info.id
        << "\nGaji: " << q->info.gaji << endl;
    } else {
        cout << "Data tidak ditemukan" << endl;
    }
}

void totalPengeluaranGaji(list &L) {
    int totalGaji = 0;
    address q = L.first;
    while (q != nil) {
        totalGaji += q->info.gaji;
        q = q->next;
    }
    cout << "Total pengeluaran perusahaan bulan ini adalah: " << totalGaji << endl;
}

void menampilkanGajiTertinggiDanTerendah(list &L) {
    if (L.first == nil) {
        cout << "List kosong" << endl;
        return;
    }

    string namaTertinggi = L.first->info.nama;
    string namaTerendah = L.first->info.nama;
    int tertinggi = L.first->info.gaji;
    int terendah = L.first->info.gaji;
    address q = L.first->next;

    while (q != nil) {
        if (q->info.gaji > tertinggi) {
            tertinggi = q->info.gaji;
            namaTertinggi = q->info.nama;
        }
        if (q->info.gaji < terendah) {
            terendah = q->info.gaji;
            namaTerendah = q->info.nama;
        }
        q = q->next;
    }

    cout << "Gaji tertinggi adalah: " << tertinggi << " (oleh: " << namaTertinggi << ")\n";
    cout << "Gaji terendah  adalah: " << terendah << " (oleh: " << namaTerendah << ")\n";
}

void hapusPekerjaDenganGajiTertentu(list &L, int batasGaji) {
    while (L.first != nil && L.first->info.gaji < batasGaji) {
        deleteFirst(L);
    }

    address q = L.first;
    while (q != nil && q->next != nil) {
        if (q->next->info.gaji < batasGaji) {
            address s = q->next;
            q->next = s->next;
            delete s;
        } else {
            q = q->next;
        }
    }
}

void printList(list L) {
    if (L.first == nil) {
        cout << "List kosong" << endl;
        return;
    }

    address q = L.first;
    while (q != nil) {
        cout << "ID: " << q->info.id
        << " Nama: " << q->info.nama
        << " Gaji: " << q->info.gaji << endl;
        q = q->next;
    }
}

void printMenu() {
    cout << "===== MENU PEKERJA KONTRAK =====" << endl
    << "1. Tambah pekerja (awal/akhir)" << endl
    << "2. Tampilkan seluruh pekerja" << endl
    << "3. Hapus pekerja berdasarkan ID" << endl
    << "4. Cari pekerja berdasarkan nama" << endl
    << "5. Total gaji perusahaan" << endl
    << "6. Sisipkan pekerja setelah ID tertentu" << endl
    << "7. Update gaji pekerja" << endl
    << "8. Tampilkan gaji tertinggi & terendah" << endl
    << "9. Hapus pekerja dengan gaji < batas" << endl
    << "0. Keluar" << endl;
}

int main() {
    int input;
    list L;
    createList(L);

    do {
        printMenu();
        cin >> input;

        switch(input) {
            case 1: {
                string nama, idPekerja;
                int gajiPekerja;
                int input1;

                cout << "Masukan nama pekerja baru: ";
                cin >> nama;
                cout << "Masukan ID Pekerja baru: ";
                cin >> idPekerja;
                cout << "Masukan gaji pekerja baru: ";
                cin >> gajiPekerja;

                infotype pekerjaBaru = {nama, idPekerja, gajiPekerja};
                address P = createElmtlist(pekerjaBaru);

                cout << "1. Tambahkan awal" << endl;
                cout << "2. Tambahkan akhir" << endl;
                cout << "Masukan Pilihan: ";
                cin >> input1;

                while(input1 != 1 && input1 != 2) {
                    cout << "Input tidak valid. Ulangi: ";
                    cin >> input1;
                }

                if(input1 == 1) {
                    insertFirst(L, P);
                } else {
                    insertLast(L, P);
                }

                cout << "Data berhasil dimasukkan." << endl;
                break;
            }

            case 2: {
                printList(L);
                break;
            }

            case 3: {
                string ID;
                cout << "Masukan ID pekerja yang ingin dihapus: ";
                cin >> ID;
                deleteById(L, ID);
                break;
            }

            case 4: {
                string cariNama;
                cout << "Masukan nama pekerja yang ingin dicari: ";
                cin >> cariNama;
                searchByName(L, cariNama);
                break;
            }

           //case selanjutnya ......

            case 0:
                cout << "Terima kasih, program selesai." << endl;
                break;

            default:
                cout << "Pilihan tidak valid!" << endl;
        }

    } while(input != 0);

    return 0;
}

