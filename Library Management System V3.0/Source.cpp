#include<iostream>
#include<Windows.h>
#include<string>
#include<ctime>

using namespace std;

struct Patrons
{
	string name;
	string email;
	string phone;
	int maxBookBorrow = 0;
	int returndays[3] = { 0,0,0 };
	string booksBorrow[3] = { "N/A","N/A","N/A" };
	string authors[3] = { "N/A","N/A" ,"N/A" };
	int front = -1;
	int rear = -1;
	string last10Books[10] = { "" };
	Patrons* tail;
}*pHead = NULL;

struct Books
{
	string name;
	string author;
	int bookId;
	int mainCat;
	int subCat;
	Books* tail;
}*bHead = NULL;

void start();
void RegisterPatron();
void SearchPatron();
void ViewPatron();
void UpdatePatronInfo();
void RemovePatron();
void Return();
void BooksAdd();
void BooksRemove();
void BooksDisplay();
void BooksUpdate();
void BooksSearch();
void Borrow();
void remove(int id);
void add(string bookName, string author, string name, string email);
void EndLines();
void Las10Books();

int main()
{
	bool infi = true;
	while (infi)
		start();
	return 0;
}

void start()
{
	int ch;
	system("cls");
	cout << "****************************** WELCOME ******************************" << endl << endl;
	cout << " 1.  REGISTER PATRON     2.  SEARCH PATRON     3.  VIEW PATRON" << endl;
	cout << " 4.  UPDATE PATRON INFO  5.  REMOVE PATRON     6.  RETURN" << endl;
	cout << " 7.  BORROW              8.  ADD BOOKS         9.  REMOVE BOOKS" << endl;
	cout << " 10. DISPLAY BOOKS       11. UPDATE BOOK INFO  12. SEARCH BOOKS" << endl;
	cout << " 13. LAST 10 BOOKS       14. EXIT" << endl << endl;
	cout << ": ";
	cin >> ch;
	switch (ch)
	{
	case 1: RegisterPatron();
		break;
	case 2: SearchPatron();
		break;
	case 3: ViewPatron();
		break;
	case 4: UpdatePatronInfo();
		break;
	case 5: RemovePatron();
		break;
	case 6: Return();
		break;
	case 7: Borrow();
		break;
	case 8: BooksAdd();
		break;
	case 9: BooksRemove();
		break;
	case 10: BooksDisplay();
		break;
	case 11: BooksUpdate();
		break;
	case 12: BooksSearch();
		break;
	case 13: Las10Books();
		break;
	case 14: exit(0);
		break;
	default:
	{
		cout << endl << endl << "ERROR!!!!" << endl << endl;
		cout << "wait.......!" << endl;
		Sleep(2000);
		start();
	}
	}
}

void RegisterPatron()
{
	int ch;
	bool flag = false;
	Patrons* patron = new Patrons;
	Patrons* pCurrent = pHead;
	string name, email, phone;
	system("cls");
	cout << "******************** PATRON REGISTRATION ********************" << endl;
	cout << "Enter your name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter your email: ";
	cin >> email;
	cout << "Enter your phone number: ";
	cin >> phone;
	while (pCurrent != NULL)
	{
		if (pCurrent->email.compare(email) == 0 || pCurrent->phone.compare(phone)==0)
		{
			cout << endl << endl;
			cout << "Email or Phone already in use" << endl;
			flag = true;
			break;
		}
		else
			pCurrent = pCurrent->tail;
	}
	if (flag)
	{
		cout << endl << endl << "wait........!" << endl;
		Sleep(2000);
		start();
	}
	else
	{
		patron->name = name;
		patron->email = email;
		patron->phone = phone;
		patron->tail = NULL;
		cout << endl << endl << "saving.........!" << endl;
		if (pHead == NULL)
			pHead = patron;
		else
		{
			pCurrent = pHead;
			while (pCurrent->tail != NULL)
				pCurrent = pCurrent->tail;
			pCurrent->tail = patron;
		}
		Sleep(3000);
		cout << "saved.........!" << endl << endl;
		Sleep(1000);
		cout << "1. Add another patron" << endl;
		cout << "2. Main Menu" << endl;
		cout << "3. Exit" << endl;
		cout << ": ";
		cin >> ch;
		switch (ch)
		{
		case 1: RegisterPatron();
			break;
		case 2: start();
			break;
		case 3: exit(0);
			break;
		default:
		{
			cout << endl << endl << "ERROR...!" << endl;
			cout << endl << "wait.......!" << endl;
			Sleep(2000);
			start();
		}
		}
	}
}

