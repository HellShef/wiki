
#include <fstream>
#include <iostream>

using namespace std;

class wiki{
    
public:
    int number;
    int connect;
    int *from;
    int *in;
    
    //переменные нужные только для отыскания пути от элемента к элементу
    int *step;
    int *way;
    string P="Python";
    string S="Список_файловых_систем";
    int Pnum=0;
    int Snum=0;
    wiki(){
        ifstream t;
        t.open("/Users/apple/Documents/test/wiki/wiki/file.txt");
        if(!t.is_open())
        {
            cerr<<"не пошло чёт"<<endl;
            t.clear();
        }
        t>>number>>connect;
        from=new int[number];
        in=new int[connect];
        step=new int[number];
        for(int j=0;j<number;j++){
            step[j]=0;
        }
        int * l=in;
        for(int j=0;j<number;j++){
            int n;
            
            string step_up;
            t>>step_up;
            if(step_up==P) Pnum=j;
            if(step_up==S) Snum=j;
            t>>n;
            t>>n;
            if(n){
                step[j]=1;
            }
            t>>n;
            from[j]=n;
            for(int k=0;k<n;k++){
                t>>*l;
                l++;
            }
        }
        t.close();
        for(int j=1;j<number;j++){
            from[j]+=from[j-1];
        }
        *(from-1)=0;
        way=new int;
    }
    
    ~wiki(){
        delete [] from;
        delete [] in;
        delete [] way;
    }
    
    //далее идут пункты из третьего вопроса по лабе
    
    void q1(){
        
        int sum;
        for(int j=0;j<number;j++) {
            sum+=step[j];
        }
        cout<<"статей с перенаправлением "<<sum<<endl;
    }
    
    void min_from(){
        int sum=1;
        int val=from[0];
        for(int j=1;j<number;j++){
            if(val>from[j]-from[j-1]){
                val=from[j]-from[j-1];
                sum=0;
            }
            if(val==from[j]-from[j-1]){
                sum++;
            }
        }
        cout<<"мининимальное число ссылок "<<val<<" статей с таким числом ссылок "<<sum<<endl;
    }
    
    void max_from(){
        int sum=1;
        int val=from[0];
        for(int j=1;j<number;j++){
            if(val<from[j]-from[j-1]){
                val=from[j]-from[j-1];
                sum=0;
            }
            if(val==from[j]-from[j-1]){
                sum++;
            }
        }
        int num_max = 0;
        for(int j=1;j<number;j++){
            if(from[j]-from[j-1]==val) num_max=j;
        }
        cout<<"максимальное число ссылок "<<val<<" статей с таким числом ссылок "<<sum<<endl<<"пример такой статьи статья номер "<<num_max<<endl;;
    }
    
    void av_from(){
        cout<<"среднее число ссылок из статьи "<<(double)connect/number<<endl;
    }
    
    void min_in(){
        int* num;
        num=new int[number];
        for(int j=0;j<number;j++){
            num[j]=0;
        }
        
        for(int j=0;j<connect;j++){
            num[in[j]]++;
        }
        if(step[0]){
            num[in[from[0]]]--;
        }
        for(int j=1;j<number;j++){
            if(step[j]){
                num[in[from[j-1]]]--;
            }
        }
        
        int sum=0;
        int val=num[0];
        for(int j=0;j<number;j++){
            if(val>num[j]){
                val=num[j];
                sum=0;
            }
            if(val==num[j]){
                sum++;
            }

        }
        
        cout<<"мининимальное число внешних ссылок на статью "<<val<<" статей с таким числом ссылок "<<sum<<endl;
        delete [] num;

    }
    
    void max_in(){
        int* num;
        num=new int[number];
        for(int j=0;j<number;j++){
            num[j]=0;
        }
        
        for(int j=0;j<connect;j++){
            num[in[j]]++;
        }
        
        for(int j=0;j<number;j++){
            if(step[j]){
                num[in[from[j-1]]]--;
            }
        }
        
        int sum=0;
        int val=num[0];
        for(int j=0;j<number;j++){
            if(val<num[j]){
                val=num[j];
                sum=0;
            }
            if(val==num[j]){
                sum++;
            }
            
        }
        int num_max = 0;
        for(int j=0;j<number;j++){
            if(num[j]==val) num_max=j;
        }
        cout<<"максимальное число внешних ссылок на статью "<<val<<" статей с таким числом ссылок "<<sum<<endl<<"пример такой статьи статья номер "<<num_max<<endl;
        delete [] num;
    }
    
