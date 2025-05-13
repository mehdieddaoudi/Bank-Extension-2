
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

void ShowMainMenue();
void ShowTransactionMainMenueScreen();
void Login();
void ShowMangeUserMenue();

struct  sClient
{
	string accountnumber;
	string pincode;
	string name;
	string phone;
	double AccountBalance;
	bool MarkForDelet = false;

};
struct StUser
{
	string Username;
	string Password;
	int permissions;
	bool MarkForDelet = false;
};

StUser CurrentUser;

enum Enmainscreen
{
	showclient = 1, addcliient = 2, deleteclient = 3, updateclient = 4, findclient = 5,
	transaction = 6, MangerUser = 7, exitscreen = 8
};
enum EnTransactionMenueScreen
{
	deposit = 1, withdraw = 2, totalbalance = 3, mainmenue = 4
};
enum EnMangeMenueScreen
{
	eListUsers = 1, eAddNewUsers = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMaineMenue = 6
};
enum EnMainMenuePermissions
{
	pAll = -1, pShowClient = 1, pAddClient = 2, pDeleteclient = 4, pUpdateClient = 8,
	pFindClient = 16, pTransaction = 32, pMangeUser = 64
};

void GoBackToMainMenueScrren()
{
	cout << "\n\nPress enter of the return to main menue screen";
	system("pause>0");
	ShowMainMenue();
}
void GoBackToTransactionMenue()
{
	cout << "\n\nPress enter of the return to transaction menue screen";
	system("pause>0");
	ShowTransactionMainMenueScreen();

}
void GoBackToMangeUsersMenue()
{
	cout << "\n\nPress enter of the return to Mange Users menue screen";
	system("pause>0");
	ShowMangeUserMenue();
}




short ReadMainMenueOption()
{
	short number = 0;
	cout << "Please Enter The Number [1} to [8] ?";
	cin >> number;

	return number;
}

short ReadMangeMenueScreen()
{
	short number = 0;
	cout << "Please Enter The Number [1} to [6] ?";
	cin >> number;

	return number;
}

vector <string> SplitString(string s1, string dilim)
{
	vector <string> vsplit;

	short pos = 0;
	string sword;

	while ((pos = s1.find(dilim)) != std::string::npos)
	{
		sword = s1.substr(0, pos);
		if (sword != "")
		{
			vsplit.push_back(sword);
		}

		s1.erase(0, pos + dilim.length());

	}

	if (s1 != "")
	{
		vsplit.push_back(s1);
	}

	return vsplit;

}

StUser ConvertUserLinetoRecord(string line, string Seperator = "#//#")
{
	vector <string> vstringline;
	StUser user;

	vstringline = SplitString(line, Seperator);

	user.Username = vstringline[0];
	user.Password = vstringline[1];
	user.permissions = stoi(vstringline[2]);


	return user;


}
vector <StUser> LoadUserssDataFromFile(string UsersFileName)
{
	vector <StUser> vUsers;
	fstream Myfile;

	Myfile.open(UsersFileName, ios::in);
	if (Myfile.is_open())
	{
		string line;
		StUser user;
		while (getline(Myfile, line))
		{
			user = ConvertUserLinetoRecord(line);

			vUsers.push_back(user);
		}

		Myfile.close();
	}

	return vUsers;
}



sClient ConvertLinetoRecord(string line, string Seperator = "#//#")
{
	vector <string> vstringline;
	sClient client;

	vstringline = SplitString(line, Seperator);

	client.accountnumber = vstringline[0];
	client.pincode = vstringline[1];
	client.name = vstringline[2];
	client.phone = vstringline[3];
	client.AccountBalance = stod(vstringline[4]);

	return client;


}

vector <sClient> LoadCleintsDataFromFile(string ClientsFileName)
{
	vector <sClient> vclients;
	fstream Myfile;

	Myfile.open(ClientsFileName, ios::in);
	if (Myfile.is_open())
	{
		string line;
		sClient client;
		while (getline(Myfile, line))
		{
			client = ConvertLinetoRecord(line);

			vclients.push_back(client);
		}


		Myfile.close();

	}



	return vclients;

}