void ViewPatron()
{
	cout << endl << endl << "loading.........!" << endl;
	Sleep(2000);
	system("CLS");
	int ch;
	cout << "******************** ALL PATRONS ********************" << endl;
	if (pHead == NULL)
		cout << "NO INFO.....!" << endl;
	else
	{
		Patrons* pCurrent = pHead;
		while (pCurrent != NULL)
		{
			cout << "NAME            : " << pCurrent->name << endl;
			cout << "EMAIL           : " << pCurrent->email << endl;
			cout << "PHONE NUMBER    : " << pCurrent->phone << endl;
			cout << "BORROW LIMIT    : " << pCurrent->maxBookBorrow << "/3" << endl;
			cout << endl;
			cout << "BORROWED BOOK 1 : " << pCurrent->booksBorrow[0] << endl;
			cout << "AUTHOR BOOK 1   : " << pCurrent->authors[0] << endl;
			cout << "DAYS BOOK 1     : " << pCurrent->returndays[0] << " days" << endl;
			cout << endl;
			cout << "BORROWED BOOK 2 : " << pCurrent->booksBorrow[1] << endl;
			cout << "AUTHOR BOOK 2   : " << pCurrent->authors[1] << endl;
			cout << "DAYS BOOK 2     : " << pCurrent->returndays[1] << " days" << endl;
			cout << endl;
			cout << "BORROWED BOOK 3 : " << pCurrent->booksBorrow[2] << endl;
			cout << "AUTHOR BOOK 3   : " << pCurrent->authors[2] << endl;
			cout << "DAYS BOOK 3     : " << pCurrent->returndays[2] << " days" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << endl;
			pCurrent = pCurrent->tail;
		}
	}
	EndLines();
}

void SearchPatron()
{
	bool flag = false;
	int ch;
	string name, email;
	system("CLS");
	cout << "******************** SEARCH PATRON ********************" << endl;
	cout << "Enter Patron name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter Patron email: ";
	cin >> email;
	Patrons* pCurrent = pHead;
	while (pCurrent != NULL)
	{
		if (pCurrent->name.compare(name) == 0)
		{
			if (pCurrent->email.compare(email) == 0)
			{
				cout << endl << endl << "searching........!" << endl << endl;
				Sleep(3000);
				cout << "NAME            : " << pCurrent->name << endl;
				cout << "EMAIL           : " << pCurrent->email << endl;
				cout << "PHONE NUMBER    : " << pCurrent->phone << endl;
				cout << "BORROW LIMIT    : " << pCurrent->maxBookBorrow << "/3" << endl;
				cout << endl;
				cout << "BORROWED BOOK 1 : " << pCurrent->booksBorrow[0] << endl;
				cout << "AUTHOR BOOK 1   : " << pCurrent->authors[0] << endl;
				cout << "DAYS BOOK 1     : " << pCurrent->returndays[0] << " days" << endl;
				cout << endl;
				cout << "BORROWED BOOK 2 : " << pCurrent->booksBorrow[1] << endl;
				cout << "AUTHOR BOOK 2   : " << pCurrent->authors[1] << endl;
				cout << "DAYS BOOK 2     : " << pCurrent->returndays[1] << " days" << endl;
				cout << endl;
				cout << "BORROWED BOOK 3 : " << pCurrent->booksBorrow[2] << endl;
				cout << "AUTHOR BOOK 3   : " << pCurrent->authors[2] << endl;
				cout << "DAYS BOOK 3     : " << pCurrent->returndays[2] << " days" << endl;
				flag = true;
				break;
			}
			else
				pCurrent = pCurrent->tail;
		}
		else
			pCurrent = pCurrent->tail;
	}
	if (flag == false)
	{
		cout << endl << endl << "searching........!" << endl << endl;
		Sleep(3000);
		cout << "NOT FOUND......!" << endl;
	}
	EndLines();
}

