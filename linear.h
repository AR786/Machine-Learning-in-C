#include<stdio.h>
#include<math.h>
#include<stdlib.h>
struct lnode{
    float x;
    float y;
    struct lnode*next;
};
typedef struct lnode lnode;
lnode*linsertbegin(lnode*start,float x,float y)
{
    lnode*temp;
    temp=(lnode*)malloc(sizeof(lnode));
    temp->x=x;
    temp->y=y;
    temp->next=NULL;
    if(start==NULL)
        return temp;
    else{
        temp->next=start;
        start=temp;
        return start;
        }
}
float err(lnode*start,float m)
{
    lnode*temp=start;
    float sum=0.0;
   // printf("%f sum",sum);
    while(temp!=NULL)
    {
        sum=(float)sum+pow((temp->y-(m*temp->x)),2);
       // printf("%f sum\n",sum);
        temp=temp->next;
    }
   // printf("%lf e\n",sum);
    return sum;
}
float descent(lnode*start)
{
    float x,y,yp,e,ep,g,m,a;
    m=0;
    a=0.000001;
    ep=10000;
    int ef=0;
    int flag=1;
    while(1)
    {
        
        printf("itterating\n");
        e=err(start,m);
        if(e<=1)
            break;
        while(e>ep)
        {
           // printf("in inner while");
            if(flag==1)
            {
                flag=0;
                m=m-e*a;
            }
            if(flag==0)
            {
                flag=1;
                m=m+e*a;
            }
            ef++;
            e=err(start,m);
            if(ef>1000)
                return m;
        }
        if(flag==0)
            m=m-e*a;
        if(flag==1)
            m=m+e*a;
     //   if(ef>1000)
       //     break;
       // printf("%f e %f ep\n",e,ep);
        //printf("%f m\n",m);
        ep=e;
    }
   // printf("%f ep %f e\n",ep,e);
   // return m;
    
}
void lgraph(lnode*start)
{
        int x,y;
        int flag=0;
        lnode*temp;
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
                            if(x==0)
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
void gl(float m,int b)
{
    int x,y;
    int yp;
    int flag=0;
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
            yp=(int)(m*x+b);
            if(yp==y&&y!=0)
                printf("*");
            if(flag==1)
                flag=0;
            else
                printf("\t");
        }
        printf("\n");
    }
}
void lr(lnode*start,int b,int xi)
{
    //lgraph(start);
    float m;float mi;
    mi=descent(start);
    m=(int)mi;
    float yp;
    yp=(int)m*xi+b;
    printf("predicted y value is %f\n",mi*xi+b);
    lgraph(start);
    gl(mi,b);
}
void linearc(int b,int xi)
{
     
    FILE *fp;//declaring file pointer
    lnode*start=NULL;
    float datax;
    float datay;
    char ch;
    float x,y;
    int cnt=0;
    fp=fopen("./data.txt","r");//opening file in read mode
    if(fp==NULL)
        printf("error");
    while(ch!=EOF)
    {
       
        if(cnt%2==0)
           {
            fscanf(fp,"%f",&datax);
             x=datax;
             printf("x value is %f\n",x);
             ch=fgetc(fp);         //moving cursor by one position
             cnt++;
           }
        else
            {
                 fscanf(fp,"%f",&datay);
                 y=datay;
               printf("y value is %f\n",y);
                 ch=fgetc(fp);
                 cnt++;
                 start=linsertbegin(start,datax,datay);

            }        
    }
    
    lr(start,b,xi);
}
