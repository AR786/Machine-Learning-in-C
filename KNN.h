#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define size 10000


struct knnode{
    int x;
    int y;
    int tag;
    struct knnode *next;
};
typedef struct knnode knnode;
struct queues{
    int a[2][size];
    int front;
    int rear;
};
typedef struct queues queue;
struct kstacks{
    int a[size];
    int top;
};
typedef struct kstacks kstack;
void knn_kmean(knnode*,int,int,int,int);
void kgraph(knnode*start,int cx,int cy)
{
        int x,y;
        int flag=0;
        knnode*temp;
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
knnode* kinset_end(knnode* start,int x,int y)
{
    knnode* temp;
    knnode* cur;
    temp=(knnode*)malloc(sizeof(knnode));
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
int knn_distance(int x1,int y1,int x2,int y2)
{
    int d;
    d=sqrt(pow((x1-x2),2)+pow((y1-y2),2));
    return d;
}
void knn_kmean(knnode*start,int k,int,int,int);
void knn_display(knnode*start)
{
    knnode*temp;
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
void enqueue(queue* q,int x,int y)
{
    if(q->front==-1)
        printf("queue empty");
    if((q->rear+1)%size==q->front)
        printf("queue full");
    q->a[0][q->rear]=x;
    q->a[1][q->rear]=y;
}
void deque(queue *q,int*dex,int*dey)
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

void knn_display_knnode(knnode*s)
{
    knnode*temp;
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
void knn_push(kstack *s,int d)
{
    if(s->top==(size-1))
       printf("kstack full");
    else
    {
        s->top++;
        s->a[s->top]=d;
    }
}
int knn_pop(kstack*s)
{
    int ele;
    if(s->top==-1)
        printf("kstack empty");
    else
    {
        ele=s->a[s->top];
        s->top--;
    }
    return ele;
}
int** knn_itterate(int **centroid,knnode *start,int k)
{
    int i;
    //printf("inside knn_itterate");
   int **centroidnew=(int **)malloc(2 * sizeof(int*));
for(i=0;i<2;i++)
    centroidnew[i]=(int*)malloc(k*sizeof(int*));
    knnode*temp;
    knnode* c[k];
    for(i=0;i<k;i++)
        c[i]=NULL;
    kstack s[k];
    temp=start;
    int buf;
    for(i=0;i<k;i++)
    {
        while(temp!=NULL)
        {
           buf=knn_distance(*(*(centroid+0)+i),*(*(centroid+1)+i),temp->x,temp->y);
            knn_push(&s[i],buf);
          // printf("knn_pushed %d in %d cluster\n ",buf,i);
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
            buf=knn_pop(&s[i]);
          //  printf("%d buf value\n",buf);
            if(buf<=min)
            {
                min=buf;
                index=i;
                //printf("min value is %d of cluster %d\n",buf,index);
            }
        }
        c[index]=kinset_end(c[index],temp->x,temp->y);
     //  printf("inserted in %d\n",index);
        temp->tag=index;
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
        knn_display(c[i]);
    exit;

}
void knn_kmean(knnode*start,int k,int kx,int ky,int kk)
{
    int i;
   printf("inside knn_kmean");
    int storek;
    storek=k;
    int **centroid=(int **)malloc(2 * sizeof(int*));
for(i=0;i<2;i++)
    centroid[i]=(int*)malloc(k*sizeof(int*));
    knnode* temp;
    temp=start;
    queue q;
    q.front=-1;
    q.rear=-1;
    for(i=0;i<k;i++)
    {
        centroid[0][i]=temp->x;
        enqueue(&q,temp->x,temp->y);
        centroid[1][i]=temp->y;
        temp=temp->next;
    //  printf("enter centroid x and y\n");
      //  scanf("%d",&centroid[0][i]);
       // scanf("%d",&centroid[1][i]);
    }
    

    knnode* c[k];
    for(i=0;i<k;i++)
        c[i]=NULL;
    kstack s[k];
    temp=start;
    int buf;
    for(i=0;i<k;i++)
    {
        while(temp!=NULL)
        {
           
            buf=knn_distance(centroid[0][i],centroid[1][i],temp->x,temp->y);
            knn_push(&s[i],buf);
        //   printf("knn_pushed %d in %d cluster\n ",buf,i);
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
            buf=knn_pop(&s[i]);
          //  printf("%d buf value\n",buf);
            if(buf<=min)
            {
                min=buf;
                index=i;
              //  printf("min value is %d of cluster %d\n",buf,index);
            }
        }
        c[index]=kinset_end(c[index],temp->x,temp->y);
  //     printf("inserted in %d\n",index);
        temp->tag=index;
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
         enqueue(&q,avgx,avgy);
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
    while(maxitter<100000)
        {
            //printf("itteration number %d\n",maxitter);
            centroid=knn_itterate(centroid,start,k);
            maxitter++;
        }
    printf("process terminated");
    for(i=0;i<k;i++)
       {
           printf(" cluster %d\n",i);
        knn_display(c[i]);
	kgraph(c[i],centroid[0][i],centroid[1][i]);
         printf(" centroid %d x and y is %d\n",centroid[0][i],centroid[1][i]);
       }
       

}
knnode*delete_key(knnode*start,int key)
{
    knnode*temp;
    knnode*prev;
    temp=start;
    prev=start;
    temp=temp->next;
    if(start==NULL)
        printf("list empty\n");
    else if(start->y==key)
        {
            start=temp;
            return start;
        }
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->y==key)
                {  
                    prev->next=temp->next;
                    return start;
                }
            else
            {
                prev=temp;
                temp=temp->next;
            }
            
        }
        if(temp->y==key)
        {
            prev->next=NULL;
            return start;
        }
        printf("key not found and key is %d\n",key);
        return start;
    }
}
int search_pos(knnode*start,int pos)
{
    knnode*temp;
    int cnt=0;
    temp=start;
    while(temp!=NULL)
    {
        if(cnt==pos)
        {
            return temp->tag;
        }
        else
        {
            cnt++;
            temp=temp->next;
        }
    }
}
void knn(int x,int y,knnode*start,int kk,int k)
{
    int buf;
    int cnt=0;
    knnode*temp;
    temp=start;
    knnode*d;
    d=NULL;
    int index=0;
    while(temp!=NULL)
    {
        //printf("inserted index %d\n",index);
        d=kinset_end(d,knn_distance(x,y,temp->x,temp->y),index);
        index++;
        temp=temp->next;
    }
    int indices[kk];
    int min;
    int count;
    int j;
    j=0;
    int secret;
   // printf("%d\n",d->y);
    for(count=0;count<kk;count++)
    {
        temp=d;
        min=10000;
        while(temp!=NULL)
        {
            if(temp->x<min)
            {
                min=temp->x;
                secret=temp->y;
                temp=temp->next;
            }
            else
                temp=temp->next;;
        }
        indices[j]=secret;
        j++;
        d=delete_key(d,secret);
    }
    int l;
    kstack final[k];
    for(l=0;l<k;l++)
        final[l].top=-1;
    for(l=0;l<j;l++)
    {
        secret=search_pos(start,indices[l]);
       knn_push(&(final[secret]),1);
    }
    int max=-1;
    int ans;
    for(j=0;j<k;j++)
    {
        if(final[j].top>max)
            ans=j;
        else
            continue;
    }
    printf("given point belongs to %d cluster",ans);
}


void knnc(int k,int kx,int ky,int kk)
{
    
    FILE *fp;
    knnode*start=NULL;
    int datax;
    int datay;
    char ch;
    int x,y;
    int cnt=0;
    fp=fopen("./data.txt","r");
    if(fp==NULL)
        printf("error");
    while(ch!=EOF)
    {
       
        if(cnt%2==0)
           {
            fscanf(fp,"%d",&datax);
             x=datax;
             //printf("x value is %d\n",x);
             ch=fgetc(fp);
             cnt++;
           }
        else
            {
                 fscanf(fp,"%d",&datay);
                 y=datay;
               //  printf("y value is %d\n",y);
                 ch=fgetc(fp);
                 cnt++;
                 start=kinset_end(start,datax,datay);

            }        
    }
    
    knn_kmean(start,k,kx,ky,kk);
    knn(kx,ky,start,kk,k);
    
}
