#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//Mau
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define GRAY "\033[90m"

#define MAX_MAT 100
#define MAX_TRANS 200

// Struct
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

// 10 san pham co san
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

// Ham chung
int isAllDigit(char s[]) {
    if (strlen(s) == 0){
		return 0;
	}
    for (int i = 0; s[i] != '\0'; i++) {
        if (!isdigit((unsigned char)s[i]))
		return 0;
    }
    return 1;
}

void deleteCharactor(char *string, int index){
    int length = strlen(string);
    if (index < 0 || index >= length) return;
    for (int i = index ; i < length - 1; i++){
        string[i] = string[i+1];
    }
    string[length-1] = '\0';
}

void removeSpaces(char *str) {
    while (str[0] == ' ') deleteCharactor(str, 0);
    int length = strlen(str);
    while (length > 0 && str[length - 1] == ' ') {
        str[length - 1] = '\0';
        length--;
    }
}

void getString(char *string, char title[], int size) {
    do {
        printf("%s: ", title);
        if (fgets(string, size, stdin) == NULL) string[0] = '\0';
        string[strcspn(string, "\n")] = 0;
        if (strlen(string) == 0) printf(RED "Khong duoc de trong!\n" RESET);
    } while (strlen(string) == 0);
}

int getInt(char title[]) {
    char temp[50];
    int value;
    while (1) {
        printf("%s: ", title);
        if (fgets(temp, sizeof(temp), stdin) == NULL) temp[0] = '\0';
        temp[strcspn(temp, "\n")] = 0;
        if (!isAllDigit(temp)) {
            printf(RED "Chi duoc nhap so! Moi nhap lai.\n" RESET);
            continue;
        }
        value = atoi(temp);
        return value;
    }
}

void getIdNumber(char *dest, char title[], int size) {
    do {
        printf("%s: ", title);
        if (fgets(dest, size, stdin) == NULL) dest[0] = '\0';
        dest[strcspn(dest, "\n")] = 0;
        if (!isAllDigit(dest)) printf(RED "ID chi duoc chua so!\n" RESET);
    } while (!isAllDigit(dest));
}

int isDuplicateId(Material *arr, int length, char matId[]) {
    for (int i = 0; i < length; i++) {
        if (strcmp(arr[i].matId, matId) == 0)
		return 1;
    }
    return 0;
}

void toLowerStr(char *str) {
    for (int i = 0; str[i]; i++) str[i] = (char)tolower((unsigned char)str[i]);
}

int getMenuChoice(char *title) {
    char choiceStr[10];
    int choice;

    while (1) {
        printf("%s", title);
        if (fgets(choiceStr, sizeof(choiceStr), stdin) == NULL) choiceStr[0] = '\0';
        choiceStr[strcspn(choiceStr, "\n")] = 0;
        removeSpaces(choiceStr);

        if (strlen(choiceStr) == 0) {
            printf(RED "Lua chon khong duoc de trong!\n" RESET);
            continue;
        }
        if (!isAllDigit(choiceStr)) {
            printf(RED "Chi nhap so!\n" RESET);
            continue;
        }

        choice = atoi(choiceStr);
        return choice;
    }
}


// F01: Them vat tu
void addMat(Material *arr, int *length) {
    int index;
    int currentIndex = *length;

    do {
        index = getInt("Nhap so luong vat tu muon them");
        if (index <= 0) printf(RED "So luong phai lon hon 0!\n" RESET);
    } while (index <= 0);

    if (currentIndex + index > MAX_MAT) {
        printf(YELLOW "Chi con the them toi da %d vat tu.\n" RESET, MAX_MAT - currentIndex);
        index = MAX_MAT - currentIndex;
        if (index <= 0) {
            printf(RED "Da dat gioi han vat tu (%d). Khong the them.\n" RESET, MAX_MAT);
            return;
        }
    }

    for (int i = 0; i < index; i++) {
        int pos = currentIndex + i;
        printf("\n--- Vat tu thu %d ---\n", pos + 1);

        do {
            getIdNumber(arr[pos].matId, "Nhap ID vat tu", sizeof(arr[pos].matId));
            if (isDuplicateId(arr, currentIndex + i, arr[pos].matId)) printf(YELLOW "ID da ton tai!\n" RESET);
        } while (isDuplicateId(arr, currentIndex + i, arr[pos].matId));

        do {
            getString(arr[pos].name, "Nhap ten vat tu", sizeof(arr[pos].name));
            removeSpaces(arr[pos].name);
            if (strlen(arr[pos].name) == 0) printf(RED "Ten vat tu khong duoc rong!\n" RESET);
        } while (strlen(arr[pos].name) == 0);

        do {
            getString(arr[pos].unit, "Nhap don vi", sizeof(arr[pos].unit));
            removeSpaces(arr[pos].unit);
            if (strlen(arr[pos].unit) == 0) printf(RED "Don vi khong duoc rong!\n" RESET);
        } while (strlen(arr[pos].unit) == 0);

        do {
            arr[pos].qty = getInt("Nhap so luong ton kho");
            if (arr[pos].qty <= 0) printf(RED "So luong phai > 0!\n" RESET);
        } while (arr[pos].qty <= 0);

        arr[pos].status = 1;
    }
    *length += index;
    printf(GREEN "Them vat tu thanh cong!\n" RESET);
}

