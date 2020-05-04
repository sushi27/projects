// SRS VALUE BAZAAR Store Management System
#include<fstream.h>
#include<string.h>
#include<iomanip.h>
#include<stdio.h>
#include<conio.h>

class Item
{
		int code;
		char iname[30];
		char company[30];
		int price;
	public:
		Item();
		void Enter();
		void Display();
		void Show();
		int getcode()
		{
			return code;
		}
		void setcode(int n)
		{
			code = n;
		}
		char* getiname()
		{
			return iname;
		}
		int getprice()
		{
			return price;
		}
};

class Customer
{
		int billno;
		char name[30];
		char phone[15];
		int code[5];
		char Iname[5][30];
		int price[5];
		int qty[5];
		int total;
		int n; // total number of item
	public:
		Customer();
		void Enter();
		void Display();
		void Show();
		int getbillno()
		{
			return billno;
		}
		void setbillno(int n)
		{
			billno = n;
		}
		char *getname()
		{
			return name;
		}
		void Update(int d, char nm[], int pr, int q)
		{
			if(n>=4)
			{
				cout<<"\n\t No more Item in a bill ";
			}
			else
			{
				n++;
				code[n] = d;
				strcpy(Iname[n], nm);
				price[n] = pr;
				qty[n] = q;
				total += (pr * q);
			}
		}
};
Customer:: Customer()
{
	billno = 0;
	strcpy(name,NULL);
	strcpy(phone,NULL);
	n = -1;
	total=0;
}

void Customer::Enter()
{
	cout<<"\n\t Customer Details Entry Form ";
	cout<<"\n\t --------------------------- ";
	cout<<"\n\t Bill No. \t : "<<billno;
	cout<<"\t Name \t\t : "; gets(name);
	cout<<"\t Phone No. \t : "; gets(phone);
}
void Customer::Display()
{
	cout<<"\n\t Customer Details Form ";
	cout<<"\n\t --------------------- ";
	cout<<"\n\t Bill No. \t : "<<billno;
	cout<<"\n\t Name \t\t : "<<name;
	cout<<"\n\t Phone No. \t : "<<phone;
	cout<<"\n---------------------------------------"
		<<"---------------------------------------";
	cout<<"\n"<<setw(10)<<"Code "<<setw(20)<<"Item Name"
		<<setw(10)<<"Price"<<setw(10)<<"Qty"<<setw(10)<<"Total";
	cout<<"\n---------------------------------------"
		<<"---------------------------------------";
	cout.setf(ios::left);
	for(int i=0; i<=n; i++)
	{
		cout<<"\n"<<setw(10)<<code[i]<<setw(20)<<Iname[i]
			<<setw(10)<<price[i]<<setw(10)<<qty[i]
			<<setw(10)<<(price[i] * qty[i]);
	}
	cout<<"\n---------------------------------------"
		<<"---------------------------------------";

	cout<<"\n\t Total Amount is Rs."<<total;
}

void Customer:: Show()
{
	cout.setf(ios::left);
	cout<<"\n"<<setw(10)<<billno<<setw(20)<<name
		<<setw(15)<<phone<<setw(10)<<total;
}


Item :: Item()
{
	code=0;
	strcpy(iname,NULL);
	strcpy(company,NULL);
	price=0;
}

void Item :: Enter()
{
	cout<<"\n\t Item Details Entry Form ";
	cout<<"\n\t ------------------------";
	cout<<"\n\t Code \t\t : "<<code;
	cout<<"\n\t Name \t\t : "; gets(iname);
	cout<<"\t Company \t : "; gets(company);
	cout<<"\t Price \t\t : ";cin>>price;
}

void Item :: Display()
{
	cout<<"\n\t Item Details Form ";
	cout<<"\n\t -----------------";
	cout<<"\n\t Code \t\t : "<<code;
	cout<<"\n\t Name \t\t : "<<iname;
	cout<<"\n\t Company \t : "<<company;
	cout<<"\n\t Price \t\t : "<<price;
}

void Item :: Show()
{
	cout.setf(ios::left); // for left align in setw()
	cout<<"\n"<<setw(10)<<code<<setw(20)<<iname<<setw(20)
		<<company<<setw(10)<<price;
}

