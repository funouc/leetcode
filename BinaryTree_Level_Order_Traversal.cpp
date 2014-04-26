#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

//Definition for binary tree
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	vector<vector<int> > levelOrder(TreeNode *root) {
		queue<TreeNode*> q;
		if(root)
			q.push(root);
		TreeNode *p;
		queue<TreeNode*> s;
		vector<vector<int>> vv;
		while(!q.empty()){
			vector<int> v;
			v.clear();
			while(!q.empty()){
				p=q.front();
				v.push_back(p->val);
				s.push(p);
				q.pop();
			}
			vv.push_back(v);
			while(!s.empty()){
				p=s.front();
				if(p->left) q.push(p->left);
				if(p->right) q.push(p->right);
				s.pop();
			}
		}
		return vv;
	}
};

class Solution2 {
public:
	vector<vector<int> > levelOrder(TreeNode *root) {
		queue<TreeNode*> q;
		if(root)
			q.push(root);
		TreeNode *p;
		queue<TreeNode*> s;
		vector<vector<int>> vv;
		vector<int> v;
		while(!q.empty()){
			v.clear();
			while(!q.empty()){
				p=q.front();
				v.push_back(p->val);
				s.push(p);
				q.pop();
			}
			vv.push_back(v);
			while(!s.empty()){
				p=s.front();
				if(p->left) q.push(p->left);
				if(p->right) q.push(p->right);
				s.pop();
			}
		}
		int j=vv.size()-1;
		int start=0;
		while(start<j){
			v=vv[j];
			vv[j]=vv[start];
			vv[start]=v;
			j--;
			start++;
		}
		return vv;
	}
};