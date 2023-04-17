//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************


#include<fstream.h>
#include<ctype.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>


//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class account
{
	int acno;
	char name[50];
	double deposit;
	char type;
public:
	void create_account();	//function to get data from user
	void show_account();	//function to show data on screen
	void modify();   //function to get new data from user
	void dep(double);	//function to accept amount and add to balance amount
	void draw(double);	//function to accept amount and subtract from balance amount
	void report();	//function to show data in tabular format
	int retacno();	//function to return account number
	double retdeposit();	//function to return balance amount
	char rettype();	//function to return type of account
};         //class ends here

void account::create_account()
{
	ifstream inFile;
	account ac;
	inFile.open("account.dat",ios::binary|ios::in);
	cout<<"\nEnter The account No. :";
	r: cin>>acno;
	while(!inFile.eof())
	{
		inFile.read((char *) &ac, sizeof(account));
		if(ac.retacno()==acno)
		{
			cout<<"Account no. already exists\n please enter another account number:";
			goto r;
		}
	}
	inFile.close();
	cout<<"\n\nEnter The Name of The account Holder : ";
	gets(name);
	ctype:
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	l:cout<<"\nEnter The Initial amount(>500 for Saving and >1000 for current ) : ";
	cin>>deposit;
	if(type!='C'&& type!='S')
	      {
			cout<<"\nInvalid Type!!!\n";
			goto ctype;
	      }
	else if(type=='C' && deposit>1000)
		cout<<"\n\n\nAccount Created..";
	else if(type=='S' && deposit>500)
		cout<<"\n\n\nAccount Created..";
	else
	{
		cout<<"Please enter the appropriate amount";
		goto l;
	}
}

void account::show_account()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nThe account No."<<acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	gets(name);
	ctype1:
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	l:cout<<"\nEnter The New amount(>500 for Saving and >1000 for current ) : ";
	cin>>deposit;
	if(type!='C'&& type!='S')
	      {
			cout<<"\nInvalid Type!!!\n";
			goto ctype1;
	      }
	else if(type=='C' && deposit>1000)
		cout<<"\nRecord Updated\n";
	else if(type=='S' && deposit>500)
		cout<<"\nRecord Updated\n";
	else
	{
		cout<<"Please enter the appropriate amount";
		goto l;
	}
}



void account::dep(double x)
{
	deposit+=x;
}

void account::draw(double x)
{
	deposit-=x;
}

void account::report()
{
	cout<<setw(2)<<acno<<setw(5)<<" "<<setw(10)<<name<<setw(9)<<" "<<setw(3)<<type<<setw(10)<<" "<<deposit<<endl;
}

int account::retacno()
{
	return acno;
}

double account::retdeposit()
{
	return deposit;
}

char account::rettype()
{
	return type;
}


//***************************************************************
//    	function declaration
//****************************************************************
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
	char ch;
	int num;
	clrscr();
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using Bank Managemnt System";
			break;
		 default :cout<<"\a";
		}
		getch();
    }while(ch!='8');
	return 0;
}


//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	ac.create_account();
	outFile.open("account.dat",ios::binary|ios::app);
	outFile.write((char *) &ac, sizeof(account));
	outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
    inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
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
		cout<<"\n\nAccount number does not exist";
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

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
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*sizeof(account);
			File.seekp(pos,ios::cur);
		    File.write((char *) &ac, sizeof(account));
		    found=1;
		  }
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(int n)
{
	account ac;
	int found=0;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
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
		else
			found=1;
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	if(found==0)
		cout<<"Record not found!!";
	else
		cout<<"\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

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
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.     NAME         Type        Balance\n";
	cout<<"====================================================\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
	double amt;
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
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited :";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw :";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
		      }
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
	       }
	 }
    File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	cout<<"\n\n\n\t  BANK";
	cout<<"\n\n\tMANAGEMENT";
	cout<<"\n\n\t  SYSTEM";
	cout<<"\n\n\n\nMADE BY : Vedanshu and Subhiksha";
	cout<<"\n\nSCHOOL : Sri Sri Ravishankar Vidya Mandir";
	getch();
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************