

#include<fstream.h>
#include<ctype.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>
class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//function to get data from user
	void show_account();	//function to show data on screen
	void modify();          //function to get new data from user
	void dep(int);	        //function to accept amount and add to balance amount
	void draw(int);    	//function to accept amount and subtract from balance amount
	void report();	        //function to show data in tabular format
	int retacno();	        //function to return account number
	int retdeposit();	//function to return balance amount
	char rettype();	        //function to return type of account 
};

void account::create_account()
{
	cout<<"\nEnter the account number  :";
	cin>>acno;
	cout<<"\nEnter the full name of account holder : ";
	gets(name);
	cout<<"\nEnter the type of account : ";
	cout<<"\nC for CURRENT ACCOUNT \n";
	cout<<"\nS for SAVING ACCOUNT \n";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter the initial deposit : ";
	cin>>deposit;
	cout<<"\n\n\nAccount credited";
}

void account::show_account()
{
	cout<<"\nAccount number  : "<<acno;
	cout<<"\nAccount holder name : ";
	cout<<name;
	cout<<"\nType of account : "<<type;
	cout<<"\nBalance : "<<deposit;
}


void account::modify()
{
	cout<<"\nThe account number :"<<acno;
	cout<<"\nEnter the name of account holder : ";
	gets(name);
	cout<<"\nEnter the type of account : ";
	cout<<"\nC for CURRENT ACCOUNT \n\n";
	cout<<"\nS for SAVING ACCOUNT \n\n";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter the amount : ";
	cin>>deposit;
}



void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report()
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

int account::retacno()
{
	return acno;
}

int account::retdeposit()
{
	return deposit;
}

char account::rettype()
{
	return type;
}
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function
void help();   //function to display help about project
int main()
{
	char ch;
	int num,ch1,ch2;
	clrscr();
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\tWelcome to our";
		cout<<"\n\n\tBanking project\n";
		cout<<"\n\n\t01. New account";
		cout<<"\n\n\t02. List of accounts";
		cout<<"\n\n\t03. Individual account";
		cout<<"\n\n\t04. Daily transection  (Deposit/Withdrawal)";
		cout<<"\n\n\t05. Edit Acounts  (Modify/close)";
		cout<<"\n\n\t06. Help";
		cout<<"\n\n\t07. Exit";
		cout<<"\n\n\tChoose any option from 1 to 7 ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			display_all();
			break;
		case '3':
			cout<<"\nEnter your account number : "; cin>>num;
			display_sp(num);
			break;
		case '4':cout<<"\n 1.Deposit amount";
			 cout<<"\n 2.Withdrawal"<<"\nEnter your choice(1 or 2)\n";
			 cin>>ch1;
			 if(ch1==1)
		       {
			cout<<"\n\nEnter your account number : "; cin>>num;
			deposit_withdraw(num, 1);
		       }
			else if(ch1==2)
		       {cout<<"\n\n\tEnter your account number : "; cin>>num;
			deposit_withdraw(num, 2);}
			break;
		case '5':cout<<"\n 1.Modify your account";
			 cout<<"\n 2.Delete your account"<<"\n\n Enter you choise (1 or 2) \n\n";
			 cin>>ch2;
			 if(ch2==1)
			{cout<<"Enter your account number : ";cin>>num;
			 modify_account(num);}
			 if(ch2==2)
			{cout<<"Enter your account number : ";cin>>num;
			 delete_account(num);}
			break;
		 case '6':
			help();
			break;
		 case '7':
			cout<<"\n\n\tThanks for intrest in our project";
			break;
		 default :cout<<"\a";
		}
		getch();
    }while(ch!='7');
	return 0;
}
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write((char *) &ac, sizeof(account));
	outFile.close();
}
void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
    inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File not available !! Press any Key...";
		return;
	}
	cout<<"\nBalance deposit\n";
    while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
    inFile.close();
	if(flag==0)
		cout<<"\n\nInvalid account number";
}
void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
    while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\n Enter new detail of account"<<endl;
			ac.modify();
			int pos=(-1)*sizeof(account);
			File.seekp(pos,ios::cur);
		    File.write((char *) &ac, sizeof(account));
		    cout<<"\n\n\t Record updated ";
		    found=1;
		  }
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record not found";
}
void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write((char *) &ac, sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord deleted ..";
}

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tAccount holder list\n\n";
	cout<<"____________________________________________________\n";
	cout<<"____________________________________________________\n";
	cout<<"A/c no.      Name         Type    Balance\n";
	cout<<"____________________________________________________\n";
	cout<<"____________________________________________________\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}
void deposit_withdraw(int n, int option)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
    while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTo deposite amount ";
				cout<<"\n\nEnter the amount to be deposit :";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\tTo withdraw amount ";
				cout<<"\n\nEnter the amount to be withdrawn :";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficient balance!!!!!";
				else
					ac.draw(amt);
		      }
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record updated!!!!!";
			found=1;
	       }
	 }
    File.close();
	if(found==0)
		cout<<"\n\n Record not available !!!!! ";
}
/* Function to display help about this project */
void help(void)
{
clrscr();

	cout<<"\n\n\n\t\t\t\t\b\t Welcome To Our";
	cout<<"\n\n\t\t\t\b\t\t Banking Project\n";
	cout<<"\nYou can keep record of your transection";
	cout<<"\nThis Program is capable of holding any number ofaccount and amount";
	cout<<"\n---->In first option you can open a new account";
	cout<<"\nNOTE:-Our privacy purpos user are allowed to choose their account number by own";
	cout<<"\nand are requested to keep it confedential";
	cout<<"\n---->In second option you can see list of all account holder";
	cout<<"\n---->In third option you can see information of your account";
	cout<<"\n---->In fourth option you can see daily transections i.e."<<"\n(Deposit/Withdraw)";
	cout<<"\n---->In fifth option their is provision of editing your account i.e"<<"\n (Modify/Delete)";
	cout<<"\n  NOTE:-Open amount should not be less than Rs. 500/-";
	cout<<"\n---->And last option is Quit (Exit to windows)";
	cout<<"\nPress enter to continue...";
getch();
}

//    	Introductoin Function

void intro()
{
	cout<<"\n\n\n\t\t\t\t\bWelcome  To  Our ";
	cout<<"\n\n\t\b\t\t\t\tBanking Project\n";
	cout<<"\n\n\n\n\n\nPrepared By:\n\n";
	cout<<"\n:1) Deepak Kumar Pandey (XII A1)";
	cout<<"\n:2) Sawan Kumar Pal  (XII A1)";
	cout<<"\n:3) Nishant Srivastava (XII A1)";
	cout<<"\n:4) Chandraprakash Chaubey (XII A1)";
	cout<<"\n\n\nSchool : Cetral Hindu Boy's School (k)";
	getch();
}
//    			End of project