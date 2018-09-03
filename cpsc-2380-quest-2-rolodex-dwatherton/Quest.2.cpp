#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Address
{
	int streetNumber;
	string street;
	string streetType;
	string city;
	string state;
	int zipcode;
};

struct Contact
{
	string firstName;
	string lastName;
	Address address;
	string phoneNumber;
	string emailAddress;
	string twitterHandle;
	Contact* next;
	Contact* prev;
};
enum sortBy{FIRST=1,LAST,STREET,CITY,STATE,PHONE,EMAIL,TWITTER};

Contact* loadList(string fileName);
Contact* remove_(Contact* contact);
Contact* insert_(Contact* contact);
void saveList(Contact* head, string fileName);
Contact* navigateRolodex(Contact* start, Contact* end);
void displayContact(Contact* contact);
Contact* search(Contact* head, bool deleteContact);
void addContact(Contact* & head);
void removeContact(Contact* & head);
void sort(Contact* & head);

int main()
{
	string fileName = "contacts.txt";
	Contact* rolodex = loadList(fileName);
	if (rolodex != nullptr)
	{
		int command = 0;
		while (command != 6)
		{
			cout << "Welcome to Mr. Orme's Rolodex!" << endl;
			cout << "What would you like to do? " << endl;
			cout << "\t1. Naviagate through Rolodex" << endl;
			cout << "\t2. Search for a Contact" << endl;
			cout << "\t3. Sort Contacts" << endl;
			cout << "\t4. Add a Contact" << endl;
			cout << "\t5. Remove a Contact" << endl;
			cout << "\t6. Quit" << endl;
			cin >> command;
			switch (command)
			{
			case 1:
				system("cls");
				navigateRolodex(rolodex, nullptr);
				break;
			case 2:
				search(rolodex, false);
				break;
			case 3:
				sort(rolodex);
				break;
			case 4:
				addContact(rolodex);
				break;
			case 5:
				removeContact(rolodex);
				break;
			case 6:
				break;
			default:
				cout << "Please enter a valid command!" << endl;
				break;
			}
			system("PAUSE");
			system("CLS");
		}
	}
	saveList(rolodex, fileName);
	return 0;
}

Contact * loadList(string fileName)
{
	ifstream fin;
	fin.open(fileName);
	if (!fin.is_open() && !fin.eof())
	{
		cout << "ERROR! No rolodex file! Exiting program" << endl;
		return nullptr;
	}

	// Create a head and tail pointer
	Contact* head;
	Contact* tail;
	// Create the very first contact (Unique case where head & tail pointers point to it and the next & prev pointers are both nullptr)
	Contact* contact = new Contact;
	// Read in all of the data for the first contact
	fin >> contact->firstName >> contact->lastName >> contact->address.streetNumber >> contact->address.street >> contact->address.streetType >> contact->address.city >> contact->address.state >> contact->address.zipcode >> contact->phoneNumber >> contact->emailAddress >> contact->twitterHandle;
	// Remove underscores from the contact street name and city name
	remove_(contact);
	// After reading all of the first contacts data, set the next and previous pointers to nullptr (It's the first and only contact)
	contact->prev = nullptr;
	contact->next = nullptr;
	// Set the head and tail pointers to the first contact (Gives us a starting point for the head and tail to be referenced later on)
	head = contact;
	tail = contact;

	// After taking care of the special case (First Linked List item), loop through the rest of contacts
	while (!fin.eof())
	{
		// Create a new contact
		contact = new Contact;
		// Read in all of the data for the next contact
		fin >> contact->firstName >> contact->lastName >> contact->address.streetNumber >> contact->address.street >> contact->address.streetType >> contact->address.city >> contact->address.state >> contact->address.zipcode >> contact->phoneNumber >> contact->emailAddress >> contact->twitterHandle;
		// Remove underscores from the contact street name and city name
		remove_(contact);
		// Set this contacts previous pointer to tail (aka the contact before this one was created)
		contact->prev = tail;
		// Set this contacts next pointer to nullptr (If there are more contacts in the file, this will be corrected)
		contact->next = nullptr;
		// Set the contact before this one was created's next pointer to this contact (1 -> 2)
		tail->next = contact;
		// Set the tail to this new contact (aka the 'last' contact in the list at the moment)
		tail = contact;
	}
	fin.close();
	return head;
}

