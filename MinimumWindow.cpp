#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;


//class Solution {
//public:
//	string minWindow(string S, string T) {
//		int min=0;
//		string res="";
//		int count;
//		map<char,int> m;
//		map<char,int>::iterator it;
//		const char *tt=T.c_str();
//		for(int i=0;i<T.size();i++){
//			it=m.find(*(tt+i));
//			if(it==m.end()){
//				m[*(tt+i)]=i;
//			}
//			else
//				continue;
//		}
//		const char *ss=S.c_str();
//		const char *begin=ss;
//		const char *end=ss;
//		//	vector<int> v;
//		while(*ss!=0){
//			count=0;
//			map<char,int> only;
//			while(m.find(*ss)==m.end()&&*ss!=0){//这里存在边界问题
//				ss++;
//			}
//			if(!*ss)
//				return res;
//			count++;
//			only[*ss]=count;
//			end=ss+1;
//			while(count!=m.size()&&*end!=0){
//				if(m.find(*end)==m.end()){
//					end++;
//					continue;
//				}
//				else{
//					if(only.find(*end)==only.end()){
//						count++;
//						only[*end]=count;
//						end++;
//					}
//					else{
//						end++;
//						continue;
//					}
//				}
//			}
//			if(count==m.size()){
//				if(min==0){
//					min=(end-ss);
//					res=S.substr(ss-begin,end-ss);
//				}
//				else{
//					if(min>(ss-end)+1){
//						min=end-ss;
//						res=S.substr(ss-begin,end-ss);
//					}
//				}
//				ss++;
//			}
//			else{
//				break;
//			}
//		}
//		return res;
//	}
//};




//class Solution {
//public:
//	string minWindow(string S, string T) {
//		map<char,int> m;
//		int min=0;
//		//当T中有S没有的字母情况暂时没考虑
//
//		int slen = S.length();
//		int tlen = T.length();
//		if (slen < tlen || slen == 0 || tlen == 0) {
//			return "";
//		}
//
//		for(int i=0;i<tlen;i++)
//			if(m.find(T[i])==m.end())
//				m[T[i]]=i;
//
//		vector<int> v;
//
//		for(int i=0;i<slen;i++)
//			if(m.find(S[i])!=m.end())
//				v.push_back(i);
//
//		int j=0;
//		int k=j;
//		int begin=j;
//		int count=0;
//		int vsize=v.size();
//		int msize=m.size();
//		
//		while(j<vsize){
//			k=j;
//			//	begin=j;
//			count=0;
//			map<char,int> mm;
//			mm.clear();
//			if((j+1)<vsize&&S[v[j]]==S[v[j+1]]){
//				j++;
//				continue;
//			}
//			while(k<vsize&&count!=msize){
//				if(mm.find(S[v[k]])==mm.end()){
//					if(min!=0&&(v[k]-v[j]+1)>min)
//						break;
//					else{
//						mm[S[v[k]]]=k;
//						count++;
//						k++;
//					}
//				}
//				else
//					k++;
//			}
//			if(count==msize){
//				if(min==0||min>v[k-1]-v[j]+1){
//					min=v[k-1]-v[j]+1;
//					begin=v[j];
//					j++;
//				}
//				else
//					j++;
//			}
//			else
//				j++;
//			if(k==vsize)
//				break;
//
//
//		}
//		return S.substr(begin,min);
//	}
//};




class Solution {
public:
	string minWindow(string S, string T) {
		map<char,int> m;
		int min=0;
		int slen = S.length();
		int tlen = T.length();
		if (slen < tlen || slen == 0 || tlen == 0) {
			return "";
		}
		for(int i=0;i<tlen;i++)
			if(m.find(T[i])==m.end())
				m[T[i]]=i;
		vector<int> v;
		int k=0;
		int count=0;
		int vsize=v.size();
		int msize=m.size();
		int vcount=0;
		int pre=k;
		vector<int> vv(256,0);
		map<char,int> mm;
		for(int i=0;i<slen;i++){

			if(m.find(S[i])!=m.end()&&count!=msize){
				v.push_back(i);
				vv[S[i]]++;
				if(mm.find(S[i])==mm.end()){
					count++;
					mm[S[i]]=i;
				}
			}
			if(count==msize){
				vsize=v.size();
				if(vcount==0&&vcount<vsize){
					k=v[vcount];
					pre=k;
				}
				if(min==0)
					min=i-k+1;
				else
					if(min>(i-k+1))
						min=i-k+1;
				vcount++;
				if(vcount<vsize){
					if(vv[S[k]]==1){
						count--;
						mm.erase(S[k]);
						vv[S[k]]--;
						pre=k;
						k=v[vcount];
					}
					else{
						while(vv[S[k]]!=1){
							vv[S[k]]--;
							k=v[vcount];
							pre=k;
						}
					}
				}
			}
		}
		return S.substr(pre,min);
	}
};




