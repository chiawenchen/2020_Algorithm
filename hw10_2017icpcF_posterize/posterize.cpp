# include <iostream>
# include <fstream>
# include <string>
# include <cstring>
# include <vector>
using namespace std;
const int MAX = 260;


int main(int argc, char* argv[]){
    long long dp[MAX][MAX];
    long long f[MAX][MAX]; //Error value query set for each combination of reds. 
    vector<long long> r; //true red intensity value.
    vector<long long> p; //number of pixels having red intensity.
    r.push_back(-1);//start from 1
    p.push_back(-1);//start from 1

    int d = 0, k = 0;
    string s = ""; //string for io
    fstream fin;
    fin.open(argv[1]);
    int i = 0; // line flag
    while(getline(fin,s)){
        // read d, k
        if(i == 0){
            int findAt = s.find(' ');
            string temp = "";
            for(int j = 0; j < findAt; j++){
                temp += s[j];
            }
            d = stoi(temp);
            temp = "";
            for(int j = findAt; j < s.size(); j++){
                if (s[j] != '\n')  temp += s[j];
            }
            k = stoi(temp);
            i++;
            continue;
        }
        // read the following d lines
        int findAt = s.find(' ');
        string temp = "";
        for(int j = 0; j < findAt; j++){
            temp += s[j];
        }
        r.push_back(stoi(temp));
        temp = "";
        for(int j = findAt; j < s.size(); j++){
            if (s[j] != '\n')  temp += s[j];
        }
        p.push_back(stoi(temp));
    }

    memset(f,0x7f,sizeof f);//max number

    //find the closet pixels for each red intensity combination.
    for(int l = 0; l < 256; l++){
        for(int i = 1; i <= d; i++){
            long long int ans = 0;
            for(int j = i; j <= d; j++){
                ans += (r[j]-l) * (r[j]-l) * p[j];//sum of squared errors
                f[i][j] = min(f[i][j], ans); //Error value query set for each combination of reds.
            }
        }
    }
    //Initialization
    memset(dp,0x7f,sizeof dp); //max number
    dp[0][0] = 0;

    //assign error value for each blank 
    for(int i = 1; i <= d; i++){
        for(int j = 1; j <= k; j++){
            for(int l = 0; l < i; l++){
                dp[i][j] = min(dp[i][j], dp[l][j-1] + f[l+1][i]);
            }
        }
    }
    cout << dp[d][k] << "\n";
    fin.close();
}
