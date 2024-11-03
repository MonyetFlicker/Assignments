/* Anggota Kelompok Alpro 2
1. Akhmad Rakhis Yudha 2802521371
2. Iqbal Kevin Kyle 2802523622
3. Marcello Aqeel Pane 2802522166
4. Shevanya Nagita Tesalonika Winowoda 2802522664
5. Zahra Illiyin 2802519745
*/

#include <stdio.h> //Standard I/O
#include <stdlib.h> //memory management 
#include <string.h> //string manipulations

#define maxBooks 100 //maximum array sizes 
#define maxHistory 100 
#define maxString 100
#define maxCode 100
#define database "databuku.txt" //easier to change

typedef struct {
    char bookCode[maxCode]; //size is defined previously
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
int bookCount = 0; //counting variables to keep track of entries in each array
int historyCount = 0; 

//Fungsi membaca file databuku.txt
void loadDataBuku() { 
    FILE *file = fopen("databuku.txt", "r"); //command to read from the .txt
    if (file == NULL) {
        printf("File tidak ditemukan, "); //error message if the user wanted to call from non-existent file
        return;
    } 
    while (!feof(file) && bookCount < maxBooks) { //scan until the end of the file
        fscanf(file, "%[^|]|%[^|]|%[^|]|%d\n", //each data is separated by | and assigned to respective variables
        books[bookCount].bookCode, 
        books[bookCount].bookTitle,
        books[bookCount].bookGenre,
        &books[bookCount].bookPrice);
    bookCount++; //counter for each entities in the books array
    }
    fclose(file);
}

//Fungsi menulis di file databuku.txt
void saveAndExit() { 
    FILE *file = fopen("databuku.txt", "w"); 
    if (file == NULL) {
        printf("Error, file tidak dapat dibuka.\n"); //error message if the file can't be written in
        return;
    }
    for (int i = 0; i < bookCount; i++) { //counter made to be dynamic as the program can delete and add entry
        fprintf(file, "%s|%s|%s|%d\n", //fprintf to write to the file
        books[i].bookCode,
        books[i].bookTitle,
        books[i].bookGenre,
        books[i].bookPrice);
    }
    fclose(file);
}

//Fungsi untuk memasukkan transaski
void inputBooks() {
    if (bookCount >= maxBooks) { 
        printf("Error, database penuh.\n"); //error message to show when the user wanted to add an entry when the book arrays has met the limit
        return;
    } 
    else {
        printf("Input data transaksi baru.\n");
        sprintf(books[bookCount].bookCode, "code%d", bookCount + 1); //the code is stored into the book.code not printed out

        printf("Judul buku: \n");
        scanf(" %[^\n]s", books[bookCount].bookTitle); //read the input until newspace 

        printf("Jenis buku: \n");
        scanf(" %[^\n]s", books[bookCount].bookGenre);

        printf("Harga buku (Rp): \n");
        scanf("%d", &books[bookCount].bookPrice);

        strcpy(history[historyCount].historyTitle, books[bookCount].bookTitle); //adding the entry into the history array
        strcpy(history[historyCount].historyGenre, books[bookCount].bookGenre);
        history[historyCount].historyPrice = books[bookCount].bookPrice;
        historyCount++;

        bookCount++; //after each iteration (input) it will increase the book number (towards max number)
        printf("Buku berhasil ditambahkan.\n");
    }    
}

//Fungsi untuk melihat riwayat transaksi (saat ini)
void viewHistory() {
    printf("Riwayat transaksi hari ini.\n"); //history array isn't stored in the databuku.txt. It's to represent daily transaction. 
                                            // historical transaction will be represented by view books
    for (int i = 0; i < historyCount; i++) {
        printf("%d. %-10s %-10s %-10d\n", //aligning data shown to the left. with minimum 10 characters each (to make it easier to read)
        i + 1,
        history[i].historyTitle,
        history[i].historyGenre,
        history[i].historyPrice);
    }
    
}

//Fungsi untuk melihat semua buku yang ada di database
void viewBooks() {
    printf("Daftar seluruh transaksi.\n"); //historical transactions

    for (int i = 0; i < bookCount; i++) {
        printf("%d. %-10s %-10s %-10s %-10d\n",
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
    
        viewHistory();
        int nomor;
        do {
            printf("Masukkan nomor yang akan dihapus:");
            scanf("%d", &nomor);
        } while (nomor < 1 || nomor > historyCount); //stops accepting input if the user entered invalid value 
        nomor--; //to make it compatible with base-0 nature of arrays

        for (int i = nomor; i < historyCount - 1; i++) { //looping the moving 
            history[i] = history[i + 1]; //deletes an entry by shifting the subsequent entry to its position
        }
        historyCount--; //updating the counter 
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
    bookCount--;
    printf("Data berhasil dihapus.\n");
}

int main() { //main interface for the program
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
        printf("Pilihan: ");
        scanf("%d", &menu);

        switch (menu) {
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
            printf("Data berhasil disimpan"); //confirmation message
            break;
        default:
            printf("Pilihan tidak valid\n"); //error message
            break;
        }
    } while (menu !=6);

    return 0;
}


