#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'isBalanced' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

bool isBracketsBalanced(char a, char b){
    if(a == '{' && b == '}'){
        return true;
    }
    if(a == '(' && b == ')'){
        return true;
    }
    if(a == '[' && b == ']'){
        return true;
    }
    return false;
}

bool getBracketNature(char a){
    if(a == '(' || a == '{' || a == '['){
        return true;
    }
    else{
        return false;
    }
}
string isBalanced(string s) {
    int top = -1;
    bool valid = true;
    char stack[100], temp;
    for(int i=0;i<int(s.size());i++){
        if(getBracketNature(s[i])){
            stack[++top] = s[i];
        }
        else{
            if(top == -1){
                valid = false;
                break;
            }else{
                temp = stack[top--];
                if(!isBracketsBalanced(temp, s[i])){
                    valid = false;
                }
            }
        }
    }
    if(top >= 0){
        while(top >= 0){
            temp = stack[top--];
            valid = false;
        }
    }
    if(!valid) return "NO";
    else{
        return "YES";
    }

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string s;
        getline(cin, s);

        string result = isBalanced(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
