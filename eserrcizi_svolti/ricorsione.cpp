

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int count_pairs(int n){
    if(n<10)
        return 0;
        return (n%10) == ((n/10)%10)? 1+count_pairs(n/10):count_pairs(n/10);
}

int sum_even(int n){
    if(n== 1)
        return 2; 
    return (2*n)+sum_even(n-1);
}

bool contains(const vector<int>& v1, const vector<int>& v2, int i, int j){
    if(j== v2.size())
        return true;
    else
        if(i== v1.size())
            return false;
     
        
    return (v1.at(i)==v2.at(j))?contains(v1,v2,i+1,j+1):contains(v1,v2,i+1,0);


}

int count_even_rec(const vector<int>& v, int idx){
    if(idx>= 0)
        return 0;
    return (v.at(idx)%2== 0)? count_even_rec(v,idx+1)+1:count_even_rec(v,idx+1);
}

int fast_power(int base, int exp){
    if(exp == 0)
        return 1; 
    else 
        if(exp%2== 0){
             int half=  fast_power(base,exp/2);
             return half*half;
        }
           
        else
            return base* fast_power(base,exp-1);
}

bool is_number(const string& s){

    if(!(s.at(0)>= '0' && s.at(0)<= '9'))
            return false;
    else
        if(s.length()== 1)
            return true;
    else 

    return is_number(s.substr(1,s.size()-1));
}


bool vectors_equal(const vector<int>& a, const vector<int>& b, int idx) {
    // Controllo size prima di tutto
    // idx >= a.size() -> true
    if(a.size() !=b.size())
        return false;
    if(idx>= a.size())
        return true;
    // a[idx] != b[idx] -> false
    if(a.at(idx)!= b.at(idx))
        return false;
    return vectors_equal(a,b,idx+1);
}
    void swap(int &a, int &b){
        int &c = a; 
        a= b; 
        b=c;
    }
void reverse_inplace(string& s, int l, int r){
    if(l>=r)
        return;
        swap(s.at(l),s.at(r));
    reverse_inplace(s,l+1,r-1);
}

int mcd(int a, int b){
    if(a==b)
        return a;
    else 
        if(a>b)
            return mcd(a-b,b);
        else
            return mcd(a,b-a);
}

int mcd_vector(const vector<int>& v, int idx){
    return(idx == v.size()-1)? v.at(idx):mcd(v.at(idx), mcd_vector(v,idx+1));
}
void permuta(const string& p, const string& s) {
    if(p.empty()) {
        cout << s << endl;
        return;             // ✅ aggiungi return per chiarezza
    }
    for(int i = 0; i < p.length(); i++) {
        string r = p;
        r.erase(i, 1);
        permuta(r, s + p.at(i));  // ✅ s accumula il prefisso
    }
}
// Chiamata: permuta("abc", "")

void estrai(vector<int>& v){
    if(v.size()>0){
        int n = rand(v.size());
        cout<<v.at(n)<<endl;
        swap(v.at(n),v.at(v.size()-1));
        v.pop_back();
        estrai(v);
    }
}


int prefix(const string &s1, const string &s2, int da){
    if(s1.size()<= da || s2.size()<da)
        return 0;
    else 
        return 1+ prefix(s1,s2,da+1);
}
void gen_s(const vector<char> & set, string prefix,int k){
    if(k == 0){
        cout<<prefix<<endl;
        return;
    }
        for(int i = 0 ; i <set.size();i++)
            gen_s(set,prefix+set.at(i),k-1);
}














int min (const vector<int>& v,int a,int b){
    int min = v.at(0);
    for(int i = 0; i<v.size();i++){
        if(min<v.at(i)){
            min = v.at(i);
        }
    }
    return min;
}

void partitions(int n, int max_val, vector<int>& curr, vector<vector<int>>& res) {
    if(n == 0){
        res.push_back(curr);
        return;
    }
    for(int i = 1;i <= min(n,max_val);i++){
     curr.push_back(i);
    partitions(n-i, i, curr, res);
    curr.pop_back();
    }
}





int massimo (const  vector<int>&v){
    int max = v.at(0);
    for(int i = 0; i <v.size();i++){
        if(v.at(i)>max)
            max = v.at(i);
    }
    return max;
}
int max_recursive(const vector<int>& v, int idx) {
    // Il tuo codice qui
    if(idx == v.size()-1)
        return v.at(idx);
    int res = max_recursive(v,idx+1);
    return max(v.at(idx),res);    
}
// binary search con intero

