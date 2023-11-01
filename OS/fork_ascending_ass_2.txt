#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int asc()
{
	int i,a[10],k,temp,n;
	printf("\nEnter the no of Array elements");
	scanf("%d",&n);

	printf("\nEnter the Array Elements");
	
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=0;i<n;i++)
	{
		for(k=0;k<n-1;k++)
		{
			if(a[i]<a[k])
			{
			 temp=a[k];
			 a[k]=a[i];
			 a[i]=temp;
			}
		}

	}
printf("\nThe Sorted array in ascending order is :\n");
for(i=0;i<n;i++)
{
	printf(" %d ",a[i]);
}
return 0;
}

int dsc()
{
        int i,a[10],k,temp,n;
        printf("\nEnter the no of Array elements\n");
        scanf("%d",&n);

        printf("\nEnter the Array Elements\n");

        for(i=0;i<n;i++)
        {
                scanf("%d",&a[i]);
        }
        for(i=0;i<n;i++)
        {
                for(k=0;k<n-1;k++)
                {
                        if(a[i]>a[k])
                        {
                         temp=a[k];
                         a[k]=a[i];
                         a[i]=temp;
                        }
                }

        }
printf("\nThe Sorted array in descending order is : \n");
for(i=0;i<n;i++)
{
	printf(" %d ",a[i]);
}
return 0;
}

int main()
{
	int pid;
	pid=fork();
	if(pid<0)
	{
		printf("\nInvalid Process");
	}
	else if(pid==0)
	{
		printf("Child Process");
		printf("Child Pid : %d", getpid());
		wait(NULL);
		// asc();
		execlp("p.out","a3.c",asc(),(char*)0);
	}
	else if(pid>0)
	{
		printf("Parent Process");
		printf("\nParent Pid = %d",getpid());
		wait(NULL);
		dsc();
	}
}
