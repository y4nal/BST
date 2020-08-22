#include<iostream>
using namespace std;
template<typename T>
class   TNode {
private:
    T  key;
    TNode* right, * left, * parent;
    template<typename T>
    friend class Tree;
    public:
            T getData(TNode*R){return R->key;}
};
template<typename T>
class Tree
{
private:
    int n;
    TNode<T>* Root;
public:
    Tree() :Root(NULL), n(0) {}
    bool empty()
    {
        return  Root == NULL;
    }
    ~Tree()
    {

    }
    TNode<T>* search(TNode<T>* p, int key)
    {

        if (!p) return NULL;
        while (p) {
            if (key == p->key) return  p;
            else if (key < p->key)
                p = p->left;
            else
                p = p->right;
        }
        return NULL;
    }


    void insert(int item)
    {
        TNode<T>* ptr = new TNode<T>;
        ptr->key = item;
        ptr->left = ptr->right = ptr->parent = NULL;

        if (empty()) { Root = ptr; n++;return; }

        TNode<T>* prev = NULL, * cur = Root;
        while (cur != NULL)
        {
            prev = cur;
            if (item > cur->key){
                cur = cur->right;
                 }

            else
            { 
                cur = cur->left;
               
                }
        }
        if (item > prev->key)
        {
            prev->right = ptr;
            ptr->parent = prev;
        }

        else
        {

            prev->left = ptr;
            ptr->parent = prev;
        }
    }



    bool remove(TNode<T>* N) {
        if (N == NULL) return false;
        if (N->left == N->right) {
            TNode<T>* p = N->parent;
            if (N == p->right)
                p->right = NULL;
            else
                p->left = NULL;
            delete  N;
        }
        return true;
    }




    TNode<T>* Succ(T item)
    {
        TNode<T>* P = find(Root, item);
        if (P == NULL) { cout << "No Item in Tree";return NULL; }
        if (P->right != NULL)
        {
            TNode<T>* s = P->right;
            while (s->left != NULL)s = s->left;
            return s;
        }
        else
        {
            int x = 0;
            int* a = findAncestors(item);
            for (int i = 1;i < a[0];i++)
            {
                if (a[i] > item)
                    x = item;
                break;
            }
            P = find(Root, x);
            return P;
        }
    }


    TNode<T>* find(TNode<T>* Node, T key)
    {
        if (Node == NULL || Node->key == key)
            return Node;

        if (Node->key < key)
            return find(Node->right, key);


        return find(Node->left, key);
    }

    
    TNode<T>* minValueNode(TNode<T>* node)
    {
        TNode<T>* current = node;

        while (current && current->left != NULL)
            current = current->left;

        return current;
    }


   T getData(TNode<T>*S)
    {
        return S->key;
    }


   void findSuccPre(TNode<T>* root, TNode<T>*& pre, TNode<T>*& suc, T info) {

       /*if key(the given node) is the root*/
       if (root == NULL) { return; }

       if (root->key == info) {
           if (root->left != NULL) {
               TNode<T>* temp = root->left;
               while (temp->right != NULL) {
                   temp = temp->right;
               }
               pre = temp;
           }
           if (root->right != NULL) {
               TNode<T>* temp = root->right;
               while (temp->left != NULL) {
                   temp = temp->left;
               }
               suc = temp;
           }
           return;
       }

       if (root->key > info) {
           suc = root;
           findSuccPre(root->left, pre, suc, info);
       }
       else {
           pre = root; 
           findSuccPre(root->right, pre, suc, info);
       }
   }  
    void DeleteNode(T item)
   {
       TNode<T>*P=find(Root, item);
        if(!P->left&&!P->right) {remove(P); return;}
       TNode<T>* C =P;
       TNode<T>* S = P;
       findSuccPre(Root, C,S,item);
                
           P->key= S->key; 

           if(S->left==S->right)
              remove(S);
               
           else
           {
             if(S->parent->right==S)S->parent->right=S->right;
             if(S->right){S->parent->left=S->right;delete S;}
           } 

         
        
        }
   void Print_LNR(TNode<T>* temp)
   {
        if(temp==NULL)return;
        
        Print_LNR(temp->left);
        cout << temp->key << " ";
        Print_LNR(temp->right);
      
        }

   void Print_RNL(TNode<T>* temp)
   {
       if (temp == NULL)return;
       Print_LNR(temp->right);
       cout << temp->key << " ";
       Print_LNR(temp->left);

   }

   void Print_LRN(TNode<T>* temp)
   {
       if (temp == NULL)return;

       Print_LNR(temp->left);
       Print_LNR(temp->right);
       cout << temp->key << " ";

   }
   void Print_RLN(TNode<T>* temp)
   {
       if (temp == NULL)return;
       Print_LNR(temp->right);
       Print_LNR(temp->left);
       cout << temp->key << " ";

   }
   void Print_NRL(TNode<T>* temp)
   {
       if (temp == NULL)return;
       cout << temp->key << " ";
       Print_LNR(temp->right);
       Print_LNR(temp->left);
      

   }
   void Print_NLR(TNode<T>* temp)
   {
       if (temp == NULL)return;
       cout << temp->key << " ";
       Print_LNR(temp->left);
       Print_LNR(temp->right);
      


   }

   TNode<T>* GetRoot() { return Root; }
  
};
int main(void)

{
    Tree<int> s;
    char selection;



    cout << "\n Menu";

    cout << "\n========";

    cout << "\n A - Insert";

    cout << "\n D - Delete";

    cout << "\n P - Print";

    cout << "\n S - Search";

    cout << "\n X - Exit";

    cout << "\n Enter selection: ";

    // read the input

    cin >> selection;



    switch (selection)

    {

    case 'A':

    case 'a': 
                int i=0;
                cin>>i;
                s.insert(i);
            break;

    case 'D':

    case 'd': int i = 0;
               cin >> i;
        s.DeleteNode(i);

            break;

    case 'P':

    case 'p': s.Print_LNR(s.GetRoot())

            break;

    case 's':

    case 'S': int i = 0;
                 cin >> i;
       s.getData(s.search(s.GetRoot(),i));

            break;

        

    default: cout << "\n Invalid selection";

 

    }

    cout << "\n";



    return 0;

}