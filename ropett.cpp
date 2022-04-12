#include <bits/stdc++.h>
#include<windows.h>
using namespace std;
#define debug 0

struct text_t {
	int key;
	struct text_t *left;
	struct text_t *right;
	int height;
};

void insert_line(text_t *txt, int index, char * new_line);
text_t * create_text() {
	text_t *tmp_node;
	tmp_node = (text_t *) malloc(sizeof(text_t));
	tmp_node->left = NULL;
	tmp_node->right = NULL;
	tmp_node->key = 0;
	tmp_node->height = 0;
	insert_line(tmp_node,1,"ADVANCED DATA STRUCTURES");
	return tmp_node;}

void left_rotation(text_t *n) {
	text_t *tmp_node;
	tmp_node = n->left;
	n->left = n->right;
	n->right = n->left->right;
	n->left->right = n->left->left;
	n->left->left = tmp_node;
	n->left->key = n->left->left->key + n->left->right->key;}

void right_rotation(text_t *n) {
	text_t *tmp_node;
	tmp_node = n->right;
	n->right = n->left;
	n->left = n->right->left;
	n->right->left = n->right->right;
	n->right->right = tmp_node;
	n->right->key = n->right->left->key + n->right->right->key;}

int length_text(text_t *txt) {
	text_t *temp = txt;
	if (txt == NULL) {
		return -1;
	} else if (temp->left == NULL) {
		return 0;
	} else {
		return txt->key;}}

char * get_line(text_t *txt, int index) {
	text_t *tmp_node = txt;
	if (tmp_node == NULL) {
		//root is null
		return NULL;
	} else if (tmp_node->key < index) {
		//index is greater than number of lines; line does not exist
		return NULL;
	} else {
		//line exists
		while (tmp_node->right != NULL) {
			if (index <= tmp_node->left->key) {
				//Go left
				tmp_node = tmp_node->left;
			} else {
				//Update index and Go right
				index = index - tmp_node->left->key;
				tmp_node = tmp_node->right;}}
		//Node found; return line
		return (char *) tmp_node->left;}}

char * set_line(text_t *txt, int index, char * new_line) {
	text_t *tmp_node = txt;
	if (tmp_node == NULL) {
		//root is null
		return NULL;
	} else if (tmp_node->key < index) {
		//index is greater than number of lines; line does not exist
		return NULL;
	} else {
		//line exists
		while (tmp_node->right != NULL) {
			if (index <= tmp_node->left->key) {
				//Go left
				tmp_node = tmp_node->left;
			} else {
				//Update index and Go right
				index = index - tmp_node->left->key;
				tmp_node = tmp_node->right;}}
		char *old_line;
		old_line = (char *) tmp_node->left;
		tmp_node->left = (text_t *) new_line;
		return old_line;}}

void insert_line(text_t *txt, int index, char * new_line) {
	text_t *tmp_node = txt;
	int finished = 0;
	if (tmp_node->left == NULL) {
		tmp_node->left = (text_t *) new_line;
		tmp_node->key = 1;
		tmp_node->height = 0;
		tmp_node->right = NULL;
	} else {
		text_t * path_stack[100];
		int path_st_p = 0;
		while (tmp_node->right != NULL) {
			if (index <= tmp_node->left->key) {
				//Go left
				tmp_node->key++;
				path_stack[path_st_p++] = tmp_node;
				tmp_node = tmp_node->left;
			} else {
				//Update index and Go right
				index = index - tmp_node->left->key;
				tmp_node->key++;
				path_stack[path_st_p++] = tmp_node;
				tmp_node = tmp_node->right;}}

		text_t *old_leaf, *new_leaf;
		old_leaf = create_text();
		old_leaf->left = tmp_node->left;
		old_leaf->key = tmp_node->key;
		old_leaf->right = NULL;
		old_leaf->height = 0;
		new_leaf = create_text();
		new_leaf->left = (text_t *) new_line;
		new_leaf->key = 1;
		new_leaf->right = NULL;
		new_leaf->height = 0;
		tmp_node->left = new_leaf;
		tmp_node->right = old_leaf;
		tmp_node->key++;
		tmp_node->height = 1;
		while (path_st_p > 0 && !finished) {
			int tmp_height, old_height;
			tmp_node = path_stack[--path_st_p];
			old_height = tmp_node->height;
			if (tmp_node->left->height - tmp_node->right->height == 2) {
				if (tmp_node->left->left->height - tmp_node->right->height== 1) {
					right_rotation(tmp_node);
					tmp_node->right->height = tmp_node->right->left->height + 1;
					tmp_node->height = tmp_node->right->height + 1;
				} else {
					left_rotation(tmp_node->left);
					right_rotation(tmp_node);
					tmp_height = tmp_node->left->left->height;
					tmp_node->left->height = tmp_height + 1;
					tmp_node->right->height = tmp_height + 1;
					tmp_node->height = tmp_height + 2;}
			} else if (tmp_node->left->height - tmp_node->right->height == -2) {
				if (tmp_node->right->right->height - tmp_node->left->height== 1) {
					left_rotation(tmp_node);
					tmp_node->left->height = tmp_node->left->right->height + 1;
					tmp_node->height = tmp_node->left->height + 1;
				} else {
					right_rotation(tmp_node->right);
					left_rotation(tmp_node);
					tmp_height = tmp_node->right->right->height;
					tmp_node->left->height = tmp_height + 1;
					tmp_node->right->height = tmp_height + 1;
					tmp_node->height = tmp_height + 2;}
			} else {
				/* update height even if there was no rotation */
				if (tmp_node->left->height > tmp_node->right->height)
					tmp_node->height = tmp_node->left->height + 1;
				else
					tmp_node->height = tmp_node->right->height + 1;}
			if (tmp_node->height == old_height)
				finished = 1;}}}