void PrintClientRecord(sClient client)
{

	cout << "| " << setw(15) << left << client.accountnumber;
	cout << "| " << setw(10) << left << client.pincode;
	cout << "| " << setw(40) << left << client.name;
	cout << "| " << setw(20) << left << client.phone;
	cout << "| " << setw(15) << left << client.AccountBalance;

}

bool checkAcssesPermission(EnMainMenuePermissions Permission)
{
	if (CurrentUser.permissions == EnMainMenuePermissions::pAll)
	{
		return true;
	}
	if ((Permission & CurrentUser.permissions) == Permission)
	{
		return true;
	}
	return false;
}
void ShowAccessDeniedMessage()
{
	cout << "\n------------------------------------\n";
	cout << "Access Denied, \nYou dont Have Permission To Do this, \nPlease Conact Your Admin.";
	cout << "\n------------------------------------\n";
}

void showclientscreen()
{
	if (!checkAcssesPermission(EnMainMenuePermissions::pShowClient))
	{
		ShowAccessDeniedMessage();
		return;
	}


	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\t\tclient (" << vclients.size() << ") client(s).";
	cout << "\n________________________________________________________";
	cout << "________________________________________________________\n" << endl;

	cout << "| " << setw(15) << left << "account number ";
	cout << "| " << setw(10) << left << "pin code ";
	cout << "| " << setw(40) << left << "name";
	cout << "| " << setw(20) << left << "phone ";
	cout << "| " << setw(15) << left << "account balance";

	cout << "\n________________________________________________________";
	cout << "________________________________________________________\n" << endl;

	if (vclients.size() == 0)
	{
		cout << "\t\t\t no clients available in the system!";
	}
	else
	{
		for (sClient client : vclients)
		{
			PrintClientRecord(client);
			cout << endl;
		}
	}
	cout << "\n________________________________________________________";
	cout << "________________________________________________________\n" << endl;

}





string ConvertRecordToLine(sClient clinet, string suplitr = "#//#")
{
	string stClientRecord = "";

	stClientRecord = stClientRecord + clinet.accountnumber + suplitr;
	stClientRecord = stClientRecord + clinet.pincode + suplitr;
	stClientRecord = stClientRecord + clinet.name + suplitr;
	stClientRecord = stClientRecord + clinet.phone + suplitr;
	stClientRecord = stClientRecord + to_string(clinet.AccountBalance) + suplitr;

	return stClientRecord;

}

bool ClientExistsByAccountNumber(string accountnumber, string FileName)
{
	vector <sClient> vclients;
	fstream Myfile;
	Myfile.open(FileName, ios::out || ios::in);
	if (Myfile.is_open())
	{
		string line;
		sClient client;
		while (getline(Myfile, line))
		{
			client = ConvertLinetoRecord(line);
			if (client.accountnumber == accountnumber)
			{
				Myfile.close();
				return true;
			}
			vclients.push_back(client);
		}
		Myfile.close();
	}


	return false;
}

sClient ReadNewClient()
{
	sClient client;

	cout << "enter account number ? ";
	getline(cin >> ws, client.accountnumber);

	while (ClientExistsByAccountNumber(client.accountnumber, ClientsFileName))
	{
		cout << "\nclient with[" << client.accountnumber << "] already exits, enter another account ";
		getline(cin >> ws, client.accountnumber);
	}


	cout << "enter pin code ? ";
	getline(cin, client.pincode);

	cout << "enter name ? ";
	getline(cin, client.name);

	cout << "enter phone ? ";
	getline(cin, client.phone);

	cout << "enter account balance ? ";
	cin >> client.AccountBalance;

	return client;

}

void AddDataLineToFile(string filename, string stDataLine)
{
	fstream Myfile;
	Myfile.open(filename, ios::out | ios::app);
	if (Myfile.is_open())
	{
		Myfile << stDataLine << endl;
		Myfile.close();
	}


}