//removes underscores from street name and city name
Contact * remove_(Contact * contact)
{
	for (int i = 0; i < contact->address.street.size(); i++)
	{
		if (contact->address.street[i] == '_') contact->address.street[i] = ' ';
	}
	for (int i = 0; i < contact->address.city.size(); i++)
	{
		if (contact->address.city[i] == '_') contact->address.city[i] = ' ';
	}
	return contact;
}

//replace spaces with underscores.
Contact * insert_(Contact * contact)
{
	for (int i = 0; i < contact->address.street.size(); i++)
	{
		if (contact->address.street[i] == ' ') contact->address.street[i] = '_';
	}
	for (int i = 0; i < contact->address.city.size(); i++)
	{
		if (contact->address.city[i] == ' ') contact->address.city[i] = '_';
	}
	return contact;
}

void saveList(Contact * head, string fileName)
{
	ofstream fout;
	fout.open(fileName);

	// If head is nullptr, list is empty. Just return semicolon, nothing to save/write to file. 
	if (head == nullptr)
	{
		return;
	}
	// Create a current contact pointer that is set to the head (beginning of the list)
	Contact* current = head;
	// Loop through each DLL item until current == nullptr, loop until we reach the end of the list
	while (current != nullptr)
	{
		// Insert underscores into the contact street name and city name
		insert_(current);
		// Don't save/write a blank line at the end of the file (exact format as starter document) No CrLf for the only/last contact
		if (current->next == nullptr)
		{
			// Write all of the contact information into the file for the only/last contact (No CrLf)
			fout << current->firstName << " " << current->lastName << endl;
			fout << current->address.streetNumber << " " << current->address.street << " " << current->address.streetType << " " << current->address.city << " " << current->address.state << " " << current->address.zipcode << endl;
			fout << current->phoneNumber << " " << current->emailAddress << " " << current->twitterHandle;
			// Quit, when current->next == nullptr, and current has been saved, there are no other contacts to save to file
			return;
		}
		// Write all of the contact information into the file in the same format as it was initially (from the starter doc) CrLf for all other contacts
		fout << current->firstName << " " << current->lastName << endl;
		fout << current->address.streetNumber << " " << current->address.street << " " << current->address.streetType << " " << current->address.city << " " << current->address.state << " " << current->address.zipcode << endl;
		fout << current->phoneNumber << " " << current->emailAddress << " " << current->twitterHandle << endl;
		// Set the current contact pointer to the next contact, after the current contact has been saved (keep looping)
		current = current->next;
	}
	fout.close();
	return;
}

