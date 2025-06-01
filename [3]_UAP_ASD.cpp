#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include <queue>

// Simpan informasi pribadi pengguna
struct informasiPengguna
{
    std::string nama;
    int umur;
    std::vector<std::string> hobi;

    informasiPengguna()
    {
        nama = "anonymus";
        umur = 0;
        hobi = {"", "", ""};
    }

    informasiPengguna(std::string name, int age, std::vector<std::string> hobby)
    {
        nama = name;
        umur = age;
        hobi = hobby;
    }
};

class Grukom
{
private:
    std::vector<informasiPengguna> dataPengguna;
    std::unordered_map<std::string, std::vector<informasiPengguna>> friendLists;

    template <typename T>
    void swap(T &a, T &b)
    {
        auto temp = a;
        a = b;
        b = temp;
    }

    bool compareWords(std::string str1, std::string str2)
    {
        if (str1[0] == str2[0])
        {
            return str1 > str2;
        }

        return str1[0] > str2[0];
    }

    void bubbleSortNama(std::vector<informasiPengguna> &arr)
    {
        int size = arr.size();
        bool swapped;
        do
        {
            swapped = false;
            for (int i = 1; i <= size - 1; i++)
            {
                if (compareWords(arr[i - 1].nama, arr[i].nama))
                {
                    swap(arr[i - 1], arr[i]);
                    swapped = true;
                }
            }
        } while (swapped);
    }

    void bubbleSortUmur(std::vector<informasiPengguna> &arr)
    {
        int size = arr.size();
        bool swapped;
        do
        {
            swapped = false;
            for (int i = 1; i <= size - 1; i++)
            {
                if (arr[i - 1].umur < arr[i].umur)
                {
                    swap(arr[i - 1], arr[i]);
                    swapped = true;
                }
            }
        } while (swapped);
    }

    bool findNameInList(std::vector<informasiPengguna> arr, std::string nama)
    {
        bool found = false;
        for (informasiPengguna info : arr)
        {
            if (info.nama == nama)
            {
                found = true;
                break;
            }
        }

        return found;
    }