    void av_in(){
        int* num;
        num=new int[number];
        for(int j=0;j<number;j++){
            num[j]=0;
        }
        
        for(int j=0;j<connect;j++){
            num[in[j]]++;
        }
        
        for(int j=0;j<number;j++){
            if(step[j]){
                num[in[from[j-1]]]--;
            }
        }
        double res=0;
        for(int j=0;j<number;j++){
            res+=num[j];
        }
        res/=number;
        cout<<"среднее число внешних ссылок "<<res<<endl;
        delete [] num;
    }
    
    void min_step(){
        int* num;
        num=new int[number];
        for(int j=0;j<number;j++){
            num[j]=0;
        }
        if(step[0]){
            num[in[from[0]]]++;
        }
        for(int j=1;j<number;j++){
            if(step[j]){
                num[in[from[j-1]]]++;
            }
        }
        
        int sum=0;
        int val=num[0];
        for(int j=0;j<number;j++){
            if(val>num[j]){
                val=num[j];
                sum=0;
            }
            if(val==num[j]){
                sum++;
            }
            
        }
        
        cout<<"мининимальное число внешних перенаправлений на статью "<<val<<" статей с таким числом перенаправлений "<<sum<<endl;
        delete [] num;
    }
    
    void max_step(){
        int* num;
        num=new int[number];
        for(int j=0;j<number;j++){
            num[j]=0;
        }
        if(step[0]){
            num[in[from[0]]]++;
        }
        for(int j=1;j<number;j++){
            if(step[j]){
                num[in[from[j-1]]]++;
            }
        }
        
        int sum=0;
        int val=num[0];
        for(int j=0;j<number;j++){
            if(val<num[j]){
                val=num[j];
                sum=0;
            }
            if(val==num[j]){
                sum++;
            }
            
        }
        int num_max = 0;
        for(int j=0;j<number;j++){
            if(num[j]==val) num_max=j;
        }
        
        cout<<"максимальное число внешних перенаправлений на статью "<<val<<" статей с таким числом перенаправлений "<<sum<<endl<<"пример такой статьи статья номер "<<num_max<<endl;
        delete [] num;
    }
    
    void av_step(){
        int* num;
        num=new int[number];
        for(int j=0;j<number;j++){
            num[j]=0;
        }
        if(step[0]){
            num[in[from[0]]]++;
        }
        for(int j=1;j<number;j++){
            if(step[j]){
                num[in[from[j-1]]]++;
            }
        }
        double res=0;
        for(int j=0;j<number;j++){
            res+=num[j];
        }
        res/=number;
        cout<<"среднее число внешних перенаправлений "<<res<<endl;
        delete [] num;
        
        
    }
    //я вывожу на экран путь в виде номеров статей которые связаны ссылками и нумерация идёт с нуля. первый номер это статья с которой начался поиск а последний номер это номер искомой
    void find(int Where, int From, int N,int n ){
        
        
        if(N-n){
            for(int j=from[From-1];j<from[From];j++){
                way[n]=in[j];
                find( Where,in[j],N,n+1);
                if(way[0]){
                    break;
                }
            }
            
        }
        
        
        else{
            for(int j=from[From-1];j<from[From];j++){
                if(in[j]==Where){
                    way[0]=N;
                    way[N]=in[j];
                }
            }
        }
    }
    
    void find_a_way(){
        int N=1;
        while(N<20){
            delete [] way;
            way=new int[N+1];
            way[0]=0;
            find(Snum,Pnum,N,1);
            if(way[0])break;
            N++;
            
        }
    }
    
    void show_way(){
        if(way[0]==0){
            cout<<"тот путь, что ты ищещь, пока не достижим ";
            return;
        }
        cout<<"начинай свой путь и, пройдя по моим следам, ты увидишь искомое"<<endl<<Pnum<<" ";
        for(int j=1;j<=way[0];j++){
            cout<<way[j]<<" ";
        }
        
        
    }

};

int main() {
    
    
    wiki a;
    a.find_a_way();
    a.show_way();
    
    return 0;
    
}
