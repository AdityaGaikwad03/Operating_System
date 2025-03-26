//bankers algo
#include <stdio.h>
#define MAX 10
int n, m;
int Allocation[MAX][MAX], Max[MAX][MAX], Need[MAX][MAX], Available[MAX];
int Request[MAX], Finish[MAX], SafeSeq[MAX];

void acceptMatrix(int matrix[MAX][MAX], char *name) {
    printf("Enter %s Matrix (row by row):\n", name);
    for (int i = 0; i < n; i++) {
        printf("Enter resources for Process P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void acceptAvailable() {
    printf("Enter Available Resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &Available[i]);
    }
}


void calculateNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}

int safetyAlgorithm() {
    int Work[MAX], count = 0;
    for (int i = 0; i < m; i++) Work[i] = Available[i];
    for (int i = 0; i < n; i++) Finish[i] = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) break;
                }
                if (j == m) {
                    for (int k = 0; k < m; k++) Work[k] += Allocation[i][k];
                    SafeSeq[count++] = i;
                    Finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) return 0;
    }
    return 1;
}

void resourceRequest() {
    int process;
    printf("Enter Process Number (0-%d): ", n - 1);
    scanf("%d", &process);

    printf("Enter Request for Process P%d:\n", process);
    for (int i = 0; i < m; i++) {
        scanf("%d", &Request[i]);
    }
/*
    for (int i = 0; i < m; i++) {
        if (Request[i] > Need[process][i]) {
            printf("Error: Request exceeds maximum need.\n");
            return;
        }
        if (Request[i] > Available[i]) {
            printf("Resources not available, Process must wait.\n");
            return;
        }
    }
*/
    for (int i = 0; i < m; i++) {
        Available[i] -= Request[i];
        Allocation[process][i] += Request[i];
        Need[process][i] -= Request[i];
    }

    if (safetyAlgorithm()) {
        printf("Request can be granted. Safe Sequence: ");
        for (int i = 0; i < n; i++) printf("P%d ", SafeSeq[i]);
        printf("\n");
    } else {
        printf("Request cannot be granted. Reverting changes.\n");
        for (int i = 0; i < m; i++) {
            Available[i] += Request[i];
            Allocation[process][i] -= Request[i];
            Need[process][i] += Request[i];
        }
    }
}

void displayMatrices() {
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) printf("%d ", Allocation[i][j]);
        printf("\t");
        for (int j = 0; j < m; j++) printf("%d ", Max[i][j]);
        printf("\t");
        for (int j = 0; j < m; j++) printf("%d ", Need[i][j]);
        printf("\n");
    }
    printf("Available Resources: ");
    for (int i = 0; i < m; i++) printf("%d ", Available[i]);
    printf("\n");

    if (safetyAlgorithm()) {
        printf("System is Safe. Safe Sequence: ");
        for (int i = 0; i < n; i++) printf("P%d ", SafeSeq[i]);
        printf("\n");
    } else {
        printf("System is Unsafe!\n");
    }
}