    informasiPengguna getPengguna(std::string name)
    {
        informasiPengguna temp;
        for (informasiPengguna info : dataPengguna)
        {
            if (info.nama == name)
            {
                temp = info;
                return temp;
            }
        }

        std::cout << "Tidak dapat menemukan pengguna!\n";
        return temp;
    }

public:
    bool findName(std::string name)
    {
        bool found = false;
        for (auto pengguna : dataPengguna)
        {
            if (pengguna.nama == name)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool findHobi(std::string hobi)
    {
        for (informasiPengguna info : dataPengguna)
        {
            for (std::string hobby : info.hobi)
            {
                if (hobby == hobi)
                {
                    return true;
                }
            }
        }

        return false;
    }

    void tambahPengguna(std::string name, int age, std::vector<std::string> hobby)
    {
        for (auto pengguna : dataPengguna)
        {
            if (pengguna.nama == name)
            {
                std::cout << "[ERROR] PENGGUNA TELAH TERDAFTAR!\n";
                return;
            }
        }

        informasiPengguna user(name, age, hobby);
        dataPengguna.push_back(user);
        friendLists[name] = {};

        std::cout << name << " BERHASIL DITAMBAH\n";
    }

    void removePengguna(std::string name)
    {
        if (!findName(name))
        {
            std::cout << "[ERROR] TIDAK DAPAT MENEMUKAN PENGGUNA " << name << "!\n";
            return;
        }

        for (informasiPengguna teman : friendLists[name])
        {
            std::string namaTeman = teman.nama;
            std::vector<informasiPengguna> &daftarPertemananTeman = friendLists[namaTeman];
            if (findNameInList(daftarPertemananTeman, name))
            {
                for (int i = 0; i < daftarPertemananTeman.size(); i++)
                {
                    if (daftarPertemananTeman[i].nama == name)
                    {
                        daftarPertemananTeman.erase(daftarPertemananTeman.begin() + i);
                        break;
                    }
                }
            }
        }

        friendLists.erase(name);
        for (int i = 0; i < dataPengguna.size(); i++)
        {
            if (dataPengguna[i].nama == name)
            {
                dataPengguna.erase(dataPengguna.begin() + i);
                break;
            }
        }

        std::cout << name << " BERHASIL DIHAPUS" << "\n\n";
    }

    void connectUser(std::string nama1, std::string nama2)
    {
        if (!findName(nama1) || !findName(nama2))
        {
            std::cout << "[ERROR] TIDAK DAPAT MENEMUKAN SALAH SATU ATAU KEDUA USER!\n\n";
            return;
        }

        std::vector<informasiPengguna> daftarPertemanan1 = friendLists[nama1];

        for (informasiPengguna info : daftarPertemanan1)
        {
            if (info.nama == nama2)
            {
                std::cout << "[ERROR] PENGGUNA " << nama1 << " DENGAN " << nama2 << " SUDAH SALING BERTEMAN!\n";
                return;
            }
        }

        friendLists[nama1].push_back(getPengguna(nama2));
        friendLists[nama2].push_back(getPengguna(nama1));

        std::cout << "Berhasil saling mengoneksikan user " << nama1 << " dengan " << nama2 << "\n\n";
    }

    void recommendUser(std::string nama)
    {
        if (!findName(nama))
        {
            std::cout << "[ERROR] TIDAK DAPAT MENEMUKAN PENGGUNA " << nama << "!\n";
            return;
        }

        std::cout << "Rekomendasi teman dari " << nama << ":\n";
        for (informasiPengguna info : friendLists[nama])
        {
            std::cout << info.nama << " " << '\n';
        }
        std::cout << "\n\n";
    }

    void printAll()
    {
        if (dataPengguna.empty())
        {
            std::cout << "[ERROR] TIDAK ADA PENGGUNA YANG TERDAFTAR!\n";
            return;
        }

        std::vector<informasiPengguna> currentUsers = dataPengguna;
        bubbleSortNama(currentUsers);

        std::cout << "\n=== PENGGUNA TERDAFTAR SAAT INI ===\n";
        int i = 1;
        for (informasiPengguna info : currentUsers)
        {
            std::cout << i << ". " << info.nama << " " << info.umur << " ";
            for (auto hobi : info.hobi)
            {
                std::cout << hobi << ", ";
            }
            std::cout << '\n';
            std::cout << "Jumlah teman: " << friendLists[info.nama].size();
            std::cout << '\n';
            i++;
        }
        std::cout << '\n';
    }

    void tampilkanTeman(std::string nama)
    {
        if (dataPengguna.empty())
        {
            std::cout << "[ERROR] TIDAK ADA PENGGUNA YANG TERDAFTAR!\n\n";
            return;
        }

        else if (!findName(nama))
        {
            std::cout << "[ERROR] TIDAK DAPAT MENEMUKAN PENGGUNA " << nama << "!\n";
            return;
        }

        std::vector<informasiPengguna> daftarPertemanan = friendLists[nama];
        if (daftarPertemanan.size() == 0)
        {
            std::cout << "[WARNING] PENGGUNA " << nama << " BELUM MEMILIKI TEMAN!\n";
            return;
        }

        bubbleSortNama(daftarPertemanan);

        std::cout << "=== DAFTAR PERTEMANAN " << nama << " ===\n";
        int i = 1;
        for (informasiPengguna info : daftarPertemanan)
        {
            std::cout << i << ". " << info.nama << '\n';
            i++;
        }
        std::cout << '\n';
    }

    void tampilkanUserHobi(std::string hobi)
    {
        if (dataPengguna.empty())
        {
            std::cout << "[ERROR] TIDAK ADA PENGGUNA YANG TERDAFTAR!\n";
            return;
        }

        else if (!findHobi(hobi))
        {
            std::cout << "[ERROR] BELUM ADA PENGGUNA YANG MEMILIKI HOBI " << hobi << '\n';
            return;
        }

        std::vector<informasiPengguna> namaHobisSama;

        for (informasiPengguna info : dataPengguna)
        {
            for (std::string hobby : info.hobi)
            {
                if (hobby == hobi)
                {
                    namaHobisSama.push_back(info);
                }
            }
        }

        bubbleSortUmur(namaHobisSama);

        std::cout << "Pengguna dengan hobi " << hobi << '\n';
        int i = 1;
        for (informasiPengguna info : namaHobisSama)
        {
            std::cout << i << ". " << info.nama << ", " << info.umur << '\n';
            i++;
        }
        std::cout << '\n';
    }
};

void executeCommand(std::queue<std::string> queue_perintah)
{
    Grukom myGrukom;
    while (!queue_perintah.empty())
    {
        std::string perintah = queue_perintah.front();
        queue_perintah.pop();

        std::stringstream ss(perintah);
        std::string apaYangHarusDilakukan;
        ss >> apaYangHarusDilakukan;

        if (apaYangHarusDilakukan == "ADD")
        {
            std::string nama, hobi;
            int usia;
            std::vector<std::string> listHobi;

            ss >> nama >> usia;
            while (ss >> hobi && listHobi.size() < 3)
            {
                listHobi.push_back(hobi);
            }

            myGrukom.tambahPengguna(nama, usia, listHobi);
        }
        else if (apaYangHarusDilakukan == "REMOVE")
        {
            std::string nama;
            ss >> nama;

            myGrukom.removePengguna(nama);
        }
        else if (apaYangHarusDilakukan == "CONNECT")
        {
            std::string nama1, nama2;
            ss >> nama1 >> nama2;

            myGrukom.connectUser(nama1, nama2);
        }
        else if (apaYangHarusDilakukan == "RECOMMEND")
        {
            std::string nama;
            ss >> nama;

            myGrukom.recommendUser(nama);
        }
        else if (apaYangHarusDilakukan == "PRINT")
        {
            std::string printApa;
            ss >> printApa;

            if (printApa == "ALL")
            {
                myGrukom.printAll();
            }
            else
            {
                if (myGrukom.findName(printApa))
                {
                    myGrukom.tampilkanTeman(printApa);
                }
                else if (myGrukom.findHobi(printApa))
                {
                    myGrukom.tampilkanUserHobi(printApa);
                }
                else if (!myGrukom.findName(printApa) || !myGrukom.findHobi(printApa))
                {
                    std::cout << "MAAF " << printApa << " BUKAN PERINTAH PRINT YANG VALID!\n";
                    std::cout << "Kemungkinan nama/hobi belum terdaftar atau memang bukan perintah yang valid!\n";
                    continue;
                }
            }
        }
        else
        {
            std::cout << "COMMAND TIDAK VALID. HARAP DIBACA PETUNJUKNYA!\n";
            continue;
        }
    }
}

int main()
{
    std::queue<std::string> commands;
    std::string masukan;

    std::cout << "MASUKAN COMMAND SESUAI KETENTUAN BERIKUT (tanpa menggunakan kurung siku): \n";
    std::cout << "=== MENAMBAHKAN USER ===\n";
    std::cout << "ADD [Nama] [USIA] [HOBI 1] [HOBI 2] [HOBI 3]\n";

    std::cout << "=== MENGHAPUS USER ===\n";
    std::cout << "REMOVE [Nama]\n";

    std::cout << "=== SALING MENGONEKSIKAN USER ===\n";
    std::cout << "CONNECT [Nama1] [Nama2]\n";

    std::cout << "=== REKOMENDASI DARI USER ===\n";
    std::cout << "RECOMMEND [Nama]\n";

    std::cout << "=== PRINT SEMUA USER ===\n";
    std::cout << "PRINT ALL\n";

    std::cout << "=== PRINT TEMAN SEORANG USER ===\n";
    std::cout << "PRINT [NAMA]\n";

    std::cout << "=== PRINT USER DENGAN HOBI YANG SAMA ===\n";
    std::cout << "PRINT [HOBI]\n";

    std::cout << "\nMasukkan command (tekan Enter kosong untuk menjalankan):\n";

    while (true)
    {
        std::getline(std::cin, masukan);
        if (masukan.empty())
        {
            break;
        }
        commands.push(masukan);
    }

    executeCommand(commands);

    return 0;
}