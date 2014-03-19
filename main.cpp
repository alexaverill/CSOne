#include<iostream>
#include<fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <ctype.h>
using namespace std;
const int SIZE=100;
int TotalUsed=0; //variable to keep track of total products available;
int ProductsBought=0;// keep track of where in receipts it is.
//Create structure for data
struct products{
	int plu;
	string name;
	int type;
	double price;
	double amount;
} items [SIZE];
struct receipts{
	int plu;
	string name;
	double price;
} receipt[SIZE];

bool readInventory(string filename){
	/*
	 * Read in products from the specified text, then cut each product to add it to the products struc
	 */
  int local=0;
  string line;
  ifstream profile (filename.c_str());
  if (profile.is_open())
  {
    while ( getline (profile,line) )
    {
	
    int length=line.length();
	//seperate the PLU
	int place=line.find(" ");
	string plu=line.substr(0,place);
	//cut string, redefine line to the smaller string, cuts one past the space after plu
	line=line.substr(place+1,length);
	//get name, via finding the space after the name, and then cut
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
	local+=1;
	TotalUsed+=1;
	//cout<<local<<endl;
    }
    profile.close();
    return true;
  }
  return false;
}
double checkout(){
	/*
	 * Take input of a PLU, then search for that PLU in the products data structure, once found do calculations
	 * regarding amount and return the total purchase price to the main()
	 */
	string string_plu;
	int plu;
	int location;
	int type;
	double amount;
	double sale=0;
	bool running=true;
	bool found;
	do{
		cout<<"PLU: ";
		cin>>string_plu;
		//search:
		found=false;
		if(atoi(string_plu.c_str())==0 && string_plu.find_first_of("0123456789")<=string_plu.length()){
			running=false;
			break;
		}
		if(atoi(string_plu.c_str())){
			plu=atoi(string_plu.c_str());
			for(int x=0; x<TotalUsed;x++){
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
				cout<<"Item: "<<items[location].name<<endl;
				cout<<"Number Available: "<<items[location].amount<<endl;
				cout<<"Enter 0 if wrong item"<<endl;
				if(type==0){
					cout<<"Enter Number of Units: ";
				}else{
					cout<<"Enter Number of Pounds: ";
				}
				cin>>amount;
				if(amount!=0){
					if((items[location].amount-amount)>=0){ //check to make sure not buying more then available;
						sale+=items[location].price * amount;
						items[location].amount-=amount;
						//add to receipt
						receipt[ProductsBought].plu=items[location].plu;
						receipt[ProductsBought].name=items[location].name;
						receipt[ProductsBought].price=items[location].price * amount;
						ProductsBought+=1;
					}else{
						cout<<"We do not have that many items"<<endl;
					}
				}
			}else{
				cout<<"PLU Not Found."<<endl;
			}
		}else{
			cout<<"That PLU is not valid"<<endl;
		}
	}while(running);
	return sale;
}
bool updateInventory(string filename){
	/*
	 * Update the inventory file on closure of store, merely rewrite the file.
	 * In theory for a real store this function should be called at the end of each checkout in order
	 * to keep the store inventory synced across registers, however at that point a database should be used
	 */
	 ofstream profile;
    profile.open (filename.c_str());
		for(int y=0;y<TotalUsed;y++){
			profile <<items[y].plu<<" "<<items[y].name<<" "<<items[y].type<<" "<<items[y].price<<" "<<items[y].amount<<"\n";
		}
		profile.close();
		return true;
}
int main(){
	//constants/definitions
	int total_sale_amount=0;
	double discount_min=50.00; //amount for 5% discount
	string file="Products.txt";
	
	//Inport products
	if(readInventory(file)){
		//log successs
	}else{
		cout<<"Products could not be imported"<<endl;
	}
	
	int option=0; //options for menu; 1= checkout, 2 is close	
	while(option!=2){
		cout<<"1. Checkout Enter 1"<<endl;
		cout<<"2.Close Store Enter 2"<<endl;
		cout<<"Choice: ";
		cin>>option;
		if(option==1){	
			double price=checkout();
			if(price>discount_min){
				price = price -(price*.05);
				cout << "You earned a 5% discount!"<<endl;
			}	
				cout<<"PlU    "<<"Name    "<<"Price "<<endl;
			for(int x=0;x<=ProductsBought; x++){
				cout <<receipt[x].plu<<" "<<receipt[x].name<<" "<<receipt[x].price<<endl;
			}
			cout<<"Total: "<<price<<endl;
			ProductsBought=0; //reset receipt;
			option=0;
		}else if(option==2){
			updateInventory(file);
			cout<<"Inventory Updated"<<endl;
		}
	}
}
