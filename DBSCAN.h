#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct dnodes{
int x;
int v;
int c;
int y;
struct dnodes*next;
};
typedef struct dnodes dnode;
dnode*insertbegin(dnode*start,int x,int y)
{
    dnode*temp;
    temp=(dnode*)malloc(sizeof(dnode));
    temp->v=0;
    temp->x=x;
    temp->y=y;
    temp->c=999;
    temp->next=NULL;
    if(start==NULL)
        return temp;
    else
    {
        temp->next=start;
        return temp;
        }
}
float ddistance(int x1,int y1,int x2,int y2)
{
    float d;
    d=sqrt(pow((x1-x2),2)+pow((y1-y2),2));
    return d;
}
void dbscan(dnode*start,float radius,int tag)
{
    dnode*temp;
    temp=start;
    float d;
    
    while(temp!=NULL)
    {
        d=ddistance(start->x,start->y,temp->x,temp->y);
       // printf("ddistance d is %f\n",d);
        if(d<=radius&&temp->v!=1)
        {
            temp->v=1;
            temp->c=tag;
            
           // printf("%d tag in dbscan\n",tag);
            dbscan(temp,radius,tag);
        }
        temp=temp->next;
    }

}
void dgraph(dnode*start)
{
        int x,y;
        int flag=0;
        dnode*temp;
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
void ddisplay(dnode*start,int tag)
{
    dnode*temp;
    dnode*f[tag];
    temp=start;
    int i;
    for(i=0;i<=tag;i++)
        f[i]=NULL;
    for(i=tag;i>=0;i--)
    {
        temp=start;
        while(temp!=NULL)
        {
            if(temp->c==i)
                {
                    printf("%d x %d y %d cluster\n",temp->x,temp->y,i);
                    f[i]=insertbegin(f[i],temp->x,temp->y);
                }
            temp=temp->next;
        }
    }
    for(i=1;i<=tag;i++)
        dgraph(f[i]);
}
void dbs(dnode*start,float radius)
{
    
    
    
    dnode*temp;
    temp=start;
    int tag=0;
    while(temp!=NULL)
    {
        //printf("in while\n");
        if(temp->v!=1)
        {
            
           // printf("%d tag in db\n",tag);
            tag++;
            dbscan(temp,radius,tag);
        }
        temp=temp->next;
    }
  //  printf("%d tag to ddisplay\n",tag);
    ddisplay(start,tag);
    //temp=start;
    /*while(temp!=NULL)
    {
        printf("%d cluster %d visited \n",temp->c,temp->v);
        temp=temp->next;
    }*/
}
void dbscanc(float radius)
{
      FILE *fp;//declaring file pointer
    dnode*start=NULL;
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
             //printf("x value is %d\n",x);
             ch=fgetc(fp);         //moving cursor by one position
             cnt++;
           }
        else
            {
                 fscanf(fp,"%d",&datay);
                 y=datay;
              // printf("y value is %d\n",y);
                 ch=fgetc(fp);
                 cnt++;
                 start=insertbegin(start,datax,datay);

            }        
    }
  dbs(start, radius); 
    
}