int binary_search(const vector<int>& v, int target, int left, int right) {
    // Il tuo codice qui
   if(left>right)
    return -1;
    int mid = left+(right-left)/2;
    if(v.at(mid)==target)
        return mid;
    if(v.at(mid) > target)
        return binary_search(v,target,left,mid-1);
    else
        return binary_search(v,target,mid+1,right);
}



// binary search bool 

bool binary_s(const vector<int> & v, int target, int da ,int a){
        if(da <= a){
            int m = (da+a)/2;
            if(v.at(m)== target)
                return true;
            else
                if(v.at(m)>target)
                    return binary_s(v,target,da,m-1);
            else
                return binary_s(v,target,m+1,a);
        }
        return false;
}















string reverse_string(const string& s) {
    // Il tuo codice qui
    if(s.empty()|| s.size()==1)
        return s;
    return s.back()+reverse_string(s.substr(0,s.size()-1));
}





bool is_prime(int n) {
    // Primo?
    int i  = 2; 
    while (i*i<= n){
        if( n%i == 0)
            return false;
        i++;
    }
    return true;
}


void fill_with_primes_h( vector <int> & v, int size ){
    if(size == 0) return;
    fill_with_primes_h(v,size-1);
    int next = v.empty()?2:v.back()+1;
    while(!is_prime(next)) next++;
        v.push_back(next);
}

vector<int> fill_with_primes(int size) {
    // Il tuo codice qui
    vector<int> v;
    fill_with_primes_h(v,size);
    return v;
}





int sum_positive_h(const vector<int>& v, int i ) {
    if(i == v.size())
        return 0 ;
    int res = sum_positive_h(v,i+1);
    if(v.at(i)>0)
       return v.at(i)+res;
    return res;

}
int sum_positive(const vector<int>& v) {

    return sum_positive_h(v,0);
}






int digit_sum(int n) {

    if(n<10)
        return n;
    return n%10+digit_sum(n/10);
}




bool vectors_equal(const vector<int>& a, const vector<int>& b, int idx) {
    // Controlla size prima di tutto
    if(a.size() != b.size() )
        return false;
    // idx >= a.size() -> true
    if(idx>= a.size())
        return true;
    // a[idx] != b[idx] -> false
    if(a.at(idx)!= b.at(idx))
        return false;
    
    return vectors_equal(a,b,idx+1);
}












int mcd_vector(const vector<int>& v, int idx) {
    // idx == v.size()-1 -> return v[idx]

    // mcd(v[idx], mcd_vector(v, idx+1))
    // mcd(a,b) e' gia' disponibile
    if(idx == v.size()-1)
        return v.at(idx);
    else
        return mcd(v.at(idx), mcd_vector(v,idx+1));
}








int from_hex(const string& s) {
    // s.empty() -> 0
    if(s.size()== 0)
        return 0;
    // Ultima cifra: c = s.back()
    char c = s.back();
    int val;
    // Se c >= 'a': val = c - 'a' + 10; altrimenti val = c - '0'
    if(c>='a')
        val = c-'a'+10;
    else
        val = c-'0';
    // 16 * from_hex(s.substr(0, s.size()-1)) + val
   return 16*from_hex( s.substr(0,s.size()-1) )+val;
}




void swap(int &a,int &b){
int tmp = a;
a = b;
b = tmp;
}
vector<string> permutations(const string& s) {
    // s.size() <= 1 -> return {s}
    if(s.size() <= 1)
        return{s};
    vector<string> res;
    // Per ogni i: scambia s[0] con s[i]
    for(int i = 0 ; i < s.size();i++){
        string tmp = s;
        swap(tmp.at(0),tmp.at(i));
        vector<string> sub = permutations(tmp.substr(1));
        for(string&p:sub){
            res.push_back(tmp.at(0)+p);
        }
    }
    // Ricorri su s.substr(1)

    // Preponi s[0] a ogni permutazione restituita
    return res;
}


void inserisci(vector<int>& v, int k){
        if(k == 0|| v.at(k)>v.at(k+1))
            return;
            swap(v.at(k),  v.at(k+1));
            inserisci(v,k-1);
}

