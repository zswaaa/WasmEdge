#include <string.h>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    vector<int> num_list;
    int content[5] = {2,8,4,6,1};
    num_list.insert(num_list.begin(), content, content+5);
    for(int i=0; i<num_list.size()-1; i++){
        for(int j=0; j<num_list.size()-i-1; j++){
            if(num_list[j]>num_list[j+1]){
                swap(num_list[j], num_list[j+1]);
            }
        }
    }

    for(int k=0; k<num_list.size(); k++){
        cout<<num_list[k]<<endl;
    }
    return 0;
}