void UpdatePatronInfo()
{
	int ch;
	string name, email, newName, newEmail, newPhone;
	bool flag = false;
	system("cls");
	cout << "******************** UPDATE PATRON INFO ********************" << endl;
	cout << "Enter Patron name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter Patron email: ";
	cin >> email;
	Patrons* pCurrent = pHead;
	while (pCurrent != NULL)
	{
		if (pCurrent->name.compare(name) == 0)
		{
			if (pCurrent->email.compare(email) == 0)
			{
				flag = true;
				break;
			}
			else
				pCurrent = pCurrent->tail;
		}
		else
			pCurrent = pCurrent->tail;
	}
	if (flag)
	{
		cout << endl << endl << "verifying............!" << endl;
		Sleep(3000);
		cout << "verified.........!" << endl;
		cout << endl;
		Sleep(1000);
		cout << "Enter NEW Patron name: ";
		cin.ignore();
		getline(cin, newName);
		cout << "Enter NEW Patron email: ";
		cin >> newEmail;
		cout << "Enter NEW Patron phone number: ";
		cin >> newPhone;
		Patrons* tempPatron;
		tempPatron = pHead;
		while (tempPatron != NULL)
		{
			if (tempPatron->name.compare(name) == 0)
			{
				if (tempPatron->email.compare(email) == 0)
				{
					tempPatron->name = newName;
					tempPatron->email = newEmail;
					tempPatron->phone = newPhone;
					break;
				}
				else
					tempPatron = tempPatron->tail;
			}
			else
				tempPatron = tempPatron->tail;
		}
		cout << endl << endl << "updating........!" << endl;
		Sleep(3000);
		cout << "completed.........!" << endl;
		Sleep(1000);
	}
	else
	{
		cout << endl << endl << "searching.........!" << endl;
		Sleep(3000);
		cout << "NOT FOUND........!" << endl;
		Sleep(1000);
	}
	EndLines();
}

void RemovePatron()
{
	int ch;
	bool flag = false;
	Patrons* tempPatron;
	Patrons* rePatron;
	Patrons* pCurrent;
	string name, email;
	tempPatron = pHead;
	rePatron = NULL;
	system("cls");
	cout << "******************** DELETE PATRON ACCOUNT ********************" << endl;
	cout << "Enter your name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter your email: ";
	cin >> email;
	if (tempPatron->name.compare(name) == 0)
	{
		if (tempPatron->email.compare(email) == 0)
		{
			rePatron = pHead->tail;
			pHead = rePatron;
			flag = true;
		}
	}
	else
	{
		while (tempPatron != NULL)
		{
			if (tempPatron->name.compare(name) == 0)
			{
				if (tempPatron->email.compare(email) == 0)
				{
					pCurrent = tempPatron->tail;
					rePatron->tail = pCurrent;
					flag = true;
				}
			}
			rePatron = tempPatron;
			tempPatron = tempPatron->tail;
		}
	}
	if (flag)
	{
		cout << endl << endl << "searching.........!" << endl;
		Sleep(3000);
		cout << "deleted........!" << endl;
		Sleep(1000);
	}
	else
	{
		cout << endl << endl << "searching..........!" << endl;
		Sleep(3000);
		cout << "NOT FOUND......!" << endl;
		Sleep(1000);
	}
	EndLines();
}

void BooksAdd()
{
	Books* book = new Books;
	Books* bCurrent = bHead;
	int random, id, c = 0, ch;
	bool flag = true;
	system("cls");
	cout << "******************** ADD BOOKS ********************" << endl;
	cout << "Enter book name: ";
	cin.ignore();
	getline(cin, book->name);
	cout << "Enter author name: ";
	getline(cin, book->author);
	cout << "Choose a category 1. Fiction" << endl;
	cout << "                  2. Non-Fiction" << endl;
	cout << ": ";
	cin >> book->mainCat;
	cout << "Choose a sub genre 1.  Fantasy" << endl;
	cout << "                   2.  Science" << endl;
	cout << "                   3.  Historical" << endl;
	cout << "                   4.  Realistic" << endl;
	cout << "                   5.  Fan" << endl;
	cout << "                   6.  Narrative" << endl;
	cout << "                   7.  Biography" << endl;
	cout << "                   8.  Periodicals" << endl;
	cout << "                   9.  Self-help" << endl;
	cout << "                   10. References" << endl;
	cout << ": ";
	cin >> book->subCat;
	book->tail = NULL;
	srand(time(0));
	while (flag)
	{
		c = 0;
		random = 1 + (rand() % 1000);
		while (bCurrent != NULL)
		{
			if (bCurrent->bookId == random)
				c++;
			bCurrent = bCurrent->tail;
		}
		if (c > 0)
			flag = true;
		else
			flag = false;
	}
	cout << endl << endl << "generating unique ID............!" << endl;
	Sleep(3000);
	cout << "Book ID: " << random;
	book->bookId = random;
	cout << endl << "saving.........!" << endl;
	if (bHead == NULL)
		bHead = book;
	else
	{
		bCurrent = bHead;
		while (bCurrent->tail != NULL)
			bCurrent = bCurrent->tail;
		bCurrent->tail = book;
	}
	Sleep(3000);
	cout << "saved.........!" << endl << endl;
	Sleep(1000);
	cout << "1. Add another book" << endl;
	cout << "2. Main Menu" << endl;
	cout << "3. Exit" << endl;
	cout << ": ";
	cin >> ch;
	switch (ch)
	{
	case 1: BooksAdd();
		break;
	case 2: start();
		break;
	case 3: exit(0);
		break;
	default:
	{
		cout << endl << endl << "ERROR...!" << endl;
		cout << endl << "wait.......!" << endl;
		Sleep(2000);
		start();
	}
	}
}

