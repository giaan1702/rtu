#include <iostream>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
// tao cau truc du lieu
using namespace std;
struct subject {
    char name[255];
    int id;
    int prerequisite_id[6];
    subject *prerequisite[6];
    subject *next;
    int chosen;
};


typedef struct subject *Subject;

//ham them ma so mon hoc tien quyet cho node
void prerequisite (char buffer[],Subject A){
    char *word = strtok(buffer,",");
    for(int i=0;i<=6;i++){
        if(word  != NULL) A->prerequisite_id[i] = atoi(word);
        else A->prerequisite_id[i]=0;
        word = strtok(NULL,",");
    }
}
//ham noi cac node lai thanh danh sach lien ket
Subject insert(Subject a, char n[255], int id, char buffer[]) {
    Subject b = (subject*)malloc(sizeof(struct subject));
    strcpy(b->name, n);
    b->id = id;
    prerequisite(buffer,b);
    a->next = b;
    return b;
}

// ham dem so dong trong file
int countLines(FILE *file) {
    int count = 0;
    char buffer[255];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }
    rewind(file);
    return count;
}
// ham gioi han so ki tu cua mot mang char o 35 ki tu (su dung de lam cho khi in ra ten mon hoc, chung duoc deu nhau)
void adjustName(char t[]) {
    t[strlen(t) - 1] = ' ';
    for (int i = strlen(t); i <= 36; i++) {
        t[i] = ' ';
    }
    t[36] = '\0';
}
// ham them dia chi mon hoc tien quyet cho cac node
void addPrerequisiteAddress(Subject A, int index) {
    Subject d = A;
    for (int i = 1; i <= index; i++) {
        int j=0;
        while(d->prerequisite_id[j]!=0){
            Subject currentNode = A;
            while (currentNode != NULL) {
                if (currentNode->id == d->prerequisite_id[j]) {
                    d->prerequisite[j] = currentNode;
                }
                currentNode = currentNode->next;
            }
            j++;
        }
       while(d->prerequisite_id==0){ d->prerequisite[j] = NULL;j++;}
        d = d->next;
    }
}
//ham dem so chu so
int countDigits(int number) {
    int count = 0;

    while (number != 0) {
        number = number / 10;
        count++;
    }

    return count;
}
// ham kiem tra tinh hop li cua danh sach lien ket
int validateSubjects(Subject A, int index, int ids[100],int requiredSubjects[100][6]) {
    int error = 0;
    Subject b = A;
    int check = 1;
    int point=1;
    
    for (int i = 1; i <= index; i++) {
        if (b->prerequisite_id[0] == 0) {
        	point ++;
            b = b->next;
            continue;
        }
        
        int k=6;
        b->prerequisite_id[6]=0;
        while(b->prerequisite_id[k]==0&&k!=-1) k--;
        while(b->prerequisite_id[k]&&k!=-1){
        	int count=0;
            for ( int j = 1; j <= index; j++) {
            	if (ids[j] != b->prerequisite_id[k]) {
				count++;
				}
			}
			if(count!=index) check=0;
			else check=1;
			if (check==1) {
            error = 1;
            printf("Error:the Subject Prerequisite was not found\n");
            printf("________________________________________________________________________________\n");
            printf("|    ID   |             Subject Name              |  Prerequisite Subject ID   |\n");
            printf("|_________|_______________________________________|____________________________|\n");
            if (b->prerequisite_id[0]==0) printf("|   %d   |%s   |                            |\n", b->id, b->name);
            if (b->prerequisite_id[0] != 0) {
            if (b->prerequisite_id[1] == 0){
			    printf("|   %d   |%s   | %d", b->id, b->name, b->prerequisite_id[0]);
			    for(int j=1;j<=28-1-countDigits(b->prerequisite_id[0]);j++) {printf(" ");}
                printf("|\n");
			}
               else{ 
                int count =0;
                printf("|   %d   |%s   | %d", b->id, b->name,b->prerequisite_id[0]);
                count=1+countDigits(b->prerequisite_id[0]);
                for (int j = 1; j < 6 && b->prerequisite_id[j] != 0; j++) {
                    printf(",%d", b->prerequisite_id[j]);
                    count=count+(countDigits(b->prerequisite_id[j])+1);
                }
                for(int j=1;j<=28-count;j++) {printf(" ");}
                printf("|\n");
            } 
            }
            printf("|_________|_______________________________________|____________________________|\n\n");
            printf("Please replace the Prerequisite Subject ID (%d) with the correct ID number (you can type '0' if there not have the Prerequisite Subject) :",b->prerequisite_id[k]);
            int replace;
            scanf("%d",&replace);
            system("cls");
            b->prerequisite_id[k]= replace;
            requiredSubjects[point][k]=replace;
            if(b->prerequisite_id[k]==0){ 
                for(int j=k;j<6;j++){
                    b->prerequisite_id[j]=b->prerequisite_id[j+1];
                    b->prerequisite_id[j+1]=0;
                    requiredSubjects[point][j]=requiredSubjects[point][j+1];
                }
                k--;
            }
            k++;
			}
            k--;
		}

        check = 1;
        k=6;
        while(b->prerequisite_id[k]==0&&k!=-1) k--;
        while(b->prerequisite_id[k]&&k!=-1){
        while (b->id <= b->prerequisite_id[k]) {
            printf("Error: the prerequisite Subject is Invalid\n");
            printf("________________________________________________________________________________\n");
            printf("|    ID   |             Subject Name              |  Prerequisite Subject ID   |\n");
            printf("|_________|_______________________________________|____________________________|\n");
            if (b->prerequisite_id[0] != 0) {
            if (b->prerequisite_id[1] == 0) {
			printf("|   %d   |%s   | %d", b->id, b->name, b->prerequisite_id[0]);
			for(int j=1;j<=28-1-countDigits(b->prerequisite_id[0]);j++) {printf(" ");}
            printf("|\n");
			}
               else{ 
                int count =0;
                printf("|   %d   |%s   | %d", b->id, b->name,b->prerequisite_id[0]);
                count=1+countDigits(b->prerequisite_id[0]);
                for (int j = 1; j < 6 && b->prerequisite_id[j] != 0; j++) {
                    printf(",%d", b->prerequisite_id[j]);
                    count=count+(countDigits(b->prerequisite_id[j])+1);
                }
                for(int j=1;j<=28-count;j++) {printf(" ");}
                printf("|\n");
            } 
            }
            printf("|_________|_______________________________________|____________________________|\n\n");
            error = 1;
            printf("Please replace the Prerequisite Subject ID (%d) with the correct ID number (you can type '0' if there not have the Prerequisite Subject) :",b->prerequisite_id[k]);
            int replace;
            scanf("%d",&replace);
            system("cls");
            b->prerequisite_id[k]= replace;
            requiredSubjects[point][k]=replace;
            if(b->prerequisite_id[k]==0){ 
                for(int j=k;j<6;j++){
                    b->prerequisite_id[j]=b->prerequisite_id[j+1];
                    b->prerequisite_id[j+1]=0;
                    requiredSubjects[point][j]=requiredSubjects[point][j+1];
                }
                k--;
            }
            k++;
        }
        k--;
		}
        b = b->next;
        point++;
        k=6;
    }
    if (error) return 0;
    else return 1;
}
//ham tim so lon nhat
int max(int ids[100], int x, int index) {
    int b = x * 100;
    for (int i = 1; i <= index; i++) if (ids[i] / 100 == x && ids[i] > b) b = ids[i];
    return b;
}
//ham sap xep be dan
void sortAscending(int h[100], int x) {
    int temp;
    for (int i = 1; i <= x; i++) {
        for (int j = i + 1; j <= x; j++) {
            if (h[j] < h[i]) {
                temp = h[i];
                h[i] = h[j];
                h[j] = temp;
            }
        }
    }
}
// ham xoa nhung ma so trung voi "temp" trong cac mang: ids,requiredSubjects.
void removeDuplicates(int requiredSubjects[100][6], int ids[100], int index, int temp) {
    for (int i = 1; i <= index; i++) {
        int k=0;
        while(requiredSubjects[i][k] == temp){ requiredSubjects[i][k] = 0;k++;}
        if (ids[i] == temp) ids[i] = 0;
    }
}
//ham chon mon cho lich hoc dua tren hoc ki va so mon ma nguoi dung da nhap.
void chooseSubjects(int total, int semesters, Subject A, int ids[100], int requiredSubjects[100][6], int index) {
    Subject d = A;
    int distribution[100];
    int chosen[100];

    for (int i = 1; i < semesters; i++) {
        distribution[i] = total / semesters;
    }
    distribution[semesters] = total - (semesters - 1) * (total / semesters);

    int chosenCount = 1;
    int tempCount = 1;
    for (int i = semesters; i > 0; i--) {
        while (distribution[i] > 0) {
            int random = rand() % (max(ids, i, index) - i * 100 + 1) + i * 100;
            for (int j = 1; j <= index; j++) {
                if (ids[j] == random) {
                    chosen[chosenCount] = ids[j];
                    ids[j] = 0;
                    chosenCount++;int p=0;
                    while(requiredSubjects[j][p] != 0) {
                        chosen[chosenCount] = requiredSubjects[j][p];
                        chosenCount++;
                        distribution[requiredSubjects[j][p] / 100]--;
                        removeDuplicates(requiredSubjects, ids, index, requiredSubjects[j][p]);
                        p++;
                        if (distribution[i] == 0) break;
                    }
                    random = rand() % (max(ids, i, index) - i * 100 + 1) + i * 100;                             
                    distribution[i]--;
                    if (distribution[i] == 0) break;
                    j = index;
                }
            }
            tempCount++;
            if (tempCount > 100) {
                for (int j = 1; j <= index; j++) {
                    if (ids[j] != 0) {
                        chosen[chosenCount] = ids[j];
                        removeDuplicates(requiredSubjects, ids, index, ids[j]);
                        distribution[i]--;
                        ids[j] = 0;
                        chosenCount++;
                        if (distribution[i] == 0) break;
                    }
                }
            }
        }
    }

    sortAscending(chosen, total);

    for (int i = 1; i <= total; i++) {
        d = A;
        while (d != NULL) {
            if (d->id == chosen[i]) {
                d->chosen = 1;
            }
            d = d->next;
        }
    }
}
// ham in lich hoc ra file Subjects.
void print(Subject A,int index){
	Subject c=A;
	FILE *file = fopen("Subjects.txt","w");
    fprintf(file,"________________________________________________________________________________\n");
    fprintf(file,"|    ID   |             Subject Name              |  Prerequisite Subject ID   |\n");
    fprintf(file,"|_________|_______________________________________|____________________________|\n");
	for (int i = 1; i <= index; i++) {
        if (c->chosen == 1) {
            if (c->prerequisite_id[0]==0) fprintf(file,"|   %d   |%s   |                            |\n", c->id, c->name);
            if (c->prerequisite_id[0] != 0) {
            if (c->prerequisite_id[1] == 0) fprintf(file,"|   %d   |%s   | %d                        |\n", c->id, c->name, c->prerequisite_id[0]);
               else{ 
                int count =0;
                fprintf(file,"|   %d   |%s   | %d", c->id, c->name,c->prerequisite_id[0]);
                for (int k = 1; k <= 6 && c->prerequisite_id[k] != 0; k++) {
                    fprintf(file,",%d", c->prerequisite_id[k]);count++;
                }
                for(int k=1;k<=28-(count+1)*4;k++) {fprintf(file," ");}
                fprintf(file,"|\n");
            } 
            }
            

        }
        c = c->next;
    }
     fprintf(file,"|_________|_______________________________________|____________________________|\n");
     fclose(file);
}
// ham chon hoc ki va chon so mon hoc.
int selectSemester(int ids[100], int index, int *semester, int *numSubjects) {
    int minSubjects[100]; minSubjects[0] = 0;
    int maxSubjects[100]; maxSubjects[0] = 0;
    int count = 0;
    printf(">>Enter the semester: ");
    scanf("%d", semester);
    while (*semester * 100 > ids[index] || *semester == 0) {
        printf("This semester does not exist, please re-enter: ");
        scanf("%d", semester);
    }
    for (int i = 1; i <= *semester; i++) {
        for (int j = 1; j <= index; j++) {
            if (ids[j] > i * 100 && ids[j] < i * 100 + 100) count++;
        }
        minSubjects[i] = maxSubjects[i - 1] + count / 2 + count % 2;
        maxSubjects[i] = maxSubjects[i - 1] + count;
        count = 0;
    }
    if (*semester == ids[index] / 100) {
        printf("This is the final semester, you need to complete all the remaining subjects \n");
        printf("The number of subjects you need to complete is %d\n", index);
        *numSubjects = index;
    }
    else {
        printf("The number of subjects in this semester is between %d and %d\n", minSubjects[*semester], maxSubjects[*semester]);
        printf("Plese enter the number of subjects you want to take: ");
        int n; scanf("%d", &n);
        while (n < minSubjects[*semester] || n > maxSubjects[*semester]) {
            printf("Invalid number of subjects, please re-enter: ");
            scanf("%d", &n);
        }
        *numSubjects = n;
    }
}
// ham hien thi lich hoc.
void showSchedule(Subject A, int index) {
    Subject c = A;
    printf("This is the suggested schedule:\n");
    for (int i = 1; i <= index; i++) {
        if (c->chosen == 1) {
        	if (i==1){ 
                printf("________________________________________________________________________________\n");
                printf("|    ID   |             Subject Name              |  Prerequisite Subject ID   |\n");
                printf("|_________|_______________________________________|____________________________|\n");
            }
            if (c->prerequisite_id[0]==0) printf("|   %d   |%s   |                            |\n", c->id, c->name);
            if (c->prerequisite_id[0] != 0) {
            if (c->prerequisite_id[1] == 0) printf("|   %d   |%s   | %d                        |\n", c->id, c->name, c->prerequisite_id[0]);
               else{ 
                int count =0;
                printf("|   %d   |%s   | %d", c->id, c->name,c->prerequisite_id[0]);
                for (int k = 1; k <= 6 && c->prerequisite_id[k] != 0; k++) {
                    printf(",%d", c->prerequisite_id[k]);count++;
                }
                for(int k=1;k<=28-(count+1)*4;k++) {printf(" ");}
                printf("|\n");
            } 
            }
            

        }
        c = c->next;
    }
     printf("|_________|_______________________________________|____________________________|\n");
}