void AddNewClient()
{
	sClient client;
	client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(client));

}

void ShowAddClientsScreen()
{
	if (!checkAcssesPermission(EnMainMenuePermissions::pAddClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	char addmore = 'Y';
	do
	{
		system("cls");
		cout << "=================================================\n";
		cout << "\t\tadd new clients screen \n";
		cout << "=================================================\n";

		cout << "Adding New Client:\n\n";

		AddNewClient();


		cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
		cin >> addmore;
	} while (toupper(addmore) == 'Y');


}



string ReadString()
{
	string s1;
	cout << "\nPlease enter AccountNumber? ";
	getline(cin >> ws, s1);

	return s1;

}

bool FindClientByAccountNumber(string accounetnumber, vector <sClient> vclients, sClient& client)
{

	for (sClient c : vclients)
	{
		if (c.accountnumber == accounetnumber)
		{
			client = c;
			return true;
		}

	}


	return false;
}

void PrintClientCard(sClient client)
{
	cout << "the following are the client delails:\n\n";
	cout << "=================================================\n";
	cout << "account number : " << client.accountnumber << endl;
	cout << "pin code       : " << client.pincode << endl;
	cout << "name           : " << client.name << endl;
	cout << "phone          : " << client.phone << endl;
	cout << "account balance : " << client.AccountBalance << endl;
	cout << "=================================================\n";

}

bool MarkClientForDeleteByAccountNumber(string accounetnumber, vector <sClient>& vclients)
{
	for (sClient& c : vclients)
	{
		if (c.accountnumber == accounetnumber)
		{
			c.MarkForDelet = true;
			return true;
		}

	}
	return false;

}

vector <sClient> SaveCleintsDataToFile(string accounetnumber, vector <sClient>& vclients)
{
	fstream Myfile;
	string dataline;
	Myfile.open(ClientsFileName, ios::out);

	if (Myfile.is_open())
	{
		for (sClient& c : vclients)
		{
			if (c.MarkForDelet == false)
			{
				dataline = ConvertRecordToLine(c);
				Myfile << dataline << endl;
			}


		}

		Myfile.close();
	}

	return vclients;

}

bool DeleteClientByAccountNumber(string accounetnumber, vector <sClient>& vclients)
{
	sClient client;
	char anwser = 'n';

	if (FindClientByAccountNumber(accounetnumber, vclients, client))
	{
		PrintClientCard(client);
		char anwser = 'n';

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> anwser;
		if (anwser == 'Y' || anwser == 'y')
		{
			MarkClientForDeleteByAccountNumber(accounetnumber, vclients);
			SaveCleintsDataToFile(accounetnumber, vclients);


			//Refresh Clients
			vclients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}

	}
	else
	{
		cout << "client with account number (" << accounetnumber << ") not found!";
		return false;
	}
	return false;

}

void ShowDeleteClientsScreen()
{
	if (!checkAcssesPermission(EnMainMenuePermissions::pDeleteclient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "=================================================\n";
	cout << "\t\tDelete clients screen \n";
	cout << "=================================================\n";
	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);
	string accounetnumber = ReadString();
	DeleteClientByAccountNumber(accounetnumber, vclients);
}



sClient ChangeClientRecord(string accounetnumber)
{
	sClient client;

	client.accountnumber = accounetnumber;

	cout << "pelase enter pin code ? ";
	getline(cin >> ws, client.pincode);

	cout << "pelase enter name ? ";
	getline(cin, client.name);

	cout << "pelase enter the phone ? ";
	getline(cin, client.phone);

	cout << "pelase enter the account balance ? ";
	cin >> client.AccountBalance;

	return client;

}

bool UpdateClientByAccountNumber(string accounetnumber, vector <sClient>& vclients)
{
	sClient client;
	char anwser = 'n';

	if (FindClientByAccountNumber(accounetnumber, vclients, client))
	{
		PrintClientCard(client);
		char anwser = 'n';

		cout << "\n\nAre you sure you want update this client? y/n?";
		cin >> anwser;
		if (anwser == 'Y' || anwser == 'y')
		{
			for (sClient& c : vclients)
			{
				c = ChangeClientRecord(accounetnumber);
				break;

			}

			SaveCleintsDataToFile(accounetnumber, vclients);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}

	}
	else
	{
		cout << "client with account number (" << accounetnumber << ") not found!";
		return false;
	}



	return false;

}

void ShowUpDateClientsScreen()
{
	if (!checkAcssesPermission(EnMainMenuePermissions::pUpdateClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "=================================================\n";
	cout << "\t\t Up Date clients screen \n";
	cout << "=================================================\n";
	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);
	string accounetnumber = ReadString();
	UpdateClientByAccountNumber(accounetnumber, vclients);

}



void ShowFindClientsScreen()
{
	if (!checkAcssesPermission(EnMainMenuePermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "=================================================\n";
	cout << "\t\tFind clients screen \n";
	cout << "=================================================\n";

	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);
	string accounetnumber = ReadString();
	sClient client;

	if (FindClientByAccountNumber(accounetnumber, vclients, client))
	{
		PrintClientCard(client);
	}
	else
	{
		cout << "\nclient with account number (" << accounetnumber << ") not found!";
	}



}










bool ReadDepositAccountBalanceToClient(string accounetnumber, vector <sClient> vclients, double depositamount)
{


	char anwser = 'n';
	cout << "\n\nAre you sure you want Deposit this client? y/n?";
	cin >> anwser;

	if (anwser == 'Y' || anwser == 'y')
	{

		for (sClient& c : vclients)
		{
			if (c.accountnumber == accounetnumber)
			{
				c.AccountBalance = c.AccountBalance + depositamount;
				SaveCleintsDataToFile(accounetnumber, vclients);
				cout << "\n\ndone Successfully. new balance is: " << c.AccountBalance << endl;
				return true;
			}

		}



	}
	return false;

}

void ShowDepositTransactionScreen()
{
	cout << "=================================================\n";
	cout << "\t\tDeposit screen \n";
	cout << "=================================================\n";

	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);
	string accounetnumber = ReadString();
	sClient client;


	while (!(FindClientByAccountNumber(accounetnumber, vclients, client)))
	{
		cout << "\nclient with account number (" << accounetnumber << ") not found!";
		string accounetnumber = ReadString();
	}

	PrintClientCard(client);

	double depositamount = 0;
	cout << "enter deposit amount ? ";
	cin >> depositamount;
	ReadDepositAccountBalanceToClient(accounetnumber, vclients, depositamount);

}



void ShowWithdrawTransactionScreen()
{
	cout << "=================================================\n";
	cout << "\t\withdraw screen \n";
	cout << "=================================================\n";

	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);
	string accounetnumber = ReadString();
	sClient client;


	while (!(FindClientByAccountNumber(accounetnumber, vclients, client)))
	{
		cout << "\nclient with account number (" << accounetnumber << ") not found!";
		string accounetnumber = ReadString();
	}

	PrintClientCard(client);

	double withdrawamount = 0;
	cout << "enter withdraw amount ? ";
	cin >> withdrawamount;

	while (withdrawamount > client.AccountBalance)
	{
		cout << "amount exceeds the balance , you can withdraw up to : " << client.AccountBalance << endl;

		cout << "enter withdraw amount ? ";
		cin >> withdrawamount;

	}

	ReadDepositAccountBalanceToClient(accounetnumber, vclients, withdrawamount * -1);


}


short ReadTransactionsMenueOption()
{
	int number = 0;
	cout << "Please Enter The Number [1} to [4] ?";
	cin >> number;

	return number;
}

void PrintClientRecordTotalBalance(sClient client)
{

	cout << "| " << setw(15) << left << client.accountnumber;
	cout << "| " << setw(40) << left << client.name;
	cout << "| " << setw(15) << left << client.AccountBalance;

}

void ShowTotalBalanceTransactionScreen()
{
	vector <sClient> vclients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\t\tclient (" << vclients.size() << ") client(s).";
	cout << "\n________________________________________________________";
	cout << "________________________________________________________\n" << endl;

	cout << "| " << setw(15) << left << "account number ";

	cout << "| " << setw(40) << left << "name";

	cout << "| " << setw(15) << left << "account balance";

	cout << "\n________________________________________________________";
	cout << "________________________________________________________\n" << endl;

	double totalbalance = 0;

	if (vclients.size() == 0)
	{
		cout << "\t\t\t no client availabe in the system! ";
	}
	else
	{
		for (sClient client : vclients)
		{

			PrintClientRecordTotalBalance(client);
			totalbalance = totalbalance + client.AccountBalance;
			cout << endl;
		}
	}


	cout << "\n________________________________________________________";
	cout << "________________________________________________________\n" << endl;

	cout << "\n\t\t\t\t\t    Total Balances = " << totalbalance;


}



void PrintUserRecord(StUser user)
{

	cout << "| " << setw(15) << left << user.Username;
	cout << "| " << setw(10) << left << user.Password;
	cout << "| " << setw(40) << left << user.permissions;

}
void ShowListUsers()
{
	vector <StUser> vUsers = LoadUserssDataFromFile(UsersFileName);

	cout << "\n\t\t\t\t\t\tclient (" << vUsers.size() << ") client(s).";
	cout << "\n________________________________________________________";
	cout << "________________________________________________________\n" << endl;

	cout << "| " << setw(15) << left << "User name ";
	cout << "| " << setw(10) << left << "Password ";
	cout << "| " << setw(40) << left << "Permissions";

	cout << "\n________________________________________________________";
	cout << "________________________________________________________\n" << endl;

	if (vUsers.size() == 0)
	{
		cout << "\t\t\t no clients available in the system!";
	}
	else
	{
		for (StUser User : vUsers)
		{
			PrintUserRecord(User);
			cout << endl;
		}
	}
	cout << "\n________________________________________________________";
	cout << "________________________________________________________\n" << endl;

}


int ReadPermission()
{
	int Permissions = 0;
	char answer = 'n';

	cout << "do tou want to give full acess? y/n?";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		return -1;
	}

	cout << "\ndo you want to give access to :\n";

	cout << "Show Client List? n/y?\n";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		Permissions = Permissions + EnMainMenuePermissions::pShowClient;
	}

	cout << "Add New Client? n/y?\n";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		Permissions = Permissions + EnMainMenuePermissions::pAddClient;
	}

	cout << "Delete Client? n/y?\n";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		Permissions = Permissions + EnMainMenuePermissions::pDeleteclient;
	}

	cout << "Update Client? n/y?\n";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		Permissions = Permissions + EnMainMenuePermissions::pUpdateClient;
	}

	cout << "Find Client? n/y?\n";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		Permissions = Permissions + EnMainMenuePermissions::pFindClient;
	}

	cout << "Transaction? n/y?\n";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		Permissions = Permissions + EnMainMenuePermissions::pTransaction;
	}

	cout << "Manage Users? n/y?\n";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		Permissions = Permissions + EnMainMenuePermissions::pMangeUser;
	}


	return Permissions;


}