void BooksDisplay()
{
	cout << endl << endl << "loading..........!" << endl;
	Sleep(2000);
	system("cls");
	int ch;
	Books* bCurrent = bHead;
	string catg[2] = { "Fiction","Non-Fiction" };
	string subgen[10] = { "Fantasy","Science","Historical","Realistic","Fan","Narrative","Biography","Periodicals","Self-help","Reference" };
	cout << "**********************ALL BOOKS**********************" << endl;
	if (bHead == NULL)
		cout << "NO INFO.....!" << endl;
	else
	{
		while (bCurrent != NULL)
		{
			cout << "NAME     : " << bCurrent->name << endl;
			cout << "ID       : " << bCurrent->bookId << endl;
			cout << "AUTHOR   : " << bCurrent->author << endl;
			cout << "CATEGORY : " << catg[bCurrent->mainCat - 1] << endl;
			cout << "GENRE    : " << subgen[bCurrent->subCat - 1] << endl;
			cout << endl << endl;
			bCurrent = bCurrent->tail;
		}
	}
	cout << "1. BORROW" << endl;
	cout << "2. Main Menu" << endl;
	cout << "3. Exit" << endl;
	cout << ": ";
	cin >> ch;
	switch (ch)
	{
	case 1: Borrow();
		break;
	case 2: start();
		break;
	case 3: exit(0);
		break;
	default:
	{
		cout << endl << endl << "ERROR...!" << endl;
		cout << endl << "wait.......!" << endl;
		Sleep(2000);
		start();
	}
	}
}

