/*Anggota Kelompok Alpro 2
1. Akhmad Rakhis Yudha 2802521371
2. Iqbal Kevin Kyle 2802523622
3. Marcello Aqeel Pane 2802522166
4. Shevanya Nagita Tesalonika Winowoda 2802522664
5. Zahra Illiyin 2802519745
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxBooks 100 
#define maxHistory 100 
#define maxString 50
#define maxCode 20
#define database "databuku.txt"

typedef struct {
    char bookCode[maxCode];
    char bookTitle[maxString];
    char bookGenre[maxString];
    int bookPrice;
} bookStruct; 

typedef struct {
    char historyCode[maxCode];
    char historyTitle[maxString];
    char historyGenre[maxString];
    int historyPrice;
} historyStruct;

bookStruct books[maxBooks];
historyStruct history[maxHistory];
int bookCount = 0; 
int historyCount = 0; 

//Fungsi membaca file databuku.txt
void loadDataBuku() {
    FILE *file = fopen("databuku.txt", "r");
    if (file == NULL) {
        printf("File tidak ditemukan, ");
        return;
    } 
    while (!feof(file) && bookCount < maxBooks) {
        fscan(file, "%[^|],%[^|],%[^|],%d\n", 
        books[bookCount].bookCode, 
        books[bookCount].bookTitle,
        books[bookCount].bookGenre,
        books[bookCount].bookPrice);
    bookCount++;
    }
    fclose(file);
}

//Fungsi menulis di file databuku.txt
void saveAndExit() {
    FILE *file = fopen("databuku.txt", "w");
    if (file == NULL) {
        printf("Error, file tidak dapat dibuka.\n");
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        fprint(file, "%s|%s|%s|%d\n",
        books[i].bookCode,
        books[i].bookTitle,
        books[i].bookGenre,
        books[i].bookPrice);
    }
    fclose(file);
}

//Fungsi untuk memasukkan transaski
void inputBooks() {
    if (bookCount < maxBooks) {
        printf("Error, database penuh.\n");
        return;
    } 
    else {
        printf("Input data buku baru.\n");
        sprintf(books[bookCount].bookCode, "code%d", bookCount +1);
        printf("Judul buku: \n");
        scanf("%[^\n]", books[bookCount].bookTitle);
        printf("Jenis buku: \n");
        scanf("%[^\n]", books[bookCount].bookTitle);
        printf("Harga buku: \n");
        scanf("%d", books[bookCount].bookPrice);

        strcpy(history[historyCount].historyTitle, books[bookCount].bookTitle);
        strcpy(history[historyCount].historyGenre, books[bookCount].bookGenre);
        history[historyCount].historyPrice = books[bookCount].bookPrice;
        historyCount++;

        bookCount++;
        printf("Buku berhasil ditambahkan.\n");
    }    
}

//Fungsi untuk melihat riwayat transaksi (saat ini)
void viewHistory() {
    printf("Riwayat transaksi hari ini.\n");

    for (int i = 0; i < historyCount; i++) {
        printf("%d %-10s %-10s %d\n",
        i + 1,
        history[i].historyTitle,
        history[i].historyGenre,
        history[i].historyPrice);
    }
    
}

//Fungsi untuk melihat semua buku yang ada di database
void viewBooks() {
    printf("Daftar seluruh transaksi.\n");

    for (int i = 0; i < bookCount; i++) {
        printf("%d %-10s %-10s %-10s %d\n",
        i + 1,
        books[i].bookCode,
        books[i].bookTitle,
        books[i].bookGenre,
        books[i].bookPrice);
    }
}

//Fungsi untuk menghapus riwayat transaksi di database
void deleteHistory() {
    if (historyCount == 0) {
        printf("Error, tidak ada riwayat transaksi hari ini.\n");
        return;
    } 
    else {
        viewHistory();
        int nomor;
        do {
            printf("Masukkan nomor yang akan dihapus:");
            scanf("%d", &nomor);
        } while (nomor < 1 || nomor > historyCount);
        nomor--;

        for (int i = nomor; i < historyCount - 1; i++) {
            history[i] = history[i + 1];
        }
    } 
    historyCount--;
    printf("Data berhasil dihapus.\n");
}

//Fungsi untuk menghapus data buku di database 
void deleteBooks() {
    if (bookCount == 0) {
        printf("Error, tidak ada buku.\n");
        return;        
    } 
    viewBooks();
    int nomor;
    do {
        printf("Masukkan nomor yang akan dihapus:");
        scanf("%d", &nomor);
    } while (nomor < 1 || nomor > bookCount);
    nomor--;

    for (int i = nomor; i < bookCount - 1; i++) {
        books[i] = books[i + 1];        
    }

}

int main() {
    loadDataBuku();
    int menu; 

    do {
        printf("Toko Buku Alpro 2\n");
        printf("1. Input\n");
        printf("2. View History\n");
        printf("3. View Buku\n");
        printf("4. Delete History\n");
        printf("5. Delete Buku\n");
        printf("6. Exit\n");

        switch (menu)
        {
        case 1: inputBooks();
            break;
        case 2: viewHistory();
            break;
        case 3: viewBooks();
            break;
        case 4: deleteHistory();
            break;
        case 5: deleteBooks();
            break;
        case 6: saveAndExit();
            saveData();
            printf("Data berhasil disimpan ke '%s'\n", database);
            break;
        default:
            printf("Pilihan tidak valid\n");
            break;
        }
    } while (menu !=6);

    return 0;
}


