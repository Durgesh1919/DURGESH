#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    pid_t pid;
    char a[30];
    int len, count=0, i;
    printf("Enter the string:");
    scanf("%[^\n]s",a);
    len=strlen(a);
    pid=fork();
    if(pid>0){
        for(i=0;i<len;i++){
            if(a[i]=='a'|| a[i]=='e'|| a[i]=='i'|| a[i]=='o'|| a[i]=='u'|| a[i]=='A'|| a[i]=='E'|| a[i]=='I'|| a[i]=='O'|| a[i]=='U'){
                count++;
            }
        }
        printf("\n No of vowels: %d \n",count);
    }else{
        for(i=0;i<len;i++){
            if(a[i]==32 & a[i-1]!=32){
                count++;
            }
        }
        printf("\n No of Words: %d \n",count+1);
    }
    return 0;
}
