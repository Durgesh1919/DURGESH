// *********write***********



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUF 1024

int main() {
    
    int fd, c = 0;
    char *myfifo1 = "myfifo1";
    int fd1;
    char *myfifo2 = "myfifo2";

    char buf1[MAX_BUF];

    mkfifo(myfifo1, 0777);
    mkfifo(myfifo2, 0777); // Create the second FIFO

    printf("Enter the Sentence (type '#' to end input):\n");
    fd = open(myfifo1, O_WRONLY);

    char str;

    while ((str = getchar()) != '#') {
        buf1[c++] = str;
    }

    buf1[c] = '\0';

    write(fd, buf1, c); // Write only the actual data, not the whole buffer
    close(fd);

    fd1 = open(myfifo2, O_RDONLY);
    ssize_t bytesRead = read(fd1, buf1, MAX_BUF);
    close(fd1);

    if (bytesRead > 0) {
        buf1[bytesRead] = '\0';
        printf("The contents of the file are as follows: %s\n", buf1);
    } else {
        printf("No data read from %s\n", myfifo2);
    }

    // unlink(myfifo1); // Unlink both FIFOs
    unlink(myfifo2);
    return 0;
}


















***********read*************






#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUF 1024

int main() {
    char *myfifo1 = "myfifo1";
    char buf[MAX_BUF];

    int words = 0, lines = 0, chars = 0;

    int fd = open(myfifo1, O_RDONLY); // Use O_RDONLY to read from the FIFO

    if (fd == -1) {
        perror("open");
        exit(1);
    }

    ssize_t bytesRead = read(fd, buf, MAX_BUF);
    close(fd);

    if (bytesRead == -1) {
        perror("read");
        exit(1);
    }

    // Null-terminate the buffer to treat it as a string
    buf[bytesRead] = '\0';

    printf("%s\n", buf);
    printf("Message Copied!\n");

    int i = 0;
    while (buf[i] != '\0') {
        // Check for newlines and increment line count
        if (buf[i] == '\n') {
            lines++;
        }

        // Check for word separation by space or newline
        if (buf[i] == ' ' || buf[i] == '\n') {
            words++;
        }

        i++;
    }

    // Char count is the total length of the message
    chars = i;

    printf("No. of Words: %d\n", words);
    printf("No. of Lines: %d\n", lines);
    printf("No. of Chars: %d\n", chars);

    FILE *fp = fopen("test.txt", "w");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    fprintf(fp, "%s\n", buf); // Write the received message to the file
    fprintf(fp, "No. of Words: %d\n", words);
    fprintf(fp, "No. of Lines: %d\n", lines);
    fprintf(fp, "No. of Chars: %d\n", chars);

    fclose(fp);

    return 0;
}
