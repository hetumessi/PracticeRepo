/*
    KMP 串的模式匹配 (25 point(s))
    给定两个由英文字母组成的字符串 String 和 Pattern，要求找到 Pattern 在 String 中第一次出现的位置，
    并将此位置后的 String 的子串输出。如果找不到，则输出“Not Found”。

    本题旨在测试各种不同的匹配算法在各种数据情况下的表现。各组测试数据特点如下：

    数据0：小规模字符串，测试基本正确性；
    数据1：随机数据，String长度为10^5，Pattern长度为10；
    数据2：随机数据，String长度为10^5，Pattern长度为10^2；
    数据3：随机数据，String长度为10^5，Pattern长度为10^3；
    数据4：随机数据，String长度为10^5，Pattern长度为10^4；
    数据5：String长度为10^6，Pattern长度为10^5；测试尾字符不匹配的情形；
    数据6：String长度为10^6，Pattern长度为10^5；测试首字符不匹配的情形。
    输入格式:
    输入第一行给出 String，为由英文字母组成的、长度不超过10^6的字符串。第二行给出一个正整数N(≤10)，为待匹配的模式串的个数。
    随后N行，每行给出一个Pattern，为由英文字母组成的、长度不超过10^5的字符串。每个字符串都非空，以回车结束。
    输出格式:
    对每个Pattern，按照题面要求输出匹配结果。

    输入样例:               输出样例:
    abcabcabcabcacabxy     abcabcacabxy
    3                      Not Found
    abcabcacab             Not Found
    cabcabcd
    abcabcabcabcacabxyz
答案：
#include<iostream>
#include<string>
#define range 100500
using namespace std;
int n,mynext[range];
string str,ptn;
void kmp(string),match(string);
int main(){
    cin>>str>>n;
    for(int i=0;i<n;i++){
        cin>>ptn;
        kmp(ptn);
    }
}
void kmp(string ptn){
    int s=0,p=0,lens=str.size(),lenp=ptn.size();
    match(ptn);
    while(s<lens&&p<lenp){
        if(str[s]==ptn[p])s++,p++;
        else if(p>0)p=mynext[p-1]+1;
        else s++;
    }
    if(lenp==p)cout<<str.substr(s-p)<<endl;
    else cout<<"Not Found"<<endl;
}
void match(string ptn){
    mynext[0]=-1
    for(int i=1;i<ptn.size();i++){
        int j=mynext[i-1];
        while(j>=0&&ptn[i]!=ptn[j+1])j=mynext[j];
        if(ptn[i]==ptn[j+1])mynext[i]=j+1;
        else mynext[i]=-1;
    }
}   */