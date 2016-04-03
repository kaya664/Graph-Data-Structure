#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
struct vertices{
	char a[30];
	int visited;
	struct vertices* next;
	struct edges* connectsEdge;
};
int count=0;
int periods=0;

struct edges{
	struct vertices* connectsTo;
	struct edges* next;
};
struct strings{
	char strs[100];	
	int h;
	struct strings* edgs;
	struct strings* next;
};
struct vertices* grs;
void DFS(struct vertices* vert);
void addVertice(char* name);
void display(struct vertices* gr);
void displayEdge(struct edges* ed);
struct edges* addEdge(struct edges** header,struct vertices* connect,struct vertices* original);
void displayNode(struct vertices* gr);
struct strings* insertString(struct strings* str,char* s,int h);
FILE *fp2;
struct strings* str=NULL;
struct strings* strEdges=NULL;
struct strings* temps=NULL;
struct strings* searchString(struct strings* s,char* name,int h);
int a=0;
struct vertices* g=NULL;
struct total* tot=NULL;
struct vertices* searchVertice(struct vertices* s,char* name);
struct stacks* stack1=NULL;
void Visited(struct vertices* vert,struct stacks* ST);
int count2=0;
int main(){
	//printf("sdsf");
    char review_string[100];
    char *name;
    char lessons[30];
    char lessons2[10];
    char lessons3[10];
    char line[1000];
    char*tok;
    //printf("sdsf");
	     if((fp2=fopen("c:\\Users\\KAYA\\Desktop\\input.txt","r"))==NULL){
	     	printf("Cannot open file.\n");
	     	exit(1);
	     }
	     int i=0;
	     struct vertices* temp=NULL;
	     struct strings* sd=NULL;
	     //printf("sdsf");
	     while(fgets(review_string,100,fp2)){
	     	tok=strtok(review_string,":");
	     	tok=strtok(NULL,"\n");
	     	str=insertString(str,tok,-5);
	     }
	     temps=str;
	     int j=0;
	     int h=0;
	     int l=0;
	     while(temps){
	     name=strtok(temps->strs,",\n");
	     strcpy(lessons,name);
	     l=h;
	     while (name != NULL)
         {
         	j++;
         	strEdges=insertString(strEdges,name,h);
            name = strtok (NULL, ",\n");
            h++;
         }
         sd=searchString(strEdges,lessons,l);
         while(sd){
         	addVertice(sd->strs);
         	sd=sd->next;
         }
         sd=searchString(strEdges,lessons,l);
         temp=searchVertice(grs,sd->strs);
         int g=l;
         while(i<j){
		 while(sd&&temp){
         	addEdge(&(temp->connectsEdge),searchVertice(grs,sd->strs),temp);
         	sd=sd->next;
         }
         sd=searchString(strEdges,lessons,l);
         if(searchString(strEdges,lessons,g)->next){
         	temp=searchVertice(grs,searchString(strEdges,lessons,g)->next->strs);
         }
         g++;
         i++;
         }
         j=0;
         temps=temps->next;
         i=0;
        }

    display(grs);
    DFS(grs);
    temp=grs;
    printf("\n\n\n");
    int x=1;
    while(x<=periods){
    	
    	printf("Final Exam Period %d => ",x);
    while(temp){
    	if(temp->visited==x){
    		printf("\t%s",temp->a);
    	}
    	temp=temp->next;
    }
    printf("\n");
    x++;
    temp=grs;
    }
	return 0;
}
void addVertice(char *name){
	
	struct vertices* newNode;
	struct vertices* temp;
	struct vertices* prev;

	// create node to insert and assign values to its fields
	newNode=malloc(sizeof(struct vertices));
	newNode->visited=0;
	newNode->connectsEdge=NULL;
	newNode->next=NULL;
	strcpy(newNode->a,name);

	// if LL empty
	if (grs == NULL) 
		grs=newNode;
	// if LL not empty
	else {
		temp=grs;
		while (temp != NULL && strcmp(temp->a,newNode->a)<0) {
			prev=temp;
			temp=temp->next;
		}

		if (temp!=NULL && strcmp(temp->a,newNode->a)==0) {
	      return; 
			
		}

		// insert node in a sorted fashion
		if (temp!=NULL)
			newNode->next=temp;

		// if value to insert is the least in LL then have header point to node
		if (temp==grs)
			grs=newNode;
		// otherwise insert node in correct position
		else 
			prev->next=newNode;
	}
}
struct edges* addEdge(struct edges** header,struct vertices* connect,struct vertices* original){
	struct edges* newNode, *tempd, *prev;