void addrec()
{
	fstream F;
	Item I1, I2;
	F.open("Item.dat",ios::in|ios::binary);

	// Move File Pointer at end of file
	F.seekg(0,ios::end);
	if(F.tellg() > 0)  // Check Record exist or not
	{
		// Move File Pointer at last record begining position
		F.seekg(F.tellg() - sizeof(I1));
		F.read((char*)&I1, sizeof(I1));
		// New Record (I2) code is last record code + 1
		I2.setcode( I1.getcode() + 1);
	}
	else
	{
		I2.setcode(1); // First Record Code is 1
	}
	F.close();
	F.open("Item.dat",ios::app|ios::binary);
	I2.Enter();
	F.write((char*)&I2, sizeof(I2));
	F.close();
}
void search()
{
	fstream F;
	Item I1;
	char name[30];
	int n,found=0,ch;
	F.open("Item.dat",ios::in|ios::binary);
	do
	{
		cout<<"\n\t Search By :- ";
		cout<<"\n\t 1.Code ";
		cout<<"\n\t 2.Item Name ";
		cout<<"\n\t Enter Choice [1-2] : ";
		cin>>ch;
		switch(ch)
		{
			case 1: cout<<"\n\t Enter Code : ";
					cin>>n;
					break;
			case 2: cout<<"\n\t Enter Name : ";
					gets(name);
					break;
			default:cout<<"\n\t Invalid Choice. Please Re-Enter";
		}
	}while(ch<1 || ch>2);

	while(F.read((char*)&I1, sizeof(I1)))
	{
		if(ch==1)
		{
			if(n == I1.getcode())
			{
				found=1;
				I1.Display();
			}
		}
		else if(ch==2)
		{
			if(strcmpi(name,I1.getiname())==0)
			{
				found=1;
				I1.Display();
			}
		}
	}
	F.close();
	if(found==0)
		cout<<"\n\t Record not Found ";
}
void update()
{
	fstream F;
	Item I1;
	int n, found=0;
	F.open("Item.dat",ios::in|ios::out|ios::binary);
	cout<<"\n\t Enter Code : ";
	cin>>n;

	while(F.read((char*)&I1, sizeof(I1)))
	{
		if(n==I1.getcode())
		{
			found=1;
			I1.Display();
			I1.Enter();
			F.seekp( F.tellg() - sizeof(I1));
			F.write((char*)&I1, sizeof(I1));
		}
	}
	F.close();

	if(found==0)
		cout<<"\n\t Record not Found ";
	else
		cout<<"\n\t Update Successful";
}
void del()
{
	fstream F,F2;
	Item I1;
	char ch;
	int n, found=0;
	F.open("Item.dat",ios::in|ios::binary);
	F2.open("Temp.dat",ios::out|ios::binary);
	cout<<"\n\t Enter Code : ";
	cin>>n;

	while(F.read((char*)&I1, sizeof(I1)))
	{
		if(n==I1.getcode())
		{
			found=1;
			I1.Display();
			cout<<"\n\t Are you sure delete this record (y/n) ? ";
			cin>>ch;
			if(ch=='n' || ch=='N')
			{
				F2.write((char*)&I1, sizeof(I1));
				cout<<"\n\t Record can not deleted";
			}
			else
			{
				cout<<"\n\t Delete Successful";
			}
		}
		else
		{
			F2.write((char*)&I1, sizeof(I1));
		}
	}
	F.close();
	F2.close();

	// Define in stdio.h
	remove("Item.dat");
	rename("Temp.dat","Item.dat");

	if(found==0)
		cout<<"\n\t Record not Found ";
}
void showall()
{
	fstream F;
	Item I1;
	int n=0;

	F.open("ITem.dat",ios::in|ios::binary);
	cout<<"\n---------------------------------------"
		<<"---------------------------------------";
	cout.setf(ios::left); // for left align in setw()
	cout<<"\n"<<setw(10)<<"Code"<<setw(20)<<"Item Name"
		<<setw(20)<<"Company"<<setw(10)<<"Price";
	cout<<"\n---------------------------------------"
		<<"---------------------------------------";
	while(F.read((char*)&I1, sizeof(I1)))
	{
		I1.Show();
		n++;
		if(n%20==0)
			getch();
	}
	cout<<"\n---------------------------------------"
		<<"---------------------------------------";
	F.close();
}
void Itemmenu()
{
	int ch;
	do
	{
		clrscr();
		cout<<"\n\t   SRS VALUE BAZAAR Store Management System";
		cout<<"\n\t------------------------------------------";
		cout<<"\n\t  Item Menu ";
		cout<<"\n\t ===========";
		cout<<"\n\t 1.Add Record ";
		cout<<"\n\t 2.Search ";
		cout<<"\n\t 3.Update ";
		cout<<"\n\t 4.Delete ";
		cout<<"\n\t 5.Show All Item ";
		cout<<"\n\t 6.Exit ";
		cout<<"\n\t Enter Choice [1-6] : ";
		cin>>ch;
		switch(ch)
		{
			case 1: addrec(); break;
			case 2: search(); break;
			case 3: update(); break;
			case 4: del(); break;
			case 5: showall(); break;
			case 6: cout<<"\n\t Exit... "; break;
			default:cout<<"\n\t Invalid Choice. ";
		}
		getch();
	}while(ch != 6);
}

