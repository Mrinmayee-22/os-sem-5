#include <stdio.h>
#include <stdlib.h>

// Function to check if a page is present in memory
int isPagePresent(int page, int frames[], int numFrames)
{
    for (int i = 0; i < numFrames; i++)
    {
        if (frames[i] == page)
        {
          return 1; // Page found
        }
    }
    return 0; // Page not found
}

// Function to display current state of frames
void displayFrames(int frames[], int numFrames)
{
    printf("Frames: ");
    for (int i = 0; i < numFrames; i++)
    {
        if (frames[i] == -1)
        {
            printf("[ ] ");
        }
        else
        {
            printf("[%d] ", frames[i]);
        }
    }
    printf("\n");
}

// FIFO Page Replacement Algorithm
void fifoPageReplacement(int pages[], int numPages, int numFrames)
{
    int frames[numFrames];
    int pageFaults = 0;
    int pageHits = 0;
    int front = 0; // Points to the oldest page (next to be replaced)

    // Initialize all frames to -1 (empty)
    for (int i = 0; i < numFrames; i++)
    {
        frames[i] = -1;
    }

    printf("\n=== FIFO Page Replacement Algorithm ===\n");
    printf("Number of Frames: %d\n", numFrames);
    printf("Reference String: ");
    for (int i = 0; i < numPages; i++)
    {
        printf("%d ", pages[i]);
    }
    printf("\n\n");

    printf("Step-by-step execution:\n");
    printf("%-10s %-15s %-10s\n", "Page", "Frames", "Status");
    printf("----------------------------------------\n");

    for (int i = 0; i < numPages; i++)
    {
        int currentPage = pages[i];
        printf("%-10d ", currentPage);

        if (isPagePresent(currentPage, frames, numFrames))
        {
            // Page hit
            pageHits++;
            displayFrames(frames, numFrames);
            printf("HIT\n");
        }
        else
        {
            // Page fault
            pageFaults++;
            frames[front] = currentPage;
            front = (front + 1) % numFrames; 
            displayFrames(frames, numFrames);
            printf("FAULT\n");
        }
    }

    // Display results
    printf("\n=== Results ===\n");
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
    printf("Page Fault Ratio: %.2f%%\n", ((float)pageFaults / numPages) * 100);
    printf("Page Hit Ratio: %.2f%%\n", ((float)pageHits / numPages) * 100);
}

int main()
{
    int numFrames, numPages;

    printf("=== FIFO Page Replacement Algorithm ===\n\n");

    // Get number of frames from user
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    if (numFrames <= 0)
    {
        printf("Error: Number of frames must be positive!\n");
        return 1;
    }

    // Get number of pages from user
    printf("Enter the number of pages in reference string: ");
    scanf("%d", &numPages);

    if (numPages <= 0)
    {
        printf("Error: Number of pages must be positive!\n");
        return 1;
    }

    // Allocate memory for pages array
    int *pages = (int *)malloc(numPages * sizeof(int));
    if (pages == NULL)
    {
        printf("Error: Memory allocation failed!\n");
        return 1;
    }

    // Get reference string from user
    printf("Enter the reference string (space-separated page numbers):\n");
    for (int i = 0; i < numPages; i++)
    {
        scanf("%d", &pages[i]);
        if (pages[i] < 0)
        {
            printf("Error: Page numbers must be non-negative!\n");
            free(pages);
            return 1;
        }
    }

    // Execute FIFO algorithm
    fifoPageReplacement(pages, numPages, numFrames);

    // Free allocated memory
    free(pages);

    printf("\nPress Enter to exit...");
    getchar(); // Consume newline
    getchar(); // Wait for user input

    return 0;
}