void append_line(text_t *txt, char * new_line) {
	text_t *tmp_node;
	int finished = 0;
	if (txt->left == NULL) {
		txt->left = (text_t *) new_line;
		txt->key = 1;
		txt->height = 0;
		txt->right = NULL;
	} else {
		text_t * path_stack[100];
		int path_st_p = 0;
		tmp_node = txt;
		while (tmp_node->right != NULL) {
			tmp_node->key++;
			path_stack[path_st_p++] = tmp_node;
			tmp_node = tmp_node->right;}

		text_t *old_leaf, *new_leaf;
		old_leaf = create_text();
		old_leaf->left = tmp_node->left;
		old_leaf->key = tmp_node->key;
		old_leaf->right = NULL;
		old_leaf->height = 0;
		new_leaf = create_text();
		new_leaf->left = (text_t *) new_line;
		new_leaf->key = 1;
		new_leaf->right = NULL;
		new_leaf->height = 0;
		tmp_node->left = old_leaf;
		tmp_node->right = new_leaf;
		tmp_node->key++;
		tmp_node->height = 1;
		while (path_st_p > 0 && !finished) {
			int tmp_height, old_height;
			tmp_node = path_stack[--path_st_p];
			old_height = tmp_node->height;
			if (tmp_node->left->height - tmp_node->right->height == 2) {
				if (tmp_node->left->left->height - tmp_node->right->height== 1) {
					if (debug)
						printf("Inside append\n");
					right_rotation(tmp_node);
					tmp_node->right->height = tmp_node->right->left->height + 1;
					tmp_node->height = tmp_node->right->height + 1;
				} else {
					left_rotation(tmp_node->left);
					right_rotation(tmp_node);
					tmp_height = tmp_node->left->left->height;
					tmp_node->left->height = tmp_height + 1;
					tmp_node->right->height = tmp_height + 1;
					tmp_node->height = tmp_height + 2;}
			} else if (tmp_node->left->height - tmp_node->right->height == -2) {
				if (tmp_node->right->right->height - tmp_node->left->height== 1) {
					left_rotation(tmp_node);
					tmp_node->left->height = tmp_node->left->right->height + 1;
					tmp_node->height = tmp_node->left->height + 1;
				} else {
					right_rotation(tmp_node->right);
					left_rotation(tmp_node);
					tmp_height = tmp_node->right->right->height;
					tmp_node->left->height = tmp_height + 1;
					tmp_node->right->height = tmp_height + 1;
					tmp_node->height = tmp_height + 2;}
			} else {
				/* update height even if there was no rotation */
				if (tmp_node->left->height > tmp_node->right->height)
					tmp_node->height = tmp_node->left->height + 1;
				else
					tmp_node->height = tmp_node->right->height + 1;}
			if (tmp_node->height == old_height)
				finished = 1;}}}