Contact* navigateRolodex(Contact * start, Contact * end)
{
	// Local variable to hold the users input ((p)rev, (q)uit, or (n)ext)
	char answer;
	
	// Allow for looping through all contacts
	while (start != end)
	{
		// Clear the screen, display contact info, and prompt the user
		system("cls");
		displayContact(start);
		cout << "<<(p)revious, (q)uit, (n)ext>>" << endl;
		cin >> answer;

		switch (answer)
		{
			case 'p':
			case 'P':
			{
				// Verify there is a previous contact to go to
				if (start->prev != nullptr)
				{
					// Set the node to the previous node
					start = start->prev;
				}
				else
				{
					// Tell the user there are no previous contacts to show
					cout << "Cannot traverse to the previous contact, This is the first contact!" << endl;
					system("pause");
				}
				break;
			}
			case 'q':
			case 'Q':
			{
				// Hacky exit from the while loop when user chooses to quit
				start = end;
				break;
			}
			case 'n':
			case 'N':
			{
				// Verify there is a next contact to go to
				if (start->next != nullptr)
				{
					// Set the node to the next node
					start = start->next;
				}
				else
				{
					// Tell the user there are no further contacts to show
					cout << "Cannot traverse to the next contact, This is the last contact!" << endl;
					system("pause");
				}
				break;
			}
			default:
			{
				cout << "Error, please enter either p, q, or n..." << endl;
				system("pause");
				break;
			}
		}
	}
	// Return the contact the user chose to quit while viewing
	return start;
}
void displayContact(Contact * contact)
{
	cout << contact->firstName << " " << contact->lastName << endl
		<< contact->address.streetNumber << " " << contact->address.street << " " << contact->address.streetType << endl
		<< contact->address.city << ", " << contact->address.state << " " << contact->address.zipcode << endl
		<< "Phone: " << contact->phoneNumber << " Email: " << contact->emailAddress << " Twitter: " << contact->twitterHandle << endl;
	return;
}
void displayMenu()
{
	cout << "\t1. First Name" << endl
		<< "\t2. Last Name" << endl
		<< "\t3. Street" << endl
		<< "\t4. City" << endl
		<< "\t5. State" << endl
		<< "\t6. Phone Number" << endl
		<< "\t7. Email" << endl
		<< "\t8. Twitter Handle" << endl
		<< "\t9. CANCEL" << endl;
	return;
}


void addContact(Contact *& head)
{
	// Create a new contact
	Contact* contact = new Contact;
 
	cout << "Please enter the contact's information: "	<< endl;

	// Add all of the new contacts data based on user prompts and inputs
	cout << "First and Last name: ";
	cin >> contact->firstName >> contact->lastName;

	cout << "Street (i.e. 123 W_Main St): ";
	cin >> contact->address.streetNumber >> contact->address.street >> contact->address.streetType;

	cout << "City (put an underscore _ between words): ";
	cin >> contact->address.city;

	cout << "State (2 letter abbreviation): ";
	cin >> contact->address.state;

	cout << "Zipcode: ";
	cin >> contact->address.zipcode;

	cout << "Phone (xxx-xxx-xxxx): ";
	cin >> contact->phoneNumber;

	cout << "Email Address: ";
	cin >> contact->emailAddress;

	cout << "Twitter Handle: ";
	cin >> contact->twitterHandle;

	// Remove underscores for pretty printing (when navigating the rolodex)
	remove_(head);

	// Finally, link the new contact into the list (update contacts next and prev pointers, the first contacts prev pointer, and the head pointer)
	// Set contact->next to the node head currently points to (add new contact to front of list!!)
	contact->next = head;
	// Set contact->prev to nullptr (now the first item in list)
	contact->prev = nullptr;
	// Set the old first contacts previous pointer to the new contact (head->prev = contact)
	head->prev = contact;
	// Update head to point to the new contact
	head = contact;

	cout << "Contact Added!!!" << endl;
	return;
}

void removeContact(Contact *& head)
{
	Contact* toDelete = search(head, true);
	if (toDelete != nullptr)
	{
		system("CLS");
		displayContact(toDelete);
		cout << "Are you sure you want to delete this contact (y/n):" << endl;
		char command = ' ';
		cin >> command;
		if (command == 'y' || command == 'Y')
		{
			// Create a next and previous contact for referencing whilst deleting
			Contact* previousContact = toDelete->prev;
			Contact* nextContact = toDelete->next;

			// Check that the contact after the one toDelete exists
			if (nextContact != nullptr)
			{
				// Set the nextContacts previous pointer to toDeletes previous contact
				nextContact->prev = previousContact;
			}

			// Check that the contact before the one toDelete exists
			if (previousContact != nullptr)
			{
				// Set the previousContacts next pointer to toDeletes next contact
				previousContact->next = nextContact;
			}

			// Check if toDelete is the head case
			if (toDelete == head)
			{
				// Update the head to the new first contact in the DLL
				head = nextContact;
			}

			cout << "Contacted Deleted!!!" << endl;
		}
		else
		{
			cout << "Nothing deleted. Returning to main menu" << endl;
		}
	}
	return;
}

