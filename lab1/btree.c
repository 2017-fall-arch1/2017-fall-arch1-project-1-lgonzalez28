#include <stdio.h>
//#include <curses.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 999

//creation of the node
struct node {
  char *value;    
  struct node *p_left;
  struct node *p_right;
};

typedef int (*Compare)(const char *, const char *);


//inserts the elements
void insert(char* key, struct node** leaf, Compare cmp)
{
  int res;
  if( *leaf == NULL ) {
    *leaf = (struct node*) malloc( sizeof( struct node ) );
    (*leaf)->value = malloc( strlen (key) +1 );
    strcpy ((*leaf)->value, key);              
    (*leaf)->p_left = NULL;
    (*leaf)->p_right = NULL;
  } else {
    res = cmp (key, (*leaf)->value);
    if( res < 0)
      insert( key, &(*leaf)->p_left, cmp);
    else if( res > 0)
      insert( key, &(*leaf)->p_right, cmp);
    else  //if all ready exists
      printf ("Try again the key '%s' already in tree\n", key);
  }
}

//compares value of the new node
int CmpStr(const char *a, const char *b)
{
  return (strcmp (a, b));     // string comparison
}

char *input( void )
{
  int c = 0, i = 0;
  FILE *file = fopen("names.txt", "r");
  static char line[MAXLEN+1];      
  while((c = fgetc(file)) != EOF)
    {
      if((fgets( line, sizeof line, stdin )) != NULL)
	puts(line);
    }
  return ( strtok(line, "\n" ));
}


//function to print out the tree in order
void in_order(struct node *root)
{
  if( root != NULL ) {
    in_order(root->p_left);
    printf("   %s\n", root->value);   
    in_order(root->p_right);
  }
}


//searches names in the tree
void search(char* key, struct node* leaf, Compare cmp)
{
  int res;
  if( leaf != NULL ) {
    res = cmp(key, leaf->value);
    if( res < 0)
      search( key, leaf->p_left, cmp);
    else if( res > 0)
      search( key, leaf->p_right, cmp);
    else
      printf("\n'%s'name found!\n", key);     
  }
  else printf("\nName is not in tree!!!\n");
  return;
}



//Main method with the instructions
int main()
{
  struct node *root = NULL;
  char option = '\0';
  int c = 0;
  char name[32];
  FILE *file;

  printf("\nPress 'i' to isert an name\n");
  printf("\nPress 's' to search for an name\n");
  printf("\nPress 'p' to print an name\n");
  printf("\nPress 'd' to delete an name\n");
  printf("\nPress 'q' to quit\n");

  while(option != 'q')
    {
      printf("\nPlease enter an option: ");
      scanf("%s", &option);
      if(option == 'i')
	{
	  printf("\nEnter the new name: ");
	  file = fopen("names.txt", "a");
	  scanf("%s", name);
	  fprintf(file, "%s\t%s\n", name);
	  printf("Added to the tree!");
	  fclose(file);
	}
      else if(option == 'p')
	{
	  insert(input(), &root, (Compare)CmpStr);
	  in_order(root);
	}
      else if(option == 's')
	{
	  printf("\nEnter the name you want to search: ");
	  scanf("%s", name);
	  search(name, root, (Compare)CmpStr);
	}
      else if(option == "q")
	printf("\n You end the program, bye");
    }
  return 0;
}
