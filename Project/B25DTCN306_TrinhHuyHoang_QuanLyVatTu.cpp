#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Material {
    char matId[10];
    char name[50];
    char unit[10];
    int qty;
    int status;
};

typedef struct Material Material;
//F01
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

void removeSpaces(char *str){
	int index = 0;
	while(str[0] == ' '){
		deleteCharactor(str, index);
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
void toLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

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

    do {        
        int start = (currentPage - 1) * matPerPage;
        int end = start + matPerPage;
        if (end > length) end = length;

        printf("\n=========== DANH SACH VAT TU (Trang %d / %d) ===========\n",
               currentPage, totalPage);
        printf("%-10s %-20s %-10s %-10s %-10s\n",
               "ID", "Ten", "Don vi", "So luong", "Trang thai");
        printf("-------------------------------------------------------------\n");

        for (int i = start; i < end; i++) {
            printf("%-10s %-20s %-10s %-10d %-10s\n",
                arr[i].matId, arr[i].name, arr[i].unit,
                arr[i].qty, arr[i].status == 1 ? "Con SD" : "Khoa");
        }

        printf("-------------------------------------------------------------\n");
        printf("1. Trang truoc\n");
        printf("2. Thoat\n");
        printf("3. Trang sau\n");
        printf("Lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                if (currentPage > 1)
                    currentPage--;
                else
                    printf("Ban dang o trang dau!\n");
                break;

            case 2:
                printf("Thoat phan trang!\n");
                break;

            case 3:
                if (currentPage < totalPage)
                    currentPage++;
                else
                    printf("Ban dang o trang cuoi!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }

    } while (choice != 2);
}

    

int main() {
	int choice = 0;
    int choice1 = 0;
    Material arr[100];
    int length = 0;
    int choice2 = 0;
    int choice3 = 0;

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
                        	printf("Chua lam den");
							break;
                        case 7:
                        	printf("Chua lam den");
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
                        	printf("Chua lam den");
							break;
                        case 2:
                        	printf("Chua lam den");
							break;
                        case 3:
                        	printf("Chua lam den");
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

