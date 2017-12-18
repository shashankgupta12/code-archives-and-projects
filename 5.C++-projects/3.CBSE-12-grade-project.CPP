#include<fstream>
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iomanip>
#include<process.h>
using namespace std;
struct date
{
	int dd;
	int mm;
	int yy;
};
class product
{
	int pcode;
	char pname[30];
	float price;
	char features[80];
	int quantity;
	public:
	product()
	{
		pcode=0;
		strcpy(pname,"NULL");
		price=0.0;
		strcpy(features,"NULL");
		quantity=0;
	}
	void getdata();
	void showdata();
	void get_features();
	void show_features();
	int getpcode();
	char* getpname();
	float getprice();
	int getquantity();
	void modify();
	void modify_features();
}prodt,prodt1;
void product::getdata()
{
	char choose,found='t';
	int i=0,ch;
	cout<<"\t\t\tProduct code : ";
	cout<<"(Choose from list (Y or N) : ";
	cin>>choose;
	if(choose=='Y'||choose=='y')
	{
		ifstream fin;
		fin.open("mobile.txt",ios::in|ios::binary);
		if(!fin)
		{
			cout<<"!!!Cannot open file!!!\n";
			exit(-1);
		}
		while(!fin.eof())
		{
			fin.read((char*)&prodt,sizeof(prodt));
			if(fin.eof())
				break;
			prodt.show_features();
			++i;
			if(i==1)
			{
				cout<<"\n\t\t\tPress 1 to continue and 2 to go back : ";
				cin>>ch;
				cout<<endl;
				i=0;
				if(ch==2)
					break;
			}
		}
		fin.close();
	}
	cout<<"\t\t\tProduct code : ";
	cin>>pcode;
	do
	{
		ifstream fi;
		fi.open("mobile.txt",ios::in|ios::binary);
		if(!fi)
		{
			cout<<"!!!Cannot open file!!!\n";
			exit(-1);
		}
		while(!fi.eof())
		{
			fi.read((char*)&prodt,sizeof(prodt));
			if(prodt.getpcode()==pcode)
			{
				found='f';
				break;
			}
		}
		fi.close();
		if(found!='f')
		{
			cout<<"\t\t\tWRONG PRODUCT CODE\n";
			cout<<"\t\t\tProduct code : ";
			cin>>pcode;
		}
	}while(found=='t');
	cout<<"\t\t\tProduct name : ";
	gets(pname);
	cout<<"\t\t\tPrice : ";
	cin>>price;
	return;
}
void product::showdata()
{
	cout<<"\t\t\tProduct code : "<<pcode<<endl;
	cout<<"\t\t\tProduct name : "<<pname<<endl;
	cout<<"\t\t\tPrice : "<<price<<endl;
}
void product::get_features()
{
	cout<<"\t\t\tProduct code : ";
	cin>>pcode;
	cout<<"\t\t\tProduct name : ";
	gets(pname);
	cout<<"\t\t\tPrice : ";
	cin>>price;
	cout<<"\t\t\tFeatures : ";
	gets(features);
	cout<<"\t\t\tQuantity : ";
	cin>>quantity;
	return;
}
void product::show_features()
{
	cout<<"\t\t\tProduct code : "<<pcode<<endl;
	cout<<"\t\t\tProduct name : "<<pname<<endl;
	cout<<"\t\t\tPrice : "<<price<<endl;
	cout<<"\t\t\tFeatures : "<<features<<endl;
	cout<<"\t\t\tQuantity : "<<quantity<<endl;
}
int product::getpcode()
{
	return pcode;
}
char* product::getpname()
{
	return pname;
}
float product::getprice()
{
	return price;
}
int product::getquantity()
{
	return quantity;
}
void product::modify()
{
	int pc;
	char nm[20];
	float pr;
	cout<<"\t\tEnter new Product code (Press '-1' to retain old one) : ";
	cin>>pc;
	cout<<"\t\tEnter new Product name (Press '.' to retain old one) : ";
	gets(nm);
	cout<<"\t\tEnter new price (Press '-1' to retain old one) : ";
	cin>>pr;
	if(pc!=(-1))
		pcode=pc;
	if(strcmp(nm,".")!=0)
		strcpy(pname,nm);
	if(pr!=(-1))
		price=pr;
}
void product::modify_features()
{
	int pc,qt;
	char nm[20],ft[80];
	float pr;
	cout<<"\t\t\t==>>Record originally contains\n";
	prodt.show_features();
	cout<<"\t\t\t==>>Enter new details\n";
	cout<<"\t\tEnter new Product code (Press '-1' to retain old one) : ";
	cin>>pc;
	cout<<"\t\tEnter new Product name (Press '.' to retain old one) : ";
	gets(nm);
	cout<<"\t\tEnter new price (Preass '-1' to retain old one) : ";
	cin>>pr;
	cout<<"\t\tEnter new features (Press '.' to retain old one) : ";
	gets(ft);
	cout<<"\t\tEnter new quantity (Press '-1' to retain old one) : ";
	cin>>qt;
	if(pc!=(-1))
		pcode=pc;
	if(strcmp(nm,".")!=0)
		strcpy(pname,nm);
	if(pr!=(-1))
		price=pr;
	if(strcmp(ft,".")!=0)
		strcpy(features,ft);
	if(qt!=(-1))
		quantity=qt;
}
class billing
{
	int billno;
	date dop;
	public:
	billing()
	{
		billno=0;
		dop.dd=0;
		dop.mm=0;
		dop.yy=0;
	}
	void getdata();
	void showdata();
	int getbillno();
	date getdate();
	void modify();
}bill;
void billing::getdata()
{
	char ch;
	cout<<"\t\t\t==>>Enter bill no. : ";
	cin>>billno;
	cout<<"\t\t\t==>>Enter date of purchase : ";
	cin>>dop.dd>>ch>>dop.mm>>ch>>dop.yy;
	while(dop.dd<1||dop.dd>31||dop.mm<1||dop.mm>12||dop.yy<2012||dop.yy>2013)
	{
		cout<<"\t\t\tWRONG DATE\n";
		cout<<"\t\t\t==>>Enter date of purchase : ";
		cin>>dop.dd>>ch>>dop.mm>>ch>>dop.yy;
	}
}
void billing::showdata()
{
	char ch;
	cout<<"\t\t\t==>>Bill no. : "<<billno<<endl;
	cout<<"\t\t\t==>>Date of purchase : "<<dop.dd<<ch<<dop.mm<<ch<<dop.yy<<endl;
}
int billing::getbillno()
{
	return billno;
}
date billing::getdate()
{
	return dop;
}
void billing::modify()
{
	char ch;
	int bn;
	date dp;
	cout<<"\t\tEnter new bill no. (Press '-1' to retain old one) : ";
	cin>>bn;
	cout<<"\t\tEnter new date (Press '-1/-1/-1' to retain old one) : ";
	cin>>dp.dd>>ch>>dp.mm>>ch>>dp.yy;
	if(bn!=(-1))
		billno=bn;
	if(dp.dd!=(-1))
	{
		dop.dd=dp.dd;
		dop.mm=dp.mm;
		dop.yy=dp.yy;
	}
}
class customer:public product,public billing
{
	char name[20];
	char address[40];
	long phno;
	char emailId[40];
	public:
	customer()
	{
		strcpy(name,"NULL");
		strcpy(address,"NULL");
		phno=0;
		strcpy(emailId,"NULL");
	}
	void getdata();
	void showdata();
	char* getname();
	long getphno();
	void modify();
}cust,cust1;
void customer::getdata()
{
	billing::getdata();
	cout<<"\n\t\t\t\t==>>Customer details\n";
	cout<<"\t\t\tName : ";
	gets(name);
	cout<<"\t\t\tAddress : ";
	gets(address);
	cout<<"\t\t\tPhone no. : ";
	cin>>phno;
	cout<<"\t\t\tEmail Id : ";
	gets(emailId);
	cout<<"\t\t\t==>>Product details\n";
	product::getdata();
	return;
}
void customer::showdata()
{
	billing::showdata();
	cout<<"\n\t\t\t\t==>>Customer details\n";
	cout<<"\t\t\tName : "<<name<<endl;
	cout<<"\t\t\tAddress : "<<address<<endl;
	cout<<"\t\t\tPhone no. : "<<phno<<endl;
	cout<<"\t\t\tEmail Id : "<<emailId<<endl;
	cout<<"\t\t\t==>>Product details\n";
	product::showdata();
}
char* customer::getname()
{
	return name;
}
long customer::getphno()
{
	return phno;
}
void customer::modify()
{
	char nm[20],ad[40],ei[40];
	long ph;
	cout<<"\t\t\t==>>Record originally contains\n";
	billing::showdata();
	customer::showdata();
	product::showdata();
	cout<<"\t\t\t==>>Enter new details\n";
	billing::modify();
	cout<<"\t\tEnter new name (Press '.' to retain old one) : ";
	gets(nm);
	cout<<"\t\tEnter new address (Press '.' to retain old one) : ";
	gets(ad);
	cout<<"\t\tEnter new phone no. (Press '-1' to retain old one) : ";
	cin>>ph;
	cout<<"\t\tEnter new Email Id (Press '.' to retain old one) : ";
	gets(ei);
	if(strcmp(nm,".")!=0)
		strcpy(name,nm);
	if(strcmp(ad,".")!=0)
		strcpy(address,ad);
	if(ph!=(-1))
		phno=ph;
	if(strcmp(ei,".")!=0)
		strcpy(emailId,ei);
	product::modify();
}
void c_enter()
{
	char ch;
	ofstream fout;
	fout.open("customer.txt",ios::out|ios::app|ios::binary);
	if(!fout)
	{
		cout<<"!!!Cannot open file!!!\n";
		exit(-1);
	}
	do
	{
		clrscr();
		cout<<"==>>Enter new record\n";
		cust.getdata();
		fout.write((char*)&cust,sizeof(cust));
		cout<<"\nRecord added\n";
		cout<<"Want to add more records...\n";
		cin>>ch;
	}while(ch=='Y'||ch=='y');
	fout.close();
	return;
}
void c_delete()
{
	char found='f',ch,ch1;
	int bno;
	do
	{
		clrscr();
		ifstream fin;
		fin.open("customer.txt",ios::in|ios::binary);
		if(!fin)
		{
			cout<<"!!!Cannot open file!!!\n";
			exit(-1);
		}
		ofstream fout;
		fout.open("temp.txt",ios::out|ios::binary);
		cout<<"\n\n\t\t\t==>>Record deletion\n";
		cout<<"\t\t\tEnter bill no. whose record is to be deleted : ";
		cin>>bno;
		while(!fin.eof())
		{
			fin.read((char*)&cust,sizeof(cust));
			if(cust.getbillno()==bno)
			{
				found='t';
				cout<<"\t\t\tRecord is :\n";
				cust.showdata();
				cout<<"\t\t\tAre you sure you want to delete this record\n";
				cin>>ch;
				if(ch=='N'||ch=='n')
				{
					fout.write((char*)&cust,sizeof(cust));
				}
				else if(ch=='Y'||ch=='y')
					cout<<"\t\t\tRecord deleted...\n";
			}
			else
				fout.write((char*)&cust,sizeof(cust));
		}
		if(found=='f')
			cout<<"\t\t\tRecord not found..\n";
		fout.close();
		fin.close();
		remove("customer.txt");
		rename("temp.txt","customer.txt");
		cout<<"\t\t\tWant to delete more records...\n\t\t\t";
		cin>>ch1;
	}while(ch1=='Y'||ch1=='y');
	return;
}
void c_display()
{
	clrscr();
	char ch,found='t',ans='Y';
	int choice,no,i=0;
	do
	{
		clrscr();
		cout<<"\n\n\t\t\t\t==>>Display records\n";
		cout<<"\t\t\t1.Display all\n";
		cout<<"\t\t\t2.Display particular record\n";
		cout<<"\n\t\t\tEnter choice\n\t\t\t";
		cin>>choice;
		switch(choice)
		{
			case 1:
			ifstream fin;
			fin.open("customer.txt",ios::in|ios::binary);
			if(!fin)
			{
				cout<<"!!!Cannot open file!!!\n";
				exit(-1);
			}
			cout<<"\n\n\t\t\t\t==>>Customer records\n";
			do
			{
				while(!fin.eof())
				{
					fin.read((char*)&cust,sizeof(cust));
					if(fin.eof())
					{
						ans='N';
						break;
					}
					i++;
					cust.showdata();
					cout<<endl;
					if(i==2)
					{
						cout<<"\t\t\tContinue...(Y or N)\n\t\t\t";
						cin>>ans;
						i=0;
					}
				}
			}while(ans=='Y');
			fin.close();
			break;
			case 2:
			cout<<"\t\t\tEnter bill no. whose record is to be displayed\n";
			cout<<"\t\t\t";
			cin>>no;
			ifstream fi;
			fi.open("customer.txt",ios::in|ios::binary);
			if(!fi)
			{
				cout<<"!!!Cannot open file!!!\n";
				exit(-1);
			}
			cout<<"\t\t\t==>>Record is\n";
			while(!fi.eof())
			{
				fi.read((char*)&cust,sizeof(cust));
				if(cust.getbillno()==no)
				{
					found='f';
					cust.showdata();
					break;
				}
			}
			fi.close();
			if(found=='t')
				cout<<"\t\t\t==>>Record not found\n";
			break;
			default:
			cout<<"\t\t\t!!!Wrong choice entered!!!\n";
		}
		cout<<"\t\t\t==>>Go back...\n\t\t\t";
		cin>>ch;
	}while(ch=='Y'||ch=='y');
	return;
}
void c_modify()
{
	char ch,found='t';
	int bno,pos;
	fstream fio;
	fio.open("customer.txt",ios::in|ios::out|ios::binary);
	if(!fio)
	{
		cout<<"!!!Cannot open file!!!\n";
		exit(-1);
	}
	do
	{
		clrscr();
		cout<<"\t\t\t==>>Modify record\n";
		cout<<"\t\t\tEnter bill no. whose record is to be modified : ";
		cout<<"\t\t\t";
		cin>>bno;
		while(!fio.eof())
		{
			pos=fio.tellg();
			fio.read((char*)&cust,sizeof(cust));
			if(cust.getbillno()==bno)
			{
				found='f';
				cust.modify();
				fio.seekp(pos);
				fio.write((char*)&cust,sizeof(cust));
				cout<<"\t\t\t==>>Record modified\n";
				break;
			}
		}
		if(found=='t')
			cout<<"\t\t\t==>>Record not found...\n";
		fio.seekg(0);
		cout<<"\t\t\t==>>Want to modify more records\n\t\t\t";
		cin>>ch;
	}while(ch=='Y'||ch=='y');
	fio.close();
	return;
}
void c_report()
{
	clrscr();
	char ch;
	long i;
	date dt;
	ifstream fin;
	fin.open("customer.txt",ios::in|ios::binary);
	if(!fin)
	{
		cout<<"!!!Cannot open file!!!\n";
		exit(-1);
	}
	cout<<"\n\n"<<setw(8)<<"Bill no."<<setw(12)<<"Name";
	cout<<setw(11)<<"Phone no."<<setw(11)<<"date";
	cout<<setw(15)<<"Product code"<<"\n\n";
	while(!fin.eof())
	{
		fin.read((char*)&cust,sizeof(cust));
		if(fin.eof())
			break;
		dt=cust.getdate();
		cout<<setw(8)<<cust.getbillno()<<setw(12)<<cust.getname();
		cout<<setw(11)<<cust.getphno()<<setw(4)<<dt.dd<<"-"<<dt.mm<<"-"<<dt.yy;
		cout<<setw(15)<<cust.getpcode();
		cout<<endl;
	}
	fin.close();
	cout<<"\n\n\t=>>Back to menu\n\t";
	cin>>ch;
	if(ch=='Y'||ch=='y')
		return;
	else
	{
		for(i=0;i<90000000;++i);
		return;
	}
}
void custom()
{
	clrscr();
	int choice;
	long i;
	cout<<"\n\n\t\t\t\tCUSTOMER RECORDS\n";
	cout<<"\t\t\t\t================\n\n";
	cout<<"\t\t\t1.==>>Enter new record\n";
	cout<<"\t\t\t2.==>>Delete existing record\n";
	cout<<"\t\t\t3.==>>Display record\n";
	cout<<"\t\t\t4.==>>Modify record\n";
	cout<<"\t\t\t5.==>>Generate report\n";
	cout<<"\t\t\t6.==>>Back to main menu\n";
	cout<<"\t\t\t7.==>>Exit\n";
	cout<<"\n\t\t\t==>>Enter choice\n\t\t\t";
	cin>>choice;
	switch(choice)
	{
		case 1:
		c_enter();
		custom();
		break;
		case 2:
		c_delete();
		custom();
		break;
		case 3:
		c_display();
		custom();
		break;
		case 4:
		c_modify();
		custom();
		break;
		case 5:
		c_report();
		custom();
		break;
		case 6:
		return;
		case 7:
		cout<<"\n\n\n\t\t\t!!!Terminating!!!";
		for(i=0;i<90000000;++i);
		exit(0);
		default:
		cout<<"\n\t\t\t!!!Wrong choice entered!!!";
		custom();
	}
}
void m_enter()
{
	char ch;
	ofstream fout;
	fout.open("mobile.txt",ios::out|ios::app|ios::binary);
	if(!fout)
	{
		cout<<"!!!Cannot open file!!!\n";
		exit(-1);
	}
	do
	{
		clrscr();
		cout<<"==>>Enter new record\n";
		prodt.get_features();
		fout.write((char*)&prodt,sizeof(prodt));
		cout<<"\nRecord added\n";
		cout<<"Want to add more records...\n";
		cin>>ch;
	}while(ch=='Y'||ch=='y');
	fout.close();
	return;
}
void m_delete()
{
	char found='f',ch,ch1;
	int pco;
	do
	{
		clrscr();
		ifstream fin;
		fin.open("mobile.txt",ios::in|ios::binary);
		if(!fin)
		{
			cout<<"!!!Cannot open file!!!\n";
			exit(-1);
		}
		ofstream fout;
		fout.open("temp.txt",ios::out|ios::binary);
		cout<<"\n\n\t\t\t==>>Record deletion\n";
		cout<<"\t\t\tEnter product code whose record is to be deleted : ";
		cin>>pco;
		while(!fin.eof())
		{
			fin.read((char*)&prodt,sizeof(prodt));
			if(prodt.getpcode()==pco)
			{
				found='t';
				cout<<"\t\t\tRecord is :\n";
				prodt.show_features();
				cout<<"\t\t\tAre you sure you want to delete this record\n";
				cin>>ch;
				if(ch=='N'||ch=='n')
				{
					fout.write((char*)&prodt,sizeof(prodt));
				}
				else if(ch=='Y'||ch=='y')
					cout<<"\t\t\tRecord deleted...\n";
			}
			else
				fout.write((char*)&prodt,sizeof(prodt));
		}
		if(found=='f')
			cout<<"\t\t\tRecord not found..\n";
		fout.close();
		fin.close();
		remove("mobile.txt");
		rename("temp.txt","mobile.txt");
		cout<<"\t\t\tWant to delete more records...\n\t\t\t";
		cin>>ch1;
	}while(ch1=='Y'||ch1=='y');
	return;
}
void m_display()
{
	clrscr();
	char ch,found='t',ans='Y';
	int choice,po,i=0;
	do
	{
		clrscr();
		cout<<"\n\n\n\t\t\t\t==>>Display records\n";
		cout<<"\t\t\t1.Display all\n";
		cout<<"\t\t\t2.Display particular record\n";
		cout<<"\n\t\t\tEnter choice\n\t\t\t";
		cin>>choice;
		switch(choice)
		{
			case 1:
			ifstream fin;
			fin.open("mobile.txt",ios::in|ios::binary);
			if(!fin)
			{
				cout<<"!!!Cannot open file!!!\n";
				exit(-1);
			}
			cout<<"\t\t\t\t==>>Mobile records\n";
			do
			{
				while(!fin.eof())
				{
					fin.read((char*)&prodt,sizeof(prodt));
					if(fin.eof())
					{
						ans='N';
						break;
					}
					i++;
					prodt.show_features();
					cout<<endl;
					if(i==2)
					{
						cout<<"\t\t\tContinue...(Y or N)\n\t\t\t";
						cin>>ans;
						i=0;
					}
				}
			}while(ans=='Y');
			fin.close();
			break;
			case 2:
			cout<<"\t\t\tEnter product code whose record is to be displayed\n";
			cout<<"\t\t\t";
			cin>>po;
			ifstream fi;
			fi.open("mobile.txt",ios::in|ios::binary);
			if(!fi)
			{
				cout<<"!!!Cannot open file!!!\n";
				exit(-1);
			}
			cout<<"\t\t\t==>>Record is\n";
			while(!fi.eof())
			{
				fi.read((char*)&prodt,sizeof(prodt));
				if(prodt.getpcode()==po)
				{
					found='f';
					prodt.show_features();
					break;
				}
			}
			fi.close();
			if(found=='t')
				cout<<"\t\t\t==>>Record not found\n";
			break;
			default:
			cout<<"\t\t\t!!!Wrong choice entered!!!\n";
		}
		cout<<"\t\t\t==>>Go back...\n\t\t\t";
		cin>>ch;
	}while(ch=='Y'||ch=='y');
	return;
}
void m_modify()
{
	char ch,found='t';
	int pco,pos;
	fstream fio;
	fio.open("mobile.txt",ios::in|ios::out|ios::binary);
	if(!fio)
	{
		cout<<"!!!Cannot open file!!!\n";
		exit(-1);
	}
	do
	{
		clrscr();
		cout<<"\t\t\t==>>Modify record\n";
		cout<<"\t\t\tEnter product code whose record is to be modified : ";
		cout<<"\t\t\t";
		cin>>pco;
		while(!fio.eof())
		{
			pos=fio.tellg();
			fio.read((char*)&prodt,sizeof(prodt));
			if(prodt.getpcode()==pco)
			{
				found='f';
				prodt.modify_features();
				fio.seekp(pos);
				fio.write((char*)&prodt,sizeof(prodt));
				cout<<"\t\t\t==>>Record modified\n";
				break;
			}
		}
		if(found=='t')
			cout<<"\t\t\t==>>Record not found...\n";
		fio.seekg(0);
		cout<<"\t\t\t==>>Want to modify more records\n\t\t\t";
		cin>>ch;
	}while(ch=='Y'||ch=='y');
	fio.close();
	return;
}
void m_report()
{
	clrscr();
	char ch;
	long i;
	ifstream fin;
	fin.open("mobile.txt",ios::in|ios::binary);
	if(!fin)
	{
		cout<<"!!!Cannot open file!!!\n";
		exit(-1);
	}
	cout<<"\n\n"<<setw(15)<<"Product code"<<setw(15)<<"Product name";
	cout<<setw(15)<<"Product price"<<setw(15)<<"Quantity"<<"\n\n";
	while(!fin.eof())
	{
		fin.read((char*)&prodt,sizeof(prodt));
		if(fin.eof())
			break;
		cout<<setw(15)<<prodt.getpcode()<<setw(15)<<prodt.getpname();
		cout<<setw(15)<<prodt.getprice()<<setw(15)<<prodt.getquantity();
		cout<<endl;
	}
	fin.close();
	cout<<"\n\n\t=>>Back to menu\n\t";
	cin>>ch;
	if(ch=='Y'||ch=='y')
		return;
	else
	{
		for(i=0;i<90000000;++i);
		return;
	}
}
void prod()
{
	clrscr();
	int choice;
	long i;
	cout<<"\n\n\t\t\t\tMOBILE RECORDS\n";
	cout<<"\t\t\t\t==============\n\n";
	cout<<"\n\t\t\t1.==>>Enter new record\n";
	cout<<"\t\t\t2.==>>Delete existing record\n";
	cout<<"\t\t\t3.==>>Display record\n";
	cout<<"\t\t\t4.==>>Modify record\n";
	cout<<"\t\t\t5.==>>Generate report\n";
	cout<<"\t\t\t6.==>>Back to main menu\n";
	cout<<"\t\t\t7.==>>Exit\n";
	cout<<"\n\t\t\t==>>Enter choice\n\t\t\t";
	cin>>choice;
	switch(choice)
	{
		case 1:
		m_enter();
		prod();
		break;
		case 2:
		m_delete();
		prod();
		break;
		case 3:
		m_display();
		prod();
		break;
		case 4:
		m_modify();
		prod();
		break;
		case 5:
		m_report();
		prod();
		break;
		case 6:
		return;
		case 7:
		cout<<"\n\t\t\t!!!Terminating!!!";
		for(i=0;i<90000000;++i);
		exit(0);
		default:
		cout<<"\n\t\t\t!!!Wrong choice entered!!!";
		prod();
	}
}
void future()
{
	char ch;
	clrscr();
	cout<<"\n\n\n\t\t\t\tFUTURE ENHANCEMENTS\n";
	cout<<"\t\t\t\t===================\n";
	cout<<"\n\t\t\t* Automatic incrementation of bill no.\n";
	cout<<"\t\t\t* Automatic updation of date\n";
	cout<<"\t\t\t* Generate special discount";
	cout<<"\n\t\t\t  for every hundreth customer\n";
	cout<<"\n\n\t\t\t==>>Back to main menu : ";
	cin>>ch;
	if(ch=='Y'||ch=='y')
		return;
	else
		exit(0);
}
void main()
{
	clrscr();
	char PASSWORD[20],ch;
	int choice,i;
	long j;
	do
	{
		clrscr();
		cout<<"\n\n\t\t\t==========================\n";
		cout<<"\t\t\tMOBILE SHOP BILLING SYSTEM\n";
		cout<<"\t\t\t==========================\n\n\n";
		cout<<"\t\t\t\t *************\n";
		cout<<"\t\t\t\t===============\n";
		cout<<"\t\t\t\t***************\n";
		cout<<"\t\t\t\t**           **\n";
		cout<<"\t\t\t\t**           **\n";
		cout<<"\t\t\t\t**           **\n";
		cout<<"\t\t\t\t**           **\n";
		cout<<"\t\t\t\t**           **\n";
		cout<<"\t\t\t\t**           **\n";
		cout<<"\t\t\t\t***************\n";
		cout<<"\t\t\t\t***************\n";
		cout<<"\t\t\t\t** 1 * 2 * 3 **\n";
		cout<<"\t\t\t\t** 4 * 5 * 6 **\n";
		cout<<"\t\t\t\t** 7 * 8 * 9 **\n";
		cout<<"\t\t\t\t** # * 0 * * **\n";
		cout<<"\t\t\t\t***************\n";
		cout<<"\t\t\t\t***************\n";
		cout<<"\t\t\t\t *************\n";
		for(j=0;j<900000000;++j);
		clrscr();
		cout<<"\n\n\n\n\n\n\t\t\t\t  Made by:\n";
		cout<<"\n\t\t\t       SHASHANK GUPTA\n";
		cout<<"\n\t\t\t\t    and\n";
		cout<<"\n\t\t\t\tSAHIL GUPTA\n";
		for(j=0;j<900000000;++j);
		clrscr();
		cout<<"\n\n\n\n\n\t\t\t\tTHE MOBLILE SHOP\n";
		cout<<"\t\t\t\t================\n";
		cout<<"\n\t\t\t1.==>>Update Customer records\n";
		cout<<"\t\t\t2.==>>Update Mobile records\n";
		cout<<"\t\t\t3.==>>Future enhancements\n";
		cout<<"\t\t\t4.==>>Exit\n";
		cout<<"\n\t\t\tEnter choice\n\t\t\t";
		cin>>choice;
		switch(choice)
		{
			case 1:
			custom();
			break;
			case 2:
			prod();
			break;
			case 3:
			future();
			break;
			case 4:
			cout<<"\t\t\t!!!Terminating!!!\n";
			for(j=0;j<900000000;++j);
			exit(0);
			default:
			cout<<"\t\t\t!!!Wrong choice!!!\n";
		}
		cout<<"\n\t\t\tDo you want to continue...\n\t\t\t";
		cin>>ch;
	}while(ch=='Y'||ch=='y');
	if(ch=='n'||ch=='N')
	{
		for(j=0;j<79999999;++j);
		clrscr();
		cout<<"\n\n\n\n\n\n\t\t\t\t=========\n";
		cout<<"\t\t\t\tTHANK YOU\n";
		cout<<"\t\t\t\t=========\n";
	}
	getch();
}