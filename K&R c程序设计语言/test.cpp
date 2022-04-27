//
// Created by 徐绍骞 on 2021/7/25.
//
#define range 100500
int n,mynext[range];
string str,ptn;
void KMP(const string&),match(const string&);
void KMP(const string&ptn){
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
void match(const string&ptn){
    mynext[0]=-1;
    for(int i=1;i<ptn.size();i++){
        int j=mynext[i-1];
        while(j>=0&&ptn[i]!=ptn[j+1])j=mynext[j];
        if(ptn[i]==ptn[j+1])mynext[i]=j+1;
        else mynext[i]=-1;
    }
}