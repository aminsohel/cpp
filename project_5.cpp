#include <iostream>

using namespace std;
class Article{
    private:
    string model;
    double netPrice;
    double taxRate;
public:
    Article(string modell,double netPricee,double taxRatee=19){
        model=modell;
        netPrice=netPricee;
        taxRate=taxRatee;
    }
    virtual ~Article(){cout<<"~Article "+model+" ";}
    void setmodel(string x){
        model=x;
    }
    void setnetprice(double x){netPrice=x;}
    string getmodel(){return model;}
    double getnetprice(){return netPrice;}

    double getGroseprice(){return (((taxRate*netPrice)/100)+netPrice);}
    virtual void print()=0;
};

class Accessory:public Article{
private:
    bool original;
public:
    Accessory(string name,double price,bool originall=true):Article(name,price),original(originall){}
    virtual ~Accessory(){cout<<"~Accessory()";}
    virtual void print(){cout<<Article::getmodel(); if(original==true){cout<<" original accessories ";}}

};

enum operatingsystem{unknown,android,Ios,macos,Linux,proprietary,Unix,windows};

ostream& operator<<(ostream& out,operatingsystem& o){
    if(o==unknown){out<<"unknown";}
    if(o==android){out<<"android";}
    if(o==Ios){out<<"ios";}
    if(o==macos){out<<"macos";}
    if(o==Linux){out<<"linux";}
    if(o==proprietary){out<<"proprietary";}
    if(o==Unix){out<<"unix";}
    if(o==windows){out<<"windows";}

    return out;
}

class Device:public Article{
private:
    int main_memory;
    operatingsystem os;
public:
    Device(string aname,double nprice,int mmsize,operatingsystem oss=unknown):Article(aname,nprice),main_memory(mmsize),os(oss){}
    virtual ~Device(){cout<<"~Device()";}
    operatingsystem getOS(){return os;}
    virtual void print(){
        cout<<Article::getmodel()<<" RAM "<<main_memory<<" GB "<<os<<endl;
    };

};

class Notebook:public Device{
private:
    string drive;
    bool convertable;
public:
    Notebook(string name,double price,int msize,string drivee,operatingsystem os=Linux,bool c=false):Device(name,price,msize,os),drive(drivee),convertable(c){}
    virtual ~Notebook(){cout<<"~Notebook()";}
    bool is_a_convertable(){return convertable;}
    virtual void print(){
                         Device::print();
                         if(convertable==true)
                         {cout<<" "<<drive<<" "<<endl;}
                         }
};

class Phone:public Device{
public:
    Phone(string name,double price,int size=4,operatingsystem os=android):Device(name,price,size,os){}
    virtual ~Phone(){cout<<"~Phone()";}
    virtual void print(){
        Device::print();cout<<"phone"<<endl;
    }

};

class Incart{
private:
    Article *article;
    int amount;
    Incart *next;
public:

    Incart(Article *a,int b=0,Incart *c=nullptr):article(a),amount(b),next(c){}
    virtual ~Incart(){cout<<"~Incart()";delete article;}
    Incart* getNext(){return next;}
    virtual void print(){cout<<amount<<" ";article->print();cout<<endl<<article->getGroseprice()<<"   "<<(article->getGroseprice()*amount);

    }
};
class ShoppingCart{
private:
    Incart *articels=nullptr;
    double minFreeShipping;
    double sumNetPrice;
    double sumGrossPrice;
public:
    ShoppingCart():minFreeShipping(1000),sumNetPrice(0),sumGrossPrice(0){}
    ~ShoppingCart(){ cout<<"~ShoopingCart()"<<endl;
        while(articels!=nullptr){
            cout<<"delete article: ";
            delete articels;
            cout<<endl;
            articels=articels->getNext();
        }


    }
    void set_mainFreeShipping(int x){minFreeShipping=x;}
    void add_article(int amount,Article *a){
        if(articels==nullptr)
        {articels=new Incart(a,amount);}
        else{
                articels =new Incart(a,amount,articels);
            }

        sumNetPrice=sumNetPrice+(a->getnetprice()*amount);
        sumGrossPrice=sumGrossPrice+(a->getGroseprice()*amount);
    }

    virtual void print(){
        Incart *articel;
        articel=articels;
        while(articel!=nullptr)
        {
            articel->print();cout<<endl;
            articel=articel->getNext();
        }
cout<<"sum net price:  "<<sumNetPrice<<endl;
        cout<<"tax:            "<<sumGrossPrice-sumNetPrice<<endl;
        cout<<"sum gross price:"<<sumGrossPrice<<endl;
        if(sumNetPrice<minFreeShipping){
        cout<<"shipping:       "<<"5.90"<<endl;
        cout<<"total:          "<<(sumGrossPrice+5.90)<<endl;
        }else{
            cout<<"shipping:       "<<"0.00"<<endl;
            cout<<"total:          "<<(sumGrossPrice)<<endl;

        }
    }
};




int main() {

    ShoppingCart shoppingcart;
    shoppingcart.set_mainFreeShipping(500);
    Article *A1= new Accessory("YOOLOX 10k Wireless Powerbank Qi",31.08,false);
    shoppingcart.add_article(3,A1);
shoppingcart.print();
    Article *A2=new Phone("Samsung s10 + SM-G975F/DS Dual SIM",661.67,8);
    shoppingcart.add_article(1,A2);
    Article *A3=new Phone("Apple iPhone 11 pro 256GB",1097.47,4,Ios);
    shoppingcart.add_article(2, A3);
    Article *A4=new Notebook("ASUS ROG Strix Scar III G731",1586.55,16,"512GB SSD + 1TB SSHD",windows);
    shoppingcart.add_article(1,A4);

shoppingcart.print();





    return 0;
}
