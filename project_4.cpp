#include <iostream>

using namespace std;

enum TimeZone{ACT,CET,CST,EST,GMT,MSK,PST};
enum ArraivalOrDeparture{arraival,departure};

class LocalTime{

private:
    int minits;
    TimeZone timezone;
public:
    LocalTime(){minits=-1;timezone=CET;}
    LocalTime(int hour,int minit,TimeZone timezon=CET){SetTime(hour,minit);timezone=timezon;}
    void SetTime(int hour,int minit)
    {
        minits=((60*hour)+minit);
    }
    int GetHour()
    {
        return minits/60;
    }
    int GetMinit()
    {
        return minits%60;
    }

    bool IsValid()
    {
        return minits<0 ? false:true;
    }
};

ostream &operator<<(ostream &couts,LocalTime &time)
{
    if(time.IsValid())
    {
        if(time.GetHour()/10==0){couts<<"0";}
        couts<<time.GetHour()<<":";
        if(time.GetMinit()/10==0){couts<<"0";}
        couts<<time.GetMinit()<<"    ";

    }
    else{couts<<"         ";}
    return couts;
}

class Flight{
private:
    ArraivalOrDeparture arraivalOrdeparture;
    string code;
    string destination;
    string gate;
    string checkIn;
    string comment;
    LocalTime expected;
public:
    Flight(ArraivalOrDeparture arraivalOrdeparture ,string code,string destination,string gate,string checkIn);
     ~Flight();
    string GetCode();
    string GetDestination();
    string GetGate();
    string GetCheckIn();
    string GetComment();
    LocalTime GetExpected();
    void SetExpected(LocalTime time);
    void SetComment(string comment);
    bool IsArraival();
    bool IsDeparture();
    void Print(LocalTime scheduled);
};

Flight::Flight(ArraivalOrDeparture arraivalOrdeparturee ,string codee,string destinationn,string gatee,string checkInn="")
{
    arraivalOrdeparture=arraivalOrdeparturee;
    checkIn=checkInn;
    code=codee;
    comment="        ";
    destination=destinationn;
    gate=gatee;


}
Flight::~Flight(){
cout<<code<<"  deleted"<<endl;}

string Flight::GetCode()
{
    return code;
}
string Flight::GetDestination()
{
    return destination;
}
string Flight::GetGate()
{
    return gate;
}
string Flight::GetCheckIn()
{
    return checkIn;
}
LocalTime Flight::GetExpected()
{
    return expected;
}
string Flight::GetComment()
{
    return comment;
}
void Flight::SetComment(string commentt)
{
 comment=commentt;
}
void Flight::SetExpected(LocalTime expectedd)
{
    expected=expectedd;
}
void Flight::Print(LocalTime scheduled)
{
    cout<<code<<"\t"<<destination<<"\t"<<scheduled<<"\t"<<expected<<"\t"<<gate<<"\t"<<checkIn<<"\t"<<comment;
}
bool Flight::IsArraival()
{
    if(arraivalOrdeparture==arraival){return true;}else{return false;}
}
bool Flight::IsDeparture()
{
     if(arraivalOrdeparture==departure){return true;}else{return false;}
}
class Airport{

private:
    string name;
    Flight* slot[24][64];
public:
    Airport(string namee)
    {   int m,n;
       name=namee;
        for(m=0;m<24;m++){for(n=0;n<64;n++){slot[m][n]=nullptr;}}
    }
    ~Airport()
    {
        int p,q;
        for(p=0;p<24;p++){for(q=0;q<64;q++){delete slot[p][q];}}
    }
    void Schedule(LocalTime time,Flight* flight)
    {   int h,m;
    h=time.GetHour();
    m=time.GetMinit();
        slot[h][m]=flight;
    }
    void Comment(LocalTime time,string comment)
    {int h,m;
    h=time.GetHour();
    m=time.GetMinit();
      slot[h][m]->SetComment(comment);
    }
    void Delay(LocalTime timeForSlot, LocalTime timeToBeStored)
    {int h,m;
    h=timeForSlot.GetHour();
    m=timeForSlot.GetMinit();
        slot[h][m]->SetExpected(timeToBeStored);

    }
    void Print(ArraivalOrDeparture arraivalOrdeparture)
    {
        if(arraivalOrdeparture==arraival)
        {cout<<name;
        cout<<" ARRAIVALS"<<endl;

        }
        if(arraivalOrdeparture==departure)
        {cout<<name;
        cout<<" DEPARTURES"<<endl;

        }
        cout<<"=============================="<<endl;
        cout<<"Flight \t";
         cout<<"to              \t";
         cout<<"scheduled\t";
         cout<<"Expected \t";
         cout<<"Gate\t";
         cout<<"Check-in\t";
         cout<<"Comment \t"<<endl;
         int m,n;
       for(m=0;m<24;m++){for(n=0;n<64;n++){
            if(slot[m][n]!=nullptr)
            {   LocalTime t(m,n);
                if(arraivalOrdeparture==arraival)
                {
                    if(slot[m][n]->IsArraival()){slot[m][n]->Print(t);cout<<endl;}
                }else
                {
                    if(slot[m][n]->IsDeparture()){slot[m][n]->Print(t);cout<<endl;}
                }
            }
       }}

    }
};

int main()
{
    Airport Dusseldorf_Airport("Duesseldorf Airport");
    Flight* flight1=new Flight(arraival,"LH 2010","Munich          ","A04 ");
    Flight* flight2=new Flight(arraival,"EW 9347","Manchester      ","B04 ");
    Flight* flight3=new Flight(departure,"AF 1307","Paris           ","B51 ","192-194 ");
    Flight* flight4=new Flight(departure,"SU 2637","Moscow          ","C31 ","252-255 ");
    Flight* flight5=new Flight(departure,"EW 9466","London-Heathrow ","B35 ","151-170 ");
    Flight* flight6=new Flight(departure,"LH 2011","Munich          ","A40 ","115-120 ");
    Flight* flight7=new Flight(departure,"XQ 959", "Izmir           ","C45 ","240-242 ");
    LocalTime time1(12,40);
    LocalTime time2(14,50);
    LocalTime time3(9,10);
    LocalTime time4(10,40);
    LocalTime time5(11,15);
    LocalTime time6(13,25);
    LocalTime time7(14,55);
    LocalTime delayedtime1(13,5);
    LocalTime delayedtime7(15,20);
    Dusseldorf_Airport.Schedule(time1,flight1);
    Dusseldorf_Airport.Schedule(time2,flight2);
    Dusseldorf_Airport.Schedule(time3,flight3);
    Dusseldorf_Airport.Schedule(time4,flight4);
    Dusseldorf_Airport.Schedule(time5,flight5);
    Dusseldorf_Airport.Schedule(time6,flight6);
    Dusseldorf_Airport.Schedule(time7,flight7);
    Dusseldorf_Airport.Delay(time1,delayedtime1);
    Dusseldorf_Airport.Delay(time7,delayedtime7);
    Dusseldorf_Airport.Comment(time3,"departed");
    Dusseldorf_Airport.Comment(time4,"boarding");
    Dusseldorf_Airport.Comment(time6,"Code Sharing");
    Dusseldorf_Airport.Print(arraival);
    Dusseldorf_Airport.Print(departure);



return 0;
}
