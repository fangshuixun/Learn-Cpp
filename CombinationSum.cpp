//回溯法

class Solution {
public:
    int Check(const vector<int> &result,int target)
    {
        int sum=accumulate(result.begin(),result.end(),0);
        if(sum==target)
            return 1;
        if(sum<target)
            return 0;
        if(sum>target)
            return 2;
    }
    void insertComination(vector<int> &candidate,int target,vector<int> &test,vector<vector<int>> &result)
    {
        for(auto element:candidate)
        {
            test.push_back(element);
            if(Check(test,target)==0)
                insertComination(candidate,target,test,result);
            else if(Check(test,target)==1)
            {
                vector<int> vec=test;
                sort(vec.begin(),vec.end());
                result.push_back(vec);
            }
           // else
            //{
            //    test.pop_back();
            //    continue;
            //}
            test.pop_back();
        }    
    }
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> result;
        vector<int> test;
        insertComination(candidates,target,test,result);
        sort(result.begin(),result.end());
        auto unique_end=unique(result.begin(),result.end());
        result.erase(unique_end,result.end());
        return result;
    }
};