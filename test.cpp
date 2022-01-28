#include <bits/stdc++.h>
using namespace std;
#define infinity 1000000007

typedef struct _hashing {
    int key;
    struct _hashing *next;
}hash_table;

void chaining(hash_table **arr,int key,int value,int size){
    int h_key = key%size;
    arr[h_key]->key = key;
    hash_table *temp = arr[h_key]->next;
    hash_table *new_node = (hash_table*)malloc(sizeof(hash_table));
    new_node->next = temp;
    new_node->key = value;
    arr[h_key]->next = new_node;
    return;
}

void delete_val(hash_table **arr,int key,int value,int size){
    hash_table *temp,*prev;
    int h_key = key%size;
    prev = arr[h_key];
    temp = arr[h_key]->next;
    while(temp!=NULL){
        if(temp->key == value){
            prev->next = temp->next;
            free(temp);
            break;
        }
        else{
            prev = temp;
            temp = temp->next;
        }
    }
    if(arr[h_key]->next==NULL){
        arr[h_key]->key = -1*infinity;
    }
    return;
}

void print_table(hash_table **arr,int size,int t,char c){
    int i;
    hash_table *temp;
    for(i=0;i<size;i++){
        temp = arr[i]->next;
        if(temp==NULL){
            printf("%c %d -1 -1\n",c,i);
        }
        else{
            while(temp!=NULL){
                printf("%c %d %d %d\n",c,i,arr[i]->key,temp->key);
                temp = temp->next;
            }
        }
    }
    return;
}

int main(){
    int size,t;
    cin >> size >> t;
    int i,y,p;
    char c;
    hash_table **p_askey = (hash_table**)malloc(size*sizeof(hash_table*));
    hash_table **c_askey = (hash_table**)malloc(size*sizeof(hash_table*));
    for(i=0;i<size;i++){
        p_askey[i] = (hash_table*)malloc(sizeof(hash_table));
        c_askey[i] = (hash_table*)malloc(sizeof(hash_table));
        p_askey[i]->next = c_askey[i]->next = NULL;
        p_askey[i]->key = c_askey[i]->key = -1*infinity;
    } 
    int h_key;
    hash_table *temp,*del_node;
    for(i=0;i<t;i++){
        cin >> c;
        if(c=='+'){
            cin >> y >> p;
            chaining(p_askey,p,y,size);
            chaining(c_askey,y,p,size);
        }
        else{
            cin >> y;
            h_key = y%size;
            temp = c_askey[h_key]->next;
            while(temp!=NULL){
                delete_val(p_askey,temp->key,y,size);       
                temp = temp->next;
            }
            temp = c_askey[h_key]->next;
            while(temp!=NULL){
                del_node = temp;
                temp = temp->next;
                free(del_node);
            }
            c_askey[h_key]->next = NULL;
            c_askey[h_key]->key = -1*infinity;
        }
    }
    print_table(p_askey,size,t,'p');
    print_table(c_askey,size,t,'c');
    return 0;
}