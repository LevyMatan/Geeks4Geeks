    long long int numoffbt(long long int arr[], int n)
    {
        long long int maxValue = LLONG_MIN;
        long long int minValue = LLONG_MAX;
        long long int MOD = 1000000007;
        for (int i = 0; i < n; i++)
        {
            maxValue = (maxValue < arr[i]) ? (arr[i]) : (maxValue);
            minValue = (minValue > arr[i]) ? (arr[i]) : (minValue);
        }
     
        vector<bool> mark(maxValue+1, false);
        vector<long long int> value(maxValue+1, 0);

        for(int i=0; i<n; ++i){
            mark[arr[i]] = true; // it is there
            value[arr[i]] = 1; // single node forms a complete binary tree
        }
        int ans = 0;
        for(long long int i=minValue; i<=maxValue; ++i){
            if(mark[i]){ // if it is prime, go for multiples and unmark them, similarly, if it is there in arr, find for other node to get a parent node which is in array
                for(long long int j=i+i; j<=maxValue && j<=i*i; j+=i){
                    if(mark[j] == false){
                        continue; // not there in array
                    }
                    value[j] = (value[j]+value[i]*value[j/i]%MOD)%MOD;
                    // we can interchage left subtree and right subtree
                    if(i != j/i){
                        value[j] = (value[j]+value[i]*value[j/i]%MOD)%MOD;
                    }
                }
            }
            ans = (ans + value[i])%MOD;
        }
        return ans;
    }
