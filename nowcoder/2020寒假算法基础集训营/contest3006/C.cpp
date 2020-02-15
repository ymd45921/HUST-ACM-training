/**
 * 
 * 纯粹麻烦的要死的模拟
 * 直接贴题解代码
 */
#include <bits/stdc++.h>
using namespace std;
 
string source;
void replaceAll(string &s, string oldstr, string newstr)
{
    for (string::size_type pos = 0; pos != string::npos; pos += newstr.length())
        if ((pos = s.find(oldstr, pos)) != string::npos) s.replace(pos, oldstr.length(), newstr);
        else break;
}
struct functions{
    string inClass, name, outputType;
    vector<string> inputType;
    functions(string inClass = "", string name = "", string outputType = "void", vector<string> inputType = vector<string>(0))
    :inClass(inClass), name(name), outputType(outputType), inputType(inputType) {}
};
vector<functions> funs;
void solve(string &s)
{
    replaceAll(s, "/*", " /* ");
    replaceAll(s, "*/", " */ ");
    replaceAll(s, "//", " // ");
    replaceAll(s, "(", " ( ");
    replaceAll(s, ")", " ) ");
    replaceAll(s, "{", " { ");
    replaceAll(s, "}", " } ");
    replaceAll(s, "=", " = ");
    replaceAll(s, "\"", " \" ");
    replaceAll(s, "'", " ' ");
    replaceAll(s, ";", " ; ");
    replaceAll(s, ",", " , ");
    replaceAll(s, "+ = ", "+=");
    replaceAll(s, "- = ", "-=");
    replaceAll(s, "* = ", "*=");
    replaceAll(s, "/ = ", "/=");
    replaceAll(s, "^ = ", "^=");
    replaceAll(s, "| = ", "|=");
    replaceAll(s, "& = ", "&=");
    replaceAll(s, ":", " : ");
    replaceAll(s, " :  : ", "::");
    //ע���滻������ע��
    vector<string> tokens; string now = "";
    for (int i = 0; s[i]; i++)
    {
        if (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n' || s[i] == '\0')
        {
            if (now != "")
            {
                if (now == ":" && tokens.back() == ")")
                {
                    string tmpnow = "";
                    for (int j = i + 1; s[j]; j++)
                    {
                        if (s[j] == ' ' || s[j] == '\t' || s[j] == '\r' || s[j] == '\n' || s[j] == '\0')
                        {
                            if (tmpnow == "{")
                            {
                                now = "{";
                                i = j - 1;
                                break;
                            }
                            tmpnow = "";
                        }
                        else tmpnow += s[j];
                    }
                    continue;
                }
                if (now == "const")
                {
                    now = "";
                    continue;
                }
                if (now == "//")
                {
                    for (int j = i; s[j]; j++)
                    {
                        if (s[j] == '\n')
                        {
                            i = j - 1;
                            break;
                        }
                    }
                    now = "";
                    continue;
                }
                if (now == "/*")
                {
                    int num = 1;
                    string tmpnow = "";
                    for (int j = i + 1; s[j]; j++)
                    {
                        if (s[j] == ' ' || s[j] == '\t' || s[j] == '\r' || s[j] == '\n' || s[j] == '\0')
                        {
                            if (tmpnow == "/*") num++;
                            if (tmpnow == "*/")
                            {
                                num--;
                                if (num == 0)
                                {
                                    i = j - 1;
                                    break;
                                }
                            }
                            tmpnow = "";
                        }
                        else tmpnow += s[j];
                    }
                    now = "";
                    continue;
                }
                //cout << now << s[i];
                tokens.push_back(now);
                now = "";
            }
            //else cout << s[i];
        }
        else now += s[i];
    }
    int cnt = 0;
    string nowNamespace = "";
    for (int i = 1; i < (int)tokens.size(); i++)
    {
        if ((tokens[i] == "struct" || tokens[i] == "class") && tokens[i + 2] == "{")
        {
            cnt = 0;
            nowNamespace = tokens[i + 1];
            i += 2;
        }
        functions tmp(nowNamespace);
        if (tokens[i] == "{" && tokens[i - 1] == ")")
        {
            int num = 1;
            for (int j = i - 2; j >= 0; j--)
            {
                if (tokens[j] == ")") num++;
                if (tokens[j] == "(")
                {
                    num--;
                    if (num == 0)
                    {
                        tmp.name = tokens[j - 1];
                        tmp.outputType = "";
                        for (int k = j - 2; k >= 0; k--)
                            if (tokens[k] != "}" && tokens[k] != "}" && tokens[k] != ";" &&
                                tokens[k].back() != ':' && tokens[k] != "inline" &&
                                tokens[k] != "static" && tokens[k][0] != '#' &&
                                tokens[k].back() != '\"' && tokens[k].back() != '>')
                                tmp.outputType = tmp.outputType == "" ? tokens[k] : tokens[k] + " " + tmp.outputType;
                            else break;
                        int last = i - 2;
                        for (int k = i - 2; k >= j; k--)
                        {
                            if (tokens[k] == "(" || tokens[k] == ",")
                            {
                                string tt = "";
                                for (int t = k + 1; t < last; t++)
                                    tt = tt == "" ? tokens[t] : tt + " " + tokens[t];
                                if (tt != "") tmp.inputType.push_back(tt);
                                last = k - 1;
                            }
                            if (tokens[k] == "=" || tokens[k] == ")") last = k - 1;
                        }
                        reverse(tmp.inputType.begin(), tmp.inputType.end());
                        break;
                    }
                }
            }
            funs.push_back(tmp);
            num = 1;
            for (int j = i + 1; j < (int)tokens.size(); j++)
            {
                if (tokens[j] == "{") num++;
                if (tokens[j] == "}")
                {
                    num--;
                    if (num == 0)
                    {
                        i = j;
                        //cout << tmp.outputType << " " << tmp.name << " ";
                        //cout << j << endl;
                        break;
                    }
                }
            }
            continue;
        }
        if (nowNamespace != "")
        {
            //cout << i << " " << nowNamespace << " " << cnt << endl;
            if (tokens[i] == "{") cnt++;
            if (tokens[i] == "}")
            {
                cnt--;
                if (!cnt) nowNamespace = "";
            }
        }
    }
}
int main()
{
    char ch;
    while ((ch = getchar()) != EOF)
        source += ch;
    solve(source);
    for (auto & i: funs)
    {
        if (i.outputType != "") cout << i.outputType << " ";
        if (i.inClass != "") cout << i.inClass << "::";
        cout << i.name << "(";
        for (int j = 0; j < (int)i.inputType.size(); j++)
            cout << i.inputType[j] << (j == (int)i.inputType.size() - 1 ? ")" : ",");
        if ((int)i.inputType.size() == 0) cout << ")";
        cout << endl;
    }
    return 0;
}