void c_addrec()
{
	fstream F;
	Customer c1,c2;
	F.open("bill.dat",ios::in|ios::binary);

	F.seekg(0,ios::end); // File Pointer move at end of file

	if(F.tellg() > 0)
	{
		// Move File pointer at beginning of last record
		F.seekg(F.tellg() - sizeof(c1));
		// Read Last Record and store in c1
		F.read((char*)&c1, sizeof(c1));
		// set new record (c2) bill number is last record bill no + 1
		c2.setbillno( c1.getbillno() + 1);
	}
	else
	{
		// Set First Bill number is 101
		c2.setbillno(101);
	}
	F.close();
	F.open("bill.dat",ios::app|ios::binary);
	c2.Enter();
	char ch;
	fstream F2;
	int code;
	Item I1;
	int q;
	do
	{
		showall();
		cout<<"\n\t Enter Code : ";
		cin>>code;

		F2.open("Item.dat",ios::in|ios::binary);
		F2.seekg(0,ios::beg);

		while(F2.read((char*)&I1, sizeof(I1)))
		{
			if(code == I1.getcode())
			{
				I1.Display();
				cout<<"\n\t Enter Quantity : ";
				cin>>q;
				c2.Update(I1.getcode(), I1.getiname(), I1.getprice(), q);
			}
		}
		cout<<"\n\t More Item (y/n) ? : ";
		cin>>ch;
		F2.close();
	}while(ch=='y'||ch=='Y');
	F2.close();
	F.write((char*)&c2, sizeof(c2));
	F.close();
}
void c_search()
{
	int no, found=0;
	fstream F;
	Customer C;
	F.open("bill.dat",ios::in|ios::binary);
	cout<<"\n\t Enter Bill no : ";
	cin>>no;

	while(F.read((char*)&C, sizeof(C)))
	{
		if(no == C.getbillno())
		{
			found = 1;
			C.Display();
		}
	}
	F.close();

	if(found==0)
		cout<<"\n\t Record not Found ";
}

void c_update()
{
	char ch;
	fstream F2;
	F2.open("Item.dat",ios::in|ios::binary);
	int code;
	Item I1;
	int found,q;
	int a,no;
	fstream F;
	Customer C;
	F.open("bill.dat",ios::in|ios::out|ios::binary);
	cout<<"\n\t Enter Bill no : ";
	cin>>no;

	while(F.read((char*)&C, sizeof(C)))
	{
		if(no == C.getbillno())
		{
			found = 1;
			C.Display();
			do
			{
				showall();
				cout<<"\n\t Enter Code : ";
				cin>>code;
				found=0;
				F2.seekg(0,ios::beg);
				a=0;
				while(F2.read((char*)&I1, sizeof(I1)))
				{
					if(code == I1.getcode())
					{
						a=1;
						I1.Display();
						cout<<"\n\t Enter Quantity : ";
						cin>>q;
						C.Update(I1.getcode(), I1.getiname(), I1.getprice(), q);
					}
				}
				if(a==0)
					cout<<"\n\t Invalid Item Code ";
				cout<<"\n\t More Item (y/n) ? : ";
				cin>>ch;
			}while(ch=='y'||ch=='Y');
			F2.close();
			F.seekp(F.tellg() - sizeof(C));
			F.write((char*)&C, sizeof(C));
		}
	}
	F.close();
	if(found==0)
		cout<<"\n\t Record not Found ";
}

