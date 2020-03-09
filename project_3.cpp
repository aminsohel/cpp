#include <iostream>
#include <fstream>

using namespace std;



struct Entry{

string key;
string value;
};

int hashFunction(string key, int p){
    unsigned int i,x;
    x=(int)key[0];
   for (i=0;i<key.length()-1;i++)
   {
      x=((x*128+(int)key[i+1])%p);

   }

return x;
}
void entervalueinhashtable(string gword,string eword, Entry hashtable[],int &p)
{ int n,i=0;


n=hashFunction(gword,p);
  while(1)
  {   if(n==p){n=0;}
      if(hashtable[n].value.empty())
        {   hashtable[n].key=gword;
            hashtable[n].value=eword;

            break;
        }
      n++;
      i++;
      if(i==p)
        {

             break;

        }
}
}
void searchword(string gword,Entry hashtable[],int p)
{
    int n,i=0,searchfail=1;

    n=hashFunction(gword,p);


    while(1)
    {
        if(n==p)
        {
            n=0;
        }
        if(hashtable[n].key==gword)
    {
        cout<<hashtable[n].value<<endl;
        searchfail=0;

    }
        n++;
        i++;
        if(i==p)
        {   if(searchfail==1)
            {cout<<"sorry not known"<<endl;}
            break;
        }
    }



}

void getdatafromFile(string name,Entry hashtable[],int p)
{
    char c;
    string temp="";
    string gword,gword2="";
    string eword;
    int beforesemicolone=1;


 ifstream i;

 i.open(name.c_str());



 if(!i.is_open())
    {cout<<"error opening file";}
else
    {

        while (! i.eof())
      {    c=i.get();




               if(c==';')
               {
                   gword=temp;

                   temp="";
                   beforesemicolone=0;
                   c=i.get();

               }
               if(c==',')
               {
                   if(gword2!="" && beforesemicolone==0)
                   {
                     eword=temp;
                     entervalueinhashtable(gword2,eword,hashtable,p);
                     gword2="";
                     temp="" ;
                     c=i.get();
                   }

                  if(beforesemicolone==1)
                   {    c=i.get();
                        gword2=temp;

                   temp="";
                   c=i.get();

                   }
               }


               if(c=='\n')
               {
                   eword=temp;

                   entervalueinhashtable(gword,eword,hashtable,p);
                   if(gword2!="")
                   {
                      entervalueinhashtable(gword2,eword,hashtable,p);
                      gword2="";
                   }

                   temp="";
                   beforesemicolone=1;
                   c=i.get();
               }



               if(i.eof())
               {
                    eword=temp;

                   entervalueinhashtable(gword,eword,hashtable,p);
                   temp="";
                   c=i.get();
               }


           temp=temp+c;

      }


    }
}


int main()
{    int p;
     string gword;
     cout<<"please input value for (prime) number p: ";
     cin>>p;
     Entry hashtable[p];
     getdatafromFile("\tiere_animals.txt",hashtable,p);
     while(1)
     {
        cout<<"translate (0 for end): ";
        cin>>gword;
        if(gword=="0")
        {
            break;
        }else
        {
            cout<<gword<<" translation : "<<endl;
            searchword(gword,hashtable,p);
            cout<<endl;
        }
     }
    return 0;
}
