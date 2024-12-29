#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// untuk Menyimpan Informasi Pelanggan dan Pesanan
struct Pelanggan
{
    string nama;
    string noTelp;
    string jenisLayanan; // regular atau express
    float jumlahKg; // jumlah kilogram
    bool statusPembayaran; // true jika sudah bayar, false jika belum
    int biaya;
    int estimasiWaktu; // dalam hari
    string catatanKhusus; // catatan khusus pelanggan
    string statusPesanan; // status pesanan (terima/proses/selesai)
    string uuid; // UUID Pelanggan
};

// untuk Menyimpan Catatan Komplain Pelanggan
struct Komplain
{
    string namaPelanggan;
    string noTelp;
    string deskripsiKomplain;
};

// untuk Membuat UUID(kode unik pelanggan) dari 3 karakter awal nama dan 3 Digit Terakhir No. Telp pelanggan
string buatUUID(const string& nama, const string& noTelp)
{
    string inisial = nama.substr(0, 3);
    string tigaDigitTerakhir = noTelp.substr(noTelp.length() - 3);
    return inisial + tigaDigitTerakhir;
}

// untuk Menangani Proses Penerimaan Pesanan
void terimaPesanan(vector<Pelanggan>& daftarPesanan)
{
    Pelanggan pelangganBaru;
    cout << "Masukkan Nama Pelanggan: ";
    getline(cin, pelangganBaru.nama);
    cout << "Masukkan Nomor Telepon Pelanggan: ";
    getline(cin, pelangganBaru.noTelp);
    cout << "Masukkan Jenis Layanan (regular/express): ";
    getline(cin, pelangganBaru.jenisLayanan);
    cout << "Masukkan Jumlah Kilogram: ";
    cin >> pelangganBaru.jumlahKg;
    cin.ignore();
    cout << "Masukkan Catatan Khusus: ";
    getline(cin, pelangganBaru.catatanKhusus);

    // hitung biaya dan estimasi waktu
    if (pelangganBaru.jenisLayanan == "regular")
    {
        pelangganBaru.biaya = pelangganBaru.jumlahKg * 6000;
        pelangganBaru.estimasiWaktu = 3;
    }
    else if (pelangganBaru.jenisLayanan == "express")
    {
        pelangganBaru.biaya = pelangganBaru.jumlahKg * 10000;
        pelangganBaru.estimasiWaktu = 1;
    }

    // Membuat UUID dengan 3 huruf awal nama dan 3 Digit Terakhir No. Telp pelanggan
    pelangganBaru.uuid = buatUUID(pelangganBaru.nama, pelangganBaru.noTelp);

    // Status awal pesanan
    pelangganBaru.statusPesanan = "terima";

    daftarPesanan.push_back(pelangganBaru);
    cout << "Pesanan berhasil diterima!" << endl;
}

