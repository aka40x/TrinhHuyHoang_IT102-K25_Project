#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct Material {
    char matId[10];
    char name[50];
    char unit[10];
    int qty;
    int status;
};

typedef struct Material Material;

struct Transaction {
    char transId[20];
    char matId[10];
    char type[5];
    char date[15];
    int amount;
};

typedef struct Transaction Transaction;

//10 san pham co san:
struct Material initList[10] = {
	    {"01", "Kho Ga Mixi Food", "Bich", 20, 1},
	    {"02", "Sung", "Khau", 30, 1},
	    {"03", "Ao T1 4*", "Cai", 50, 0},
	    {"04", "Ao T1 5*", "Cai", 50, 0},
	    {"05", "Ao T1 6*", "Cai", 10, 1},
	    {"06", "Keo Kera", "Binh", 36, 1},
	    {"07", "Keo cat tia", "Cai", 20, 1},
	    {"08", "Trim Day Ticket", "Cai", 80, 1},
	    {"09", "Blind Box Chiikawa", "Hop", 40, 1},
	    {"10", "Nem Nuong Ba Tuyet", "Goi", 40, 1}
	};

//Ham chung
int isAllDigit(char s[]) {
    if (strlen(s) == 0) return 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isdigit(s[i])) return 0;
    }
    return 1;
}

void deleteCharactor(char *string, int index){
	int length = strlen(string);
	for (int i = index ; i< length - 1;i++){
		string [i] = string[i+1];
	}
	string [length-1] = '\0';
}

void removeSpaces(char *str) {
    int length = strlen(str);

    while(length > 0 && str[0] == ' ') {
        deleteCharactor(str, 0);
        length--;
    }
    
    while(length > 0 && str[length - 1] == ' ') {
        str[length - 1] = '\0';
        length--;
    }
}

void getString(char *string, char title[], int size) {
    do {
        printf("%s: ", title);
        fgets(string, size, stdin);
        string[strcspn(string, "\n")] = 0;

        if (strlen(string) == 0) {
            printf("Khong duoc de trong!\n");
        }
    } while (strlen(string) == 0);
}

int getInt(char title[]) {
    char temp[50];
    int value;

    while (1) {
        printf("%s: ", title);
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = 0;

        if (!isAllDigit(temp)) {
            printf("Chi duoc nhap so! Moi nhap lai.\n");
            continue;
        }

        value = atoi(temp);
        return value;
    }
}

void getIdNumber(char *dest, char title[], int size) {
    do {
        printf("%s: ", title);
        fgets(dest, size, stdin);
        dest[strcspn(dest, "\n")] = 0;

        if (!isAllDigit(dest)) {
            printf("ID chi duoc chua so!\n");
        }
    } while (!isAllDigit(dest));
}

int isDuplicateId(Material *arr, int length, char matId[]) {
    for (int i = 0; i < length; i++) {
        if (strcmp(arr[i].matId, matId) == 0)
            return 1;
    }
    return 0;
}

void toLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

//F01
void addMat(Material *arr, int *length) {
    int index;
    int currentIndex = *length;

    do {
        index = getInt("Nhap so luong vat tu muon them");
        if (index <= 0) {
            printf("So luong phai lon hon 0!\n");
        }
    } while (index <= 0);

    for (int i = 0; i < index; i++) {
        int pos = currentIndex + i;

        printf("\n--- Vat tu thu %d ---\n", pos + 1);

        do {
            getIdNumber(arr[pos].matId, "Nhap ID vat tu", sizeof(arr[pos].matId));
            if (isDuplicateId(arr, pos, arr[pos].matId))
                printf("ID da ton tai!\n");
        } while (isDuplicateId(arr, pos, arr[pos].matId));

        do {
            getString(arr[pos].name, "Nhap ten vat tu", sizeof(arr[pos].name));
            removeSpaces(arr[pos].name);
            if (strlen(arr[pos].name) == 0)
                printf("Ten vat tu khong duoc rong!\n");
        } while (strlen(arr[pos].name) == 0);

        do {
            getString(arr[pos].unit, "Nhap don vi", sizeof(arr[pos].unit));
            removeSpaces(arr[pos].unit);
            if (strlen(arr[pos].unit) == 0)
                printf("Don vi khong duoc rong!\n");
        } while (strlen(arr[pos].unit) == 0);

        do {
            arr[pos].qty = getInt("Nhap so luong ton kho");
            if (arr[pos].qty <= 0) {
                printf("So luong phai > 0!\n");
            }
        } while (arr[pos].qty <= 0);

        arr[pos].status = 1; 
    }

    *length += index;

    printf("Them vat tu thanh cong!\n");
}