void BooksSearch()
{
	system("cls");
	cout << "******************* BOOK SEARCH ********************" << endl;
	bool flag = false;
	Books* bCurrent = bHead;
	int ch, category, genre;
	string catg[2] = { "Fiction","Non-Fiction" };
	string subgen[10] = { "Fantasy","Science","Historical","Realistic","Fan","Narrative","Biography","Periodicals","Self-help","Reference" };
	cout << "1. Search by category & genre" << endl;
	cout << "2. Search by book name & author" << endl;
	cout << ": ";
	cin >> ch;
	switch (ch)
	{
	case 1: 
	{
		cout << "Enter category: 1. Fiction" << endl;
		cout << "                2. Non-Fiction" << endl;
		cout << ": ";
		cin >> category;
		cout << "Enter genre 1.  Fantasy" << endl;
		cout << "            2.  Science" << endl;
		cout << "            3.  Historical" << endl;
		cout << "            4.  Realistic" << endl;
		cout << "            5.  Fan" << endl;
		cout << "            6.  Narrative" << endl;
		cout << "            7.  Biography" << endl;
		cout << "            8.  Periodicals" << endl;
		cout << "            9.  Self-help" << endl;
		cout << "           10. References" << endl;
		cout << ": ";
		cin >> genre;
		cout << endl << endl << "searching............!" << endl << endl;
		Sleep(3000);
		while (bCurrent != NULL)
		{
			if (bCurrent->mainCat == category)
			{
				if (bCurrent->subCat == genre)
				{
					cout << "NAME     : " << bCurrent->name << endl;
					cout << "AUTHOR   : " << bCurrent->author << endl;
					cout << "ID       : " << bCurrent->bookId << endl;
					cout << "CATEGORY : " << catg[bCurrent->mainCat - 1] << endl;
					cout << "GENRE    : " << subgen[bCurrent->subCat - 1] << endl;
					cout << endl;
					flag = true;
					bCurrent = bCurrent->tail;
				}
				else
					bCurrent = bCurrent->tail;
			}
			else
				bCurrent = bCurrent->tail;
		}
	}
	break;
	case 2:
	{
		string name, author;
		cout << "Enter Book Name: ";
		cin.ignore();
		getline(cin, name);
		cout << "Enter Book Author: ";
		getline(cin, author);
		cout << endl << endl << "searching............!" << endl << endl;
		Sleep(3000);
		while (bCurrent != NULL)
		{
			if (bCurrent->name.compare(name) == 0)
			{
				if (bCurrent->author.compare(author) == 0)
				{
					cout << "NAME     : " << bCurrent->name << endl;
					cout << "AUTHOR   : " << bCurrent->author << endl;
					cout << "ID       : " << bCurrent->bookId << endl;
					cout << "CATEGORY : " << catg[bCurrent->mainCat - 1] << endl;
					cout << "GENRE    : " << subgen[bCurrent->subCat - 1] << endl;
					cout << endl;
					flag = true;
					bCurrent = bCurrent->tail;
				}
				else
					bCurrent = bCurrent->tail;
			}
			else
				bCurrent = bCurrent->tail;
		}
	}
	break;
	default:
	{
		cout << endl << endl << "ERROR.......!" << endl;
		cout << endl << "wait........!" << endl;
		Sleep(2000);
		start();
	}
	}
	if (flag == false)
		cout << "NOT FOUND......!" << endl;
	cout << endl;
	cout << "1. BORROW" << endl;
	cout << "2. Main Menu" << endl;
	cout << "3. Exit" << endl;
	cout << ": ";
	cin >> ch;
	switch (ch)
	{
	case 1: Borrow();
		break;
	case 2: start();
		break;
	case 3: exit(0);
		break;
	default:
	{
		cout << endl << endl << "ERROR.......!" << endl;
		cout << endl << "wait........!" << endl;
		Sleep(2000);
		start();
	}
	}
}

void BooksRemove()
{
	int ch, id;
	bool flag = false;
	Books* tempBook;
	Books* reBook;
	Books* bCurrent;
	tempBook = bHead;
	reBook = NULL;
	system("cls");
	cout << "******************** REMOVE BOOKS ********************" << endl;
	cout << "Enter Book ID: ";
	cin >> id;
	if (tempBook->bookId == id)
	{
		reBook = bHead->tail;
		bHead = reBook;
		flag = true;
	}
	else
	{
		while (tempBook != NULL)
		{
			if (tempBook->bookId == id)
			{
				bCurrent = tempBook->tail;
				reBook->tail = bCurrent;
				flag = true;
			}
			reBook = tempBook;
			tempBook = tempBook->tail;
		}
	}
	if (flag)
	{
		cout << endl << endl << "searching..............!" << endl;
		Sleep(3000);
		cout << "deleted...........!" << endl;
		Sleep(1000);
	}
	else
	{
		cout << endl << endl << "searching..............!" << endl;
		Sleep(3000);
		cout << "NOT FOUND........!" << endl;
		Sleep(1000);
	}
	EndLines();
}

