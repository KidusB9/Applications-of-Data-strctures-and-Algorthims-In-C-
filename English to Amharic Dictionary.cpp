// kidus habte
#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

struct node //stores the address of any variable of type 'node


//define the node with data type string
/* A binary tree node has data, pointer to left child
and a pointer to right child */
{
        string word,Amharic;
        node *left,*right; /*pointer to node, store the address of left and right child */
        int height;//simillar to doubly linked list but doubly linked list uses linear while BST is in Binary
        // A utility function to get height
        // of the tree
};
// linked list to Bst Following is a simple algorithm where
        //we first find the middle node of the list and make it the root of the tree to be constructed.
        //in linked list the information is kept on the head node if we know the head node we can access all the nodes
        //in BST the information is kept on the root node
class avl
{
        public:
        node *root;//to store address of the root node
        // to create a tree we need to declare a pointer to BSt node

        avl()
        {
                root=NULL; // setting tree  as empty
        }
        node* new_node(string wo,string an);
        /* Function to create a new node with given data */
        int find_ht(node*);
        int balance(node*);
        node* l_rot(node *);//intilizie a node
        node* r_rot(node *);
        node *insert(node *,string,string);
        void preorder(node*);//function  for Preorder traversal i used to create a copy of the tree.
         //Preorder traversal i also used to get prefix expression on an expression tree
        node *leftmost(node* );
        node * delet(node *root,string w);
        void search(node*,string);
        void modify(node*,string);
        node * ret()
        {
        return root;
        }
        int max(int a, int b) // A utility function to get maximum
                               // of two integers
        {
        return (a > b)? a : b;

        }

};
/*The Search operation can be performed with the key value that need to be searched in the given AVL tree.
The search operation returns a node from a tree if the node value matches with the key value.
If the key value does not match with any node value in the tree no value is returned.*/
void avl::search(node* r,string w)
/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
{
        if(r==NULL)
        {
                cout<<"\n Not Found";
                return ;
        }

        if(w<r->word)
        search(r->left,w);
        if(w>r->word)
        search(r->right,w);
        else if(r->word==w)
        {
       cout<<"\nWord : "<<r->word;
       cout<<"\nAmharic : "<<r->Amharic;
        return ;
        }


}
void avl::modify(node* r,string w)
{

        if(r==NULL)
        {
                cout<<"\n Not Found";
                return ;
        }
     string spa;   /* 1. Perform the normal BST insertion and modfiy it to the new file */
        if(w<r->word)
        modify(r->left,w);
        if(w>r->word)
        modify(r->right,w);
        else if(r->word==w)
        {

       cout<<"\nWord : "<<r->word;
       cout<<"\nOriginal Amharic : "<<r->Amharic;
       cout<<"\n New Amharic : ";
       cin>>spa;
       r->Amharic=spa;
       fstream f,f1;
       string g;
       f.open("dic.txt",ios::in|ios::out);
       f1.open("dic1.txt",ios::out);
       while(f)
       {
              f>>g;
              if(g!=w)
              {
                  f1<<g;
                  getline(f,g);
                  f1<<g;
                f1<<endl;

              }

              else
              {
              f1<<g;

              f1<<" ";
              f1<<spa;

              f1<<endl;
              getline(f,g);
              }
              if(f.eof())
              break;

        }
        remove("dic.txt");
        rename("dic1.txt","dic.txt");

         return ;

   }
   }
int avl:: find_ht(node * t)
{
        if(t==NULL)
        return 0;
        return t->height;// A utility function to get height
                          // of the tree
}
int avl::balance(node *t)
{
        if(t==NULL)
        return 0;
        return ((find_ht(t->left))-find_ht(t->right));

}

node * avl::new_node(string wo,string opp) //function to modifiy
   /* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
{
        node *r=new node();
        r->word=wo;
        r->Amharic=opp;
        r->height=1;
        r->left=NULL;
        r->right=NULL;
        return r;

}
node *avl::r_rot(node *y) //A utility function to right
        // rotate subtree rooted with y
{
        node *t=y->left;
        node *g=t->right;
         t->right=y;
        y->left=g;


        y->height=max(find_ht(y->left),find_ht(y->right))+1;
        t->height=max(find_ht(t->left),find_ht(t->right))+1;

// Return new root
        return t;

}
node *avl::l_rot(node *y)  //A utility function to right or balance
        // rotate subtree rooted with y
{
        node *t=y->right;
        node *g=t->left;
         t->left=y;

        y->right=g;

        y->height=max(find_ht(y->left),find_ht(y->right))+1;
        /* 2. Update height of this ancestor node */
         // Update heights

        t->height=max(find_ht(t->left),find_ht(t->right))+1;

        // Return new root
        return t;
