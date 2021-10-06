#include <iostream>
#include<climits>
using namespace std;

class Node
{
  public:
   int key;
   Node *left;
   Node *right;

   Node(int key){
       this->key = key;
       left = right  = NULL;
   }
};

class LinkedList{
    public:
    Node*head;
    Node*tail;
};

LinkedList tree2LL(Node * root){
    LinkedList l;
    if(root==NULL){
        l.head=l.tail=NULL;
        return l;
    }
    if(root->left == NULL and root->right == NULL){
        l.head=l.tail=root;
        return l;
    }
    else if(root->left!=NULL and root->right==NULL){
        LinkedList leftLL = tree2LL(root->left);
        leftLL.tail->right = root;
        l.head = leftLL.head;
        l.tail = root;
    }
    else if(root->left==NULL and root->right!=NULL){
        LinkedList rightLL = tree2LL(root->right);
        root->right = rightLL.head;
        l.head = root;
        l.tail = rightLL.tail;
    }
    else{
        LinkedList leftLL = tree2LL(root->left);
        LinkedList rightLL = tree2LL(root->right);
        leftLL.tail->right = root;
        root->right = rightLL.head;
        l.head = leftLL.head;
        l.tail = rightLL.tail;
    }

    return l;
}


// Node* sortedArrayToBST(vector<int> arr, int start, int end) 
// { 
//     //Return Null if s > e, because no array elements are there
//     if (start > end) 
//         return NULL; 
  
//     /* Get the middle element and make it root */
//     int mid = (start + end)/2; 
//     Node *root = new Node(arr[mid]); 
  
//     //create left & right subtrees recursively
//     root->left = sortedArrayToBST(arr, start, mid - 1); 
//     root->right = sortedArrayToBST(arr, mid + 1, end); 

//     return root; 
// } 

Node* insert(Node * root, int key){
	if(root==NULL){
		return new Node(key);
	}

	//rec case 
	if(key < root->key){
		root->left = insert(root->left,key);
	}
	else{
		root->right = insert(root->right,key);
	}
	return root;

}

// bool search(Node * root, int key,int){
// 	//Homework
// 	if(root == NULL){
//         return false;
//     }
//     if(root->key == key){
//         return ;
//     }
    
//     if(root->key < key){
//         return search(root->right,key);
//     }
//     else{
//         return search(root->left,key);
//     }

// }

void printInOrder(Node *root){
	if(root==NULL){
		return;
	}
	//left, root, right
	printInOrder(root->left);
	cout << root-> key <<" ";
	printInOrder(root->right);
}

int findClosest(Node* root, int target ){
    int closest,curdiff;
    int diff = INT_MAX;
    Node * temp = root ;
    while(temp!=NULL){

        curdiff =abs(temp->key - target);
        if(curdiff==0){
            return temp->key;
        }

        if(curdiff <diff){
            diff = curdiff;
            closest = temp->key;
        }

        if(temp->key<target){
            temp = temp->right;
        }
        else{
            temp->left;
        }

    }
    return closest;
}

node * successor(Node* root, Node * target){
    if(target->right!=NULL){
        Node * temp = target->right;
        while(temp->left!=NULL){
            temp=temp->left;
        }
        return temp;
    }

    Node * temp = root;
    Node * succ = NULL;

    while(temp!=NULL){

        if(temp->key > target->key){
            succ = temp;
            temp = temp->left;
        }
        if(temp->key < target->key){
            temp = temp->right;
        }
        else{
            break;
        }
    }
    return succ;
} 

int main(){

	Node * root = NULL;
	int arr[] = {8,3,10,1,6,14,4,7,13};

	for(int x : arr){
		root = insert(root,x);
	}
	LinkedList l=tree2LL(root);
    Node * temp = l.head;
    while(temp!=NULL){
        cout<<temp->key<<" ";
        temp=temp->right;
    }
    //cout<<"\n"<<search(root,8);
	return 0;
}