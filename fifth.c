#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node *left;
    struct node *right;
};
struct node *root=NULL;

/// creating tree
struct node *create_bst(struct node *root,int item)
{
    if (root==NULL)
    {
        struct node *temp=(struct node *)malloc(sizeof(struct node));
        temp->data=item;
        temp->left=NULL;
        temp->right=NULL;
        root=temp;
        return root;
    }
    else if (item<root->data)
    {
        root->left=create_bst(root->left,item);
    }
    else if (item>root->data)
    {
        root->right=create_bst(root->right,item);
    }
    else
        return NULL;
};

/// inorder traversal
struct node *inorder(struct node *root)
{
    if (root)
    {
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
};

/// preorder traversal
struct node *preorder(struct node *root)
{
    if (root)
    {
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
};

/// postorder traversal
struct node *postorder(struct node *root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->data);
    }
};

/// searching for a no in tree
struct node *searching(struct node *root,int item)
{
    if (root==NULL)
        return NULL;
    else if (item<root->data)
        return searching(root->left,item);
    else if (item>root->data)
        return searching(root->right,item);
    else
        return root;
};

/// finding min element from the tree to swap it with the node have 2 child and is to be deleted
struct node *findminright(struct node *root)
{
    while(root->left != NULL)
        root = root->left;
    return root;
};

/// deletion
struct node *deletion(struct node *root,int item)
{
    if (root==NULL)
        return root;
    else if (item<root->data)
        root->left=deletion(root->left,item);
    else if (item>root->data)
        root->right=deletion(root->right,item);
    else
    {
        if (root->left==NULL && root->right==NULL)  /// having no child
        {
            free(root);
            root=NULL;
        }
        else if (root->left==NULL)  /// having one child
        {
            struct node * temp=root;
            root=root->right;
            free(temp);
        }
        else if (root->right==NULL)     /// having one child
        {
            struct node * temp=root;
            root=root->left;
            free(temp);
        }
        else          /// having two child
        {
            struct node *temp=findminright(root->right);
            root->data=temp->data;
            root->right=deletion(root->right,temp->data);
        }
    }
    return root;
};


int main()
{
    struct node * temp;
    int n,m,p,a,c,val;
    printf("enter the limit of the tree  ::");
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        scanf("%d",&m);
        root=create_bst(root,m);
    }
    while(p!=5)
    {
        printf("\nSELECT ANY OPTION:\n1.TRAVERSAL\n2.SEARCHING\n3.DELETION\n4.ADDITION\n5.EXIT\n");
        scanf("%d",&p);
        switch(p)
        {
        case 1:
            printf("select any traversal\n1.preorder\n2.inorder\n3.postorder\n");
            scanf("%d",&a);
            if (a==1)
            {
                printf("PREORDER::  ");
                preorder(root);
            }
            else if (a==2)
            {
                printf("INORDER:: ");
                inorder(root);
            }
            else if (a==3)
            {
                printf("POSTORDER::  ");
                postorder(root);
            }
            break;
        case 2:
            printf("enter any no to search:: ");
            scanf("%d",&val);
            temp=searching(root,val);
            if (temp!=NULL)
                printf("present\n");
            else
                printf("not present\n");
            break;
        case 3:
            printf("enter the no delete:: ");
            scanf("%d",&val);
            temp=searching(root,val);
            if (temp!=NULL)
                printf("no is present do you want to delete\n1.yes\n2.no\n");
            scanf("%d",&a);
            if (a==1)
            {
                deletion(root,val);
                printf("done");
            }
            else if (a==2)
                break;
            else
                printf("not present can not be deleted\n");
            break;
        case 4:
            printf("enter the no to add:: ");
            scanf("%d",&val);
            root=create_bst(root,val);
            printf("done");
        }
    }
    free(root);
}
