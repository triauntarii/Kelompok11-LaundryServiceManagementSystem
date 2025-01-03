#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_PELANGGAN = 100;
const int MAX_KOMPLAIN = 50;

// Data pelanggan
string namaPelanggan[MAX_PELANGGAN];
string noTelpPelanggan[MAX_PELANGGAN];
string jenisLayanan[MAX_PELANGGAN];
float jumlahKg[MAX_PELANGGAN];
bool statusPembayaran[MAX_PELANGGAN];
int biaya[MAX_PELANGGAN];
int estimasiWaktu[MAX_PELANGGAN];
string catatanKhusus[MAX_PELANGGAN];
string statusPesanan[MAX_PELANGGAN];
string uuidPelanggan[MAX_PELANGGAN];
int jumlahPelanggan = 0;

// Data komplain
string namaKomplain[MAX_KOMPLAIN];
string noTelpKomplain[MAX_KOMPLAIN];
string deskripsiKomplain[MAX_KOMPLAIN];
int jumlahKomplain = 0;

string buatUUID(const string& nama, const string& noTelp)
{
    string inisial = nama.substr(0, 3);
    string tigaDigitTerakhir = noTelp.substr(noTelp.length() - 3);
    return inisial + tigaDigitTerakhir;
}

void tampilkanDaftarPesanan()
{
    cout << "\nDaftar Pesanan:" << endl;
    cout << setw(5) << "No." << setw(15) << "UUID" << setw(20) << "Nama" 
         << setw(15) << "Status" << setw(15) << "Pembayaran" << endl;
    cout << string(70, '-') << endl;
    
    for (int i = 0; i < jumlahPelanggan; i++)
    {
        cout << setw(5) << (i + 1) 
             << setw(15) << uuidPelanggan[i]
             << setw(20) << namaPelanggan[i]
             << setw(15) << statusPesanan[i]
             << setw(15) << (statusPembayaran[i] ? "Lunas" : "Belum") << endl;
    }
    cout << endl;
}

void terimaPesanan()
{
    if (jumlahPelanggan >= MAX_PELANGGAN)
    {
        cout << "Tidak dapat menerima lebih banyak pesanan!" << endl;
        return;
    }

    cout << "Masukkan Nama Pelanggan: ";
    getline(cin, namaPelanggan[jumlahPelanggan]);
    cout << "Masukkan Nomor Telepon Pelanggan: ";
    getline(cin, noTelpPelanggan[jumlahPelanggan]);
    
    // Pilihan jenis layanan dengan nomor
    cout << "\nPilih Jenis Layanan:" << endl;
    cout << "1. Regular (Rp 6.000/kg - 3 hari)" << endl;
    cout << "2. Express (Rp 10.000/kg - 1 hari)" << endl;
    cout << "Pilihan (1/2): ";
    
    int pilihanLayanan;
    cin >> pilihanLayanan;
    cin.ignore();
    
    if (pilihanLayanan == 1)
    {
        jenisLayanan[jumlahPelanggan] = "regular";
        biaya[jumlahPelanggan] = jumlahKg[jumlahPelanggan] * 6000;
        estimasiWaktu[jumlahPelanggan] = 3;
    } else if (pilihanLayanan == 2)
    {
        jenisLayanan[jumlahPelanggan] = "express";
        biaya[jumlahPelanggan] = jumlahKg[jumlahPelanggan] * 10000;
        estimasiWaktu[jumlahPelanggan] = 1;
    } else
    {
        cout << "Pilihan tidak valid! Menggunakan layanan regular sebagai default." << endl;
        jenisLayanan[jumlahPelanggan] = "regular";
        biaya[jumlahPelanggan] = jumlahKg[jumlahPelanggan] * 6000;
        estimasiWaktu[jumlahPelanggan] = 3;
    }

    cout << "Masukkan Jumlah Kilogram: ";
    cin >> jumlahKg[jumlahPelanggan];
    cin.ignore();
    
    cout << "Masukkan Catatan Khusus: ";
    getline(cin, catatanKhusus[jumlahPelanggan]);

    // Buat UUID dan set status awal
    uuidPelanggan[jumlahPelanggan] = buatUUID(namaPelanggan[jumlahPelanggan], noTelpPelanggan[jumlahPelanggan]);
    statusPesanan[jumlahPelanggan] = "terima";
    statusPembayaran[jumlahPelanggan] = false;

    // Tampilkan ringkasan pesanan
    cout << "\nRingkasan Pesanan:" << endl;
    cout << "UUID: " << uuidPelanggan[jumlahPelanggan] << endl;
    cout << "Nama: " << namaPelanggan[jumlahPelanggan] << endl;
    cout << "Layanan: " << jenisLayanan[jumlahPelanggan] << endl;
    cout << "Biaya: Rp " << biaya[jumlahPelanggan] << endl;
    cout << "Estimasi Selesai: " << estimasiWaktu[jumlahPelanggan] << " hari" << endl;

    jumlahPelanggan++;
}

