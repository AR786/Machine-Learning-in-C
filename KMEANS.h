#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define size 10000


struct knode{
    int x;
    int y;
    struct knode *next;
};
typedef struct knode knode;
struct stacks{
    int a[size];
    int top;
};
typedef struct stacks stack;
struct kqueues{
    int a[2][size];
    int front;
    int rear;
};
typedef struct kqueues kqueue;
void kmean(knode*,int);
knode* inset_end(knode* start,int x,int y)
{
    knode* temp;
    knode* cur;
    temp=(knode*)malloc(sizeof(knode));
    temp->x=x;
    temp->y=y;
    temp->next=NULL;    
    if(start==NULL)
    {
        start=temp;
        return start;
    }
    else
    {
        cur=start;
        while(cur->next!=NULL)
        {
            cur=cur->next;
        }
        cur->next=temp;
        return start;
    }
}
int kdistance(int x1,int y1,int x2,int y2)
{
    int d;
    d=sqrt(pow((x1-x2),2)+pow((y1-y2),2));
    return d;
}
void kmean(knode*start,int k);
void kenqueue(kqueue* q,int x,int y)
{
    if(q->front==-1)
        printf("queue empty");
    if((q->rear+1)%size==q->front)
        printf("queue full");
    q->a[0][q->rear]=x;
    q->a[1][q->rear]=y;
}
void kdeque(kqueue *q,int*dex,int*dey)
{
    if(q->front=-1)
        printf("queue is empty");
    else if(q->rear=q->front)
    {

        *dex=q->a[0][q->front];
        *dey=q->a[1][q->front];
        q->front=-1;
        q->rear=-1;
        
    }
    else
    {
        *dex=q->a[0][q->front];
        *dey=q->a[1][q->front];
        q->front=(q->front+1)%size;
    }
}

void display(knode*start)
{
    knode*temp;
    if(start==NULL)
        printf("list empty");
    else
    {
        temp=start;
        while(temp!=NULL)
        {
          
            printf("x value is %d y value is %d\n",temp->x,temp->y);
              temp=temp->next;
        }
    }
}


