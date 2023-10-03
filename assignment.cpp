/* Psuedo code:
    
    Class RUIClass{
        str RUI_ID
        std::vector<int> eventIDList
        str Banner ID
        std Banner Cost
    }

    Class Banner{
        str BannerID
        float cost
        std::map<int,int> (eventID,occurences) eventOccuMap
        float Revenue
    }

    std::map<int,int> eventListToMap(std::vector int eventID)
    
    std::map<RUI_ID,RUIClass> RUIMap
    std::map<Banner_ID,Banner> BannerMap
    
    Read Line while (not EndOfDocument){
        If start with sel{
            If RUI_ID not in RUIMap:
                Create a RUIClass instance with the RUI_ID, BannerID, BannerCost.
            else:
                Update BannerId, BannerCost.
            If Banner_ID not in BannerMap:
                Create a Banner instance with BannerID, float cost.
        }
        if start with cnt{
            If RUI_ID not in RUIMAP:
                Create a RUIClass instance with the RUI_ID, eventID.
            If RUI_ID in RUI_MAP:
                add eventID.
        }
    }

    For BannerId in BannerMAP{
        if BannerID == RUIClass.BannerID
        BannerMAP[BannerID].eventOccuMap = eventListToMap(RUIClass.eventIDList)
        BannerMAP[BannerID].TotalRevenue = BannerMAP[BannerID].eventOccuMap[1]*BannerMAP[BannerID].cost
    }

    */

#include<iostream>
#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include<string.h>
#include<vector>
using namespace std;

class Banner{
    public:
        string bannerID;
        double banner_cost;
        map<string,string> eventOccuMap; //(eventID,occurences)
        double revenue;
    Banner(const string& bannerID="",const double banner_cost=0.0f)
    :bannerID(bannerID),banner_cost(banner_cost){}

    void setRevenue(){
        revenue = stod(eventOccuMap[to_string(1)])*banner_cost;
    }
};

class RUIClass{
    public:
        string RUI_ID;
        string bannerID;
        vector<int> eventIDlist;
        double banner_cost;
        

    RUIClass(const std::string& RUI_ID,int eventAdd)
        :RUI_ID(RUI_ID){if(eventAdd!=-1){eventIDlist.push_back(eventAdd);}
    }
    
    RUIClass(const std::string& RUI_ID ,const string& bannerID,const double& banner_cost)
    :RUI_ID(RUI_ID),bannerID(bannerID),banner_cost(banner_cost){
    }
};

map<string,int> eventListToMap(vector<int> eventID){
    map<string,int> eventMap;
    for(int i: eventID){
        eventMap[to_string(i)] +=1;
    }
    return eventMap;
}

vector<string> stringSplitter(string* str){
    string substr = str->substr(4, str->length()-1);
    vector<string> parts;
    boost::split(parts,substr,boost::is_any_of(","));
    return parts;
}


bool readlogfile(char* datafile){

    map<string,RUIClass*> mapRUI;
    map<string,Banner*> mapBanner;

    boost::filesystem::ifstream fileHandler(datafile);
    string line; 

    while (getline(fileHandler, line)){
       
        vector<string> split  = stringSplitter(&line);

        if(line.substr(0,3) == "sel"){
        
            if (mapRUI.find(split[1]) != mapRUI.end()){
                cout<<split[1];
                // mapRUI[split[1]].bannerID = split[2];
                // mapRUI[split[1]].banner_cost = stof(split[3]);
                auto inst = mapRUI.find(split[1])->second;
                inst->bannerID = split[2];
                inst->banner_cost =stof(split[3]);
            }

            else{
                RUIClass* ruiInstance = new RUIClass(split[1],split[2],stof(split[3]));
                mapRUI[split[1]] = ruiInstance;
            }

            if (mapBanner.find(split[2])== mapBanner.end()){
                Banner* bannerInstance= new Banner(split[2],stof(split[3]));
                mapBanner[split[2]] = bannerInstance;
            }
        }
        if(line.substr(0,3)=="cnt"){

            if (mapRUI.find(split[1]) != mapRUI.end()){
                auto inst = mapRUI.find(split[1])->second;
                inst->eventIDlist.push_back(stoi(split[0]));
                // mapRUI[split[1]].eventIDlist.push_back(stoi(split[0]));
            }

            else{
                RUIClass* ruiInstance = new RUIClass(split[1],stoi(split[0]));

                mapRUI[split[1]]= ruiInstance;
            }
        }
        
    }

    cout <<"End of File." << endl;
    
    for (auto& pair: mapRUI){
        std::string key = pair.first;
        RUIClass* instance = pair.second;

        cout<<"Map Key:"<<key<<endl;
        cout<<"RUI_ID from RUI_Class: "<<instance->RUI_ID<<endl;
    }
    
    cout<<"End of mapRUI"<<endl;

    for (auto& pair: mapBanner){
        std::string key = pair.first;
        Banner* instance = pair.second;

        cout<<"Map Key:"<<key<<endl;
        cout<<"BannerID: "<<instance->bannerID<<endl;
    }
    
    
    return true;
}

int main(int argc, char* argv[]){
    readlogfile(argv[1]);
    // string strSample = "sel:6,b94c672a-6185-43e0-be4f-d92d36a1aa97,Banner-16,12.022";
    // vector<string> splitSample = stringSplitter(&strSample);
    // Banner sampleA("Banner-7",8.12);
    // sampleA.banner_cost = 2.11;

    // cout<<sampleA.bannerID<<endl;
    // cout<<sampleA.banner_cost<<endl;

    return 0;
}