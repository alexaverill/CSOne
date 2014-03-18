#include<iostream>
#include<fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;
const int SIZE=100;
//Create structure for data
struct products{
	int plu;
	string name;
	int type;
	double price;
	double amount;
} items [SIZE];
bool readInventory(string filename){
  int local=0;
  string line;
  ifstream myfile ("Products.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
	
    int length=line.length();
	//seperate the PLU
	int place=line.find(" ");
	string plu=line.substr(0,place);
	//cut string
	line=line.substr(place+1,length);
	//get name
	int name_place=line.find(" ");
	string name=line.substr(0,name_place);
	//cut string
	line=line.substr(name_place+1,length);
	//type
	int type_place=line.find(" ");
	string type=line.substr(0,type_place);
	//cut string
	line=line.substr(type_place+1,length);
	//cost
	int cost_place=line.find(" ");
	string cost=line.substr(0,cost_place);
	//cut string
	line=line.substr(cost_place+1,length);
	//amount
	int amount_place=line.find(" ");
	string amount=line.substr(0,amount_place);
	//cut string
	line=line.substr(amount_place+1,length);
	//int place2=line.find(" ");
	if(atoi(plu.c_str()) && atof(cost.c_str()) && atof(amount.c_str())){
		items[local].plu= atoi(plu.c_str());
		items[local].name=name;
		items[local].type=atoi(type.c_str());
		items[local].price=atof(cost.c_str());
		items[local].amount= atof(amount.c_str());
	}
	/*cout << "PLU: " << atoi(plu.c_str())<<endl;
	cout <<"Name: " << name<<endl;
	cout <<"type: " <<type<<endl;
	cout << "cost: "<<atof(cost.c_str())<<endl;
	cout << "Amount: "<<atof(amount.c_str())<<endl;*/
	local+=1;
	//cout<<local<<endl;
    }
    myfile.close();
  }
	
}
double checkout(){
	int plu;
	double amount;
	int type;
	double sale;
	while(plu!=0){
		cout<<"PLU: ";
		cin>>plu;
		if(plu==0){
			break;
		}
		int location;
		bool found;
		//search:
		for(int x=0; x<SIZE;x++){
			if(plu==items[x].plu){
				location=x;
				found=true;
				break;
			}else{
				found=false;
			}
		}
		if(found){
			type=items[location].type;
			if(type==0){
				cout<<"Enter Number of Units: ";
			}else{
				cout<<"Enter Number of Pounds: ";
			}
			cin>>amount;
			if((items[location].amount-amount)>0){ //check to make sure not buying more then available;
				sale+=items[location].price * amount;
				items[location].amount-=amount;
			}else{
				cout<<"We do not have that many items"<<endl;;
			}
		}else{
			cout<<"PLU Not Found.";
		}
		
	}
	return sale;
}
bool updateInventory(){
	
}
int main(){
	int total_sale_amount=0;
	string file="Products.txt";
readInventory(file);
	double price=checkout();
	cout<<price<<endl;
/*for(int x=0; x<SIZE;x++){
	cout<<x<<endl;
	cout<< items[x].name<<endl;
}*/
//start by reading in file

}
