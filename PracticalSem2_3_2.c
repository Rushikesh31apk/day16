#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// this stucture can be use to construct tree node

typedef struct node
{
    char code[10];          // it can use to crating charcter array
    char ch;               // it can intialize character 
    int freq;              //it can be stored chracter frequency
    struct node* left;     //address of left node stored
    struct node* right;    // address of right node stored
} NODE;  // changeing name of above structure


// this stucture can be use to construct priority tree

typedef struct queue
{ 
    NODE* data[20];   // defining queue size
    int front, rear;  // it can be use to follow FIFO principle
} QU;  // changeing name of above structure

void init(QU* p)
{
    p->front = p->rear = -1; // ininitialize Empty queue 
}

void add(QU* p, NODE* num) 
{
    int i;
    for (i = p->rear; i > p->front; i--) // traversing rear to front F<------R
	{
        if (num->freq < p->data[i]->freq) // comparison of new charater freq and 
                                          // last ele to first ele if is less then rear 
                                          // increment bye one 
		{
            p->data[i + 1] = p->data[i];
        } 
		else 
		{
            break;
        }
    }
    p->data[i + 1] = num;
    p->rear++;
}

NODE* pop(QU* p) 
{
    return (p->data[++p->front]);// deleteing first element in queue
}

int isempty(QU* p) 
{
    return (p->front == p->rear);// check queue is empty or note
}

NODE* getnode(char ch, int f) // this function get charcter and freq then create leaf node
{
    //    |left|char|freq|right|-->eg:   \0\a\3\0\
    
    NODE*ptr = (NODE*)malloc(sizeof(NODE));//creating newnode
    ptr->ch = ch;             //newnode pointing character 
    ptr->freq = f;           //newnode pointing character frequency 
    strcpy(ptr->code, "");  // Initialize code as an empty string
    ptr->left = ptr->right = NULL;  //we have know leaf node point NULL
    return ptr; // return this type of node--> \0\a\3\0\*/
}

void encode(NODE* root) //imp function to generate character code
{
    if (root != NULL) // it can be invock when root not null
	{
		/*we have know root left and right null mean this root is leaf node
		so we have find charater node then simple print 
		character and frequency and genreted code */
		
        if (root->left == NULL && root->right == NULL) 
		{
            printf("\n%c \t%d\t%s", root->ch, root->freq, root->code);
        }
        
        if (root->left != NULL) // we have to simple count 0 to traversing root to leaf node
		{
			// copy karega root ka code root ke left me 
            strcpy(root->left->code, root->code);
            
            // hamanee upar copy kiya root node ka code root ke left mai
            // bs use connect karna hai hamare root se us node ke 
            // path tak
            strcat(root->left->code, "0");//left mai 0 add hoga bhai
            
        // chalo ab karo recuresive call aur bhej do root ka left node process ke liye
            encode(root->left);
        }
        if (root->right != NULL) // we have to simple count 1  to traversing root to leaf node
		{
			// copy karega root ka code root ke right me
            strcpy(root->right->code, root->code);
            
            // hamane upar copy kiya root node ka code root ke right mai
            // bs use connect karna hai hamare root se us node ke 
            // path tak
            strcat(root->right->code, "1");//right mai 1 add hoga bha
        // chalo ab karo recuresive call aur bhej do root ka right node process ke liye
            encode(root->right);
        }
    }
}

void huffman(NODE* list[], int n) 
{
    int i;
    NODE* t1, * t2, * t3;// creating 3 pointer in bellow use
    QU q;
    init(&q);

    for (i = 0; i < n; i++) 
	{
        add(&q, list[i]);// adding one by one charcter as consider priority
    }

    while (1) // creating infinite loop
	{
        t1 = pop(&q);// get  front 1
        if (isempty(&q)) 
		{
            break;
        }
        t2 = pop(&q); // get front 2 
        t3 = getnode('-', t1->freq + t2->freq); // add  char1 freq and char2 freq 
        t3->left = t1; //parent of  character 1
        t3->right = t2;//parent 8of  character 2
        add(&q, t3); // adding new t1+t2 addition node in queue
    }
    encode(t1); // calling to find code of char1
}

int main() {
    int n, i, f;
    char ch;
    NODE* newnode;
    NODE* list[10];

    printf("How many characters: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
	 {
        printf("\nEnter character and frequency:[e.g., a 5]:\n");
        scanf(" %c\n %d", &ch, &f);
        list[i] = getnode(ch, f);
    }
    printf("\nchar\tfreq\tcode\t");
       huffman(list, n);
        


    return 0;
}