class Solution2 {
public:
	string minWindow(string S, string T) {
		// IMPORTANT: Please reset any member data you declared, as
		// the same Solution instance will be reused for each test case.
		vector<int> count(256, 0), cur_count(256, 0);
		int lp = -1, rp = -1, ans = 0x7fffffff, lb = 0, lack = T.size();
		for(int i = 0; i < T.size(); ++i)
			++count[T[i]];
		for(int i = 0; i < S.size(); ++i) {
			if(cur_count[S[i]] < count[S[i]])
				--lack;
			++cur_count[S[i]];
			if(lack == 0) {
				while(lb <= i && (cur_count[S[lb]] - 1 >= count[S[lb]])) {
					--cur_count[S[lb]];
					++lb;
				}
				if(ans > i - lb + 1) {//ans是记录当前最短匹配字符串的长度
					ans = i - lb + 1;
					lp = lb;
					rp = i;
				}
				while(lb <= i && lack == 0) {
					--cur_count[S[lb]];
					if(cur_count[S[lb]] < count[S[lb]]) {
						++lack;
					}
					++lb;
				}
			}
		}
		return lp == -1?"":S.substr(lp, rp - lp + 1);
	}
};

class Solution3 {
public:
	string minWindow(string S, string T) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int cnt_map[256], ex_map[256];
		memset(cnt_map, 0, sizeof(cnt_map));
		memset(ex_map, 0, sizeof(ex_map));
		int slen = S.length();
		int tlen = T.length();
		if (slen < tlen || slen == 0 || tlen == 0) {
			return "";
		}
		for (int i = 0; i < tlen; i++) {
			cnt_map[ T[i] ]++;
		}
		int match_count = 0, left = 0, right = 0;
		int st_pos, len = slen + 1;
		while (right < slen) {
			while (right < slen && match_count < tlen) {
				ex_map[ S[right] ]++;
				if (ex_map[ S[right] ] <= cnt_map[ S[right] ]) {
					match_count++;
				}
				right++;
			}
			while (left < right && ex_map[ S[left] ] > cnt_map[ S[left] ]) {
				ex_map[ S[left] ]--;
				left++;
			}
			if (match_count == tlen) {
				if (len > right - left) {
					st_pos = left;
					len = right - left;
				}
			}
			ex_map[ S[left] ]--;
			match_count--;
			left++;
		}
		if (len == slen + 1) {
			return "";
		} else {
			return S.substr(st_pos, len);
		}
	}
};


class Solution4 {
public:
	string minWindow(string S, string T) {
		if (S.empty()) return "";
		if (S.size() < T.size()) return "";
		const int ASCII_MAX = 256;
		int appeared_count[ASCII_MAX];
		int expected_count[ASCII_MAX];
		fill(appeared_count, appeared_count + ASCII_MAX, 0);
		fill(expected_count, expected_count + ASCII_MAX, 0);
		for (size_t i = 0; i < T.size(); i++) expected_count[T[i]]++;
		int minWidth = INT_MAX, min_start = 0; // 窗口大小，起点
		int wnd_start = 0;
		int appeared = 0; // 完整包含了一个T
		//尾指针不断往后扫
		for (size_t wnd_end = 0; wnd_end < S.size(); wnd_end++) {
			if (expected_count[S[wnd_end]] > 0) { // this char is a part of T
				appeared_count[S[wnd_end]]++;
				if (appeared_count[S[wnd_end]] <= expected_count[S[wnd_end]])
					appeared++;
			}
			if (appeared == T.size()) { // 完整包含了一个T
				// 收缩头指针
				while (appeared_count[S[wnd_start]] > expected_count[S[wnd_start]]
				|| expected_count[S[wnd_start]] == 0) {
					appeared_count[S[wnd_start]]--;
					wnd_start++;
				}
				if (minWidth > (wnd_end - wnd_start + 1)) {
					minWidth = wnd_end - wnd_start + 1;
					min_start = wnd_start;
				}
			}
		}
		if (minWidth == INT_MAX) return "";
		else return S.substr(min_start, minWidth);
	}
};


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////思路：利用两组数组记录，当两个数组的情况是一样的 那么当前S字符串中已经出现了T中所有的字符，要在这个S字符串中找到开始的位置，记录
//////////////
//////////////////////////////////////////////////////////////////////////////////////////

class Solutionfun {
public:
	string minWindow(string S, string T) {
		int ss[256],tt[256];
		memset(ss, 0, sizeof(ss));
		memset(tt, 0, sizeof(tt));
		int slen=S.length(),min=0,tlen=T.length();
		if (slen < tlen || slen == 0 || tlen == 0)
			return "";
		for(int i=0;i<tlen;++i)
			tt[T[i]]++;
		int lack=tlen,start=0,pre=start;
		for(int i=0;i<slen;++i){
			if(ss[S[i]]<tt[S[i]])
				lack--;
			ss[S[i]]++;
			if(lack==0){
				while(start<i&&ss[S[start]]>tt[S[start]]){//虽然当前start到i肯定是包含了T字符串，但是并不是唯一长度，需要收缩
					ss[S[start]]--;//相当于把前面的字符都丢掉，重新的字符从唯一的那个开始
					++start;//start指向唯一的那个
				}
				if(min==0||min>(i-start+1)){
					min=i-start+1;
					pre=start;//记录当前min开始的位置
				}
				ss[S[start]]--;
				++start;
				lack++;	
			}
		}
		return S.substr(pre,min);
	}
};




int main(){//
	string S,T;
	S = "cabwefgewcwaefgcf";
	T = "cae";
	/*map<char,int> m;
	map<char,int>::iterator it;
	const char *tt=T.c_str();
	for(int i=0;i<T.size();i++){
	it=m.find(*(tt+i));
	if(it==m.end()){
	m[*(tt+i)]=i;
	}
	else
	continue;
	}
	cout<<(m.find('A')==m.end())<<endl;*/
	string res;
	Solution4 s;
	res=s.minWindow(S,T);
	cout<<res<<endl;
	return 0;
}