void swap(Contact* & head, Contact* & contact1, Contact* contact2)
{
	Contact* temp = new Contact;
	
	// Swap the contacts data from contact1 to contact2 via a temp Contact*
	temp->firstName = contact1->firstName;
	temp->lastName = contact1->lastName;
	temp->address.streetNumber = contact1->address.streetNumber;
	temp->address.street = contact1->address.street;
	temp->address.streetType = contact1->address.streetType;
	temp->address.city = contact1->address.city;
	temp->address.state = contact1->address.state;
	temp->address.zipcode = contact1->address.zipcode;
	temp->phoneNumber = contact1->phoneNumber;
	temp->emailAddress = contact1->emailAddress;
	temp->twitterHandle = contact1->twitterHandle;

	contact1->firstName = contact2->firstName;
	contact1->lastName = contact2->lastName;
	contact1->address.streetNumber = contact2->address.streetNumber;
	contact1->address.street = contact2->address.street;
	contact1->address.streetType = contact2->address.streetType;
	contact1->address.city = contact2->address.city;
	contact1->address.state = contact2->address.state;
	contact1->address.zipcode = contact2->address.zipcode;
	contact1->phoneNumber = contact2->phoneNumber;
	contact1->emailAddress = contact2->emailAddress;
	contact1->twitterHandle = contact2->twitterHandle;

	contact2->firstName = temp->firstName;
	contact2->lastName = temp->lastName;
	contact2->address.streetNumber = temp->address.streetNumber;
	contact2->address.street = temp->address.street;
	contact2->address.streetType = temp->address.streetType;
	contact2->address.city = temp->address.city;
	contact2->address.state = temp->address.state;
	contact2->address.zipcode = temp->address.zipcode;
	contact2->phoneNumber = temp->phoneNumber;
	contact2->emailAddress = temp->emailAddress;
	contact2->twitterHandle = temp->twitterHandle;

	return;
}

