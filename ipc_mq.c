#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

struct message
{
    long type;
    char text[100];
};


int main () {

    struct message msg;
    int msgid;
    pid_t pid;

    msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);

    pid = fork();

    if(pid > 0) {
        // parent process
        char str[100];
        printf("Enter the string: ");
        scanf("%s", str);

        strcpy(msg.text, str);

        // send the string into message queue
        msg.type = 1;
        msgsnd(msgid, &msg, sizeof(msg.text), 0);

        //recieve the reversed string from child process
        msgrcv(msgid, &msg, sizeof(msg.text), 2, 0);

        // compare
        if(strcmp(msg.text, str) == 0) {
            printf("Palindrome..\n");
        } else {
            printf("Not Palindrome..\n");
        }

    } else if(pid == 0) {
        // child process
        char temp[100];
        //recieve the message from the parent process
        msgrcv(msgid, &msg, sizeof(msg.text), 1, 0);
        strcpy(temp, msg.text);

        //reverse the string;
        int len = strlen(temp);
        for(int i=0; i<len/2; i++) {
            char c = temp[i];
            temp[i] = temp[len - i - 1];
            temp[len - i - 1] = c;
        }

        // send the reversed string back to message queue
        strcpy(msg.text, temp);
        msg.type = 2;
        msgsnd(msgid, &msg, sizeof(msg.text), 0);

    } else {
        printf("Fork Failed\n");
    }

    return 0;
}