//F02
void updateMat(Material *arr, int length) {
    char id[10];
    int found = -1;

    printf("Nhap ID vat tu muon cap nhat: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    for (int i = 0; i < length; i++) {
        if (strcmp(arr[i].matId, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Khong tim thay vat tu!\n");
        return;
    }

    printf("\n--- Cap nhat thong tin cho vat tu: %s ---\n", arr[found].matId);

    do {
        getString(arr[found].name, "Nhap ten moi", sizeof(arr[found].name));
        removeSpaces(arr[found].name);
        if (strlen(arr[found].name) == 0)
            printf("Ten vat tu khong duoc rong!\n");
    } while (strlen(arr[found].name) == 0);

    do {
        getString(arr[found].unit, "Nhap don vi moi", sizeof(arr[found].unit));
        removeSpaces(arr[found].unit);
        if (strlen(arr[found].unit) == 0)
            printf("Don vi khong duoc rong!\n");
    } while (strlen(arr[found].unit) == 0);

    do {
	    arr[found].qty = getInt("Nhap so luong ton kho moi");
	    if (arr[found].qty < 0) {
	        printf("So luong phai >= 0!\n");
	    }
	} while (arr[found].qty < 0);

    printf("\nCap nhat thanh cong!\n");
}

//F03
void lockMat(Material *arr, int length) {
    char id[10];

    getIdNumber(id, "Nhap ID vat tu can khoa", sizeof(id));

    for (int i = 0; i < length; i++) {
        if (strcmp(arr[i].matId, id) == 0) {

            if (arr[i].status == 0) {
                printf("Vat tu da bi khoa truoc do!\n");
                return;
            }

            arr[i].status = 0;
            printf("Khoa vat tu thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay vat tu!\n");
}

void unlockMat(Material *arr, int length) {
    char id[10];

    getIdNumber(id, "Nhap ID vat tu can mo khoa", sizeof(id));

    for (int i = 0; i < length; i++) {

        if (strcmp(arr[i].matId, id) == 0) {

            if (arr[i].status == 1) {
                printf("Vat tu dang o trang thai su dung, khong can mo khoa!\n");
                return;
            }

            arr[i].status = 1;
            printf("Mo khoa vat tu thanh cong!\n");
            return;
        }
    }

    printf("Khong tim thay vat tu!\n");
}

void deleteMat(Material *arr, int *length) {
    char id[10];
    int index = -1;

    getIdNumber(id, "Nhap ID vat tu can xoa", sizeof(id));

    for (int i = 0; i < *length; i++) {
        if (strcmp(arr[i].matId, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay vat tu!\n");
        return;
    }

    for (int i = index; i < *length - 1; i++) {
        arr[i] = arr[i + 1];
    }

    (*length)--;

    printf("Da xoa thanh cong!\n");
}

void matStatus(Material *arr, int *length) {
    int choice4;
    do {
        printf("========== QUAN LY TRANG THAI ==========");
        printf("\n1. Khoa vat tu");
        printf("\n2. Mo khoa vat tu");
        printf("\n3. Xoa vat tu");
        printf("\n4. Thoat");
        printf("\n========================================");
        printf("\nLua chon: ");
        scanf("%d", &choice4);
        getchar();

        switch (choice4) {
            case 1:
				lockMat(arr, *length);
				break;
            case 2:
				unlockMat(arr, *length);
				break;
            case 3:
            	deleteMat(arr, length);
				break;
			case 4:
				break;
            default:
				printf("Vui long chon 1-4!\n");
        }
    } while (choice4 != 4);
}

//F04
void searchMaterial(Material arr[], int length) {
    if (length == 0) {
        printf("\nDanh sach rong, khong co du lieu!\n");
        return;
    }

    int choose;
    char keyword[50];

    printf("\n========== TRA CUU VAT TU ==========\n");
    printf("1. Tim theo ID\n");
    printf("2. Tim theo ten\n");
    printf("\n========================================");
    printf("\nChon chuc nang: ");
    scanf("%d", &choose);
    getchar();

    do {
	    printf("Nhap tu khoa can tim: ");
	    fgets(keyword, sizeof(keyword), stdin);
	    keyword[strcspn(keyword, "\n")] = '\0';
	    
	    removeSpaces(keyword);
	
	    if (strlen(keyword) == 0) {
	        printf("Tu khoa khong duoc de trong! Vui long nhap lai.\n");
	    }
	} while (strlen(keyword) == 0);


    char keyLower[50];
    strcpy(keyLower, keyword);
    toLower(keyLower);

    int found = 0;

    printf("\n%-10s | %-20s | %-10s | %-8s | %-10s\n",
           "ID", "Ten vat tu", "Don vi", "So luong", "Trang thai");
    printf("---------------------------------------------------------------\n");

    switch (choose) {
        case 1:
            for (int i = 0; i < length; i++) {
                if (strcmp(arr[i].matId, keyword) == 0) {
                    printf("%-10s | %-20s | %-10s | %-8d | %-10s\n",
                        arr[i].matId, arr[i].name, arr[i].unit,
                        arr[i].qty, arr[i].status == 1 ? "Con SD" : "Het han");

                    found = 1;
                    break;
                }
            }
            break;
        case 2:
            for (int i = 0; i < length; i++) {
                char nameLower[50];
                strcpy(nameLower, arr[i].name);
                toLower(nameLower);

                if (strstr(nameLower, keyLower) != NULL) {
                    printf("%-10s | %-20s | %-10s | %-8d | %-10s\n",
                        arr[i].matId, arr[i].name, arr[i].unit,
                        arr[i].qty, arr[i].status == 1 ? "Con SD" : "Het han");
                    found = 1;
                }
            }
            break;
        default:
            printf("\nLua chon khong hop le!\n");
            return;
    }
    if (!found) {
        printf("\nKhong tim thay ket qua!\n");
    }
}

//F05
void listMat(Material *arr, int length) {
    if (length == 0) {
        printf("\nDanh sach rong!\n");
        return;
    }

    int currentPage = 1;
    int matPerPage = 5;
    int totalPage = (length + matPerPage - 1) / matPerPage;
    int choice;
    int page;

    do {
        int start = (currentPage - 1) * matPerPage;
        int end = start + matPerPage;
        if (end > length) end = length;

        printf("\n============== DANH SACH VAT TU (Trang %d / %d) ==============\n",
               currentPage, totalPage);
        printf("%-10s %-20s %-10s %-10s %-10s\n",
               "ID", "Ten", "Don vi", "So luong", "Trang thai");
        printf("-------------------------------------------------------------\n");

        for (int i = start; i < end; i++) {
            printf("%-10s %-20s %-10s %-10d %-10s\n",
                arr[i].matId, arr[i].name, arr[i].unit,
                arr[i].qty, arr[i].status == 1 ? "Con SD" : "Het Han");
        }

        printf("-------------------------------------------------------------\n");
        printf("1. Trang truoc\t2. Trang sau\t3. Den trang\t4. Thoat\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                if (currentPage > 1) currentPage--;
                else printf("Ban dang o trang dau!\n");
                break;
            case 2:
                if (currentPage < totalPage) currentPage++;
                else printf("Ban dang o trang cuoi!\n");
                break;
            case 3:
                printf("Nhap so trang muon den (1-%d): ", totalPage);
                scanf("%d", &page);
                getchar();
                if (page >= 1 && page <= totalPage) currentPage = page;
                else printf("Trang khong ton tai!\n");
                break;
            case 4:
                printf("Thoat phan trang!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }

    } while (choice != 4);
}

//F06
void sortMat(struct Material *arr, int length) {
    int choice;
    while (1) {
        printf("\n===== MENU SAP XEP =====\n");
        printf("1. Sap xep theo ten (A-Z, khong phan biet hoa thuong)\n");
        printf("2. Sap xep theo so luong (tang dan)\n");
        printf("3. Sap xep theo so luong (Giam dan)\n");
        printf("4. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                for (int i = 0; i < length - 1; i++) {
                    for (int j = 0; j < length - i - 1; j++) {
                        const char *a = arr[j].name;
                        const char *b = arr[j + 1].name;
                        while (*a && *b && tolower(*a) == tolower(*b)) { a++; b++; }
                        if (tolower(*a) > tolower(*b)) {
                            struct Material tmp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = tmp;
                        }
                    }
                }
                printf("Da sap xep theo ten!\n");
                break;
            }
            case 2: {
                for (int i = 0; i < length - 1; i++) {
                    for (int j = 0; j < length - i - 1; j++) {
                        if (arr[j].qty > arr[j + 1].qty) {
                            Material tmp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = tmp;
                        }
                    }
                }
                printf("Da sap xep theo so luong tang dan!\n");
                break;
            }
            case 3:
                for (int i = 0; i < length - 1; i++) {
                    for (int j = i + 1; j < length; j++) {
                        if (arr[i].qty < arr[j].qty) {
                            Material temp = arr[i];
                            arr[i] = arr[j];
                            arr[j] = temp;
                        }
                    }
                }
                printf("\nDa sap xep theo So luong giam dan!\n");
                break;
            case 4:
                printf("Da thoat chuc nang sap xep!\n");
                return;
            default:
                printf("Lua chon khong hop le, vui long chon 1->4!\n");
        }
    }
}

//F07
void generateTransId(char *transId, int index) {
    sprintf(transId, "T%03d", index + 1);
}

void getCurrentDate(char *date) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    sprintf(date, "%02d/%02d/%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
}

void transaction(Material *arr, int length, Transaction *transArr, int *transLen) {
    char id[10];
    int index = -1;
    int choose, amount;

    getIdNumber(id, "Nhap ID vat tu can giao dich", sizeof(id));

    for (int i = 0; i < length; i++) {
        if (strcmp(arr[i].matId, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay vat tu!\n");
        return;
    }

    if (arr[index].status == 0) {
        printf("Vat tu dang bi khoa, khong the giao dich!\n");
        return;
    }

    printf("\n1. Nhap kho (IN)");
    printf("\n2. Xuat kho (OUT)");
    printf("\nLua chon: ");
    scanf("%d", &choose);
    getchar();

    if (choose != 1 && choose != 2) {
        printf("Lua chon khong hop le!\n");
        return;
    }

    amount = getInt("Nhap so luong");

    if (amount <= 0) {
        printf("So luong phai > 0!\n");
        return;
    }

    if (choose == 2 && amount > arr[index].qty) {
        printf("Khong du so luong de xuat!\n");
        return;
    }

    if (choose == 1)
        arr[index].qty += amount;
    else
        arr[index].qty -= amount;

    Transaction t;
    generateTransId(t.transId, *transLen);
    strcpy(t.matId, id);
    strcpy(t.type, choose == 1 ? "IN" : "OUT");
    t.amount = amount;
    getCurrentDate(t.date);

    transArr[*transLen] = t;
    (*transLen)++;

    printf("\nGiao dich thanh cong!\n");
}

//F08

int main() {
	int choice = 0;
    int choice1 = 0;
    int length = 10;
    struct Material arr[100];
    for (int i = 0; i < 10; i++) {
        arr[i] = initList[i];
    }   
    int choice2 = 0;
    int choice3 = 0;
    Transaction transArr[200];
	int transLen = 0;
	

    do {
        printf("\n========== MENU QUAN LY VAT TU ==========");
        printf("\n1. Quan ly tai khoan");
        printf("\n2. Quan ly giao dich");
        printf("\n3. Thoat");
        printf("\n=========================================");
        printf("\nNhap lua chon: ");
        scanf("%d", &choice1);
        getchar();

        switch (choice1) {
            case 1:
                do {
                    printf("\n========== MENU QUAN LY TAI KHOAN ==========");
                    printf("\n1. Them ma hang moi");
                    printf("\n2. Cap nhat thong tin");
                    printf("\n3. Quan ly trang thai (Khoa/Xoa)");
                    printf("\n4. Tra cuu");
                    printf("\n5. Danh sach");
                    printf("\n6. Sap xep danh sach");
                    printf("\n7. Thoat");
                    printf("\n============================================");
                    printf("\nNhap lua chon: ");
                    scanf("%d", &choice2);
                    getchar();

                    switch (choice2) {
                        case 1:
							addMat(arr, &length);
							break;
                        case 2:
							updateMat(arr, length);
							break;
                        case 3:
							matStatus(arr, &length);
							break;
                        case 4:
                        	searchMaterial(arr, length);
							break;
                        case 5:
                        	listMat(arr,length);
							break;
                        case 6:
                        	sortMat(arr, length);
                        	listMat(arr, length);
							break;
                        case 7:
                        	printf("Thoat chuong trinh...\n");
							break;
                        default:
							printf("Vui long chon 1-7!\n");
                    }

                } while (choice2 != 7);
                break;

            case 2:
                do {
                    printf("========== MENU QUAN LY GIAO DICH ==========");
                    printf("\n1. Giao dich xuat/nhap vat tu");
                    printf("\n2. Lich su xuat/nhap");
                    printf("\n3. Thoat");
                    printf("\n============================================");
                    printf("\nNhap lua chon: ");
                    scanf("%d", &choice3);
                    getchar();

                    switch (choice3) {
                        case 1:
                        	transaction(arr, length, transArr, &transLen);
							break;
                        case 2:
                        	printf("\nChua lam den\n");
							break;
                        case 3:
                        	printf("\nThoat chuong trinh...");
							break;
                        default:
							printf("Vui long chon 1-3!\n");
                    }
                } while (choice3 != 3);
                break;

            case 3:
                printf("Thoat chuong trinh...\n");
                exit(0);

            default:
                printf("Vui long chon 1-3!\n");
        }

    } while (choice1 != 3);

    return 0;
}
