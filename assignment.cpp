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

    map<string,RUIClass> mapRUI;
    map<string,Banner> mapBanner;

    boost::filesystem::ifstream fileHandler(datafile);
    string line; 

    while (getline(fileHandler, line)){
        if(line.substr(0,3) == "sel"){
        vector<string> split  = stringSplitter(&line);
        if (mapRUI.find(split[1]) != mapRUI.end()){
        }
    }
    cout <<"End of File." << endl;
    return true;
}

int main(int argc, char* argv[]){
    // readlogfile(argv[1]);
    string strSample = "sel:6,b94c672a-6185-43e0-be4f-d92d36a1aa97,Banner-16,12.022";
    vector<string> splitSample = stringSplitter(&strSample);

    for (const auto& element : splitSample){
        cout << element << " ";
    }   
        return 0;
}