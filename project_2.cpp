#include <iostream>
#include <cmath>

using namespace std;

struct pointobstracle{
    string pointname;
    double coordinateX, coordinateY, OriginDistance;
    pointobstracle* nextpoint;
};

struct pointobstracle* Primary_list;

double OriginDist(pointobstracle* p){
    double x1, x2, y1,y2,dd;
    x1 =p->coordinateX;
    x2 = 0;
    y1 =(*p).coordinateY;
    y2 =0;
    dd = sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
    return dd;
};

double EucDistance(pointobstracle* p1, pointobstracle* p2){
    double x1, x2, y1,y2,dd;
    x1 =p1->coordinateX;
    x2 = (*p2).coordinateX;
    y1 =(*p1).coordinateY;
    y2 =(*p2).coordinateY;
    dd = sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
    return dd;
};

struct pointobstracle* CalNearestPoint(pointobstracle*List ,pointobstracle* P){
    int min = INT_MAX;
    pointobstracle* near = NULL;
    double dd;
    pointobstracle* temp = List;
    while (temp!= NULL){
        if (temp == P){
            temp = temp->nextpoint;
        } else{
            dd = EucDistance(P,temp);
            if (min > dd){
                min = dd;
                near = temp;
            }
            temp = temp->nextpoint;
        }
    }
    return  near;
};
void sortedInsert(struct pointobstracle** head_ref, struct pointobstracle* new_node)
{
    struct pointobstracle* current;
    if (*head_ref == NULL || (*head_ref)->OriginDistance >= new_node->OriginDistance)
    {
        new_node->nextpoint = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        current = *head_ref;
        while (current->nextpoint!=NULL &&
               current->nextpoint->OriginDistance < new_node->OriginDistance)
        {
            current = current->nextpoint;
        }
        new_node->nextpoint = current->nextpoint;
        current->nextpoint = new_node;
    }
}

void insertionSort(struct pointobstracle **head_ref)
{
    struct pointobstracle *sorted = NULL;
    struct pointobstracle *current = *head_ref;
    while (current != NULL)
    {
        struct pointobstracle *next = current->nextpoint;
        sortedInsert(&sorted, current);
        current = next;
    }
    *head_ref = sorted;
}


void OutPutPoints (){
    pointobstracle* temp = NULL;
    pointobstracle*nearP = NULL;
    string near;
    temp= Primary_list;
    while (temp!= NULL){
        nearP = CalNearestPoint(Primary_list,temp);
        near = nearP->pointname;
        cout<<"Obstacle : " <<temp->pointname << " ("<<temp->coordinateX<<","<<temp->coordinateY<< ")"<<"\tDistance : "<<temp->OriginDistance<<"m"<<"\tnearest to this : "<<near<<endl;
        temp = temp->nextpoint;
    }
}

void deleteList(pointobstracle** head_ref)
{
    pointobstracle* current = *head_ref;
    pointobstracle* next;

    while (current != NULL)
    {
        next = current->nextpoint;
        delete (current);
        current = next;
    }
    *head_ref = NULL;
}

int main()
{
    Primary_list= nullptr;
    string Input;
    cout<<"String descriving obstracle (\"end\" for end of input):";
    cin>>Input;
    while (Input!="end"){
        pointobstracle* Newpoint= new pointobstracle;
        (*Newpoint).pointname=Input;
        cout<<"x and y coordinate: ";
        cin>>(*Newpoint).coordinateX>>(*Newpoint).coordinateY;
        (*Newpoint).OriginDistance=OriginDist(Newpoint);
        (*Newpoint).nextpoint= Primary_list;
        insertionSort(&Newpoint);
        Primary_list=Newpoint;

        cout<<"String descriving obstracle (\"end\" for end of input):";
        cin>>Input;
    }
    cout<<endl;
    OutPutPoints();
    cout<<"delete : ";
    while (Primary_list!= NULL){
        cout<<Primary_list->pointname << " ";
        Primary_list = Primary_list->nextpoint;
    }
    deleteList(&Primary_list);
    return 0;
}
