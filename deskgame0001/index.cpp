#include<iostream>
#include<list>
using namespace std;

class Game_build{//建立共用規則
    private:
        int Select_Game,client_amount;
    public:
        class Card{
            private:
                string card_value;
                string card_kind;
                bool undefined;
                int rank;
                int value;
            public:
                Card(){
                    this->card_value = "undefined";
                    this->card_kind = "undefined";
                    this->undefined = true;
                    this->rank=0;
                };
                Card(string x,string y,int z){
                    /*
                        x = card_value
                        y = card_kind
                        z = card_rank
                    */
                    this->card_value = x;
                    this->card_kind = y;
                    this->rank=z;
                    this->undefined=false;
                };
                Card(string x,string y,int z,int value){
                    this->card_value = x;
                    this->card_kind = y;
                    this->rank=z;
                    this->undefined=false;
                    this->value = value;
                };
                void show(){
                    cout<<this->card_kind<<' '<<this->card_value<<endl;
                };
                int Get_rank(){
                    return rank;
                };
                int Get_value(){
                    return this->value;
                };
                bool undef_state(){
                    return this->undefined;
                };
                int match(Card x){
                    if(this->undefined!=true&&x.undef_state()!=true){
                        return (x.Get_rank())>(this->rank)?0:1;
                    }else{
                        cout<<"undefined! can not to match!"<<endl;
                        return 0;
                    }
                };
        };
        class Center_Deck{
            private:
                string kind[4];
                string val[13];
                Card Deck[54];
            public:
                Center_Deck(){
                    this->kind[0] = "spade";this->kind[1] = "heart";this->kind[2] = "diamond";this->kind[3] = "club";
                    this->val[0]="A";this->val[1]="2";this->val[2]="3";this->val[3]="4";this->val[4]="5";this->val[5]="6";this->val[6]="7";this->val[7]="8";this->val[8]="9";this->val[9]="10";this->val[10]="J";this->val[11]="Q";this->val[12]="K";
                    for(int i=0;i<52;i++){
                        int a = (i%13)+1;
                        int b = (i%4)+1;
                        Deck[i] = Game_build::Card(val[a],kind[b],i+1,a);
                    }
                    Deck[52] = Game_build::Card("Ghost","Ghost",53);
                    Deck[53] = Game_build::Card("Ghost","Ghost",53);
                };
                Center_Deck(string x){
                    this->kind[0] = "spade";this->kind[1] = "heart";this->kind[2] = "diamond";this->kind[3] = "club";
                    this->val[0]="A";this->val[1]="2";this->val[2]="3";this->val[3]="4";this->val[4]="5";this->val[5]="6";this->val[6]="7";this->val[7]="8";this->val[8]="9";this->val[9]="10";this->val[10]="J";this->val[11]="Q";this->val[12]="K";
                    if(x=="Inf"){
                        cout<<"inf"<<endl;
                    }
                };
                int Get_length(){
                    for(int i=0;i<54;i++){
                        if(this->Deck[i].undef_state()==true){
                            return i+1;
                        }
                    }
                    return 54;
                };
        };
        class Desktop{
            private:
                list<Card> Abandoned;
                string atTime_users;
                string next_users;
            public:
                void refresh(string atTime_users,Card x){
                    this->atTime_users = atTime_users;
                    Abandoned.push_back(x);
                };
                bool regret(string users,Card x){//回傳悔棋是否成功
                    if(users!=this->atTime_users){
                        cout<<"The chance is passed, can't do regret chese"<<endl;
                        return false;
                    }
                    Abandoned.back();
                    return true;
                };
        };
        class handle_cards{
            private:
                list<Card> handles;
                int amount;
            public:
                handle_cards(){
                    this->amount=0;
                };
                int card_amount(){
                    return this->amount;
                };
                void add_card(Card x){
                    this->handles.push_back(x);
                };
                list<Card> get_cards(){
                    return this->handles;
                };
                void cover_handles(list<Card> x){
                    this->handles = x;
                };
                int sum(){
                    list<Card>::iterator it;
                    int sum=0;
                    for(it=this->handles.begin();it!=handles.end();it++){
                        sum+=it->Get_value();
                    }
                    return sum;
                };
                list<int> sum(string mode){
                    int sum=0;
                    list<int> total;
                    if(mode=="black_jack"){
                        list<Card>::iterator it;
                        for(it=this->handles.begin();it!=handles.end();it++){
                            if(it->Get_value()>10)sum+=10;
                            else sum+=it->Get_value();
                        }
                        total.push_back(sum);
                        sum=0;
                        for(it=this->handles.begin();it!=handles.end();it++){
                            if(it->Get_value()>10)sum+=10;
                            else if(it->Get_value()==1)sum+=11;
                            else sum+=it->Get_value();
                        }
                        total.push_back(sum);
                    }
                    return total;
                };
        };
        class user{
            private:
                handle_cards handled;
                int angry_energy_point;
                int UID;
                string name;
                bool computer;
                int sum;
            public:
                user(){
                    this->computer = false;
                    this->angry_energy_point=0;
                    this->name="undefined";
                    this->sum=0;
                }
                user(string x){
                    this->computer = false;
                    this->angry_energy_point=0;
                    this->name = x;
                    this->sum=0;
                }
                user(string x,bool t){//computer
                    this->angry_energy_point=0;
                    this->name = x;
                    computer = t;
                    this->sum=0;
                }
                void reconstructor(string x){
                    this->name=x;
                };
                void reconstructor(string x,bool t){
                    this->name=x;
                    this->computer = t;
                }