int main() {
    //khai bao bien
    int index;
    char buffer[255];
    Subject A = (subject*)malloc(sizeof(struct subject));
    Subject c;
    int check_point=1;
   int temp1=0;
    

    while (1) {
        if(check_point==1){
            printf("Enter the file name: ");
            char filename[100];
            scanf("%s", &filename);
            FILE *file;
            file = fopen(filename, "r");
            if (file == NULL) {
                printf("Error: Can't open this file  \n");
                break;
            }

            index = countLines(file);

            fgets(buffer, sizeof(buffer), file);
            A->id = atoi(buffer);
            fgets(buffer, sizeof(buffer), file);
            adjustName(buffer);
            strcpy(A->name, buffer);
            fgets(buffer, sizeof(buffer), file);
            prerequisite(buffer,A);

            Subject p = (subject*)malloc(sizeof(struct subject));
            p = A;
            while (fgets(buffer, sizeof(buffer), file) != NULL) {
                int id = atoi(buffer);
                fgets(buffer, sizeof(buffer), file);
                adjustName(buffer);
                char name[255];
                strcpy(name, buffer);
                fgets(buffer, sizeof(buffer), file);
                p = insert(p, name, id, buffer);
            }
        }

        c = A;
        int ids[100];
        int requiredSubjects[100][6];
        for (int i = 1; i <= index / 3; i++) {
            c->chosen=0;
            ids[i] = c->id;
            int k=0;
            for(int k=0;k<=6;k++) requiredSubjects[i][k] = c->prerequisite_id[k];
            c = c->next;
        }
        validateSubjects(A, index / 3, ids,requiredSubjects);
        addPrerequisiteAddress(A, index / 3);
        if(temp1==0) printf("File data is correct\n\n");
        printf("============================================================\n");
        printf("                           MENU                             \n");
        printf("============================================================\n");
        printf("1.View reference schedule   ");
        printf("||       2. Exit \n");
        printf("============================================================\n");
        printf("Please enter your choice: ");                             
        scanf("%d", &temp1);
        while(temp1==1) {
            int semester;
            int numSubjects;
            selectSemester(ids, index / 3, &semester, &numSubjects);
            system("pause");
            system("cls");
            int temp;
            while(1){         
                chooseSubjects(numSubjects, semester, A, ids, requiredSubjects, index / 3);
                showSchedule(A, index / 3);
                system("pause");
                printf("============================================================\n");
                printf("1.View reference schedule   ");
                printf("||           2.Print \n");
                printf("                            ||                       \n");
                printf ("                         3.Exit to mainu  \n");
                printf("============================================================\n");
                printf("");
                scanf("%d", &temp);

                if (temp== 1) {
                    system("cls");
                    c = A;
                    for (int i = 1; i <= index / 3; i++) {
                        c->chosen=0;
                        ids[i] = c->id;
                        int k=0;
                        for(int k=0;k<=6;k++) requiredSubjects[i][k] = c->prerequisite_id[k];
                        c = c->next;
                    }
                }

                if(temp==2||temp==3) break;
            }
            check_point=0;
            if (temp==2){
                system("cls");
                printf("Print file is correct and file name is Subjects\n");
                system("pause");
                system("cls");
                print(A,index/3);
                c = A;
                for (int i = 1; i <= index / 3; i++) {
                    c->chosen=0;
                    ids[i] = c->id;
                    int k=0;
                    for(int k=0;k<=6;k++) requiredSubjects[i][k] = c->prerequisite_id[k];
                    c = c->next;
                }
                break;
			}
            if(temp==3) {
            temp1=temp;
            break;
            }  
        }
        if(temp1==3) {
            check_point=0;
            system("cls");
        }  
        if(temp1==2) {
            break;
        }  
    }
    return 0;
}

