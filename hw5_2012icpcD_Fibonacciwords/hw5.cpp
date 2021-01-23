# include <iostream>
# include <fstream>
# include <string>
# include <cstdlib>
# include <vector>
using namespace std;

long long int FibonacciWords(int n, string p){
    int p_len = p.length();
    for(int i = 0; i < p_len; i++){
        if(p[i] == '0' && p[i+1] == '0'){
            return 0;
        }
    }
    for(int i = 0; i < p_len; i++){
        if(p[i] == '1' && p[i+1] == '1' && p[i+2] == '1'){
            return 0;
        }
    }
    for(int i = 0; i < p_len; i++){
        if(p[i] == '0' && p[i+1] == '1' && p[i+2] == '0' && p[i+3] == '1' && p[i+4] == '0'){
            return 0;
        }
    }    

    long long int ans = 0; 
    bool canFind = false;
    bool case1 = false;
    bool case2 = false;
    int firstOccr = -1;
    string n2 = "0";
    string n1 = "1";

    //Fibonacci 1~n
    long long int fib[101] = {0};
    fib[0] = 0;
    fib[1] = 1;
    for(int i = 2; i <= n + 1; i++){
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    // cout << "fib[3]: " << fib[3] << endl;
    //p length = 1
    if(p == "0"){ 
        if(n == 0){
            return 1;
        }
        firstOccr = 0;
    }
    else if(p == "1"){
        firstOccr = 1;
    }
    //p length > 1
    else{
        for(int i = 2; i <= n; i++){
            string cur = n1 + n2;
            int cur_len = cur.length();
            if(cur_len >= p_len && cur.find(p) != -1){
                    canFind = true;
                    firstOccr = i;

                    string curPlus1 = cur + n1;
                    string curPlus2 = curPlus1 + cur;

                    if(curPlus1.substr(fib[i+1] - p_len + 1, 2*p_len - 2).find(p) != -1){
                        case1 = true;
                   //     cout << "CASE1" << endl;
                    }
                    if(curPlus2.substr(fib[i+2] - p_len + 1, 2*p_len - 2).find(p) != -1){
                        case2 = true;
                  //      cout << "CASE2" << endl;
                    }
                break;
            }
            n2 = n1;
            n1 = cur;
        }
    }
    if (firstOccr <= n){
      //  cout << "firstOccur: " << firstOccr << endl;
        if(firstOccr == 0)
            ans += fib[n - 1];
        else
            ans += fib[n - firstOccr + 1];
       // cout << ans << endl;
        if(case2 && !case1){//let say p occur first on n = x. p also occur on the boarder of x+2.
          //  cout << "Case 2" << endl;
            int i = firstOccr + 2;
            while(i <= n){
                ans += fib[n - i + 1];
                i = i + 2;
            }

        }
        if(case1){ //let say p occur first on n = x. p also occur on the boarder of x+1.
            int i = firstOccr + 1;
         //   cout << "Case 1" << endl;
            while(i <= n){
                ans += fib[n - i + 1];
                i = i + 1;
            }
        }   
        return ans;
    }
    return 0;
}


int main(int argc, char* argv[]){
    string s;
    fstream fin;
    fin.open(argv[1]);
    int n = 0;
    int i = 1;
    int caseCnt = 1;
    string p;

    if (!fin)
    {
        cout << "Failed Loading File..." << endl;
    }
    while (getline(fin,s))
    {
        if (i % 2 == 1)
        {
            n = atoi(s.c_str());
            i++;
        }
        else
        {
            p = s;
            i++;
            cout << "Case " << caseCnt << ": " << FibonacciWords(n,p) << endl;
            caseCnt++;
        }
    }

    fin.close();
}



    