string ConvertUserRecordToLine(StUser User, string suplitr = "#//#")
{
	string stUserRecord = "";

	stUserRecord = stUserRecord + User.Username + suplitr;
	stUserRecord = stUserRecord + User.Password + suplitr;
	stUserRecord = stUserRecord + to_string(User.permissions);

	return stUserRecord;

}
bool UserExistsByUserName(string username, string FileName)
{
	vector <StUser> vUsers;
	fstream Myfile;
	Myfile.open(FileName, ios::out || ios::in);
	if (Myfile.is_open())
	{
		string line;
		StUser User;
		while (getline(Myfile, line))
		{
			User = ConvertUserLinetoRecord(line);
			if (User.Username == username)
			{
				Myfile.close();
				return true;
			}
			vUsers.push_back(User);
		}
		Myfile.close();
	}


	return false;
}
StUser ReadNewUser()
{
	StUser User;

	cout << "enter UesrName ? ";
	getline(cin >> ws, User.Username);

	while (UserExistsByUserName(User.Username, UsersFileName))
	{
		cout << "\nUser with[" << User.Username << "] already exits, enter another Username ";
		getline(cin >> ws, User.Username);
	}

	cout << "enter Password ? ";
	getline(cin, User.Password);

	User.permissions = ReadPermission();

	return User;

}
void AddNewUser()
{
	StUser User;
	User = ReadNewUser();
	AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));

}
void AddNewUsers()
{

	char addmore = 'Y';
	do
	{
		system("cls");


		cout << "Adding New Users:\n\n";

		AddNewUser();

		cout << "\nClient Added Successfully, do you want to add more User ? Y / N ? ";
		cin >> addmore;
	} while (toupper(addmore) == 'Y');

}
void ShowAddNewUsersScreen()
{
	cout << "=================================================\n";
	cout << "\t\tadd new Users screen \n";
	cout << "=================================================\n";

	AddNewUsers();

}