void BooksUpdate()
{
	string newName, newAuthor;
	int id, newCat, newGenr, ch;
	bool flag = false;
	system("cls");
	cout << "******************** UPDATE BOOKS INFO ********************" << endl;
	cout << "Enter book ID: ";
	cin >> id;
	Books* bCurrent = bHead;
	while (bCurrent != NULL)
	{
		if (bCurrent->bookId == id)
		{
			flag = true;
			break;
		}
		else
			bCurrent = bCurrent->tail;
	}
	if (flag)
	{
		cout << endl << endl << "verifying...........!" << endl;
		Sleep(3000);
		cout << "verified.......!" << endl;
		cout << endl;
		Sleep(1000);
		cout << "Enter new book name: ";
		cin.ignore();
		getline(cin, newName);
		cout << "Enter new author name: ";
		getline(cin, newAuthor);
		cout << "Choose a category 1. Fiction" << endl;
		cout << "                  2. Non-Fiction" << endl;
		cout << ": ";
		cin >> newCat;
		cout << "Choose a sub genre 1.  Fantasy" << endl;
		cout << "                   2.  Science" << endl;
		cout << "                   3.  Historical" << endl;
		cout << "                   4.  Realistic" << endl;
		cout << "                   5.  Fan" << endl;
		cout << "                   6.  Narrative" << endl;
		cout << "                   7.  Biography" << endl;
		cout << "                   8.  Periodicals" << endl;
		cout << "                   9.  Self-help" << endl;
		cout << "                   10. References" << endl;
		cout << ": ";
		cin >> newGenr;
		Books* tempBook;
		tempBook = bHead;
		while (tempBook != NULL)
		{
			if (tempBook->bookId == id)
			{
				tempBook->name = newName;
				tempBook->author = newAuthor;
				tempBook->mainCat = newCat;
				tempBook->subCat = newGenr;
				break;
			}
			else
				tempBook = tempBook->tail;
		}
		cout << endl << endl << "updating..........!" << endl;
		Sleep(3000);
		cout << "completed..........!" << endl;
		Sleep(1000);
	}
	else
	{
		cout << endl << endl << "searching.........!" << endl;
		Sleep(3000);
		cout << "NOT FOUND........!" << endl;
		Sleep(1000);
	}
	EndLines();
}

void Return()
{
	int ch, days;
	string name, email, bookName, author;
	Patrons* pCurrent = pHead;
	boolean flag = false;
	system("cls");
	cout << "******************** RETURN ********************" << endl;
	cout << "Enter Patron name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter Patron email: ";
	cin >> email;
	while (pCurrent != NULL)
	{
		if (pCurrent->name.compare(name) == 0)
		{
			if (pCurrent->email.compare(email) == 0)
			{
				cout << "Enter Book name: ";
				cin.ignore();
				getline(cin, bookName);
				cout << "Enter Book author: ";
				getline(cin, author);
				cout << "Enter number of days: ";
				cin >> days;
				cout << endl << endl << "verifying..........!" << endl << endl;;
				Sleep(3000);
				for (int i = 0; i < 3; i++)
				{
					if (pCurrent->booksBorrow[i].compare(bookName) == 0)
					{
						if (pCurrent->authors[i].compare(author) == 0)
						{
							flag = true;
							if (pCurrent->returndays[i] > days)
							{
								cout << "1. Return Book" << endl;
								cout << "2. Extend days" << endl;
								cout << ": ";
								cin >> ch;
								switch (ch)
								{
								case 1:
								{
									pCurrent->maxBookBorrow--;
									if (pCurrent->maxBookBorrow < 0)
										pCurrent->maxBookBorrow = 0;
									pCurrent->booksBorrow[i] = "N/A";
									pCurrent->authors[i] = "N/A";
									pCurrent->returndays[i] = 0;
									add(bookName, author, pCurrent->name, pCurrent->email);
								}
								break;
								case 2:
								{
									int oldDays;
									oldDays = pCurrent->returndays[i];
									pCurrent->returndays[i] = pCurrent->returndays[i] + 15;
									cout << endl << "processing.........!" << endl << endl;
									Sleep(3000);
									cout << "In hand " << oldDays << " days" << endl;
									cout << "Date extended for more " << pCurrent->returndays[i] - oldDays << " days" << endl;
									EndLines();
								}
								break;
								default:
								{
									cout << endl << endl << "ERROR.......!" << endl;
									cout << "wait..........!" << endl;
									Sleep(2000);
									start();
								}
								}
							}
							else
							{
								cout << endl;
								cout << "A fine of RM100 has been charged on Mr/Miss. " << pCurrent->name << "'s registered credit card for late return" << endl;
								cout << endl << endl << "proceeding for retrun process............!" << endl;
								Sleep(3000);
								pCurrent->maxBookBorrow--;
								if (pCurrent->maxBookBorrow < 0)
									pCurrent->maxBookBorrow = 0;
								pCurrent->booksBorrow[i] = "N/A";
								pCurrent->authors[i] = "N/A";
								pCurrent->returndays[i] = 0;
								add(bookName, author, pCurrent->name, pCurrent->email);
							}
						}
					}
				}
				if (flag == false)
				{
					cout << endl << "Invalid book credentials" << endl;
					cout << "wait........!";
					Sleep(2000);
					start();
				}
			}
			else
			{
				pCurrent = pCurrent->tail;
				if (pCurrent == NULL)
				{
					cout << endl << "Invalid email" << endl;
					cout << "wait.......!" << endl;
					Sleep(2000);
					start();
				}
			}
		}
		else
		{
			pCurrent = pCurrent->tail;
			if (pCurrent == NULL)
			{
				cout << endl << "Invalid name" << endl;
				cout << "wait.......!" << endl;
				Sleep(2000);
				start();
			}
		}
	}
}