void lakukanPembayaran()
{
    if (jumlahPelanggan == 0)
    {
        cout << "Belum ada pesanan yang tercatat." << endl;
        return;
    }

    tampilkanDaftarPesanan();
    
    cout << "Pilih nomor pesanan (1-" << jumlahPelanggan << "): ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    
    if (pilihan < 1 || pilihan > jumlahPelanggan)
    {
        cout << "Nomor pesanan tidak valid!" << endl;
        return;
    }
    
    int index = pilihan - 1;
    if (statusPembayaran[index])
    {
        cout << "Pesanan ini sudah dibayar!" << endl;
        return;
    }
    
    statusPembayaran[index] = true;
    cout << "Pembayaran untuk " << namaPelanggan[index] << " telah diterima." << endl;
    cout << "Total biaya: Rp " << biaya[index] << endl;
}

void updateStatusPesanan()
{
    if (jumlahPelanggan == 0)
    {
        cout << "Belum ada pesanan yang tercatat." << endl;
        return;
    }

    tampilkanDaftarPesanan();
    
    cout << "Pilih nomor pesanan (1-" << jumlahPelanggan << "): ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    
    if (pilihan < 1 || pilihan > jumlahPelanggan)
    {
        cout << "Nomor pesanan tidak valid!" << endl;
        return;
    }
    
    int index = pilihan - 1;
    cout << "Status saat ini: " << statusPesanan[index] << endl;
    cout << "\nPilih status baru:" << endl;
    cout << "1. Terima" << endl;
    cout << "2. Proses" << endl;
    cout << "3. Selesai" << endl;
    cout << "Pilihan (1-3): ";
    
    int statusPilihan;
    cin >> statusPilihan;
    cin.ignore();
    
    string statusBaru;
    switch (statusPilihan)
    {
        case 1: statusBaru = "terima"; break;
        case 2: statusBaru = "proses"; break;
        case 3: statusBaru = "selesai"; break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            return;
    }
    
    statusPesanan[index] = statusBaru;
    cout << "Status pesanan " << namaPelanggan[index] << " telah diperbarui ke " << statusBaru << endl;
}

void tampilkanPesananAktif()
{
    cout << "\nDaftar Pesanan Aktif:" << endl;
    cout << setw(5) << "No." << setw(15) << "UUID" << setw(20) << "Nama" 
         << setw(15) << "Status" << setw(15) << "Pembayaran" << endl;
    cout << string(70, '-') << endl;
    
    int count = 0;
    for (int i = 0; i < jumlahPelanggan; i++)
    {
        if (statusPesanan[i] != "selesai")
        {
            count++;
            cout << setw(5) << count 
                 << setw(15) << uuidPelanggan[i]
                 << setw(20) << namaPelanggan[i]
                 << setw(15) << statusPesanan[i]
                 << setw(15) << (statusPembayaran[i] ? "Lunas" : "Belum") << endl;
        }
    }
    
    if (count == 0)
    {
        cout << "Tidak ada pesanan aktif saat ini." << endl;
    }
    cout << endl;
}

void terimaKomplain()
{
    if (jumlahKomplain >= MAX_KOMPLAIN)
    {
        cout << "Tidak dapat menerima lebih banyak komplain!" << endl;
        return;
    }

    cout << "Masukkan Nama Pelanggan: ";
    getline(cin, namaKomplain[jumlahKomplain]);
    cout << "Masukkan Nomor Telepon Pelanggan: ";
    getline(cin, noTelpKomplain[jumlahKomplain]);
    cout << "Masukkan Deskripsi Komplain: ";
    getline(cin, deskripsiKomplain[jumlahKomplain]);

    cout << "Komplain berhasil diterima!" << endl;
    jumlahKomplain++;
}

void tampilkanKomplain()
{
    if (jumlahKomplain == 0)
    {
        cout << "Belum ada komplain yang tercatat." << endl;
        return;
    }

    cout << "\nDaftar Komplain Pelanggan:" << endl;
    cout << setw(5) << "No." << setw(20) << "Nama" 
         << setw(15) << "No. Telp" << setw(30) << "Deskripsi" << endl;
    cout << string(70, '-') << endl;
    
    for (int i = 0; i < jumlahKomplain; i++)
    {
        cout << setw(5) << (i + 1)
             << setw(20) << namaKomplain[i]
             << setw(15) << noTelpKomplain[i]
             << setw(30) << deskripsiKomplain[i] << endl;
    }
    cout << endl;
}

int main()
{
    while (true)
    {
        cout << string(50, '=') << endl;
        cout << "   Laundry Service Management System (LSMS)" << endl;
        cout << string(50, '=') << endl;
        cout << "Menu:" << endl;
        cout << "1. Terima Pesanan" << endl;
        cout << "2. Lakukan Pembayaran" << endl;
        cout << "3. Update Status Pesanan" << endl;
        cout << "4. Tampilkan Daftar Pesanan Aktif" << endl;
        cout << "5. Terima Komplain" << endl;
        cout << "6. Tampilkan Daftar Komplain" << endl;
        cout << "7. Keluar" << endl;
        cout << string(50, '-') << endl;
        cout << "Pilih opsi (1-7): ";

        int pilihan;
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
            case 1: terimaPesanan(); break;
            case 2: lakukanPembayaran(); break;
            case 3: updateStatusPesanan(); break;
            case 4: tampilkanPesananAktif(); break;
            case 5: terimaKomplain(); break;
            case 6: tampilkanKomplain(); break;
            case 7:
                cout << "Terima kasih telah menggunakan LSMS!" << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}