                bool Flip_over_the_table(int x,string s){ //每輸1場累積 x 點怒氣 若怒氣達標則可翻桌
                    srand(time(0));
                    bool success;
                    success = (x - (rand()%100+1))<10?true:false;
                    if(success){
                        cout<<s<<endl;
                        return true;
                    }else{
                        return false;
                    }
                }
                string Get_name(){
                    return this->name;
                }
                handle_cards sqrt_handle_card(handle_cards handles,string mode){
                    list<Card> tmp = handles.get_cards();
                    Card tmpp = Card();
                    Card tmpArr[handles.card_amount()];
                    Card sortAr[handles.card_amount()];
                    int leng = handles.card_amount();
                    for(int i = leng;i>0;i--){
                        tmpArr[i-1] = tmp.back();
                        tmp.pop_back();
                    }
                    if(mode=="B2S"){
                        for(int l=0,c=0;l<leng;l++){
                            for(int i=0;i<leng;i++){
                                if(tmpArr[i].Get_rank()>tmpp.Get_rank()){
                                    tmpp = tmpArr[i];
                                    c=i;
                                }
                            }
                            tmpArr[c]=Card();
                            sortAr[l] = tmpp;
                            tmpp = Card();
                            c=0;
                        }
                        for(int i=0;i<leng;i++){
                            tmp.push_back(tmpArr[i]);
                        }
                        handles.cover_handles(tmp);
                        return handles;
                    }else if(mode=="S2B"){
                        for(int i=0,c=0;i<leng;i++){
                            for(int l=0;l<leng;l++){
                                if(tmpArr[l].Get_rank()<tmpp.Get_rank()){
                                    tmpp = tmpArr[l];
                                    c=l;
                                }
                            }
                            tmpArr[c]=Card();
                            sortAr[i] = tmpp;
                            tmpp = Card();
                            c=0;
                        }
                        for(int i=0;i<leng;i++){
                            tmp.push_back(tmpArr[i]);
                        }
                        handles.cover_handles(tmp);
                        return handles;
                    }
                    return handles;
                };
                handle_cards sqrt_handle_card_by_config(handle_cards handles,string mode,string config){
                    if(config == "black_jack"){
                        handles = sqrt_handle_card(handles,mode);
                    }
                    return handles;
                };
                int handled_sum(){
                    this->sum = handled.sum();
                    return this->sum;
                };
        };
        class control{
            private:
                int m;
            public:
                control(){
                    cout<<"**Center building**"<<endl;
                }
                int show_player_list(user *users,int amount){
                    int real_player=0;
                    cout<<"player list:\n"<<endl;
                    for(int i=0;i<amount;i++){
                            cout<<i+1<<"."<<users[i].Get_name()<<endl;
                            real_player++;
                    }
                    cout<<endl;
                    return real_player;
                };
        };
        class router{
            private:
                int online;
            public:
                router(){
                    cout<<"Game Build"<<endl;
                };
        };
        virtual void Game_set()=0;
};
class Games{
    class black_jack{
        private:
            string master;
            int passed;
            int online;
        public:
            black_jack(string user,int on){
                this->master = user;
                this->passed = 0;
                this->online = on;
            };
            int get_online(){
                return this->online;
            }
            class Rule{
                private:
                    int servive;
                public:
                    Rule(int online){
                        this->servive = online;
                    };
                    list<Game_build::user> winer(list<Game_build::user> users){
                            list<Game_build::user>winers;
                            list<Game_build::user>res;
                            Game_build::user tmp;
                            list<Game_build::user>::iterator it;
                            winers.push_back(tmp);
                            for(it = users.begin();it!=users.end();it++){
                                if(it->handled_sum()>tmp.handled_sum()){
                                    winers.pop_front();
                                    winers.push_front(*it);
                                    tmp = *it;
                                }else if(it->handled_sum()==tmp.handled_sum()){
                                    if(it->Get_name()!=tmp.Get_name()){
                                        winers.push_front(*it);
                                        tmp = *it;
                                    }
                                }
                            }
                            tmp = *winers.begin();
                            for(it=winers.begin();it!=winers.end();it++){
                                if(tmp.handled_sum()>it->handled_sum()){
                                    *it = tmp;
                                }
                            }
                            res.push_back(*winers.begin());
                            for(it=winers.begin();it!=winers.end();it++){
                                if(res.back().Get_name()!=it->Get_name()){
                                    res.push_back(*it);
                                }
                            }
                            return res;
                    };
            };
    };
};
class Control_Center:public Game_build{//實做規則及控制
    private:
        int Select_Game,client_amount;
        control controler;
        list<user> users;
        class tools{
            public:
            tools(){
                cout<<"**Center tools building!**"<<endl;
            };
            int dice(){
                srand(time(0));
                return (rand()%6)+1;
            };
            int dice(int n){
                srand(time(0));
                return (rand()%(6*n)+1);
            };
        };
    public:
    Control_Center(int x,int y){
        this->Select_Game = x;
        this->client_amount = y;
        string input;
        getline(cin,input);
        user useres[client_amount];
        for(int i=0;i<client_amount;i++){
            getline(cin,input);
            useres[i].reconstructor(input);
            users.push_back(useres[i]);
        }
        Game_set();
        int online_users_num = controler.show_player_list(useres,client_amount);
        cout<<"Real online users: "<<online_users_num<<endl;
    };
    void Game_set(){
        cout<<"== All center config has been built! ==\n"<<endl;
    };
    tools tool;
    void start(){
        system("clear");
        this->Game_set();
        string tmp;
        for(int i=0;i<client_amount;i++){
            cout<<"enter any key to drop dice"<<endl;
            cin>>tmp;
            cout<<this->tool.dice(3)<<endl;
            system("clear");
        }
    };
    ~Control_Center(){
        cout<<"== Game Finish! =="<<endl;
    }
};

int Game_main(int select,int mode){
    Control_Center Center = Control_Center(select,mode);
    Center.start();
    return 0;
}
int main(){
    cout<<"Please enter Game kind and total slots"<<endl;
    int a,b;
    cin>>a>>b;
    Game_main(a,b);
    return 0;
}