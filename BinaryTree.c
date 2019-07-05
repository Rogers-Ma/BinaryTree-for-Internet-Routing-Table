#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct _node{
	unsigned int NextHop;
	unsigned int length;
	char *prefix;
	struct _node * l;
	struct _node * r;
} node;

void load();
void save(node *);
void display(node *);
void buildtree(node *, unsigned int, unsigned int, char * , int);
int ipparser(const char *dststr);
void ruleSplit(const char *, int * , int *, char *);
node * newnode(unsigned int, unsigned int, char*);

int main(int argc, char * argv[]){

	clock_t begin_time, end_time;
	double time_used;
	begin_time = clock();
    
	load();
	
	end_time = clock();
	time_used = (double)(end_time - begin_time) / CLOCKS_PER_SEC;
	fprintf(stderr, "Time usage = %17.13f\n", time_used);
	return 0;
	
}

void load(){
	char buff[32];
	int x;
	{
		node * root = (node *)malloc(sizeof(node));
		root->l = NULL;
		root->r = NULL;
		root->prefix = "";
		while (fscanf(stdin, "%s", buff) != EOF){
			int dst, mskl;
			char * s = (char *)malloc(16);
			ruleSplit(buff, &dst, &mskl, s);
			fscanf(stdin , "%d", &x);		
		    buildtree(root, x, mskl, s, dst);
			s=NULL;
		}
		display(root);
	}
}
int ipparser(const char *dststr){
	char * str;
	str = (char *)malloc(strlen(dststr) + 1);
	strcpy(str, dststr);
	char *token = strtok(str, ".");
	int ip = 0;
	while (NULL != token) {
		ip <<= 8;
		ip += atoi(token);
		token = strtok(NULL, ".");
	}
    free(str);
	return ip;
}


node * newnode(unsigned int n, unsigned int l, char * p){

	node * root = (node *)malloc(sizeof(node));
	root->l = NULL;
	root->r = NULL;
    //root->prefix = (char *)malloc(strlen(p));
    root->prefix= p;
	root->NextHop = n;
	root->length = l;
	return root;
}

void ruleSplit(const char *rule, int *dest, int *masklen, char *gw){
	char * p = strchr(rule, '/');
	strncpy(gw, rule, p - rule+1);
	gw[p-rule] = '\0';
	*masklen = atoi(p + 1);
	*dest = ipparser(gw);
}
void buildtree(node * root,unsigned int NextHop, unsigned int length, char * prefix, int netip){
	node * p = root;
	int i = 0;
	int len = length;
	for (i = 31; i >= 0 && len > 0; i--, len--) {
		if (netip & (1 << i)) {
			if ( p->r == NULL ) {
				node *newNode = newnode(0, 0, "");
				p->r = newNode;
			}
			p = p->r;
		}
		else {
			if (p->l == NULL) {
				node *newNode = newnode(0, 0, "");
				p->l = newNode;
			}
			p = p->l;
		}
	}
	p->length = length;
	p->NextHop =NextHop;
	p->prefix =prefix;
}

void display(node * root) {
    if (root){
        display(root->l);
        display(root->r);
        if (root->prefix!=NULL&&strcmp(root->prefix, "") != 0)
        {
            int i;
            for (i = 0; i < root->length; i++){
                fputs(" ", stdout);
            }
            //fprintf(fp,"%s/%d\t%d\n", root->prefix, root->length, root->NextHop);
            fprintf(stdout,"%s/%d\t%d\n", root->prefix, root->length, root->NextHop);
            char * temp=root->prefix;
            root->prefix=NULL;
            free(temp);
		}
        
        free(root);
        root=NULL;
	}
}
