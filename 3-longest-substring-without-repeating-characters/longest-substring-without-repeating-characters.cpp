class Solution {
public:
int max(int i,int j)
{
      return  i>j?i:j;
}
    int lengthOfLongestSubstring(string s) {

        unordered_set<char>store;
        int i=0,j=0,sum=0;
        int n=s.length();
        if(n==0||n==1) return n; 
        store.insert(s[j++]);
        while(j<n)
        {
          while(store.find(s[j])!=store.end())
          {
            store.erase(s[i++]);

          }
          store.insert(s[j++]);
          sum=max(sum,store.size());
        }
        return  sum>store.size()?sum:store.size();
    }
};