	// create node to insert and assign values to its fields
	newNode=malloc(sizeof(struct edges));
	newNode->connectsTo=connect;
	newNode->next=NULL;

	// if LL empty
	if(strcmp(connect->a,original->a)==0){
		return;
	}
	if (*header == NULL) 
		*header=newNode;
	// if LL not empty
	else {
		tempd=*header;
		while (tempd != NULL && strcmp(tempd->connectsTo->a,newNode->connectsTo->a)<0) {
			prev=tempd;
			tempd=tempd->next;
		}

		if (tempd!=NULL && strcmp(tempd->connectsTo->a,newNode->connectsTo->a)==0) {
			return;
		}

		// insert node in a sorted fashion
		if (tempd!=NULL)
			newNode->next=tempd;

		// if value to insert is the least in LL then have header point to node
		if (tempd==*header)
			*header=newNode;
		// otherwise insert node in correct position
		else 
			prev->next=newNode;
	}
}
void display(struct vertices* gr){
	if(gr){
		
		printf("\n%s\t->",gr->a);
	    displayEdge(gr->connectsEdge);
	    if(count2==0){
	    	printf("\t-> NONE");
	    }
	    count2=0;
	    display(gr->next);
   }
}
void displayEdge(struct edges* ed){
	if(ed){	
	count2++;
	printf("  %s  ",ed->connectsTo->a);
	    displayEdge(ed->next);  
	}
}
void displayNode(struct vertices* gr){
	if(gr){
		printf("%s ",gr->a);
		displayEdge(gr->connectsEdge);
	}
}
struct strings* insertString(struct strings* str,char* s,int h){
    if(str){
		str->next=insertString(str->next,s,h);
		return str;
	}
	else{
		struct strings* st=(struct strings*)malloc(sizeof(struct strings));
		strcpy(st->strs,s);
		st->next=NULL;
        st->edgs=NULL;
        st->h=h;
		str=st;
		return str;
	}
}
struct vertices* searchVertice(struct vertices* s,char* name){
	if(s){
	
		if(strstr(s->a,name)){
			return s;
		}
		else{
			searchVertice(s->next,name);
		}
	}
	else{
		return NULL;
	}
}
struct strings* searchString(struct strings* s,char* name,int h){
	if(s){
		if(h==s->h){
			return s;
		}
		else{
			searchString(s->next,name,h);
		}
	}
	else{
		return s;
	}
}


void DFS(struct vertices* vert){
	struct vertices* temp=NULL;
	temp=vert;
	while(temp){
		temp->visited=0;
		temp=temp->next;
	}
	temp=vert;
    
	while(temp){
		//printf("dsdf");
		if(temp->visited==0)
		Visited(temp,stack1);
	//	printf("dsdf");
		temp=temp->next;
	}
	
}
void Visited(struct vertices* vert,struct stacks* ST){

	int xx=1;
	while(vert->visited==0){
		if(searchForColor(vert->connectsEdge,xx)==0){
			xx++;
		
			if(xx>periods){
				periods=xx;
			}
		}
		else{
			vert->visited=xx;
		}
	}
	struct vertices* temp=vert;
	//temp->visited=1;
	//printf("\n%s",temp->a);
	//struct edges* temp2=temp->connectsEdge;
	
	while(temp->connectsEdge){
		//printf("15");
		if(temp->connectsEdge->connectsTo->visited==0){
			Visited(temp->connectsEdge->connectsTo,ST);
		}
		temp->connectsEdge=temp->connectsEdge->next;
	}
	
    
}
int searchForColor(struct edges* node,int y){
	int x=y;
	while(node){
		if(node->connectsTo->visited==x){
			return 0;
		}
		node=node->next;
	}
	
	return 1;
}