// F02: Cap nhat vat tu
void updateMat(Material *arr, int length) {
    char id[10]; int found = -1;
    printf("Nhap ID vat tu muon cap nhat: ");
    if (fgets(id, sizeof(id), stdin) == NULL) id[0] = '\0';
	id[strcspn(id, "\n")] = 0;

    for (int i = 0; i < length; i++)
        if (strcmp(arr[i].matId, id) == 0) {
			found = i;
			break;
		}

    if (found == -1) {
		printf(RED "Khong tim thay vat tu!\n" RESET);
		return;
	}

    printf("\n--- Cap nhat thong tin cho vat tu: %s ---\n", arr[found].matId);

    do { getString(arr[found].name, "Nhap ten moi", sizeof(arr[found].name));
        removeSpaces(arr[found].name);
        if (strlen(arr[found].name) == 0)
			printf(RED "Ten vat tu khong duoc rong!\n" RESET);
    } while (strlen(arr[found].name) == 0);

    do { getString(arr[found].unit, "Nhap don vi moi", sizeof(arr[found].unit));
        removeSpaces(arr[found].unit);
        if (strlen(arr[found].unit) == 0)
			printf(RED "Don vi khong duoc rong!\n" RESET);
    } while (strlen(arr[found].unit) == 0);

    do { arr[found].qty = getInt("Nhap so luong ton kho moi");
        if (arr[found].qty < 0)
			printf(RED "So luong phai >= 0!\n" RESET);
    } while (arr[found].qty < 0);

    printf(GREEN "\nCap nhat thanh cong!\n" RESET);
}

// F03: Khoa / mo khoa / xoa vat tu
void lockMat(Material *arr, int length) {
    char id[10]; getIdNumber(id, "Nhap ID vat tu can khoa", sizeof(id));
    for (int i = 0; i < length; i++) {
        if (strcmp(arr[i].matId, id) == 0) {
            if (arr[i].status == 0) {
				printf(YELLOW "Vat tu da bi khoa truoc do!\n" RESET);
				return;
			}
            arr[i].status = 0;
			printf(GREEN "Khoa vat tu thanh cong!\n" RESET);
			return;
        }
    }
    printf(RED "Khong tim thay vat tu!\n" RESET);
}

void unlockMat(Material *arr, int length) {
    char id[10]; getIdNumber(id, "Nhap ID vat tu can mo khoa", sizeof(id));
    for (int i = 0; i < length; i++) {
        if (strcmp(arr[i].matId, id) == 0) {
            if (arr[i].status == 1){
				printf(YELLOW "Vat tu dang o trang thai su dung!\n" RESET);
				return;
			}
            arr[i].status = 1; printf(GREEN "Mo khoa vat tu thanh cong!\n" RESET);
			return;
        }
    }
    printf(RED "Khong tim thay vat tu!\n" RESET);
}

void deleteMat(Material *arr, int *length) {
    char id[10]; int index = -1; getIdNumber(id, "Nhap ID vat tu can xoa", sizeof(id));
    for (int i = 0; i < *length; i++)
	if (strcmp(arr[i].matId, id) == 0) { index = i; break; }
    if (index == -1) { printf(RED "Khong tim thay vat tu!\n" RESET);
		return; }
    for (int i = index; i < *length - 1; i++) arr[i] = arr[i + 1];
    (*length)--; printf(GREEN "Da xoa thanh cong!\n" RESET);
}

