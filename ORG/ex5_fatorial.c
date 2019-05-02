int main(){
    int n = 4;
    fatorial(n);
    return 0;
}

int fatorial(int n){
    if(n == 1)
        return n;
    else
        return n * fatorial(n-1)
}