int main() {
    int choice;

    printf("Enter number of processes and resource types: ");
    scanf("%d %d", &n, &m);

    acceptMatrix(Allocation, "Allocation");
    acceptMatrix(Max, "Max");
    calculateNeed();
    acceptAvailable();
    displayMatrices(); 

    while (1) {
        printf("\nMenu:\n");
        printf("1. Accept Request and Apply Banker's Algorithm\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                resourceRequest();
                break;
            case 0:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}


// sequential file aloccaton
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILES 100

struct File { char name[20]; int start, size; };

int *disk, n, fileCount = 0;
struct File files[MAX_FILES];

void initDisk() { for (int i = 0; i < n; i++) disk[i] = 0; }

int findSpace(int size) {
    for (int i = 0; i <= n - size; i++) {
        int found = 1;
        for (int j = 0; j < size; j++) if (disk[i + j]) { found = 0; break; }
        if (found) return i;
    }
    return -1;
}

void createFile() {
    if (fileCount >= MAX_FILES) return;
    struct File f;
    printf("Enter File Name: "); scanf("%s", f.name);
    printf("Enter File Size: "); scanf("%d", &f.size);

    if ((f.start = findSpace(f.size)) == -1) { printf("No space!\n"); return; }

    for (int i = 0; i < f.size; i++) disk[f.start + i] = 1;
    files[fileCount++] = f;
    printf("File '%s' stored at %d - %d\n", f.name, f.start, f.start + f.size - 1);
}

void deleteFile() {
    char name[20];
    printf("Delete: "); scanf("%s", name);
    for (int i = 0; i < fileCount; i++) {
        if (!strcmp(files[i].name, name)) {
            for (int j = 0; j < files[i].size; j++) disk[files[i].start + j] = 0;
            files[i] = files[--fileCount];
            printf("Deleted '%s'\n", name);
            return;
        }
    }
    printf("Not found!\n");
}

void displayDisk() {
    for (int i = 0; i < n; i++) printf("%d ", disk[i]);
    printf("\nFiles:\n");
    for (int i = 0; i < fileCount; i++)
        printf("File: %s, Start: %d, Size: %d blocks\n", files[i].name, files[i].start, files[i].start + files[i].size - 1);
}

int main() {
    printf("Blocks: "); scanf("%d", &n);
    disk = (int*)calloc(n, sizeof(int));

    int ch;
    while (1) {
        printf("\n1.Create 2.Delete 3.Display 0.Exit: ");
        scanf("%d", &ch);
        
        switch (ch) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: displayDisk(); break;
            case 0: free(disk); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}




// linked list file allocation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILES 100

struct Block { int index; struct Block *next; };
struct File { char name[20]; int size; struct Block *start; };

int n, fileCount = 0, *disk;
struct File files[MAX_FILES];

void initDisk() { for (int i = 0; i < n; i++) disk[i] = 0; }

struct Block* allocateBlocks(int size) {
    struct Block *head = NULL, *temp = NULL;
    for (int i = 0, count = 0; i < n && count < size; i++) {
        if (!disk[i]) {
            struct Block *newBlock = (struct Block*)malloc(sizeof(struct Block));
            newBlock->index = i;
            newBlock->next = NULL;
            disk[i] = 1;
            if (!head) head = newBlock;
            else temp->next = newBlock;
            temp = newBlock;
            count++;
        }
    }
    return (temp && temp->index - head->index + 1 == size) ? head : NULL;
}

void createFile() {
    if (fileCount >= MAX_FILES) return;
    struct File f;
    printf("Name: "); scanf("%s", f.name);
    printf("Size: "); scanf("%d", &f.size);

    f.start = allocateBlocks(f.size);
    if (!f.start) { printf("No space!\n"); return; }

    files[fileCount++] = f;
    printf("File '%s' allocated.\n", f.name);
}

void deleteFile() {
    char name[20];
    printf("Delete: "); scanf("%s", name);
    for (int i = 0; i < fileCount; i++) {
        if (!strcmp(files[i].name, name)) {
            struct Block *temp = files[i].start;
            while (temp) {
                disk[temp->index] = 0;
                struct Block *del = temp;
                temp = temp->next;
                free(del);
            }
            files[i] = files[--fileCount];
            printf("Deleted '%s'\n", name);
            return;
        }
    }
    printf("Not found!\n");
}

void displayDisk() {
    for (int i = 0; i < n; i++) printf("%d ", disk[i]);
    printf("\nFiles:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%s: ", files[i].name);
        struct Block *temp = files[i].start;
        while (temp) {
            printf("%d -> ", temp->index);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    printf("Blocks: "); scanf("%d", &n);
    disk = (int*)calloc(n, sizeof(int));

    int ch;
    while (1) {
        printf("\n1.Create 2.Delete 3.Display 0.Exit: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: displayDisk(); break;
            case 0: free(disk); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}





// indexed file code 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILES 100
#define MAX_BLOCKS 100

struct File {
    char name[20];
    int indexBlock;
    int size;
    int *blocks;
};

int *disk, n, fileCount = 0;
struct File files[MAX_FILES];

void initDisk() { for (int i = 0; i < n; i++) disk[i] = 0; }

int findFreeBlock() {
    for (int i = 0; i < n; i++)
        if (disk[i] == 0) return i;
    return -1;
}

void createFile() {
    if (fileCount >= MAX_FILES) return;
    struct File f;
    printf("Name: "); scanf("%s", f.name);
    printf("Size: "); scanf("%d", &f.size);

    if ((f.indexBlock = findFreeBlock()) == -1) { printf("No space!\n"); return; }

    disk[f.indexBlock] = 1;
    f.blocks = (int*)malloc(f.size * sizeof(int));

    for (int i = 0; i < f.size; i++) {
        if ((f.blocks[i] = findFreeBlock()) == -1) {
            printf("Not enough space!\n");
            disk[f.indexBlock] = 0;
            free(f.blocks);
            return;
        }
        disk[f.blocks[i]] = 1;
    }

    files[fileCount++] = f;
    printf("File '%s' stored. Index Block: %d\n", f.name, f.indexBlock);
}

void deleteFile() {
    char name[20];
    printf("Delete: "); scanf("%s", name);
    for (int i = 0; i < fileCount; i++) {
        if (!strcmp(files[i].name, name)) {
            disk[files[i].indexBlock] = 0;
            for (int j = 0; j < files[i].size; j++) disk[files[i].blocks[j]] = 0;
            free(files[i].blocks);
            files[i] = files[--fileCount];
            printf("Deleted '%s'\n", name);
            return;
        }
    }
    printf("Not found!\n");
}

void displayDisk() {
    for (int i = 0; i < n; i++) printf("%d ", disk[i]);
    printf("\nFiles:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%s (Index %d): ", files[i].name, files[i].indexBlock);
        for (int j = 0; j < files[i].size; j++) printf("%d ", files[i].blocks[j]);
        printf("\n");
    }
}

int main() {
    printf("Blocks: "); scanf("%d", &n);
    disk = (int*)calloc(n, sizeof(int));

    int ch;
    while (1) {
        printf("\n1.Create 2.Delete 3.Display 4.Exit: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: displayDisk(); break;
            case 4: free(disk); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}






//fcfs disk scheduling

#include<stdio.h>
#include<stdlib.h>
int main(){
	int i,j;
	int n,head,total_seek_time=0;

	printf("Enter no. of disk requests: ");
	scanf("%d",&n);
	int request[n];

	printf("Enter disk request queue: ");
	for( i=0;i<n;i++){
		scanf("%d",&request[i]);
        }

	printf("Enter initial head: ");
	scanf("%d",&head);

	printf("SEEK SEQUENCE: %d",head);
	for(i=0;i<n;i++){
		total_seek_time += abs(request[i]-head);
		head=request[i];
        	printf("->%d",head);
	}

	printf("\n\ntotal seek time: %d\n",total_seek_time);
	printf("Average seek time: %.2f\n",(float)total_seek_time/n);

}




//sstf disk scheduling

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  

int main() {
    int i, j;
    int n, head, total_seek_time = 0, temp, min_seek, min_idx;

    printf("Enter no. of disk requests: ");
    scanf("%d", &n);
    int request[n], visited[n];

    printf("Enter disk request queue: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
        visited[i] = 0; 
    }

    printf("Enter initial head: ");
    scanf("%d", &head);

    printf("SEEK SEQUENCE: %d", head);
    for (i = 0; i < n; i++) {
        min_seek = INT_MAX;
        min_idx = -1;
        for (j = 0; j < n; j++) {
            if (!visited[j]) { 
                temp = abs(request[j] - head);
                if (temp < min_seek) {
                    min_seek = temp;
                    min_idx = j;
                }
            }
        }

        total_seek_time += min_seek;
        head = request[min_idx];
        visited[min_idx] = 1; 
        printf(" -> %d", head);
    }

    printf("\n\nTotal seek time: %d\n", total_seek_time);
    printf("Average seek time: %.2f\n", (float)total_seek_time / n);

    return 0;
}




//scan disk scheduling

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, disk_size, direction, i, j, temp, total_seek_time = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);
    int request[n];

    printf("Enter request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &request[i]);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (request[i] > request[j]) {
                temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }
    int start = 0;
    while (start < n && request[start] < head) start++;

    printf("Seek sequence: %d", head);

    if (direction == 1) { 
        for (i = start; i < n; i++) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }
        total_seek_time += abs(disk_size - 1 - head);
        printf(" -> %d", disk_size - 1);
        head = disk_size - 1;

        for (i = start - 1; i >= 0; i--) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }
    } else {  
        for (i = start - 1; i >= 0; i--) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }
        total_seek_time += abs(head);
        printf(" -> 0");
        head = 0;

        for (i = start; i < n; i++) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal seek time: %d\n", total_seek_time);
    return 0;
}





//c- scan disk scheduling

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, disk_size, direction, i, j, temp, total_seek_time = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);
    int request[n];

    printf("Enter request queue: ");
    for (i = 0; i < n; i++) scanf("%d", &request[i]);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &direction);

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (request[i] > request[j]) {
                temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    int start = 0;
    while (start < n && request[start] < head) start++;

    printf("Seek sequence: %d", head);

    if (direction == 1) { 
        for (i = start; i < n; i++) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }

       if (head != disk_size - 1) {
            printf(" -> %d", disk_size - 1);
            total_seek_time += abs(disk_size - 1 - head);
        }

        head = 0;
        printf(" -> 0");

        for (i = 0; i < start; i++) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }
    } else { 
        for (i = start - 1; i >= 0; i--) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }

        if (head != 0) {
            printf(" -> 0");
            total_seek_time += abs(head);
        }

        head = disk_size - 1;
        printf(" -> %d", disk_size - 1);

        for (i = n - 1; i >= start; i--) {
            total_seek_time += abs(request[i] - head);
            head = request[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal seek time: %d\n", total_seek_time);
    return 0;
}





//mpi sum
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000
int main(int argc, char *argv[]) {
    int rank, size, sum = 0, total;
    int *data = NULL, *part;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int chunk = N / size;
    if (rank == 0) {
        data = malloc(N * sizeof(int));
        srand(time(0));
        for (int i = 0; i < N; i++) data[i] = rand() % 100;
    }
    part = malloc(chunk * sizeof(int));
    MPI_Scatter(data, chunk, MPI_INT, part, chunk, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < chunk; i++) sum += part[i];
    MPI_Reduce(&sum, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) printf("Sum: %d\n", total);
    free(data); free(part);
    MPI_Finalize();
}




//mpi min max

#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 1000
int main(int argc,char *argv[]){
    int r,s,lmin,lmax,gmin,gmax,*d=NULL,*p;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&r);
    MPI_Comm_size(MPI_COMM_WORLD,&s);
    int c=N/s;
    if(r==0){d=malloc(N*sizeof(int));srand(time(0));for(int i=0;i<N;i++)d[i]=rand()%1000;}
    p=malloc(c*sizeof(int));
    MPI_Scatter(d,c,MPI_INT,p,c,MPI_INT,0,MPI_COMM_WORLD);
    lmin=lmax=p[0];
    for(int i=1;i<c;i++){if(p[i]<lmin)lmin=p[i];if(p[i]>lmax)lmax=p[i];}
    MPI_Reduce(&lmin,&gmin,1,MPI_INT,MPI_MIN,0,MPI_COMM_WORLD);
    MPI_Reduce(&lmax,&gmax,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);
    if(r==0)printf("Min:%d\nMax:%d\n",gmin,gmax);
    free(d);free(p);
    MPI_Finalize();
}