void sort(Contact *& head, sortBy sortKey)
{
	// Make sure sortKey is is 1 - 8
	if ((int)sortKey > 8 || (int)sortKey < 0)
	{
		cout << "Invalid sort key!" << endl;
		return;
	}
	for (Contact* contact1 = head; contact1 != nullptr; contact1 = contact1->next)
	{
		for (Contact* contact2 = contact1->next; contact2 != nullptr; contact2 = contact2->next)
		{
			switch (sortKey)
			{
				case FIRST:
				{
					if (contact1->firstName > contact2->firstName)
					{
						swap(head, contact1, contact2);
					}		
					break;
				}
				case LAST:
				{
					if (contact1->lastName > contact2->lastName)
					{
						swap(head, contact1, contact2);
					}
					break;
				}
				case STREET:
				{
					if (contact1->address.street > contact2->address.street)
					{
						swap(head, contact1, contact2);
					}
					break;
				}
				case CITY:
				{
					if (contact1->address.city > contact2->address.city)
					{
						swap(head, contact1, contact2);
					}
					break;
				}
				case STATE:
				{
					if (contact1->address.state > contact2->address.state)
					{
						swap(head, contact1, contact2);
					}
					break;
				}
				case PHONE:
				{
					if (contact1->phoneNumber > contact2->phoneNumber)
					{
						swap(head, contact1, contact2);
					}
					break;
				}
				case EMAIL:
				{
					if (contact1->emailAddress > contact2->emailAddress)
					{
						swap(head, contact1, contact2);
					}
					break;
				}
				case TWITTER:
				{
					if (contact1->twitterHandle > contact2->twitterHandle)
					{
						swap(head, contact1, contact2);
					}
					break;
				}
			}
		}
	}
	return;
}
void sort(Contact* & head)
{
	//this is called by the main program. Doesn't do the sorting!
	system("CLS");
	cout << "Sort by: " << endl;
	displayMenu();
	int command;
	cin >> command;
	if (command != 9) sort(head, (sortBy)command);
	return;
}
Contact* search(Contact * head, bool deleteContact)
{
	int searchBy;
	string searchText;
	char answer;
	bool found = false;

	system("CLS");
	//options are same as sortBy enum!!!
	cout << "Search by: " << endl;
	displayMenu();

	// Get the type of search
	cout << "Please enter a 'search by' type: ";
	cin >> searchBy;

	// If 1-8, get the search text
	if (searchBy > 0 && searchBy < 9)
	{
		cout << "Search text: ";
		cin >> searchText;
	} // If == 9, CANCEL
	else if (searchBy == 9)
	{
		return nullptr;
	} // Else, Invalid search key!
	else
	{
		cout << "Invalid search key!" << endl;
		return nullptr;
	}

	// Sort based on the type of search to be preformed (allows for navigating next and previous if there are multiple matching results to the query, cannot do if unsorted!)
	sort(head, (sortBy)searchBy);

	// Switch for the searchBy type
	switch ((sortBy)searchBy)
	{
		case FIRST:
		{
			// Loop through the list
			while (head != nullptr)
			{
				// Check if the searchText matches any contact->firstName
				if (head->firstName == searchText)
				{
					found = true;
					// Clear the screen, display contact info, and prompt the user
					system("cls");
					displayContact(head);
					// Allow the user to find the right contact to delete (granted more than one exists!)
					if (deleteContact)
					{
						cout << endl << "Hint: press (q)uit when you've found the contact you'd like to delete!" << endl << endl;
					}
					cout << "<<(p)revious, (q)uit, (n)ext>>" << endl;
					cin >> answer;

					// Switch for the previous, quit, or next prompt
					switch (answer)
					{
						case 'p':
						case 'P':
						{
							// Verify there is a previous contact to go to and the previous contact has the search keys first name
							if (head->prev != nullptr && head->prev->firstName == searchText)
							{
								// Set the node to the previous node
								head = head->prev;
							}
							break;
						}
						case 'q':
						case 'Q':
						{
							// Return the contact the user quit searching at (asks if they want to delete in removeContact())
							return head;
							break;
						}
						case 'n':
						case 'N':
						{
							// Verify there is a next contact to go to and the next contact has the search keys first name
							if (head->next != nullptr && head->next->firstName == searchText)
							{
								// Set the node to the next node
								head = head->next;
							}
							break;
						}
						default:
						{
							// Invalid input, remind the user of his options
							cout << "Error, please enter either p, q, or n..." << endl;
							system("pause");
							break;
						}
					}
				}
				else
				{
					// If not this contact, set head to the next contact to check it's first name
					head = head->next;
				}
			}
			if (!found)
			{
				// Not found at all, tell the user it could not be found
				cout << "Sorry, unable to find a contact with the first name " << searchText << "!" << endl;
			}
			break;
		}
		case LAST:
		{
			// Loop through the list
			while (head != nullptr)
			{
				// Check if the searchText matches any contact->lastName
				if (head->lastName == searchText)
				{
					found = true;
					// Clear the screen, display contact info, and prompt the user
					system("cls");
					displayContact(head);
					// Allow the user to find the right contact to delete (granted more than one exists!)
					if (deleteContact)
					{
						cout << endl << "Hint: press (q)uit when you've found the contact you'd like to delete!" << endl << endl;
					}
					cout << "<<(p)revious, (q)uit, (n)ext>>" << endl;
					cin >> answer;

					// Switch for the previous, quit, or next prompt
					switch (answer)
					{
						case 'p':
						case 'P':
						{
							// Verify there is a previous contact to go to and the previous contact has the search keys last name
							if (head->prev != nullptr && head->prev->lastName == searchText)
							{
								// Set the node to the previous node
								head = head->prev;
							}
							break;
						}
						case 'q':
						case 'Q':
						{
							// Return the contact the user quit searching at (asks if they want to delete in removeContact())
							return head;
							break;
						}
						case 'n':
						case 'N':
						{
							// Verify there is a next contact to go to and the next contact has the search keys last name
							if (head->next != nullptr && head->next->lastName == searchText)
							{
								// Set the node to the next node
								head = head->next;
							}
							break;
						}
						default:
						{
							// Invalid input, remind the user of his options
							cout << "Error, please enter either p, q, or n..." << endl;
							system("pause");
							break;
						}
					}
				}
				else
				{
					// If not this contact, set head to the next contact to check it's last name
					head = head->next;
				}
			}
			if (!found)
			{
				// Not found at all, tell the user it could not be found
				cout << "Sorry, unable to find a contact with the last name " << searchText << "!" << endl;
			}
			break;
		}
		case STREET:
		{
			// Loop through the list
			while (head != nullptr)
			{
				// Put the underscore back into the city and/or street name for the searching (Make things simple)
				insert_(head);
				// Check if the searchText matches any contact->address.street
				if (head->address.street == searchText)
				{
					// Remove the underscore to print the city and/or street name (Pretty printing)
					remove_(head);
					found = true;
					// Clear the screen, display contact info, and prompt the user
					system("cls");
					displayContact(head);
					// Allow the user to find the right contact to delete (granted more than one exists!)
					if (deleteContact)
					{
						cout << endl << "Hint: press (q)uit when you've found the contact you'd like to delete!" << endl << endl;
					}
					cout << "<<(p)revious, (q)uit, (n)ext>>" << endl;
					cin >> answer;

					// Switch for the previous, quit, or next prompt
					switch (answer)
					{
						case 'p':
						case 'P':
						{
							// Verify there is a previous contact to go to and the previous contact has the search keys street name
							if (head->prev != nullptr && head->prev->address.street == searchText)
							{
								// Set the node to the previous node
								head = head->prev;
							}
							break;
						}
						case 'q':
						case 'Q':
						{
							// Return the contact the user quit searching at (asks if they want to delete in removeContact())
							return head;
							break;
						}
						case 'n':
						case 'N':
						{
							// Verify there is a next contact to go to and the next contact has the search keys street name
							if (head->next != nullptr && head->next->address.street == searchText)
							{
								// Set the node to the next node
								head = head->next;
							}
							break;
						}
						default:
						{
							// Invalid input, remind the user of his options
							cout << "Error, please enter either p, q, or n..." << endl;
							system("pause");
							break;
						}
					}
				}
				else
				{
					// Remove the underscore to print the city and/or street name (Pretty printing)
					remove_(head);
					// If not this contact, set head to the next contact to check it's street name
					head = head->next;
				}
			}
			if (!found)
			{
				// Not found at all, tell the user it could not be found
				cout << "Sorry, unable to find a contact with the street name " << searchText << "!" << endl;
			}
			break;
		}
		case CITY:
		{
			// Loop through the list
			while (head != nullptr)
			{
				// Put the underscore back into the city and/or street name for the searching (Make things simple)
				insert_(head);
				// Check if the searchText matches any contact->address.city
				if (head->address.city == searchText)
				{
					// Remove the underscore to print the city and/or street name (Pretty printing)
					remove_(head);
					found = true;
					// Clear the screen, display contact info, and prompt the user
					system("cls");
					displayContact(head);
					// Allow the user to find the right contact to delete (granted more than one exists!)
					if (deleteContact)
					{
						cout << endl << "Hint: press (q)uit when you've found the contact you'd like to delete!" << endl << endl;
					}
					cout << "<<(p)revious, (q)uit, (n)ext>>" << endl;
					cin >> answer;

					// Switch for the previous, quit, or next prompt
					switch (answer)
					{
						case 'p':
						case 'P':
						{
							// Verify there is a previous contact to go to and the previous contact has the search keys city name
							if (head->prev != nullptr && head->prev->address.city == searchText)
							{
								// Set the node to the previous node
								head = head->prev;
							}
							break;
						}
						case 'q':
						case 'Q':
						{
							// Return the contact the user quit searching at (asks if they want to delete in removeContact())
							return head;
							break;
						}
						case 'n':
						case 'N':
						{
							// Verify there is a next contact to go to and the next contact has the search keys city name
							if (head->next != nullptr && head->next->address.city == searchText)
							{
								// Set the node to the next node
								head = head->next;
							}
							break;
						}
						default:
						{
							// Invalid input, remind the user of his options
							cout << "Error, please enter either p, q, or n..." << endl;
							system("pause");
							break;
						}
					}
				}
				else
				{
					// Remove the underscore to print the city and/or street name (Pretty printing)
					remove_(head);
					// If not this contact, set head to the next contact to check it's city name
					head = head->next;
				}
			}
			if (!found)
			{
				// Not found at all, tell the user it could not be found
				cout << "Sorry, unable to find a contact with the city name " << searchText << "!" << endl;
			}
			break;
		}
		case STATE:
		{
			// Loop through the list
			while (head != nullptr)
			{
				// Check if the searchText matches any contact->address.state
				if (head->address.state == searchText)
				{
					found = true;
					// Clear the screen, display contact info, and prompt the user
					system("cls");
					displayContact(head);
					// Allow the user to find the right contact to delete (granted more than one exists!)
					if (deleteContact)
					{
						cout << endl << "Hint: press (q)uit when you've found the contact you'd like to delete!" << endl << endl;
					}
					cout << "<<(p)revious, (q)uit, (n)ext>>" << endl;
					cin >> answer;

					// Switch for the previous, quit, or next prompt
					switch (answer)
					{
						case 'p':
						case 'P':
						{
							// Verify there is a previous contact to go to and the previous contact has the search keys state name
							if (head->prev != nullptr && head->prev->address.state == searchText)
							{
								// Set the node to the previous node
								head = head->prev;
							}
							break;
						}
						case 'q':
						case 'Q':
						{
							// Return the contact the user quit searching at (asks if they want to delete in removeContact())
							return head;
							break;
						}
						case 'n':
						case 'N':
						{
							// Verify there is a next contact to go to and the next contact has the search keys state name
							if (head->next != nullptr && head->next->address.state == searchText)
							{
								// Set the node to the next node
								head = head->next;
							}
							break;
						}
						default:
						{
							// Invalid input, remind the user of his options
							cout << "Error, please enter either p, q, or n..." << endl;
							system("pause");
							break;
						}
					}
				}
				else
				{
					// If not this contact, set head to the next contact to check it's state name
					head = head->next;
				}
			}
			if (!found)
			{
				// Not found at all, tell the user it could not be found
				cout << "Sorry, unable to find a contact with the state name " << searchText << "!" << endl;
			}
			break;
		}
		case PHONE:
		{
			// Loop through the list
			while (head != nullptr)
			{
				// Check if the searchText matches any contact->phoneNumber
				if (head->phoneNumber == searchText)
				{
					found = true;
					// Clear the screen, display contact info, and prompt the user
					system("cls");
					displayContact(head);
					// Allow the user to find the right contact to delete (granted more than one exists!)
					if (deleteContact)
					{
						cout << endl << "Hint: press (q)uit when you've found the contact you'd like to delete!" << endl << endl;
					}
					cout << "<<(p)revious, (q)uit, (n)ext>>" << endl;
					cin >> answer;

					// Switch for the previous, quit, or next prompt
					switch (answer)
					{
						case 'p':
						case 'P':
						{
							// Verify there is a previous contact to go to and the previous contact has the search keys phone number
							if (head->prev != nullptr && head->prev->phoneNumber == searchText)
							{
								// Set the node to the previous node
								head = head->prev;
							}
							break;
						}
						case 'q':
						case 'Q':
						{
							// Return the contact the user quit searching at (asks if they want to delete in removeContact())
							return head;
							break;
						}
						case 'n':
						case 'N':
						{
							// Verify there is a next contact to go to and the next contact has the search keys phone number
							if (head->next != nullptr && head->next->phoneNumber == searchText)
							{
								// Set the node to the next node
								head = head->next;
							}
							break;
						}
						default:
						{
							// Invalid input, remind the user of his options
							cout << "Error, please enter either p, q, or n..." << endl;
							system("pause");
							break;
						}
					}
				}
				else
				{
					// If not this contact, set head to the next contact to check it's phone number
					head = head->next;
				}
			}
			if (!found)
			{
				// Not found at all, tell the user it could not be found
				cout << "Sorry, unable to find a contact with the phone number " << searchText << "!" << endl;
			}
			break;
		}
		case EMAIL:
		{
			// Loop through the list
			while (head != nullptr)
			{
				// Check if the searchText matches any contact->emailAddress
				if (head->emailAddress == searchText)
				{
					found = true;
					// Clear the screen, display contact info, and prompt the user
					system("cls");
					displayContact(head);
					// Allow the user to find the right contact to delete (granted more than one exists!)
					if (deleteContact)
					{
						cout << endl << "Hint: press (q)uit when you've found the contact you'd like to delete!" << endl << endl;
					}
					cout << "<<(p)revious, (q)uit, (n)ext>>" << endl;
					cin >> answer;

					// Switch for the previous, quit, or next prompt
					switch (answer)
					{
						case 'p':
						case 'P':
						{
							// Verify there is a previous contact to go to and the previous contact has the search keys email address
							if (head->prev != nullptr && head->prev->emailAddress == searchText)
							{
								// Set the node to the previous node
								head = head->prev;
							}
							break;
						}
						case 'q':
						case 'Q':
						{
							// Return the contact the user quit searching at (asks if they want to delete in removeContact())
							return head;
							break;
						}
						case 'n':
						case 'N':
						{
							// Verify there is a next contact to go to and the next contact has the search keys email address
							if (head->next != nullptr && head->next->emailAddress == searchText)
							{
								// Set the node to the next node
								head = head->next;
							}
							break;
						}
						default:
						{
							// Invalid input, remind the user of his options
							cout << "Error, please enter either p, q, or n..." << endl;
							system("pause");
							break;
						}
					}
				}
				else
				{
					// If not this contact, set head to the next contact to check it's email address
					head = head->next;
				}
			}
			if (!found)
			{
				// Not found at all, tell the user it could not be found
				cout << "Sorry, unable to find a contact with the email address " << searchText << "!" << endl;
			}
			break;
		}
		case TWITTER:
		{
			// Loop through the list
			while (head != nullptr)
			{
				// Check if the searchText matches any contact->twitterHandle
				if (head->twitterHandle == searchText)
				{
					found = true;
					// Clear the screen, display contact info, and prompt the user
					system("cls");
					displayContact(head);
					// Allow the user to find the right contact to delete (granted more than one exists!)
					if (deleteContact)
					{
						cout << endl << "Hint: press (q)uit when you've found the contact you'd like to delete!" << endl << endl;
					}
					cout << "<<(p)revious, (q)uit, (n)ext>>" << endl;
					cin >> answer;

					// Switch for the previous, quit, or next prompt
					switch (answer)
					{
						case 'p':
						case 'P':
						{
							// Verify there is a previous contact to go to and the previous contact has the search keys twitter handle
							if (head->prev != nullptr && head->prev->twitterHandle == searchText)
							{
								// Set the node to the previous node
								head = head->prev;
							}
							break;
						}
						case 'q':
						case 'Q':
						{
							// Return the contact the user quit searching at (asks if they want to delete in removeContact())
							return head;
							break;
						}
						case 'n':
						case 'N':
						{
							// Verify there is a next contact to go to and the next contact has the search keys twitter handle
							if (head->next != nullptr && head->next->twitterHandle == searchText)
							{
								// Set the node to the next node
								head = head->next;
							}
							break;
						}
						default:
						{
							// Invalid input, remind the user of his options
							cout << "Error, please enter either p, q, or n..." << endl;
							system("pause");
							break;
						}
					}
				}
				else
				{
					// If not this contact, set head to the next contact to check it's twitter handle
					head = head->next;
				}
			}
			if (!found)
			{
				// Not found at all, tell the user it could not be found
				cout << "Sorry, unable to find a contact with the twitter handle " << searchText << "!" << endl;
			}
			break;
		}
	}
	// Otherwise return head (nullptr)
	return head;
}
