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
    //const char*ttd[13]={"CHAN","BIRT","DEAT","HEAD","@SUB","NOTE","_UID","OCCU","MARR","SEX ","FAMS","FAMC"};
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
        //outfile<<tb<<"  "<<curt<<"\t";
        /*    if((curt<tb)&&(curt!=-1)){
                //outfile<<"\n";
                continue;
            }
            else{
                curt=-1;
            }*/
        //else{
            skeep=true;
            tmp=inpu.substr(2,4);
            for(int i=0;i<7;i++){
                //cout<<tmp<<" "<<ttk[i]<<" ";
                if(tmp==ttk[i]){skeep=false;}
                if((i==3)||(i==4)){
                    tmp=tmp.substr(0,tmp.length()-1);
                }
            }
            //cout<<"\n";
            if(skeep){
            //if((inpu.substr(2,4)=="CHAN")||(inpu.substr(2,4)=="BIRT")||(inpu.substr(2,4)=="DEAT")||(inpu.substr(2,4)=="HEAD")||(inpu.substr(2,4)=="@SUB")||(inpu.substr(2,4)=="NOTE")||(inpu.substr(2,4)=="_UID")||(inpu.substr(2,4)=="OCCU")||(inpu.substr(2,4)=="MARR")){
                //curt=tb;
                //outfile<<"\n";
                continue;
            }
        //}
        for(int i=0;i<tb;i++){
            //outfile<<"\t";
        }
        outfile<<inpu<<"\n";
        if(famcount){
            if(tmp!="@F"){famstarthere++;}
            else{famcount=false;}
        }
    }
    //cout<<famstarthere;

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
        //cout<<tb<<"\n";
        while(tb>curt){
            mom=mom.substr(0,tb)+"\\"+mom.substr(tb,mom.length()-tb);
            curt=tb+1;
            //cout<<mom<<"\n";
            tb=mom.find("'");
        }

        outfile<<"id_name('"<<dad<<"','"<<mom<<"').\n";
    }
    /*int wtf,curline=0;


    while(getline(infile,inpu)){
        if((++famstarthere)%20==1){
            cout<<famstarthere<<"\n";
        }
    //for(int i=1;i<10;i++){
        //getline(infile,inpu);
        if(inpu.substr(2,2)=="@F"){
            //cout<<"\n";
            if(child=="N"){
                rez="parents(\"N\""+dad+"\",\""+mom+"\")\n";
                outfile<<rez;
            }
            dad="N";
            mom="N";
            child="N";
            continue;
        }
        //outfile<<inpu<<"\n";
        tmp=inpu.substr(2,4);
        tb=stoi(inpu.substr(9,inpu.length()-10));
        //rez="";
        wtf=whichLine(tb);
        if(wtf<curline){
            curline=0;
            lnsk.clear();
            lnsk.seekg(0);
        }
        //cout<<tb<<"->"<<wtf<<"\n";
        for(int li=curline;li<wtf;li++){
            getline(lnsk,rez);
        }
        curline=wtf;
        //rez=rez.substr(7,rez.length()-8);
        //curt=rez.find_first_of(",/");
        curt=min(rez.find(","),rez.find(" /"));
        rez=rez.substr(7,curt-7);//+" "+rez.substr(curt+1,rez.length()-curt-2);
        */
    while(getline(infile,inpu)){
        /*if((++famstarthere)%20==1){
            cout<<famstarthere<<"\n";
        }*/
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
            //cout<<inpu<<" "<<rez<<"\n";
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


    /*
    stmp=inpu.find_first_not_of("0123456789");
    t1=stoi(inpu.substr(0,stmp));
    inpu=inpu.substr(stmp+1,inpu.length());
    stmp=inpu.find_first_not_of("0123456789");
    t2=stoi(inpu.substr(0,stmp));
    inpu=inpu.substr(stmp+1,inpu.length());
    stmp=inpu.find_first_not_of("0123456789");
    t3=stoi(inpu.substr(0,stmp));
    inpu=inpu.substr(stmp+1,inpu.length());
    stmp=inpu.find_first_not_of("0123456789");
    t4=stoi(inpu.substr(0,stmp));
    one.setData(t1,t2,t3,t4);
    */
    //lnsk.close();
    infile.close();
    outfile.close();
    remove("output.txt");
    return 0;
}
