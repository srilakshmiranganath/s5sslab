#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_BLOCKS 1000

typedef struct {
  char name[30];
  int startBlock;
  int length;
} File;

typedef struct {
  char name[30];
  int fcount;
  File files[MAX_FILES];
} Directory;

Directory directories[MAX_FILES];
int numDirectories = 0;

void createDirectory(char *name) {
  if (numDirectories == MAX_FILES) {
    printf("Error: Maximum number of directories reached.\n");
    return;
  }

  strcpy(directories[numDirectories].name, name);
  directories[numDirectories].fcount = 0;
  numDirectories++;
}

void addFile(char *dirname, char *filename, int startBlock, int length) {
  int dirIndex = -1;
  for (int i = 0; i < numDirectories; i++) {
    if (strcmp(directories[i].name, dirname) == 0) {
      dirIndex = i;
      break;
    }
  }

  if (dirIndex == -1) {
    printf("Error: Directory '%s' does not exist.\n", dirname);
    return;
  }

  if (directories[dirIndex].fcount == MAX_FILES) {
    printf("Error: Directory '%s' is full.\n", dirname);
    return;
  }

  strcpy(directories[dirIndex].files[directories[dirIndex].fcount].name, filename);
  directories[dirIndex].files[directories[dirIndex].fcount].startBlock = startBlock;
  directories[dirIndex].files[directories[dirIndex].fcount].length = length;
  directories[dirIndex].fcount++;
}

void listFiles(char *dirname) {
  int dirIndex = -1;
  for (int i = 0; i < numDirectories; i++) {
    if (strcmp(directories[i].name, dirname) == 0) {
      dirIndex = i;
      break;
    }
  }

  if (dirIndex == -1) {
    printf("Error: Directory '%s' does not exist.\n", dirname);
    return;
  }

  printf("Files in directory '%s':\n", dirname);
  for (int i = 0; i < directories[dirIndex].fcount; i++) {
    printf("%s\n", directories[dirIndex].files[i].name);
  }
}

int main() {
  printf("Hierarchical File Allocation System\n");

  char dirname[30], filename[30];
  int startBlock, length;

  while (1) {
    printf("\nMenu:\n");
    printf("1. Create Directory\n");
    printf("2. Add File\n");
    printf("3. List Files\n");
    printf("4. Exit\n");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        printf("Enter directory name: ");
        scanf("%s", dirname);
        createDirectory(dirname);
        break;

      case 2:
        printf("Enter directory name: ");
        scanf("%s", dirname);
        printf("Enter file name: ");
        scanf("%s", filename);
        printf("Enter start block: ");
        scanf("%d", &startBlock);
                printf("Enter length: ");
        scanf("%d", &length);

        addFile(dirname, filename, startBlock, length);
        break;

      case 3:
        printf("Enter directory name: ");
        scanf("%s", dirname);
        listFiles(dirname);
        break;

      case 4:
        printf("Exiting...\n");
        exit(0);

      default:
        printf("Invalid choice. Please enter a valid option.\n");
    }
  }

  return 0;
}
