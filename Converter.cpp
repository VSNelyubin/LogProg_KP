#include <iostream>
#include <fstream>
#include <string>

using namespace::std;


int whichLine(int n){
    return 2+n;//+(3*n);
}

int main(){
    ifstream infile;
    ofstream outfile;
    string filename;
    cin>>filename;
    //filename="royal_gen_20_11_2002.ged";
    infile.open(filename);
    const char*ttk[7]={"NAME","HUSB","WIFE","CHIL","SiX","@I","@F"};;
    outfile.open("output.txt",std::ofstream::out | std::ofstream::trunc);
    string inpu,tmp="";
    short tb,curt=-1;
    bool skeep=false,famcount=true,header=true;
    int famstarthere=0;
    while(getline(infile,inpu)){
        if(inpu.substr(2,4)=="@I1@"){header=false;}
        if(header){continue;}
        tb=stoi(inpu.substr(0,1));
        skeep=true;
        tmp=inpu.substr(2,4);
        for(int i=0;i<7;i++){
            if(tmp==ttk[i]){skeep=false;}
            if((i==3)||(i==4)){
                tmp=tmp.substr(0,tmp.length()-1);
            }
        }
        if(skeep){
            continue;
        }
        outfile<<inpu<<"\n";
        if(famcount){
            if(tmp!="@F"){famstarthere++;}
            else{famcount=false;}
        }
    }

    infile.close();
    outfile.close();

    ifstream lnsk;
    cin>>filename;
    //filename="rules.pg";
    lnsk.open("output.txt");
    infile.open("output.txt");
    outfile.open(filename,std::ofstream::out | std::ofstream::trunc);
    string dad,mom,child="e",rez;
    for(int i=0;i<famstarthere;i+=2){
        getline(infile,inpu);
        dad=inpu.substr(3,inpu.length()-9);
        getline(infile,inpu);
        curt=min(inpu.find(","),inpu.find("/"));
        mom=inpu.substr(7,curt-7);
        curt=mom.find_last_not_of(" ");
        mom=mom.substr(0,curt+1);
        tb=mom.find("'");
        curt=-1;
        while(tb>curt){
            mom=mom.substr(0,tb)+"\\"+mom.substr(tb,mom.length()-tb);
            curt=tb+1;
            tb=mom.find("'");
        }
        outfile<<"id_name('"<<dad<<"','"<<mom<<"').\n";
    }
    while(getline(infile,inpu)){
        if(inpu.substr(2,2)=="@F"){
            if(child=="N"){
                rez="parents('N','"+dad+"','"+mom+"').\n";
                outfile<<rez;
            }
            dad="N";
            mom="N";
            child="N";
            continue;
        }
        else{
            tmp=inpu.substr(2,4);
            rez=inpu.substr(8,inpu.length()-9);
            if(tmp=="HUSB"){
                dad=rez;
            }
            if(tmp=="WIFE"){
                mom=rez;
            }
            if(tmp=="CHIL"){
                child=rez;
                rez="parents('"+child+"','"+dad+"','"+mom+"').\n";
                outfile<<rez;
            }
        }
    }
    lnsk.close();
    infile.close();
    outfile.close();
    remove("output.txt");
    return 0;
}