void matStatus(Material *arr, int *length) {
    int choice4;
    char choiceStr[10];
    do {
        printf(GRAY "========== QUAN LY TRANG THAI ==========" RESET);
        printf("\n1. Khoa vat tu\n2. Mo khoa vat tu\n3. Xoa vat tu\n4. Thoat\n");
		choice4 = getMenuChoice("Lua chon: ");
        switch(choice4) {
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
				printf(RED "Vui long chon 1-4!\n" RESET);
        }
    } while(choice4 != 4);
}

// F04: Tim kiem vat tu
void searchMaterial(Material arr[], int length) {
    if (length == 0) {
        printf(RED "\nDanh sach rong, khong co du lieu!\n" RESET);
        return;
    }

    int choose;
    char keyword[50];
	char chooseStr[10];
	do{
    printf(GRAY "\n========== TRA CUU VAT TU ==========" RESET);
    printf("\n1. Tim theo ID\n");
    printf("2. Tim theo ten\n");
    choose = getMenuChoice("Nhap lua chon: ");
    do {
        printf("Nhap tu khoa can tim: ");
        if (fgets(keyword, sizeof(keyword), stdin) == NULL) keyword[0] = '\0';
        keyword[strcspn(keyword, "\n")] = '\0';
        removeSpaces(keyword);
        if (strlen(keyword) == 0) {
            printf(YELLOW "Tu khoa khong duoc de trong! Vui long nhap lai.\n" RESET);
        }
    } while (strlen(keyword) == 0);

    char keyLower[50];
    strcpy(keyLower, keyword);
    toLowerStr(keyLower);

    int found = 0;

    printf("\n%-10s | %-20s | %-10s | %-8s | %-10s\n",
           "ID", "Ten vat tu", "Don vi", "So luong", "Trang thai");
    printf(GRAY "---------------------------------------------------------------\n" RESET);

    switch (choose) {
        case 1:
            for (int i = 0; i < length; i++) {
                if (strcmp(arr[i].matId, keyword) == 0) {
                    printf(GREEN "%-10s | %-20s | %-10s | %-8d | %-10s\n" RESET,
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
                toLowerStr(nameLower);

                if (strstr(nameLower, keyLower) != NULL) {
                    printf(GREEN "%-10s | %-20s | %-10s | %-8d | %-10s\n" RESET,
                           arr[i].matId, arr[i].name, arr[i].unit,
                           arr[i].qty, arr[i].status == 1 ? "Con SD" : "Het han");
                    found = 1;
                }
            }
            break;
        default:
            printf(RED "\nLua chon khong hop le!\n" RESET);
            return;
    }
    if (!found) {
        printf(YELLOW "\nKhong tim thay ket qua!\n" RESET);
    }
}while(choose != 2);
}

// F05: Phan trang
void listMat(Material *arr, int length) {
    if (length == 0) {
        printf(RED "\nDanh sach rong!\n" RESET);
        return;
    }

    int currentPage = 1;
    int matPerPage = 5;
    int totalPage = (length + matPerPage - 1) / matPerPage;
    int choice;
    int page;
	char choiceStr[10];
    do {
        int start = (currentPage - 1) * matPerPage;
        int end = start + matPerPage;
        if (end > length) end = length;

        printf(GRAY "\n============== DANH SACH VAT TU (Trang %d / %d) ==============\n" RESET,
               currentPage, totalPage);
        printf("%-10s %-20s %-10s %-10s %-10s\n",
               "ID", "Ten", "Don vi", "So luong", "Trang thai");
        printf("-------------------------------------------------------------\n");

        for (int i = start; i < end; i++) {
            printf("%-10s %-20s %-10s %-10d %-10s\n",
                   arr[i].matId, arr[i].name, arr[i].unit,
                   arr[i].qty, arr[i].status == 1 ? "Con SD" : "Het Han");
        }

        printf(GRAY "-------------------------------------------------------------\n" RESET);
        printf("1. Trang truoc\t2. Trang sau\t3. Den trang\t4. Thoat\n");
        choice = getMenuChoice("Nhap lua chon: ");

        switch (choice) {
            case 1:
                if (currentPage > 1) currentPage--;
                else printf(YELLOW "Ban dang o trang dau!\n" RESET);
                break;
            case 2:
                if (currentPage < totalPage) currentPage++;
                else printf(YELLOW "Ban dang o trang cuoi!\n" RESET);
                break;
            case 3:
                printf("Nhap so trang muon den (1-%d): ", totalPage);
                scanf("%d", &page);
                getchar();
                if (page >= 1 && page <= totalPage) currentPage = page;
                else printf(YELLOW "Trang khong ton tai!\n" RESET);
                break;
            case 4:
                printf(GREEN "Thoat phan trang!\n" RESET);
                break;
            default:
                printf(RED "Lua chon khong hop le!\n" RESET);
        }

    } while (choice != 4);
}

// F06: Sap xep vat tu
void sortMat(struct Material *arr, int length) {
    int choice;
    char choiceStr[10];
    while (1) {
        printf(GRAY "\n===== MENU SAP XEP =====" RESET);
        printf("\n1. Sap xep theo ten (A-Z, khong phan biet hoa thuong)\n");
        printf("2. Sap xep theo so luong (tang dan)\n");
        printf("3. Sap xep theo so luong (Giam dan)\n");
        printf("4. Thoat\n");
        choice = getMenuChoice("Nhap lua chon: ");

        switch (choice) {
            case 1: {
                for (int i = 0; i < length - 1; i++) {
                    for (int j = 0; j < length - i - 1; j++) {
                        char a[50], b[50];
                        strcpy(a, arr[j].name);
                        strcpy(b, arr[j+1].name);
                        toLowerStr(a);
                        toLowerStr(b);
                        if (strcmp(a, b) > 0) {
                            Material tmp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = tmp;
                        }
                    }
                }
                printf(GREEN "Da sap xep theo ten!\n" RESET);
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
                printf(GREEN "Da sap xep theo so luong tang dan!\n" RESET);
                break;
            }
            case 3: {
                for (int i = 0; i < length - 1; i++) {
                    for (int j = 0; j < length - i - 1; j++) {
                        if (arr[j].qty < arr[j + 1].qty) {
                            Material tmp = arr[j];
                            arr[j] = arr[j + 1];
                            arr[j + 1] = tmp;
                        }
                    }
                }
                printf(GREEN "Da sap xep theo So luong giam dan!\n" RESET);
                break;
            }
            case 4:
                printf(GREEN "Da thoat chuc nang sap xep!\n" RESET);
                return;
            default:
                printf(RED "Lua chon khong hop le, vui long chon 1->4!\n" RESET);
        }
    }
}

// F07: Giao dich xuat/nhap vat tu
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
	char choiceStr[10];
    getIdNumber(id, "Nhap ID vat tu can giao dich", sizeof(id));
    for (int i = 0; i < length; i++) {
        if (strcmp(arr[i].matId, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf(RED "Khong tim thay vat tu!\n" RESET);
        return;
    }

    if (arr[index].status == 0) {
        printf(YELLOW "Vat tu dang bi khoa, khong the giao dich!\n" RESET);
        return;
    }
	printf(GRAY "========== MENU NHAP/XUAT ==========" RESET);
    printf("\n1. Nhap kho (IN)");
    printf("\n2. Xuat kho (OUT)");
    choose = getMenuChoice("\nNhap lua chon: ");

    if (choose != 1 && choose != 2) {
        printf(RED "Lua chon khong hop le!\n" RESET);
        return;
    }

    amount = getInt("Nhap so luong");

    if (amount <= 0) {
        printf(RED "So luong phai > 0!\n" RESET);
        return;
    }

    if (choose == 2 && amount > arr[index].qty) {
        printf(YELLOW "Khong du so luong de xuat!\n" RESET);
        return;
    }

    if (*transLen >= MAX_TRANS) {
        printf(RED "Khong the luu them giao dich. Da dat gioi han (%d).\n" RESET, MAX_TRANS);
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

    printf(GREEN "\nGiao dich thanh cong!\n" RESET);
}

// F08: Lich su xuat/nhap
void listTransaction(Transaction *transArr, int transLen) {
    if (transLen == 0) {
        printf(RED "\nChua co giao dich nao!\n" RESET);
        return;
    }

    int transPerPage = 5;
    int totalPage = (transLen + transPerPage - 1) / transPerPage;
    int currentPage = 1;
    int choice, page;
	char choiceStr[10];
    do {
        int start = (currentPage - 1) * transPerPage;
        int end = start + transPerPage;
        if (end > transLen) end = transLen;

        printf(GRAY "\n========== LICH SU GIAO DICH (Trang %d / %d) ==========\n" RESET,
               currentPage, totalPage);
        printf("%-10s | %-10s | %-5s | %-6s | %-12s\n",
               "Ma GD", "Ma VT", "Loai", "So luong", "Ngay");
        printf("----------------------------------------------------\n");

        for (int i = start; i < end; i++) {
            printf("%-10s | %-10s | %-5s | %-6d | %-12s\n",
                   transArr[i].transId,
                   transArr[i].matId,
                   transArr[i].type,
                   transArr[i].amount,
                   transArr[i].date);
        }

        printf(GRAY "----------------------------------------------------\n" RESET);
        printf("1. Trang truoc\t2. Trang sau\t3. Den trang\t4. Thoat\n");
        choice = getMenuChoice("Nhap lua chon: ");

        switch (choice) {
            case 1:
                if (currentPage > 1) currentPage--;
                else printf(YELLOW "Ban dang o trang dau!\n" RESET);
                break;
            case 2:
                if (currentPage < totalPage) currentPage++;
                else printf(YELLOW "Ban dang o trang cuoi!\n" RESET);
                break;
            case 3:
                printf("Nhap so trang muon den (1-%d): ", totalPage);
                scanf("%d", &page);
                getchar();
                if (page >= 1 && page <= totalPage) currentPage = page;
                else printf(YELLOW "Trang khong ton tai!\n" RESET);
                break;
            case 4:
                printf(GREEN "Thoat lich su giao dich!\n" RESET);
                break;
            default:
                printf(RED "Lua chon khong hop le!\n" RESET);
        }

    } while (choice != 4);
}

// MAIN
int main() {
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int length = 10;
    Material arr[MAX_MAT];
    for(int i = 0; i < 10; i++){
        arr[i] = initList[i];
    }
    Transaction transArr[MAX_TRANS];
    int transLen = 0;
	char choiceStr[10];
    do {
        printf(GRAY "\n========== MENU QUAN LY VAT TU ==========" RESET);
        printf("\n1. Quan ly tai khoan\n2. Quan ly giao dich\n3. Thoat\n");
		choice1 = getMenuChoice("Nhap lua chon: ");
        switch(choice1) {
            case 1:
            	char choiceStr1[10];
                do {
                    printf(GRAY "\n========== MENU QUAN LY TAI KHOAN ==========" RESET);
                    printf("\n1. Them ma hang moi\n2. Cap nhat thong tin\n3. Quan ly trang thai (Khoa/Xoa)");
                    printf("\n4. Tra cuu\n5. Danh sach\n6. Sap xep danh sach\n7. Thoat\n");
                    choice2 = getMenuChoice("Nhap lua chon: ");
                    switch(choice2){
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
                            listMat(arr, length);
                            break;

                        case 6:
                            sortMat(arr, length);
							listMat(arr, length);
                            break;

                        case 7:
                            printf(GREEN "Thoat chuong trinh...\n" RESET);
                            break;

                        default:
                            printf(RED "Vui long chon 1-7!\n" RESET);
                    }
                } while(choice2 != 7);
                break;
            case 2:
                char choiceStr2[10];
				do {
					printf(GRAY "========== MENU QUAN LY GIAO DICH ==========" RESET);
				    printf("\n1. Giao dich xuat/nhap vat tu\n2. Lich su xuat/nhap\n3. Thoat\n");
				    choice3 = getMenuChoice("Nhap lua chon: ");
                    switch(choice3){
                        case 1:
                            transaction(arr, length, transArr, &transLen);
                            break;

                        case 2:
                            listTransaction(transArr, transLen);
                            break;

                        case 3:
                            printf(GREEN "\nThoat chuong trinh..." RESET);
                            break;

                        default:
                            printf(RED "Vui long chon 1-3!\n" RESET);
                    }
                } while(choice3 != 3);
                break;
            case 3:
                printf(GREEN "Thoat chuong trinh...\n" RESET);
                exit(0);
            default: printf(RED "Vui long chon 1-3!\n" RESET);
        }
    } while(choice1 != 3);

    return 0;
}
