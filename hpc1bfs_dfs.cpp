#include<bits/stdc++.h>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode* right;
    TreeNode(int x): val(x),left(NULL),right(NULL) {}
};

void bfs(TreeNode* root)
{
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty())
    {
        TreeNode* node=q.front();
        q.pop();
        cout<<node->val<<" ";
        if(node->left){ q.push(node->left);}
        if(node->right){ q.push(node->right);}
    }
}

void pll_bfs(TreeNode* root)
{
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
    int qsize=q.size();
    #pragma omp parallel for
    for(int i=0;i<qsize;i++)
    {
        TreeNode* node;
        #pragma omp critical
        {
            node=q.front();
            q.pop();
            cout<<node->val<<" ";
        }
        if(node->left){q.push(node->left);}
        if(node->right){q.push(node->right);}
    }
    }
}

void dfs(TreeNode* root)
{
    stack<TreeNode*>s;
    s.push(root);
    while(!s.empty())
    {
        TreeNode* node=s.top();
        s.pop();
        cout<<node->val<<" ";
        if(node->right){s.push(node->right);}
        if(node->left){s.push(node->left);}
        
    }
}

void pll_dfs(TreeNode* root)
{
    stack<TreeNode*>s;
    s.push(root);
    while(!s.empty())
    {
        int ssize=s.size();
        #pragma omp parallel for
        for(int i=0;i<ssize;i++)
        {
            TreeNode *node;
            #pragma omp critical
            {
                node=s.top();
                s.pop();
                cout<<node->val<<" ";

            }
            if(node->right){ s.push(node->right);}
            if(node->left){ s.push(node->left);}
            
        }
    }
}

int main()
{
    TreeNode* root=new TreeNode(1);
    root->left=new TreeNode(2);
    root->right=new TreeNode(3);
    root->left->left=new TreeNode(4);
    root->left->right=new TreeNode(5);
    root->right->left=new TreeNode(6);
    root->right->right=new TreeNode(7);

    cout<<"\nBFS Traversal: ";
    auto start=chrono::high_resolution_clock::now();
    bfs(root);
    auto end=chrono::high_resolution_clock::now();
    cout<<"\nBFS took "<<chrono::duration_cast<chrono::microseconds>(end-start).count()<<" microseconds"<<endl;
    cout<<endl;

    cout<<"\nParallel BFS Traversal: ";
    start=chrono::high_resolution_clock::now();
    pll_bfs(root);
    end=chrono::high_resolution_clock::now();
    cout<<"\nParallel BFS took "<<chrono::duration_cast<chrono::microseconds>(end-start).count()<<" microseconds"<<endl;
    cout<<endl;

    

    cout<<"\nDFS Traversal: ";
    start=chrono::high_resolution_clock::now();
    dfs(root);
    end=chrono::high_resolution_clock::now();
    cout<<"\nDFS took "<<chrono::duration_cast<chrono::microseconds>(end-start).count()<<" microseconds"<<endl;
    cout<<endl;

    

    cout<<"\nParallel DFS Traversal: ";
    start=chrono::high_resolution_clock::now();
    pll_dfs(root);
    end=chrono::high_resolution_clock::now();
    cout<<"\nParallel DFS took "<<chrono::duration_cast<chrono::microseconds>(end-start).count()<<" microseconds"<<endl;
    cout<<endl;

}