char * delete_line(text_t *txt, int index) {
	if (debug) printf("Inside delete\n");
	text_t *tmp_node, *upper_node, *other_node;
	char *deleted_object;
	int finished;
	if (txt == NULL) {
		return NULL;
	} else if (txt->left == NULL) {
		return NULL;
	} else if (txt->key < index) {
		return NULL;
	} else if (txt->right == NULL) {
		return (char *) txt->left;
	} else {
		text_t * path_stack[100];
		int path_st_p = 0;
		tmp_node = txt;
		while (tmp_node->right != NULL) {
			tmp_node->key--;
			path_stack[path_st_p++] = tmp_node;
			upper_node = tmp_node;
			if (index <= upper_node->left->key) {
				tmp_node = upper_node->left;
				other_node = upper_node->right;
			} else {
				index = index - upper_node->left->key;
				tmp_node = upper_node->right;
				other_node = upper_node->left;}}
		upper_node->key = other_node->key;
		upper_node->left = other_node->left;
		upper_node->right = other_node->right;
		upper_node->height = other_node->height;
		deleted_object = (char *) tmp_node->left;
		/*rebalance*/
		finished = 0;
		path_st_p -= 1;
		while (path_st_p > 0 && !finished) {
			int tmp_height, old_height;
			tmp_node = path_stack[--path_st_p];
			old_height = tmp_node->height;
			if (tmp_node->left->height - tmp_node->right->height == 2) {
				if (tmp_node->left->left->height - tmp_node->right->height
						== 1) {
					right_rotation(tmp_node);
					tmp_node->right->height = tmp_node->right->left->height + 1;
					tmp_node->height = tmp_node->right->height + 1;
				} else {
					left_rotation(tmp_node->left);
					right_rotation(tmp_node);
					tmp_height = tmp_node->left->left->height;
					tmp_node->left->height = tmp_height + 1;
					tmp_node->right->height = tmp_height + 1;
					tmp_node->height = tmp_height + 2;
				}
			} else if (tmp_node->left->height - tmp_node->right->height == -2) {
				if (tmp_node->right->right->height - tmp_node->left->height
						== 1) {
					left_rotation(tmp_node);
					tmp_node->left->height = tmp_node->left->right->height + 1;
					tmp_node->height = tmp_node->left->height + 1;
				} else {
					right_rotation(tmp_node->right);
					left_rotation(tmp_node);
					tmp_height = tmp_node->right->right->height;
					tmp_node->left->height = tmp_height + 1;
					tmp_node->right->height = tmp_height + 1;
					tmp_node->height = tmp_height + 2;
				}
			} else {
				/* update height even if there was no rotation */
				if (tmp_node->left->height > tmp_node->right->height)
					tmp_node->height = tmp_node->left->height + 1;
				else
					tmp_node->height = tmp_node->right->height + 1;}
			if (tmp_node->height == old_height)
				finished = 1;}
		return deleted_object;}}

void print(text_t* root){
    text_t* temp=root;
    for(int i=1;i<length_text(temp);i++){
        cout<<i<<"."<<get_line(root,i)<<endl;}}

int main(){    
	system("cls");  
    cout<<"\t\t\tTEXT EDITOR USING ROPE ";
	int i, tmp; text_t *root,*temp; char c[100];
    int ind ,choice,choice1;
	  root = create_text();
	  append_line(root,NULL );
	  insert_line(root,2,"PROJECT DEMO");
	  insert_line(root,3,"TEXT EDITOR");
	  insert_line(root,4,"USING ROPE");
	  print(root);
    do{
        cout<<"\n\t\t\t\tMENU";
        cout<<"\n\t\t\t1.INSERT \n\t\t\t2.DELETE \n\t\t\t3.FIND\n\t\t\t4.FIND AND REPLACE \n\nEnter your choice: ";
        cin>>choice;
        switch( choice ){
        case 1:
				   cout<<"\nENTER THE INDEX";
				   cin>>ind;
                   cout<<"\n ENTER THE TEXT\n";
                   cin>>c;
                   insert_line(root,ind,c);
                   cout<<endl;break; 
        case 2:
		            cout<<"\n ENTER THE INDEX:";
                    cin>>ind;
                    if(delete_line( root,ind)== NULL){
                        cout<<"THE INDEX: "<<ind<<" NOT IN THE FILE";}
                    cout<<endl;
                    break;
        case 3:
		            cout<<"\n ENTER THE INDEX:";
                    cin>>ind;
                    cout<<get_line(root,ind)<<endl;
                    break;
        case 4:    
                    temp=root;
                    cout<<"\nREPLACE WITH : ";
                    cin>>c;
                    cout<<"\n ENTER THE INDEX TO FIND THE STRING:";
                    cin>>ind;
                    if( get_line(temp,ind)!=NULL )
                        set_line(temp,ind,c);
                    else
                        cout<<"\nNot in Text\n";
                    break;

        default:
                    cout<<"\nINVALID OPTION";}
					print(root);
        cout<<"\n \n 1 - CONTINUE \n 0 - EXIT";
        cin>>choice1;
    }while( choice1 );}