void add(string bookName, string author, string name, string email)
{
	Books* book = new Books;
	Patrons* pCurrent = pHead;
	Books* bCurrent = bHead;
	int random, id, c = 0, ch;
	bool flag = true;
	book->name = bookName;
	book->author = author;
	cout << endl;
	cout << "Choose a category 1. Fiction" << endl;
	cout << "                  2. Non-Fiction" << endl;
	cout << ": ";
	cin >> book->mainCat;
	cout << "Choose a sub genre 1.  Fantasy" << endl;
	cout << "                   2.  Science" << endl;
	cout << "                   3.  Historical" << endl;
	cout << "                   4.  Realistic" << endl;
	cout << "                   5.  Fan" << endl;
	cout << "                   6.  Narrative" << endl;
	cout << "                   7.  Biography" << endl;
	cout << "                   8.  Periodicals" << endl;
	cout << "                   9.  Self-help" << endl;
	cout << "                   10. References" << endl;
	cout << ": ";
	cin >> book->subCat;
	book->tail = NULL;
	srand(time(0));
	while (flag)
	{
		c = 0;
		random = 1 + (rand() % 1000);
		while (bCurrent != NULL)
		{
			if (bCurrent->bookId == random)
				c++;
			bCurrent = bCurrent->tail;
		}
		if (c > 0)
			flag = true;
		else
			flag = false;
	}
	book->bookId = random;
	if (bHead == NULL)
		bHead = book;
	else
	{
		bCurrent = bHead;
		while (bCurrent->tail != NULL)
			bCurrent = bCurrent->tail;
		bCurrent->tail = book;
	}
	cout << endl << endl << "returning..........!" << endl;
	Sleep(3000);
	cout << "completed..........!" << endl;
	Sleep(1000);
	EndLines();
}

void Borrow()
{
	Books* bCurrent = bHead;
	Patrons* pCurrent = pHead;
	Books* tempBook = bHead;
	Books* reBook = NULL;
	string name, email;
	int id, ch;
	bool quCh = false, flag = false;;
	system("cls");
	cout << "******************** BORROW ********************" << endl;
	cout << "                              max limit: 3 books" << endl << endl;
	cout << "Enter Patron name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter Patron email: ";
	cin >> email;
	cout << "Enter Book ID: ";
	cin >> id;
	while (bCurrent != NULL)
	{
		if (bCurrent->bookId == id)
		{
			while (pCurrent != NULL)
			{
				if (pCurrent->name.compare(name) == 0)
				{
					if (pCurrent->email.compare(email) == 0)
					{
						cout << endl << endl << "processing.........!" << endl;
						Sleep(3000);
						if (pCurrent->maxBookBorrow < 3)
						{
							if (pCurrent->returndays[0] == 0)
							{
								pCurrent->booksBorrow[0] = bCurrent->name;
								pCurrent->returndays[0] = 15;
								pCurrent->authors[0] = bCurrent->author;
							}
							else if (pCurrent->returndays[1] == 0)
							{
								pCurrent->booksBorrow[1] = bCurrent->name;
								pCurrent->returndays[1] = 15;
								pCurrent->authors[1] = bCurrent->author;
							}
							else if (pCurrent->returndays[2] == 0)
							{
								pCurrent->booksBorrow[2] = bCurrent->name;
								pCurrent->returndays[2] = 15;
								pCurrent->authors[2] = bCurrent->author;
							}
							pCurrent->maxBookBorrow++;
							if (pCurrent->rear == 9)
							{
								if (pCurrent->front == pCurrent->rear)
								{
									pCurrent->front = pCurrent->rear = -1;
									quCh = true;
								}
								else
								{
									pCurrent->front++;
									quCh = true;
								}
								if (quCh)
								{
									if (pCurrent->front == -1)
										pCurrent->front = 0;
									pCurrent->rear++;
									pCurrent->last10Books[pCurrent->rear] = bCurrent->name;
									remove(id);
								}
							}
							else
							{
								if (pCurrent->front == -1)
								{
									pCurrent->front = 0;
								}
								pCurrent->rear++;
								pCurrent->last10Books[pCurrent->rear] = bCurrent->name;
								remove(id);
							}
						}
						else
						{
							cout << endl << "CAN'T  BORROW MORE BOOKS, LIMIT REACHED...........!" << endl;
							Sleep(1000);
							EndLines();
						}
					}
					else
					{
						bCurrent = bCurrent->tail;
						if (bCurrent == NULL)
						{
							cout << endl << endl << "Invalid email" << endl;
							cout << "wait........!" << endl;
							Sleep(2000);
							start();
						}
					}
				}
				else
				{
					bCurrent = bCurrent->tail;
					if (bCurrent == NULL)
					{
						cout << endl << endl << "Invalid name" << endl;
						cout << "wait........!" << endl;
						Sleep(2000);
						start();
					}
				}
			}
		}
		else
		{
			bCurrent = bCurrent->tail;
			if (bCurrent == NULL)
			{
				cout << endl << endl << "Invalid ID" << endl;
				cout << "wait........!"<<endl;
				Sleep(2000);
				start();
			}
		}
	}
	cout << endl << endl;
	cout << "1. Borrow" << endl;
	cout << "2. Main Menu" << endl;
	cout << "3. Exit" << endl;
	cout << ": ";
	cin >> ch;
	switch (ch)
	{
	case 1: Borrow();
		break;
	case 2: start();
		break;
	case 3: exit(0);
		break;
	default:
	{
		cout << endl << endl << "ERROR........!" << endl;
		cout << "wait.........!" << endl;
		Sleep(2000);
		start();
	}
	}
}

