#include <stdio.h>

int main() {
    int pages[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    int frames[10], freq[10], page_faults = 0, n;

    printf("Enter number of frames: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) frames[i] = -1, freq[i] = 0;

    for (int i = 0; i < 16; i++) {
        int found = 0;
        for (int j = 0; j < n; j++) {
            if (frames[j] == pages[i]) {
                freq[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            int pos = 0;
            for (int j = 1; j < n; j++) {
                if (freq[j] > freq[pos]) pos = j;
            }
            frames[pos] = pages[i];
            freq[pos] = 1;
            page_faults++;
        }
        printf("Accessing page %d: Frames: ", pages[i]);
        for (int j = 0; j < n; j++) {
            if (frames[j] == -1) printf("- ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("MFU: Total Page Faults = %d\n", page_faults);
    return 0;
}