void sort(vector<int>& v, int n){
        if(n<= 1)
            return;
        sort(v,n-1);
        inserisci(v,n-1);
}


bool is_sorted_rec(const vector<int>& v, int idx) {
    
    if(idx>= (int)v.size()-1)
        return true;
    if(v.at(idx)> v.at(idx+1))
        return false;
    
    return is_sorted_rec(v,idx+1);
}


int count_char(const string& s, char c) {
    // s.empty() -> return 0
    // (s[0] == c ? 1 : 0) + count_char(s.substr(1), c)
    if(s.empty())
        return 0;
    int res = s.at(0) == c ? 1:0;
    return res+count_char(s.substr(1),c);
}




bool is_palindrome_rec(const string& s, int l, int r) {
    if(l>=r)
        return true;
    else 
        if(s.at(l) != s.at(r) )
            return false;
    return is_palindrome_rec(s,l+1,r-1);
}


int product_from(const vector<int>& v, int idx) {
   if(idx>= v.size())
    return 1;
    return v.at(idx)*product_from(v,idx+1);
}



bool is_subsequence(const string& s, const string& t, int i, int j) {
  if(j>=t.size())
    return  true; 
    if(i >=s.size())
        return false; 
    if(s.at(i) == t.at(j))
        return is_subsequence(s,t,i+1,j+1);
    else
        return is_subsequence(s,t,i+1,j);
}


int count_even(const vector<int>& v, int idx) {
    if(idx>=v.size())
        return 0; 
    
    return (v.at(idx)%2 ==0 ?1:0)+count_even(v,idx+1);
}

bool all_positive(const vector<int>& v, int idx) {
    if(idx>= v.size())
        return true;
    if(idx<= 0)
        return false;
    return all_positive(v,idx+1);
}



int find_first(const vector<int>& v, int target, int idx) {
    if(idx>= v.size())
        return -1;
    if(v.at(idx)== target)
        return idx;
    return find_first(v,target,idx+1);
}

void reverse_vec(vector<int>& v, int l, int r) {
    if(l>= r)
        return;
    swap(v.at(l),v.at(r));
    reverse_vec(v,l+1,r-1);
}




int sum_dc(const vector<int>& v, int left, int right) {
    if(left == right)
        return v.at(left);
    int mid = (left+right)/2;
    return   sum_dc(v,left,mid)+sum_dc(v,mid+1,right);  
}

void remove_all(vector<int>& v, int k, int idx = 0){
    if(idx > v.size())
        return;
    if(v.at(idx)==k){
        v.erase(v.at(0)+idx);
    }
}
// remove_all({1,3,3,2,3}, 3) → {1,2}
void remove_char(string& s, char c, int idx ){
    if(idx > s.length())
        return;
    else 
        if(s.at(idx)==c){
            s.erase(idx,1);
            remove_char(s,c,idx);
        }
        else
            remove_char(s,c,idx+1);

}

bool helper(const vector<int>& a, const vector<int>& b, int i, int j) {
    if (j >= i) return true;
    else if (a.at(i) == b.at(j)) return helper(a, b, i+1,j+1);
    else return helper(a,b,i+1,j);
}

bool contains(const vector<int>& b, int val, int idx ){
    if(idx > b.size())
        return false;
    if(b.at(idx)== val) return true;

    return  contains(b,val,idx+1);

}

bool is_subset(const vector<int>& a, const vector<int>& b, int idx ) {
    // Il tuo codice qui
        if(idx >=a.size())
            return false;
        else if(!contains(a,b.at(idx),0))
            return is_subset(a,b,idx+1);
            
}
void reverse_inplace(string& s, int i, int j){
    if(i>= j)   return;
    swap(s[i],s[j]);
    reverse_inplace(s,i+1,j-1);
}
string reverse_str(const string& s, int idx ) {
    if(s.empty())
        return s; 

}

string reverse_str(const string& s, int idx = 0) {
    if(idx >= (int)s.size()) return "";     // caso base sull'indice
    return reverse_str(s, idx + 1) + s[idx];
}
string reverse_str(const string& s) {
    if(s.empty()) return "";                // caso base sulla stringa
    return reverse_str(s.substr(1)) + s[0];
}

string to_binary(int n) {
    if(n == 0)
        return 0;
    if (n == 1)
        return 1;
    return to_binary(n/2)+to_binary('0'+n%2);
}