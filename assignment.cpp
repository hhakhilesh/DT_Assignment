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
#include<string.h>
#include<vector>
using namespace std;

class Banner{
        string banner_ID;
        float cost;
        map<int,int> eventOccuMap; //(eventID,occurences)
        float revenue;
};

class RUIClass{
        string RUI_ID;
        vector<int> eventIDlist;
        string bannerID;
        float banner_cost;
};

map<string,int> eventListtoMap(vector<int> eventID){
    map<string,int> eventMap;
    for(int i: eventID){
        eventMap[to_string(i)] +=1;
    }
    return eventMap;
}

int main(int argc, char* argv[]){
    boost::filesystem::ifstream fileHandler(argv[1]);
    string line;
    vector<int> event_sam {1,2,3,1,2,4,0,0,1};
    map<string,int> eLM  = eventListtoMap(event_sam);
    for(auto iter = eLM.begin();iter!=eLM.end();iter++){
        cout << "{" << (*iter).first << ": " << (*iter).second << "}\n";
    }
    // while (getline(fileHandler, line)) {
    //     cout << line << endl;
    // }

    return 0;
}