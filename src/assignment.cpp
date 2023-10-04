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
// #include<boost/property_tree/ptree.hpp>
// #include<boost/property_tree/xml_parser.hpp>
#include<boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "pugixml.cpp"
#include<string.h>
#include<vector>
using namespace std;

class Banner{
    public:
        string bannerID;
        double banner_cost;
        vector<int> eventsList;
        map<string,int> eventOccuMap; //(eventID,occurences)
        double revenue;
    Banner(const string& bannerID="",const double banner_cost=0.0f)
    :bannerID(bannerID),banner_cost(banner_cost){}

    void setRevenue(){
        revenue = (eventOccuMap[to_string(1)])*banner_cost;
    }
};

class RUIClass{
    public:
        string RUI_ID;
        string bannerID;
        vector<int> eventIDlist;
        double banner_cost;
        

    RUIClass(const std::string& RUI_ID,int eventAdd)
        :RUI_ID(RUI_ID){
            if(eventAdd!=-1){
            eventIDlist.push_back(eventAdd);
            cout<<eventAdd<<" line 87"<<endl;
            }
    }
    
    RUIClass(int eventAdd,const std::string& RUI_ID ,const string& bannerID,const double& banner_cost)
    :RUI_ID(RUI_ID),bannerID(bannerID),banner_cost(banner_cost){
        if(eventAdd!=-1){
            eventIDlist.push_back(eventAdd);
            cout<<eventAdd<<" line 95"<<endl;
            }
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

bool checkline(string* line){

    string linedata = line->substr(4, line->length()-1);
    string prefix = line->substr(0,3);
    bool validLine=false;

    if(prefix=="sel"||prefix =="cnt"){

        vector<string> parts;
        boost::split(parts,linedata,boost::is_any_of(","));

        if(prefix=="sel"){
            // cout<<parts.size()<<endl;

            if((parts.size()==4)){
                // cout<<parts[1].length()<<endl;

                if((parts[1].length()==36)){
                    // cout<<parts[2].substr(0,6)<<endl;

                    if((parts[2].substr(0,6)=="Banner")){

                        validLine=true;
                    }
                }
            }
       }

        if(prefix=="cnt"){

            if((parts.size()==2)){

                if(parts[1].length()==36){

                    validLine=true;
                }
            }
        }
    }
    else{validLine = false;}

    return validLine;
    }

map<string,Banner*> logtoBanner(char* datafile){

    map<string,RUIClass*> mapRUI;
    map<string,Banner*> mapBanner;

    boost::filesystem::ifstream fileHandler(datafile);
    string line; 
    int linenum= 0;

    while (getline(fileHandler, line)){
        linenum++;
        if(!checkline(&line)){
            cout<<"Line format invalid for line "<<linenum<<".Line Content: "<<line<<endl;
            cout<<"Skipping Line>>>>>>>>>>>>>>>"<<endl;
            continue;
        }
        
        vector<string> split  = stringSplitter(&line);

        if(line.substr(0,3) == "sel"){
        
            if (mapRUI.find(split[1]) != mapRUI.end()){
                // cout<<split[1];
                // mapRUI[split[1]].bannerID = split[2];
                // mapRUI[split[1]].banner_cost = stof(split[3]);
                auto inst = mapRUI.find(split[1])->second;
                inst->bannerID = split[2];
                inst->banner_cost =stof(split[3]);
                inst->eventIDlist.push_back(stoi(split[0]));
            }

            else{
                RUIClass* ruiInstance = new RUIClass(stoi(split[0]),split[1],split[2],stof(split[3]));
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

    cout <<"Total lines parsed = "<<linenum<<endl;
    
    
    // for (auto& pair: mapRUI){
    //     std::string key = pair.first;
    //     RUIClass* instance = pair.second;

    //     cout<<"Map Key:"<<key<<endl;
    //     cout<<"RUI_ID from RUI_Class: "<<instance->RUI_ID<<endl;
    // }
    
    cout<<"End of mapRUI"<<endl;
    // Get eventIDs from RUI to Banners and calculate revenue
    for (auto& Bpair: mapBanner){

        std::string Bkey = Bpair.first;
        Banner* Binst = Bpair.second;
        
        for(auto& Rpair: mapRUI){
            std::string Rkey = Rpair.first;
            RUIClass* Rinst = Rpair.second;

            if(Bkey==Rinst->bannerID){
                Binst->eventsList.insert(Binst->eventsList.end(),
                Rinst->eventIDlist.begin(),Rinst->eventIDlist.end());
            }
        }
        map<string,int> evO = eventListToMap(Binst->eventsList);
        Binst->eventOccuMap = evO;
        Binst->setRevenue();
        cout<<endl<<"The revenue for "<<Binst->bannerID<<" is "<<Binst->revenue<<endl;
    }

    return mapBanner;
}

int BannertoXML(map<string,Banner*> BannersMap){

    pugi::xml_document doc;
    int numBanners = BannersMap.size();

    pugi::xml_node banners = doc.append_child("Banners");

    for(auto& Bpair: BannersMap){

        std::string Bkey = Bpair.first;
        Banner* Binst = Bpair.second;

        pugi::xml_node banner = banners.append_child("Banner");
        
        banner.append_attribute("id") = (Binst->bannerID).c_str();
        banner.append_attribute("revenues") = round((Binst->revenue) * 100)/100.0;
      
        pugi::xml_node events = banner.append_child("Events");

        for(auto& Epair: Binst->eventOccuMap){

            std::string eventID = Epair.first;
            int occur = Epair.second;
            if (occur>0){

                pugi::xml_node event = events.append_child("Event");
                event.append_attribute("id")= stoi(eventID);
                event.text() = occur;
            }
        }
    }

    doc.save_file("outputpugi.xml");
    return 0;
}

int main(int argc, char* argv[]){
    map<string,Banner*> Banners = logtoBanner(argv[1]);
    int output = BannertoXML(Banners);
    return 0;
}