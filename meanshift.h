#include<stdio.h>
#include<stdlib.h>
#include<math.h>


typedef struct Node{
	float x,y;
	struct Node* next;
}node;

node* delet(node* start){
	if(start== NULL){
		return start;
	}
	else{
		node* temp= start;
		
		while(temp->next!=NULL){
			node* temp1;
			temp1= temp;
			temp= temp->next;
			free(temp1);}
			
			free(temp);
			return NULL;
			
		}
	}


node* insert_uni(float a,float b,node* start){
	if(start==NULL){
		start= (node*)malloc(sizeof(node));
		start->x= a;start->y=b;
		start->next= NULL;
		return start;
	}
	else{
		
		node* temp= start;
		node* prev= temp;
		
		while(temp!=NULL){
			if(temp->x==a && temp->y==b){
				return start;
			}
		    else if(a== temp->x){
		    	if(b < temp->y){
		    		node* temp1= (node*)malloc(sizeof(node));
		    		temp1->x=a;temp1->y=b;
		    		if(temp==start){
		    			temp1->next=start;
		    		 start= temp1;
		    			
					}
					else{
					
		    		temp1->next=prev->next;
					prev->next= temp1; }
					return start;
				}
				else{
					prev= temp;
					temp= temp->next;
					
				}
			}
			else  if(a<temp->x){
				node* temp1= (node*)malloc(sizeof(node));
		    		temp1->x=a;temp1->y=b;
		    		if(temp==start){
		    			temp1->next= start;
		    			start= temp1;
		    			
					}
					else{
					
		    		temp1->next=prev->next;
					prev->next= temp1; }
					return start;
			}
			else{
				prev= temp;
					temp= temp->next;
			}
		}
		if(temp== NULL){
			node* temp1= (node*)malloc(sizeof(node));
		    		temp1->x=a;temp1->y=b;
		    		temp1->next= NULL;
		    		prev->next= temp1;
		}
		return start;
	}
	
}

node* insert(node* start,float a,float b){
	if(start== NULL){
		start= (node*)malloc(sizeof(node));
		start->x= a;start->y=b;
		start->next= NULL;
		return start;
	}
	else{
		node* temp= start;
		while(temp->next!=NULL){
			temp= temp->next;
		}
		node* temp1= (node*)malloc(sizeof(node));
		temp1->x= a;temp1->y=b;
		temp1->next= NULL;
		temp->next= temp1;
		return start;
	}
}

int compare(node* f,node* s){
	node* temp= f;node* temp1= s;
	while(temp!= NULL && temp1!= NULL){
		if(temp1->x!= temp->x || temp1->y!= temp->y){
			return 0;
		} temp= temp->next; temp1= temp1->next;
	}
	return 1;
}

float euclid(float a,float b,float c,float d){
	
	return sqrt(pow((abs(a-c)),2)+pow((abs(b-d)),2));
}

node* find(float a, float b,node* start,node* ne,float z){
	node* temp= start;
	while(temp!= NULL){
		float distance= euclid(a,b,temp->x,temp->y);
		if(distance<= z){
			ne= insert(ne,temp->x,temp->y);
		} temp= temp->next;
	}
	return ne;
}

float averagex(node* start){
	float s=0;int t= 0;
	node* temp= start;
	while(temp!= NULL){
		s= s+ temp->x;
		t++;
		temp= temp->next;
	}
	return s/t;
	
}

float averagey(node* start){
	float s=0;int t=0;
	node* temp= start;
	while(temp!= NULL){
		s= s+ temp->y;
		t++;
		temp= temp->next;
	}
	return s/t;
	
}

void mgraph(node*start)
{
        int x,y;
        int flag=0;
        node*temp;
        temp=start;
		int cx,cy;
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
					cx=(int)temp->x;
					cy=(int)temp->y;
                    if(cx==x&&cy==y)
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



void msc(int q){
	node *dataset= NULL, *prev= NULL, *naya= NULL, *temp= NULL, *ne= NULL;
	float meany,meanx;
	float radius= (float)q;

float datax;
    float datay;
    char ch;
    float x,y;
    int cnt=0;
    FILE *fp;
    fp=fopen("./data.txt","r");//opening file in read mode
    if(fp==NULL)
        printf("error");
    while(ch!=EOF)
    {
       
        if(cnt%2==0)
           {
            fscanf(fp,"%f",&datax);
             
             ch=fgetc(fp);         //moving cursor by one position
             cnt++;
           }
        else
            {
                 fscanf(fp,"%f",&datay);
                
               
                 ch=fgetc(fp);
                 cnt++;
                 dataset=insert(dataset,datax,datay);

            }        
    }
	
	while(1){
		temp= dataset;
		while(temp!= NULL){
			float a= temp->x,b= temp->y;
			ne= find(a,b,dataset,ne,radius);
			
			if(ne!= NULL){
				 meanx= averagex(ne);
				 meany= averagey(ne);
							
			}
			else{
				meanx= a;
				meany= b;
			}
			
			naya= insert_uni(meanx,meany,naya);
			temp= temp->next;
			ne =delet(ne);				}
		
		prev= delet(prev);
		prev= dataset;
		dataset= naya;
		naya= NULL;
		
		if(compare(prev,dataset)){
			break;
		}
	}
	temp= dataset;
	while(temp!=NULL){
		printf("%f \t %f \n",temp->x,temp->y);
		temp= temp->next;
	}
	mgraph(dataset);
	
	}
