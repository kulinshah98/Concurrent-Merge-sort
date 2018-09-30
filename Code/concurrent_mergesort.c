#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void merge(int a[],int left,int mid,int right)
{
  int n1=mid-left+1,n2=right-mid,i,j,k;
  int l[n1+3],r[n2+3];
  for(i=0;i<n1;i++)
  {
    l[i]=a[left+i];
  }
  for(i=0;i<n2;i++)
  {
    r[i]=a[mid+i+1];
  }
  i=0;
  j=0;
  k=left;
  while(i<n1 && j<n2)
  {
    if(l[i]<r[j])
    {
      a[k++]=l[i++];
    }
    else
    {
      a[k++]=r[j++];
    }
  }
  while(i<n1)
  {
    a[k++]=l[i++];
  }
  while (j<n2)
  {
    a[k++]=r[j++];
  }
}

void mergesort(int a[],int l,int r)
{
  int m=(l+r)/2,status;
  int lc,rc;
  if(l>=r)
  {
    return;
  }
  lc=fork();
  if(lc<0)
  {
    perror("Error in fork\n");
    exit(1);
  }
  else if(lc==0)
  {
    mergesort(a,l,m);
    exit(0);
  }
  else
  {
    rc=fork();
    if(rc<0)
    {
      perror("Error in fork process\n");
      exit(1);
    }
    else if(rc==0)
    {
      mergesort(a,m+1,r);
      exit(0);
    }
  }
  waitpid(lc,&status,0);
  waitpid(rc,&status,0);
  merge(a,l,m,r);
}

int main()
{
  key_t k;
  int n,a[10005],i,id,mat_id;
  int *shm_array;
  scanf("%d",&n);
  for(i=0;i<n;i++)
  {
    scanf("%d",&a[i]);
  }
  k = IPC_PRIVATE;
  id = shmget(k,n*sizeof(int),IPC_CREAT | 0666);
  if(id<0)
  {
    printf("Error in shmget\n");
    exit(1);
  }
  shm_array = shmat(id,NULL,0);
  if(mat_id<0)
  {
    printf("Error in shmat\n");
    exit(1);
  }
  for(i=0;i<n;i++)
  {
    shm_array[i]=a[i];
  }
  mergesort(shm_array,0,n-1);
  for(i=0;i<n;i++)
  {
    printf("%d ",shm_array[i]);
  }
  printf("\n");
  if (shmdt(shm_array) == -1)
  {
		perror("Error in shmdt");
		exit(1);
	}
	if (shmctl(id, IPC_RMID, NULL) == -1)
  {
		perror("Error in shmctl");
		exit(1);
	}
  return 0;
}