void display_knode(knode*s)
{
    knode*temp;
    temp=s;
    
    if(s==NULL)
    {
        printf("empty");
    }
    else{
        while(temp!=NULL)
        {
            temp=temp->next;
            printf("%d x value %d y value",temp->x,temp->y);
        }
    }
}
void push(stack *s,int d)
{
    if(s->top==(size-1))
       printf("stack full");
    else
    {
        s->top++;
        s->a[s->top]=d;
    }
}
int pop(stack*s)
{
    int ele;
    if(s->top==-1)
        printf("stack empty");
    else
    {
        ele=s->a[s->top];
        s->top--;
    }
    return ele;
}
int** itterate(int **centroid,knode *start,int k)
{
    int i;
    //printf("inside itterate");
   int **centroidnew=(int **)malloc(2 * sizeof(int*));
for(i=0;i<2;i++)
    centroidnew[i]=(int*)malloc(k*sizeof(int*));
    knode*temp;
    knode* c[k];
    for(i=0;i<k;i++)
        c[i]=NULL;
    stack s[k];
    temp=start;
    int buf;
    for(i=0;i<k;i++)
    {
        while(temp!=NULL)
        {
           buf=kdistance(*(*(centroid+0)+i),*(*(centroid+1)+i),temp->x,temp->y);
            push(&s[i],buf);
          // printf("pushed %d in %d cluster\n ",buf,i);
            temp=temp->next;
         }
         temp=start;
    }
    temp=start;
    int min=10000000;
    int index;
    while(temp!=NULL)
    {
        min=100000;
        for(i=0;i<k;i++)
        {   
            buf=pop(&s[i]);
          //  printf("%d buf value\n",buf);
            if(buf<=min)
            {
                min=buf;
                index=i;
                //printf("min value is %d of cluster %d\n",buf,index);
            }
        }
    
        c[index]=inset_end(c[index],temp->x,temp->y);
     //  printf("inserted in %d\n",index);
        temp=temp->next;
    }
    int avgx;
    int avgy;
    int sumx;
    int sumy;
    int cnt;
    for(i=0;i<k;i++)
    {
        sumx=0;
        sumy=0;
        cnt=0;
        temp=c[i];
        
        while(temp!=NULL)
        {   //printf("%d value of cnt\n",cnt);
            cnt++;
            sumx=sumx+temp->x;
            sumy=sumy+temp->y;
            temp=temp->next;
        }
        if(cnt!=0)
            {
                avgx=sumx/cnt;
                avgy=sumy/cnt;
        
         *(*(centroidnew+0)+i)=avgx;
         *(*(centroidnew+1)+i)=avgy;
            }
            else
            {
               *(*(centroidnew+0)+i)=0;
         *(*(centroidnew+1)+i)=0;

            }
        //printf("updated centroids\n");
    }
    int j;
    for(i=0;i<2;i++)
    {
        for(j=0;j<k;j++)
        {
            if(*(*(centroid+i)+j)==*(*(centroidnew+i)+j))
                continue;
            else
                return centroidnew;
        }
    }
    printf("clusters found");
    for(i=0;i<k;i++)
        display(c[i]);
    exit;

}
void graph(knode*start,int cx,int cy)
{
        int x,y;
        int flag=0;
        knode*temp;
        temp=start;
        for(y=9;y>=0;y--)
        {
            printf("%d |",y);
            if(y==0)
            {
                for(x=0;x<10;x++)
                    printf("_\t");
                printf("\n");
                for(x=0;x<10;x++)
                    printf("%d\t",x);
            }
            for(x=0;x<=10;x++)
            {
                temp=start;
                if(x==cx&y==cy)
                    printf("$");
                while(temp!=NULL)
                {
                    if(temp->x==x&&temp->y==y)
                        {
                            flag=1;
                            if(x==0||y==0)
                                printf("\t\t");
                            else
                                printf("*");
                        }
                    temp=temp->next;
                }
                if(flag==1)
                    flag=0;
                else
                    printf("\t");
            }
            printf("\n");
        }
}
void kmean(knode*start,int k)
{
    int i;
   printf("inside kmean");
    int storek;
    storek=k;
   // int centroid[100][100];
   
  int **centroid=(int **)malloc(2 * sizeof(int*));
for(i=0;i<2;i++)
    centroid[i]=(int*)malloc(k*sizeof(int*));
    knode* temp;
    temp=start;
    kqueue q;
    q.front=-1;
    q.rear=-1;
    for(i=0;i<k;i++)
    {
        centroid[0][i]=temp->x;
        kenqueue(&q,temp->x,temp->y);
        centroid[1][i]=temp->y;
        temp=temp->next;
    
    }
    

    knode* c[k];
    
    for(i=0;i<k;i++)
        {
            c[i]=NULL;
           
        }
    stack s[k];
    temp=start;
    int buf;


    for(i=0;i<k;i++)
    {
        while(temp!=NULL)
        {
           
            buf=kdistance(centroid[0][i],centroid[1][i],temp->x,temp->y);
            push(&s[i],buf);
        //   printf("pushed %d in %d cluster\n ",buf,i);
            temp=temp->next;
         }
         temp=start;
    }
    temp=start;
    int min=10000000;
    int index;
    while(temp!=NULL)
    {
        min=100000;
        for(i=0;i<k;i++)
        {   
            buf=pop(&s[i]);
          //  printf("%d buf value\n",buf);
            if(buf<=min)
            {
                min=buf;
                index=i;
              //  printf("min value is %d of cluster %d\n",buf,index);
            }
        }
        
        c[index]=inset_end(c[index],temp->x,temp->y);
  //     printf("inserted in %d\n",index);
        temp=temp->next;
    }
    int avgx;
    int avgy;
    int sumx;
    int sumy;
    int cnt;
    for(i=0;i<k;i++)
    {
        sumx=0;
        sumy=0;
        cnt=0;
        temp=c[i];
        
        while(temp!=NULL)
        {   //printf("%d value of cnt\n",cnt);
            cnt++;
            sumx=sumx+temp->x;
            sumy=sumy+temp->y;
            temp=temp->next;
        }
        if(cnt!=0)
            {
                avgx=sumx/cnt;
                avgy=sumy/cnt;
            kenqueue(&q,avgx,avgy);
        centroid[0][i]=avgx;
         centroid[1][i]=avgy;
            }
            else
            {
               *(*(centroid+0)+i)=0;
         *(*(centroid+1)+i)=0;

            }
        //printf("updated centroids\n");
    }

    int maxitter;
    maxitter=0;
    while(maxitter<10000)
        {
            printf("itteration number %d\n",maxitter);
            centroid=itterate(centroid,start,k);
            maxitter++;
        }
    printf("process terminated");
    for(i=0;i<k;i++)
       {
           printf(" cluster %d\n",i);
        display(c[i]);
        graph(c[i],centroid[0][i],centroid[1][i]);
         printf(" centroid %d x and y is %d\n",centroid[0][i],centroid[1][i]);
       }

}

void kmeansc(int k)
{
       
    FILE *fp;//declaring file pointer
    knode*start=NULL;
    int datax;
    int datay;
    char ch;
    int x,y;
    int cnt=0;
    fp=fopen("./data.txt","r");//opening file in read mode
    if(fp==NULL)
        printf("error");
    while(ch!=EOF)
    {
       
        if(cnt%2==0)
           {
            fscanf(fp,"%d",&datax);
             x=datax;
             ch=fgetc(fp);         //moving cursor by one position
             cnt++;
           }
        else
            {
                 fscanf(fp,"%d",&datay);
                 y=datay;
                 ch=fgetc(fp);
                 cnt++;
                 start=inset_end(start,datax,datay);

            }        
    }
    display(start);
    kmean(start,k);
    }