vector <StUser> SaveUsersDataToFile(string UserName, vector <StUser>& vUsers)
{
	fstream Myfile;
	string dataline;
	Myfile.open(UserName, ios::out);

	if (Myfile.is_open())
	{
		for (StUser& c : vUsers)
		{
			if (c.MarkForDelet == false)
			{
				dataline = ConvertUserRecordToLine(c);
				Myfile << dataline << endl;
			}


		}

		Myfile.close();
	}

	return vUsers;

}
bool MarkClientForDeleteByUserName(string Username, vector <StUser>& vUsers)
{
	for (StUser& c : vUsers)
	{
		if (c.Username == Username)
		{
			c.MarkForDelet = true;
			return true;
		}

	}
	return false;

}
void PrintUserCard(StUser User)
{
	cout << "the following are the client delails:\n\n";
	cout << "=================================================\n";
	cout << "UserName   : " << User.Username << endl;
	cout << "Password   : " << User.Password << endl;
	cout << "Permission : " << User.permissions << endl;
	cout << "=================================================\n";

}
bool FindClientByUserName(string Username, vector <StUser> vUsers, StUser& users)
{

	for (StUser c : vUsers)
	{
		if (c.Username == Username)
		{
			users = c;
			return true;
		}

	}


	return false;
}
bool DeleteUserByUserName(string Username, vector <StUser>& vUsers)
{
	if (Username == "Admin")
	{
		cout << "\n\nYou cannot Delete This User.";
		return false;
	}


	StUser User;
	char anwser = 'n';

	if (FindClientByUserName(Username, vUsers, User))
	{
		PrintUserCard(User);
		char anwser = 'n';

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> anwser;
		if (anwser == 'Y' || anwser == 'y')
		{
			MarkClientForDeleteByUserName(Username, vUsers);
			SaveUsersDataToFile(UsersFileName, vUsers);


			//Refresh Clients
			vUsers = LoadUserssDataFromFile(UsersFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}

	}
	else
	{
		cout << "client with account number (" << Username << ") not found!";
		return false;
	}
	return false;

}
string ReadUserName()
{
	string s1;
	cout << "\nPlease enter UserName? ";
	getline(cin >> ws, s1);

	return s1;

}
void ShowDeleteUsersScreen()
{
	cout << "=================================================\n";
	cout << "\t\tDelete users screen \n";
	cout << "=================================================\n";
	vector <StUser> vUsers = LoadUserssDataFromFile(UsersFileName);
	string Username = ReadUserName();
	DeleteUserByUserName(Username, vUsers);
}





StUser ChangeUserRecord(string UserName)
{
	StUser user;

	user.Username = UserName;

	cout << "pelase enter password ? ";
	getline(cin >> ws, user.Password);

	user.permissions = ReadPermission();

	return user;

}
bool UpdateClientByUserName(string UserName, vector <StUser>& vUsers)
{
	StUser client;
	char anwser = 'n';

	if (FindClientByUserName(UserName, vUsers, client))
	{
		PrintUserCard(client);
		char anwser = 'n';

		cout << "\n\nAre you sure you want update this client? y/n?";
		cin >> anwser;
		if (anwser == 'Y' || anwser == 'y')
		{
			for (StUser& c : vUsers)
			{
				c = ChangeUserRecord(UserName);
				break;

			}

			SaveUsersDataToFile(UserName, vUsers);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}

	}
	else
	{
		cout << "client with account number (" << UserName << ") not found!";
		return false;
	}



	return false;

}
void ShowUpDateUsersScreen()
{
	cout << "=================================================\n";
	cout << "\t\t UpDate Users screen \n";
	cout << "=================================================\n";
	vector <StUser> vUsers = LoadUserssDataFromFile(UsersFileName);
	string Username = ReadUserName();
	UpdateClientByUserName(Username, vUsers);

}




void ShowFindUsersScreen()
{
	cout << "=================================================\n";
	cout << "\t\tFind User screen \n";
	cout << "=================================================\n";

	vector <StUser> vUsers = LoadUserssDataFromFile(UsersFileName);
	string Username = ReadUserName();
	StUser user;

	if (FindClientByUserName(Username, vUsers, user))
	{
		PrintUserCard(user);
	}
	else
	{
		cout << "\nclient with account number (" << Username << ") not found!";
	}



}


void PerfromMangeMenueScreen(EnMangeMenueScreen MangeMenueScreen)
{
	switch (MangeMenueScreen)
	{
	case EnMangeMenueScreen::eListUsers:
	{
		system("cls");
		ShowListUsers();
		GoBackToMangeUsersMenue();
		break;
	}
	case EnMangeMenueScreen::eAddNewUsers:
	{
		system("cls");
		ShowAddNewUsersScreen();
		GoBackToMangeUsersMenue();

		break;
	}
	case EnMangeMenueScreen::eDeleteUser:
	{
		system("cls");
		ShowDeleteUsersScreen();
		GoBackToMangeUsersMenue();
		break;
	}
	case EnMangeMenueScreen::eUpdateUser:
	{
		system("cls");
		ShowUpDateUsersScreen();
		GoBackToMainMenueScrren();
		break;
	}
	case EnMangeMenueScreen::eFindUser:
	{
		system("cls");
		ShowFindUsersScreen();
		GoBackToMainMenueScrren();
		break;
	}
	case EnMangeMenueScreen::eMaineMenue:
	{
		system("cls");
		ShowMainMenue();
		break;
	}

	}

}


void PerfromTransactionMenueOption(EnTransactionMenueScreen transactionscreen)
{
	switch (transactionscreen)
	{
	case EnTransactionMenueScreen::deposit:
	{
		system("cls");
		ShowDepositTransactionScreen();
		GoBackToTransactionMenue();
		break;
	}
	case EnTransactionMenueScreen::withdraw:
	{
		system("cls");
		ShowWithdrawTransactionScreen();
		GoBackToTransactionMenue();
		break;
	}
	case EnTransactionMenueScreen::totalbalance:
	{
		system("cls");
		ShowTotalBalanceTransactionScreen();
		GoBackToTransactionMenue();
		break;
	}
	case EnTransactionMenueScreen::mainmenue:
	{
		system("cls");
		ShowMainMenue();
		break;
	}

	}

}

void ShowTransactionMainMenueScreen()
{
	if (!checkAcssesPermission(EnMainMenuePermissions::pTransaction))
	{
		ShowAccessDeniedMessage();
		return;
	}
	system("cls");
	cout << "=================================================\n";
	cout << "\t\ttransaction menue screen \n";
	cout << "=================================================\n";

	cout << "\t\t[1] deposit.\n";
	cout << "\t\t[2] withdraw.\n";
	cout << "\t\t[3] total balance.\n";
	cout << "\t\t[4] maine menue.\n";

	cout << "=================================================\n";
	PerfromTransactionMenueOption((EnTransactionMenueScreen)ReadTransactionsMenueOption());


}
void ShowMangeUserMenue()
{
	if (!checkAcssesPermission(EnMainMenuePermissions::pMangeUser))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenueScrren();
		return;
	}
	system("cls");
	cout << "=================================================\n";
	cout << "\t\tMange User menue screen \n";
	cout << "=================================================\n";

	cout << "\t\t[1] List Users.\n";
	cout << "\t\t[2] Add New User.\n";
	cout << "\t\t[3] Delete User.\n";
	cout << "\t\t[4] Update User.\n";
	cout << "\t\t[5] find User.\n";
	cout << "\t\t[6] maine menue.\n";
	cout << "=================================================\n";

	PerfromMangeMenueScreen((EnMangeMenueScreen)ReadMangeMenueScreen());


}


