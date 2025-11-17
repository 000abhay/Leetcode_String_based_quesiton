/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
map<pair<int,int>,vector<TreeNode*>>memo;

vector<TreeNode*> fun(int start,int end)
{

if(start>end)return {nullptr};

if(start==end) {

    TreeNode *root=new TreeNode(start);
    return {root};
}
 vector<TreeNode*>result;
for(int i=start;i<=end;i++)
{
    vector<TreeNode*>left=fun(start,i-1);
    vector<TreeNode*>right=fun(i+1,end);
    
for(TreeNode* l:left)
{
    for(TreeNode* r:right)
    {
        TreeNode *root=new TreeNode(i);
        root->left=l;
        root->right=r;
        result.push_back(root);
    }
}
}




return result;
}
    vector<TreeNode*> generateTrees(int n) {
        return fun(1,n);
    }
};