void remove(int id)
{
	int ch;
	bool flag = false;
	Books* tempBook;
	Books* reBook;
	Books* bCurrent;
	tempBook = bHead;
	reBook = NULL;
	if (tempBook->bookId == id)
	{
		reBook = bHead->tail;
		bHead = reBook;
		flag = true;
	}
	else
	{
		while (tempBook != NULL)
		{
			if (tempBook->bookId == id)
			{
				bCurrent = tempBook->tail;
				reBook->tail = bCurrent;
				flag = true;
			}
			reBook = tempBook;
			tempBook = tempBook->tail;
		}
	}
	if (flag)
	{
		cout << endl << "done.........!" << endl;
		Sleep(1000);
	}
	cout << endl << endl;
	cout << "1. Borrow" << endl;
	cout << "2. Main Menu" << endl;
	cout << "3. Exit" << endl;
	cout << ": ";
	cin >> ch;
	switch (ch)
	{
	case 1: Borrow();
		break;
	case 2: start();
		break;
	case 3: exit(0);
		break;
	default:
	{
		cout << endl << endl << "ERROR........!" << endl;
		cout << "wait.........!" << endl;
		Sleep(2000);
		start();
	}
	}
}

void EndLines()
{
	int ch;
	cout << endl << endl;
	cout << "1. Main Menu" << endl;
	cout << "2. Exit" << endl;
	cout << ": ";
	cin >> ch;
	switch (ch)
	{
	case 1: start();
		break;
	case 2: exit(0);
		break;
	default:
	{
		cout << endl << endl << "ERROR........!" << endl;
		cout << "wait.........!" << endl;
		Sleep(2000);
		start();
	}
	}
}

void Las10Books()
{
	int ch;
	string name, email;
	Patrons* pCurrent = pHead;
	system("cls");
	cout << "******************** HISTORY ********************" << endl;
	cout << "Enter Patron name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter Patron email: ";
	cin >> email;
	cout << endl << endl << "loading.........!" << endl;
	Sleep(2000);
	while (pCurrent != NULL)
	{
		if (pCurrent->name.compare(name) == 0)
		{
			if (pCurrent->email.compare(email) == 0)
			{
				for (int i = 0; i < 10; i++)
					cout << pCurrent->last10Books[i] << endl;
				pCurrent = pCurrent->tail;
			}
			else
				pCurrent = pCurrent->tail;
		}
		else
			pCurrent = pCurrent->tail;
	}
	EndLines();
}