void PerfromMainMenueOption(Enmainscreen mainscreen)
{
	switch (mainscreen)
	{
	case Enmainscreen::showclient:
	{
		system("cls");
		showclientscreen();
		GoBackToMainMenueScrren();
		break;
	}

	case Enmainscreen::addcliient:
	{
		system("cls");
		ShowAddClientsScreen();
		GoBackToMainMenueScrren();
		break;
	}


	case Enmainscreen::deleteclient:
	{
		system("cls");
		ShowDeleteClientsScreen();
		GoBackToMainMenueScrren();
		break;
	}
	case Enmainscreen::updateclient:
	{
		system("cls");
		ShowUpDateClientsScreen();
		GoBackToMainMenueScrren();
		break;

	}
	case Enmainscreen::findclient:
	{
		system("cls");
		ShowFindClientsScreen();
		GoBackToMainMenueScrren();
		break;
	}
	case Enmainscreen::transaction:
	{
		system("cls");
		ShowTransactionMainMenueScreen();
		GoBackToMainMenueScrren();
		break;
	}
	case Enmainscreen::MangerUser:
	{
		system("cls");
		ShowMangeUserMenue();
		break;
	}
	case Enmainscreen::exitscreen:
	{
		system("cls");
		//ShowExitClientsScreen();
		Login();
		break;
	}

	}


}