/*A new node can be inserted if the node value is not already present in the tree.
// After the insertion of each node the tree should be checked for balance.
//The only nodes that need to be checked are the ones along the insertion path of the newly inserted node.
//Once the tree is found to be unbalanced then  we rebalance it using the appropriate rotation operation.*/
}
node * avl::insert(node *k,string w,string m)
// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
{

        if(k==NULL)
        return( new_node(w,m));/* 1. Perform the normal BST rotation */
        if(w<k->word)
        k->left=insert(k->left,w,m);
        else if(w>k->word)
        k->right=insert(k->right,w,m);

        k->height=max(find_ht(k->left),find_ht(k->right))+1;
        /* 2. Update height of this ancestor node */

      int g=balance(k); // Get Balance factor of node N

/*  Get the balance factor of this
        ancestor node to check whether
        this node became unbalanced */

       if(g>1 && w<k->left->word) // If this node becomes unbalanced,
    // then there are 4 cases
        return r_rot(k);


         if(g>1 && w>k->left->word)
        {
            k->left=l_rot(k->left);
            return r_rot(k);
        }

        if(g<-1 && w>k->right->word)
       return l_rot(k);


        if(g<-1 && w<k->right->word)
         {
            k->right=r_rot(k->right);
            return l_rot(k);
        }

     return k;


}
void avl::preorder(node * root)  // get prefix expression on an expression tree
// A utility function to print preorder
// traversal of the tree.
// The function also prints height
// of every node
{
    if(root != NULL)
    {

        cout<<root->word<<":"<<root->Amharic<<"\n";
        preorder(root->left);
        preorder(root->right);
    }

}
node *avl::leftmost(node* nod)
{
    node* current = nod;


    while (current->left != NULL)
        current = current->left;

    return current;
}
/*Deletion is more complicated than insertion. The deletion of a node from a tree may decrease the height of the tree which may lead to unbalanced tree structure.
 So appropriate rotation operation is performed to rebalance the tree.
 Present the user with a menu (i.e. interactive) that allows him or her
  to search the list for a specified word, insert a new word, delete an existing word,
  or print the entire list in ascending order of words.*/
node* avl::delet(node *n,string w)  // STEP 1: PERFORM STANDARD BST DELETE
{
        if(n==NULL)
        return n;

        // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree

         // If the key to be deleted is greater
    // than the root's key, then it lies
    // in right subtree

        if(w<n->word)
                n->left=delet(n->left,w);
        else if(w>n->word)
                n->right=delet(n->right,w);
        else
        {
                if((n->left==NULL) ||(n->right==NULL))
                {
                        node *temp=n->left?n->left:n->right;

                        if(temp==NULL) // No child case
                        {
                                temp=n;
                                n=NULL; // Copy the contents of
                           // the non-empty child
                        }
                        else
                        {
                                n=temp;

                        }

                       delete temp;
                }
                else
                {
                node *temp=leftmost(n->right);

                n->word=temp->word;

                n->right=delet(n->right,temp->word);

                }
        }
        if(n==NULL) // where n is root  // If the tree had only one node
    // then return
        return n;

        n->height=1+max(find_ht(n->left),find_ht(n->right));

        int bal=balance(n);// STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)

        if (bal > 1 && balance(n->left) >= 0)
        return r_rot(n);
        // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case


    if (bal > 1 && balance(n->left) < 0)
    {
        n->left =  l_rot(n->left);
        return r_rot(n);
    }


    if (bal < -1 && balance(n->right) <= 0)
        return l_rot(n);


    if (bal < -1 && balance(n->right) > 0)
    {
        n->right = r_rot(root->right);
        return l_rot(root);
    }

        fstream f ,f1;
        string g;
       f.open("dic.txt",ios::in|ios::out);
       f1.open("dic1.txt",ios::out);
       while(f)
       {
              f>>g;
              if(g!=w)
              {
                  f1<<g;
                  getline(f,g);
                  f1<<g;
                f1<<endl;

              }
              else
              {
              getline(f,g);
              }


              if(f.eof())
              break;

        }
        remove("dic.txt");
        rename("dic1.txt","dic.txt");

    return n;   // Return new root

}
// Driver Code
int main()
{
       avl a;
       fstream f;
      f.open("dic.txt",ios::in);
       string s,w,span;

       while(!f.eof())
       {
        f>>s;
        w=s;
        getline(f,span);
        a.root=a.insert(a.root,w,span);
        if(f.eof())
        break;
       }

       int ch;

      string a1,b;

       while(1)
       {

      cout<<"\n\t********** ENGLISH-Amharic DICTIONARY*********\n";
      cout<<"\n1.For exploring whole dictionary";
      cout<<"\n2.For seacrhing specific word";
      cout<<"\n3.For modifying meaning of a word";
      cout<<"\n4.For deleting a word";
      cout<<"\n5.For inserting a word";
      cout<<"\n6.Exit";

      cout<<"\nYOUR CHOICE : ";
      cin>>ch;

      switch(ch)
      {
        case 1: a.preorder(a.ret());
                break;
        case 2:cout<<"\n Enter word ";
               cin>>s;
               a.search(a.ret(),s);
               break;
        case 3: cout<<"\n Enter word ";
                cin>>s;
                a.modify(a.ret(),s);
                cin.clear();
                cin.ignore();
                break;
        case 4: cout<<"\n Enter word ";
                cin>>s;
                a.delet(a.ret(),s);
                break;
        case 5:
                cout<<"\n Enter Word : ";
                cin>>s;
                cout<<"\n Enter Amharic equivalent : ";
                cin>>w;
                a.insert(a.ret(),s,w);

                f.open("dic.txt",ios::in);


               while(!f.eof())
               {
                f>>a1;
                getline(f,b);

                if(f.eof())
                {
                f<<s;
                f<<" ";
                f<<w;
                f<<endl;
                break;
                }

                break;

        case 6: cout<<"Thanks for visiting Kidus GITHIB!! ";
                break;
      }



     }
     return 0;
     }
}

