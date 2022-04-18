#include <bits/stdc++.h>
using namespace std;
int page_size;
vector < map<int,pair<int,int>> > v;
//map <primary key, record size, slot id>
void insert(int primary_key, int record_size){
    bool can_be_inserted_in_existing=false;
    for(auto &m: v){
        int occupied=16;
        for(auto &n: m){
            occupied+=n.second.first+4;
        }
        int available_space=page_size-occupied;
        if(available_space>=record_size+4){
            can_be_inserted_in_existing=true;
            int maxslotid=-1;
            for(auto &n: m){
                maxslotid=max(maxslotid,n.second.second);
            }
            pair <int,int> temppair={record_size,maxslotid+1};
            m[primary_key]=temppair;
            break;
        }
    }
    if(can_be_inserted_in_existing==false){
        //will have to create a new blank page
        map <int,pair<int,int>> blank_page;
        pair<int,int> temppair={record_size,0};
        blank_page[primary_key]=temppair;
        v.push_back(blank_page);
    }
    return;
}
void display(){
    cout<<v.size()<<" ";
    for(auto &x: v){
        cout<<x.size()<<" ";
    }
    cout<<endl;
}
void search(int primary_key){
    bool found=false;
    int page_id=-1;
    int slot_id=-1;
    int i=0;
    for(auto &m: v){
        if(m.find(primary_key)!=m.end()){
            page_id=i;
            for(auto &n: m){
                if(n.first==primary_key){
                    slot_id=n.second.second;
                    break;
                }
            }
            break;
        }
        i++;
    }
    cout<<page_id<<" "<<slot_id<<endl;
}
int main()
{
    //heap file== doubly linked list of pages
    //page1<-->page2<-->page3
    cin>>page_size;//in bytes
    int choice;
    cin>>choice;
    while(choice!=4){
        if(choice==1){
            //insertion
            int record_size, primary_key;
            cin>>record_size>>primary_key;
            insert(primary_key,record_size);
        }
        else if(choice==2){
            //display
            //number of pages
            //number of record in each page
            display();
        }
        else if(choice==3){
            //search
            int primary_key;
            cin>>primary_key;
            search(primary_key);
        }
        cin>>choice;
    }
}