void ShowMainMenue()
{
	system("cls");
	cout << "=================================================\n";
	cout << "\t\tmaine menue screen \n";
	cout << "=================================================\n";
	cout << "\t\t[1] show client list.\n";
	cout << "\t\t[2] add client list.\n";
	cout << "\t\t[3] delete client list.\n";
	cout << "\t\t[4] update client list.\n";
	cout << "\t\t[5] find client list.\n";
	cout << "\t\t[6] transactions.\n";
	cout << "\t\t[7] Mange Users.\n";
	cout << "\t\t[8] Logout.\n";
	cout << "=================================================\n";

	PerfromMainMenueOption((Enmainscreen)ReadMainMenueOption());

}

bool FindUserByUsernamePasword(string username, string paswword, StUser& User)
{
	vector <StUser> Vusers = LoadUserssDataFromFile(UsersFileName);

	for (StUser u : Vusers)
	{
		if (u.Username == username && u.Password == paswword)
		{
			User = u;
			return true;
		}



	}
	return false;
}



bool loadUserinfo(string username, string password)
{
	if (FindUserByUsernamePasword(username, password, CurrentUser))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Login()
{
	bool loginfail = false;
	string username, password;

	do
	{

		system("cls");
		cout << "=================================================\n";
		cout << "\t\tlogin users \n";
		cout << "=================================================\n";

		if (loginfail)
		{
			cout << "invalid Username/Password!\n";
		}

		cout << "enter username? ";
		cin >> username;

		cout << "enter pasword? ";
		cin >> password;

		loginfail = !loadUserinfo(username, password);

	} while (loginfail);


	ShowMainMenue();
}


int main()
{
	Login();


	system("pause>0");
	return 0;
}