// untuk Menangani Pembayaran
void lakukan_pembayaran(vector<Pelanggan>& daftarPesanan)
{
    string uuid;
    cout << "Masukkan UUID Pelanggan untuk Pembayaran: ";
    cin >> uuid;
    cin.ignore();
    bool ditemukan = false;

    for (auto& pelanggan : daftarPesanan)
    {
        if (pelanggan.uuid == uuid) {
            pelanggan.statusPembayaran = true;
            cout << "Pembayaran untuk " << pelanggan.nama << " telah diterima. Total biaya: " << pelanggan.biaya << endl;
            cout << "\n========= Nota Pembayaran =========" << endl;
            cout << "Nama Pelanggan: " << pelanggan.nama << endl;
            cout << "UUID: " << pelanggan.uuid << endl;
            cout << "Jenis Layanan: " << pelanggan.jenisLayanan << endl;
            cout << "Jumlah Kilogram: " << pelanggan.jumlahKg << " kg" << endl;
            cout << "Total Biaya: " << pelanggan.biaya << endl;
            cout << "Estimasi Waktu: " << pelanggan.estimasiWaktu << " hari" << endl;
            cout << "Status Pembayaran: " << (pelanggan.statusPembayaran ? "Sudah Dibayar" : "Belum Dibayar") << endl;
            cout << "Catatan Khusus: " << pelanggan.catatanKhusus << endl;
            cout << "===================================" << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "Pesanan tidak ditemukan!" << endl;
    }
}

// untuk update Status Pesanan
void updateStatusPesanan(vector<Pelanggan>& daftarPesanan)
{
    string uuid;
    cout << "Masukkan UUID Pelanggan untuk update status: ";
    cin >> uuid;
    cin.ignore();
    bool ditemukan = false;

    for (auto& pelanggan : daftarPesanan)
    {
        if (pelanggan.uuid == uuid)
        {
            cout << "Status saat ini: " << pelanggan.statusPesanan << endl;
            cout << "Pilih status baru (terima/proses/selesai): ";
            string statusBaru;
            cin >> statusBaru;
            if (statusBaru == "terima" || statusBaru == "proses" || statusBaru == "selesai")
            {
                pelanggan.statusPesanan = statusBaru;
                cout << "Status pesanan " << pelanggan.nama << " telah diperbarui ke " << pelanggan.statusPesanan << endl;
            }
            else
            {
                cout << "Status tidak valid!" << endl;
            }
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan)
    {
        cout << "Pesanan tidak ditemukan!" << endl;
    }
}

// untuk Menampilkan Daftar Pesanan Aktif
void tampilkanPesananAktif(const vector<Pelanggan>& daftarPesanan)
{
    cout << "Daftar Pesanan Aktif:" << endl;
    for (const auto& pelanggan : daftarPesanan)
    {
        if (pelanggan.statusPesanan != "selesai")
        {
            cout << "UUID: " << pelanggan.uuid << " | Nama: " << pelanggan.nama << " | Status: " << pelanggan.statusPesanan << endl;
        }
    }
}

// untuk Menghitung Jumlah Pesanan Harian
void tampilkanJumlahPesananHarian(const vector<Pelanggan>& daftarPesanan)
{
    map<string, int> pesananCount;
    for (const auto& pelanggan : daftarPesanan)
    {
        if (pelanggan.statusPembayaran && pelanggan.statusPesanan != "selesai")
        {
            pesananCount[pelanggan.statusPesanan]++;
        }
    }
    cout << "Jumlah Pesanan Harian (Belum Selesai):" << endl;
    for (const auto& pair : pesananCount)
    {
        cout << pair.first << ": " << pair.second << " pesanan" << endl;
    }
}

// untuk Menampilkan Catatan Komplain
void tampilkanKomplain(const vector<Komplain>& daftarKomplain)
{
    cout << "Daftar Komplain Pelanggan:" << endl;
    for (const auto& komplain : daftarKomplain)
    {
        cout << "Nama Pelanggan: " << komplain.namaPelanggan << endl;
        cout << "Nomor Telepon: " << komplain.noTelp << endl;
        cout << "Deskripsi Komplain: " << komplain.deskripsiKomplain << endl;
        cout << "---" << endl;
    }
}

// untuk Menerima Komplain
void terimaKomplain(vector<Komplain>& daftarKomplain)
{
    Komplain komplainBaru;
    cout << "Masukkan Nama Pelanggan: ";
    getline(cin, komplainBaru.namaPelanggan);
    cout << "Masukkan Nomor Telepon Pelanggan: ";
    getline(cin, komplainBaru.noTelp);
    cout << "Masukkan Deskripsi Komplain: ";
    getline(cin, komplainBaru.deskripsiKomplain);
    daftarKomplain.push_back(komplainBaru);
    cout << "Komplain berhasil diterima!" << endl;
}

// untuk Melihat Total Pendapatan Harian
void tampilkanPendapatanHarian(const vector<Pelanggan>& daftarPesanan)
{
    int totalPendapatan = 0;
    for (const auto& pelanggan : daftarPesanan)
    {
        if (pelanggan.statusPembayaran)
        {
            totalPendapatan += pelanggan.biaya;
        }
    }
    cout << "Total Pendapatan Harian: " << totalPendapatan << endl;
}

// untuk Menampilkan Layanan Paling Sering Dipesan
void tampilkanLayananPalingSeringDipesan(const vector<Pelanggan>& daftarPesanan)
{
    map<string, int> layananCount;
    for (const auto& pelanggan : daftarPesanan)
    {
        if (pelanggan.statusPembayaran)
        {
            layananCount[pelanggan.jenisLayanan]++;
        }
    }

    string layananPalingSering;
    int maxCount = 0;

    for (const auto& pair : layananCount)
    {
        if (pair.second > maxCount)
        {
            maxCount = pair.second;
            layananPalingSering = pair.first;
        }
    }

    cout << "Layanan Paling Sering Dipesan: " << layananPalingSering << endl;
}

int main()
{
    vector<Pelanggan> daftarPesanan;
    vector<Komplain> daftarKomplain;

    while (true)
    {
        cout << "=== Laundry Service Management System (LSMS) ===" << endl;
        cout << "Menu:" << endl;
        cout << "1. Terima Pesanan" << endl;
        cout << "2. Lakukan Pembayaran" << endl;
        cout << "3. Update Status Pesanan" << endl;
        cout << "4. Tampilkan Daftar Pesanan Aktif" << endl;
        cout << "5. Tampilkan Jumlah Pesanan Harian" << endl; // Menu baru untuk jumlah pesanan harian
        cout << "6. Terima Komplain" << endl;
        cout << "7. Tampilkan Daftar Komplain" << endl;
        cout << "8. Tampilkan Total Pendapatan Harian" << endl;
        cout << "9. Tampilkan Layanan Paling Sering Dipesan" << endl;
        cout << "10. Keluar" << endl;
        cout << "Pilih opsi (1-10): ";

        int pilihan;
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            terimaPesanan(daftarPesanan);
            break;
        case 2:
            lakukan_pembayaran(daftarPesanan);
            break;
        case 3:
            updateStatusPesanan(daftarPesanan);
            break;
        case 4:
            tampilkanPesananAktif(daftarPesanan);
            break;
        case 5:
            tampilkanJumlahPesananHarian(daftarPesanan); // Menampilkan jumlah pesanan harian
            break;
        case 6:
            terimaKomplain(daftarKomplain);
            break;
        case 7:
            tampilkanKomplain(daftarKomplain);
            break;
        case 8:
            tampilkanPendapatanHarian(daftarPesanan);
            break;
        case 9:
            tampilkanLayananPalingSeringDipesan(daftarPesanan);
            break;
        case 10:
            cout << "Keluar dari program." << endl;
            return 0;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;
        }
    }
}