void c_del()
{
	fstream F,F2;
	Customer C;
	char ch;
	int n, found=0;
	F.open("bill.dat",ios::in|ios::binary);
	F2.open("Temp.dat",ios::out|ios::binary);
	cout<<"\n\t Enter bill no : ";
	cin>>n;

	while(F.read((char*)&C, sizeof(C)))
	{
		if(n==C.getbillno())
		{
			found=1;
			C.Display();
			cout<<"\n\t Are you sure delete this record (y/n) ? ";
			cin>>ch;
			if(ch=='n' || ch=='N')
			{
				F2.write((char*)&C, sizeof(C));
				cout<<"\n\t Record can not deleted";
			}
			else
			{
				cout<<"\n\t Delete Successful";
			}
		}
		else
		{
			F2.write((char*)&C, sizeof(C));
		}
	}
	F.close();
	F2.close();

	// Define in stdio.h
	remove("bill.dat");
	rename("Temp.dat","bill.dat");

	if(found==0)
		cout<<"\n\t Record not Found ";
}
void c_showall()
{
	fstream F;
	Customer C;
	int n=0;

	F.open("bill.dat",ios::in|ios::binary);
	cout<<"\n---------------------------------------"
		<<"---------------------------------------";
	cout.setf(ios::left); // for left align in setw()
	cout<<"\n"<<setw(10)<<"Bill No"<<setw(20)<<"Customer Name"
		<<setw(15)<<"Phone No"<<setw(10)<<"Amount";
	cout<<"\n---------------------------------------"
		<<"---------------------------------------";
	while(F.read((char*)&C, sizeof(C)))
	{
		C.Show();
		n++;
		if(n%20==0)
			getch();
	}
	cout<<"\n---------------------------------------"
		<<"---------------------------------------";
	F.close();
}


void Customermenu()
{
	int ch;
	do
	{
		clrscr();
		cout<<"\n\t   SRS VALUE BAZAAR Store Management System";
		cout<<"\n\t------------------------------------------";
		cout<<"\n\t Saloni Aggrawal, Manasvi Jain, Simran Arora ";
		cout<<"\n\t------------------------------------------";
		cout<<"\n\t  Customer Menu ";
		cout<<"\n\t ===============";
		cout<<"\n\t 1.Add Record ";
		cout<<"\n\t 2.Search ";
		cout<<"\n\t 3.Update ";
		cout<<"\n\t 4.Delete ";
		cout<<"\n\t 5.Show All Item ";
		cout<<"\n\t 6.Exit ";
		cout<<"\n\t Enter Choice [1-6] : ";
		cin>>ch;
		switch(ch)
		{
			case 1: c_addrec(); break;
			case 2: c_search(); break;
			case 3: c_update(); break;
			case 4: c_del(); break;
			case 5: c_showall(); break;
			case 6: cout<<"\n\t Exit... "; break;
			default:cout<<"\n\t Invalid Choice. ";
		}
		getch();
	}while(ch != 6);
}

void Mainmenu()
{
	int ch;
	do
	{
		clrscr();
		cout<<"\n\t   SRS VALUE BAZAAR Store Management System";
		cout<<"\n\t------------------------------------------";
		cout<<"\n\t Saloni Aggrawal, Manasvi Jain, Simran Arora ";
		cout<<"\n\t------------------------------------------";
		cout<<"\n\t  Main Menu ";
		cout<<"\n\t ===========";
		cout<<"\n\t 1.Item Menu ";
		cout<<"\n\t 2.Customer Menu ";
		cout<<"\n\t 3.Exit ";
		cout<<"\n\t Enter Choice [1-3] : ";
		cin>>ch;
		switch(ch)
		{
			case 1: Itemmenu(); break;
			case 2: Customermenu(); break;
			case 3: cout<<"\n\t Exit... "; break;
			default:cout<<"\n\t Invalid Choice. ";
		}
		getch();
	}while(ch != 3);
}

void Password()
{
	clrscr();
	int i;
	char pass[80];

	gotoxy(20,10); // define in conio.h
	cout<<"Enter Password : ";

	i=0;
	do
	{
		pass[i] = getch();   // input one char but not visible

		if(pass[i] == 13) // 13 is ASCII code of Enter key
			break;

		cout<<"*";
		i++;
	}while(i<79);
	pass[i] = '\0'; // string assign end with NULL

	gotoxy(20,12);
	if(strcmp(pass,"ais")==0)

	{
		cout<<"Login Successful";
		getch();
		Mainmenu();
	}
	else
	{
		cout<<"Login Fail. Password is wrong.";
		getch();
	}
}

void main()
{
	Password();
}

