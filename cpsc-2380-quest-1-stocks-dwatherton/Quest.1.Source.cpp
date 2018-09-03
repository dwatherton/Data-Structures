#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Stock.h"
#include <string>
using namespace std;
// I set SYMBOL to be 1 to simplify my menu's (instead of 0)
enum FIELD { SYMBOL = 1, COMPANY_NAME, LAST_PRICE, CHANGE, VOLUME, QUIT };
std::vector<Stock*> loadStocks(std::string fileName);
void displayStocks(std::vector<Stock*> & stocks); //passed by reference to speed up program!
FIELD displayChoices();
void changePrice(FIELD field, int pos, std::vector<Stock*> & stocks);

void insertionSort(std::vector<Stock*> & stocks);
void selectionSort(std::vector<Stock*> & stocks);
void mergeSort(std::vector<Stock*> & stocks, int first, int last);
void merge(std::vector<Stock*>& stocks, int first, int mid, int last);
void quickSort(std::vector<Stock*> & stocks, int left, int right);
int partition(vector<Stock*> & stocks, int left, int right);
void bubbleSort(std::vector<Stock*> & stocks);

// I added a char parameter to binarySearch to allow for price updating when the user chooses update
void binarySearch(FIELD field, std::string key, std::vector<Stock*> & stocks, char answer);

void saveStocks(std::string fileName, std::vector<Stock*> & stocks);

Stock * remove_(Stock * stock);
Stock * insert_(Stock * stock);

int main()
{
	// Local variables
	char answer;
	vector<Stock*> stocks;
	int choice, searchChoice;
	string key;

	// Load stocks from file into a vector
	stocks = loadStocks("stocks.txt");

	do {
		// Clear the console
		system("cls");

		// Print out the stock data with column headers
		displayStocks(stocks);

		// Ask what the user wants to do
		cout << endl << "Would you like to (s)ort, s(e)arch, (u)pdate a stock price, or (q)uit?: ";
		// Get the users answer
		cin >> answer;

		// SWITCH FOR SORT, SEARCH, UPDATE, OR QUIT
		switch (answer)
		{
			// SORT
			case 's':
			case 'S':
			{
				// Get the users choice returned from displayChoices
				choice = displayChoices();

				// SWITCH FOR DIFFERENT SORTS
				switch (choice)
				{
					case 1:
					{
						// Clear the screen
						system("cls");
						// Tell the user which sorting algorithm was used
						cout << "Sorted by symbol using Insertion Sort, Here are the results!" << endl;
						// Sort with Insertion Sort 
						insertionSort(stocks);
						// Print the stocks
						cout << endl;
						displayStocks(stocks);
						cout << endl;
						// Pause to view the results
						system("pause");
						break;
					}
					case 2:
					{
						// Clear the screen
						system("cls");
						// Tell the user which sorting algorithm was used
						cout << "Sorted by company name using Selection Sort, Here are the results!" << endl;
						// Sort with Selection Sort
						selectionSort(stocks);
						// Print the stocks
						cout << endl;
						displayStocks(stocks);
						cout << endl;
						// Pause to view the results
						system("pause");
						break;
					}
					case 3:
					{
						// Clear the screen
						system("cls");
						// Tell the user which sorting algorithm was used
						cout << "Sorted by last price using Merge Sort, Here are the results!" << endl;
						// Sort with Merge Sort
						mergeSort(stocks, 0, stocks.size() - 1);
						// Print the stocks
						cout << endl;
						displayStocks(stocks);
						cout << endl;
						// Pause to view the results
						system("pause");
						break;
					}
					case 4:
					{
						// Clear the screen
						system("cls");
						// Tell the user which sorting algorithm was used
						cout << "Sorted by change using Quick Sort, Here are the results!" << endl;
						// Sort with Quick Sort
						quickSort(stocks, 0, stocks.size() - 1);
						// Print the stocks
						cout << endl;
						displayStocks(stocks);
						cout << endl;
						// Pause to view the results
						system("pause");
						break;
					}
					case 5:
					{
						// Clear the screen
						system("cls");
						// Tell the user which sorting algorith was used
						cout << "Sorted by volume using Bubble Sort, Here are the results!" << endl;
						// Sort with Bubble Sort
						bubbleSort(stocks);
						// Print the stocks
						cout << endl;
						displayStocks(stocks);
						cout << endl;
						// Pause to view the results
						system("pause");
						break;
					}
					case 6:
					{
						// Return to the main menu, the user chose quit
						system("exit");
						break;
					}
					default:
					{
						// Remind the user to enter a valid option of 1 - 6
						cout << endl << "Please enter a number 1 - 6..." << endl << endl;
						// Pause to view the results
						system("pause");
						break;
					}
				}
			// Break from sorting options
			break;
			}
			// SEARCH
			case 'e':
			case 'E':
			{
				// Get the users search choice returned from displayChoices
				searchChoice = displayChoices();
	
				// SWITCH FOR DIFFERENT SEARCHES
				switch (searchChoice)
				{
					case 1:
					{
						// Clear the screen to show the stocks and search results
						system("cls");
						// Let the user know the stocks are sorted and ready to search
						cout << "Sorted by symbol using Insertion Sort, Here are the results! You may now search for a stock." << endl;
						// User wants to binary search by symbol, sort by symbol (Insertion Sort for me)
						insertionSort(stocks);
						// Print the stocks
						cout << endl;
						displayStocks(stocks);
						cout << endl;
						// With data sorted by the users desired search method, get the search key
						cout << "Please enter a symbol to search by: ";
						getline(cin, key);
						// With data sorted and a key, call binary search
						binarySearch(SYMBOL, key, stocks, answer);
						// Pause to view the results
						system("pause");
						break;
					}
					case 2:
					{
						// Clear the screen to show the stocks and search results
						system("cls");
						// Let the user know the stocks are sorted and ready to search
						cout << "Sorted by company name using Selection Sort, Here are the results! You may now search for a stock." << endl;
						// User wants to binary search by company name, sort by company name (Selection Sort for me)
						selectionSort(stocks);
						// Print the stocks
						cout << endl;
						displayStocks(stocks);
						cout << endl;
						// With data sorted by the users desired search method, get the search key
						cout << "Please enter a company name to search by: ";
						getline(cin, key);
						// With data sorted and a key, call binary search
						binarySearch(COMPANY_NAME, key, stocks, answer);
						// Pause to view the results
						system("pause");
						break;
					}
					case 3:
					{
						// Clear the screen to show the stocks and search results
						system("cls");
						// Let the user know the stocks are sorted and ready to search
						cout << "Sorted by last price using Merge Sort, Here are the results! You may now search for a stock." << endl;
						// User wants to binary search by last price, sort by last price (Merge Sort for me)
						mergeSort(stocks, 0, stocks.size() - 1);
						// Print the stocks
						cout << endl;
						displayStocks(stocks);
						cout << endl;
						// With data sorted call binary search (get the float to search by in the function, it started with a string parameter so I left it like that)
						binarySearch(LAST_PRICE, key, stocks, answer);
						// Pause to view the results
						system("pause");
						break;
					}
					case 4:
					{
						// Clear the screen to show the stocks and search results
						system("cls");
						// Let the user know the stocks are sorted and ready to search
						cout << "Sorted by change using Quick Sort, Here are the results! You may now search for a stock." << endl;
						// User wants to binary search by change, sort by change (Quick Sort for me)
						quickSort(stocks, 0, stocks.size() - 1);
						// Print the stocks
						cout << endl;
						displayStocks(stocks);
						cout << endl;
						// With data sorted call binary search (get the float to search by in the function, it started with a string parameter so I left it like that)
						binarySearch(CHANGE, key, stocks, answer);
						// Pause to view the results
						system("pause");
						break;
					}
					case 5:
					{
						// Clear the screen to show the stocks and search results
						system("cls");
						// Let the user know the stocks are sorted and ready to search
						cout << "Sorted by volume using Bubble Sort, Here are the results! You may now search for a stock." << endl;
						// User wants to binary search by volume, sort by volume (Bubble Sort for me)
						bubbleSort(stocks);
						// Print the stocks
						cout << endl;
						displayStocks(stocks);
						cout << endl;
						// With data sorted call binary search (get the float to search by in the function, it started with a string parameter so I left it like that)
						binarySearch(VOLUME, key, stocks, answer);
						// Pause to view the results
						system("pause");
						break;
					}
					case 6:
					{
						// Return to the main menu, the user chose quit
						system("exit");
						break;
					}
					default:
					{
						// Remind the user to enter a valid option of 1 - 6
						cout << endl << "Please enter a number 1 - 6..." << endl << endl;
						// Pause to view the results
						system("pause");
						break;
					}
				}
			break;
			}
			// UPDATE
			case 'u':
			case 'U':
			{
				// Clear the screen to show the new data
				system("cls");
				// Sort the stocks by symbol (Insertion Sort for me) to Binary Search
				insertionSort(stocks);
				// Print the stocks
				cout << endl;
				displayStocks(stocks);
				cout << endl;
				// Ask the user for a symbol to search for and update
				cout << "Please enter a symbol to search for and update the price: ";
				// Get the key
				cin >> key;
				// Search the array with a binary search
				binarySearch(SYMBOL, key, stocks, answer);
				// CALL CHANGE PRICE INSIDE BINARY SEARCH
				system("pause");
				break;
			}
			// QUIT
			case 'q':
			case 'Q':
			{
				// Save the stocks back into stocks.txt to be loaded next time the program launches
				saveStocks("stocks.txt", stocks);
				// Thank the user for using the program!
				cout << endl << "Thank you for using the stocks program!" << endl << endl;
				// Pause to view the thank you message
				system("pause");
				// Exit
				system("exit");
				break;
			}
			default:
			{
				// Remind the user to enter a valid search option
				cout << endl << "Error: Please select either 's', 'e', 'u', or 'q' to proceed!" << endl << endl;
				// Pause to view the results
				system("pause");
				break;
			}
		}

		// I was having a very small bug with allowing a capitol Q to quit, so this was a quick fix
		if (answer == 'Q')
		{
			// Convert the capitol Q for quit to lowercase to end the do-while loop
			answer = 'q';
		}

	} while (answer != 'q');
	// Return 0 (Successfully executed)
	return 0;
}

//removes underscores from street name and city name
Stock * remove_(Stock * stock)
{
	for (unsigned int i = 0; i < stock->companyName.size(); i++)
	{
		if (stock->companyName[i] == '_') stock->companyName[i] = ' ';
	}
	return stock;
}

//replace spaces with underscores.
Stock * insert_(Stock * stock)
{
	for (unsigned int i = 0; i < stock->companyName.size(); i++)
	{
		if (stock->companyName[i] == ' ') stock->companyName[i] = '_';
	}

	return stock;
}

std::vector<Stock*> loadStocks(std::string fileName)
{
	// Local variables to store file input data
	string symbol, companyName;
	float lastPrice, change, volume;

	// Vector of Stock object pointers to store the stocks.txt data
	vector<Stock*> stocks;

	// Instantiate a file input stream to read from file
	fstream fin;
	// Open stocks.txt to read from
	fin.open("stocks.txt");

	// Verify that the filestream was able to open the file
	if (!fin.is_open())
	{
		// Tell user unable to open file
		cerr << "Error opening " << fileName << "." << endl;
		// Pause to view results
		system("pause");
		// Return an empty vector after warning unable to open
		return stocks;
	}

	// Loop until the end of file
	while (!fin.eof())
	{
		// Read the stock data with the filestream fin
		fin >> symbol >> companyName >> lastPrice >> change >> volume;

		// Instantiate a new Stock object pointer to hold the read data
		Stock* newStock = new Stock(symbol, companyName, lastPrice, change, volume);

		// Remove underscores from each stocks companyName member variable (Looks better printed to console :p)
		remove_(newStock);

		// Store the data into a vector
		stocks.push_back(newStock);
	}

	// Close after loading
	fin.close();
	// Return the vector called stocks
	return stocks;
}

int longestName(std::vector<Stock*>& stocks)
{
	int longest = 0;
	for (auto stock : stocks)
	{
		if (int currSize = stock->companyName.size(); currSize > longest)
		{
			longest = currSize;
		}

	}
	return longest;
}

void displayStocks(std::vector<Stock*>& stocks)
{
	int longest = longestName(stocks);
	std::cout << "SYMBOL" << "\t" << "COMPANY NAME" << std::setw(longest - 12) << "\t" <<
		"LST PR" << "\t" << "CHANGE" << "\t" << "VOLUME" << std::endl;
	std::cout.setf(std::ios_base::fixed);
	std::cout.precision(2);

	// Loop through the vector of stocks
	for (unsigned int i = 0; i < stocks.size(); i++)
	{
		// Print the data for each category in the stock with left alignment and space between columns
		cout << left << setw(8) << stocks[i]->symbol << setw(32) << stocks[i]->companyName << setw(8) << stocks[i]->lastPrice << setw(8) << stocks[i]->change << setw(5) << stocks[i]->volume << endl;
	}
	return;
}

FIELD displayChoices()
{
	// Local variable
	int answer;

	// Label to goto if the answer was invalid
InvalidAnswer:
	// Clear the screen
	system("cls");

	// Prompt the user with the options
	cout << "1. Symbol" << endl;
	cout << "2. Company Name" << endl;
	cout << "3. Last Price" << endl;
	cout << "4. Change" << endl;
	cout << "5. Volume" << endl;
	cout << "6. Quit" << endl;

	// Ask for a selection
	cout << endl << "Please select a catagory: ";

	// Get the answer
	cin >> answer;
	// Ignore the enter from the previous input
	cin.ignore();

	// SWITCH FOR DIFFERENT FIELDS
	switch (answer)
	{
		case 1:
		{
			// Return SYMBOL (1)
			return SYMBOL;
		}
		case 2:
		{
			// Return COMPANY_NAME(2)
			return COMPANY_NAME;
		}
		case 3:
		{
		// Return LAST_PRICE (3)
		return LAST_PRICE;
		}
		case 4:
		{
			// Return CHANGE (4)
			return CHANGE;
		}
		case 5:
		{
			// Return VOLUME (5)
			return VOLUME;
		}
		case 6:
		{
			// Return QUIT (6)
			return QUIT;
		}
		default:
		{
			// Remind the user to enter a valid answer 1 - 6
			cout << endl << "Error: Please select 1 - 6" << endl << endl;
			// Pause to show the prompt
			system("pause");
			// Goto the InvalidAnswer label to ask again
			goto InvalidAnswer;
		}
	}
}

//SORT BY SYMBOL (Insertion Sort)
void insertionSort(std::vector<Stock*>& stocks)
{
	//Local variables (j is for looping backwards to sort and current is for holding the stock at stocks[i] for comparing it to the stock at stocks[j])
	int j;
	Stock* current;

	// Loop forward through stocks
	for (unsigned int i = 1; i < stocks.size(); i++)
	{
		// Grab the stock at index i each iteration for comparing
		current = stocks[i];
		// Set j to be the index before the current index in loop i 
		j = i - 1;

		// Loop backwards at each index i and compare the current symbol value at index j to the symbols before it
		while (j >= 0 && stocks[j]->symbol > current->symbol)
		{
			// Move the larger stock to the right
			stocks[j + 1] = stocks[j];
			// Subtract 1 from j to continue comparing the stock symbol at index I to the stocks symbol at index J
			j--;
		}
		// Set the last stock in the vector to current, loop J goes 0 - 8, not 0 - 9, so we have to add the largest to the end of the vector
		stocks[j + 1] = current;
	}
	return;
}

// SORT BY COMPANY NAME (Selection Sort)
void selectionSort(std::vector<Stock*>& stocks)
{
	// Local variables (i loops forward through stocks and j loops forward 1 element in front of i, lowest is for checking index of smallest stock company name, and temp is a temporary stock for swapping)
	int i, j, lowest;
	Stock* temp;

	// Loop forward through the stocks
	for (unsigned i = 0; i < stocks.size(); i++)
	{
		// Set the lowest index to i
		lowest = i;

		// Loop 1 element in front of the element at i to search for a new lowest index
		for (unsigned j = i + 1; j < stocks.size(); j++)
		{
			// Check that the company name at j is less than the lowest index company name
			if (stocks[j]->companyName < stocks[lowest]->companyName)
			{
				// Set the new lowest index to j if it is smaller than the previous smallest index
				lowest = j;
			}
		}

		// Make the swap after comparing all elements in loop j to the lowest from loop i 
		temp = stocks[i];
		stocks[i] = stocks[lowest];
		stocks[lowest] = temp;
	}
	return;
}

//SORT BY LAST PRICE (Merge Sort) [CITATION: I USED THE EXAMPLE FROM ZYBOOK FIGURE 2.5.1 "MERGE SORT ALGORITH" URL: https://learn.zybooks.com/zybook/UALRcpsc2380OrmeSummer2018/chapter/2/section/5 to help me get this algorithm working properly, I hope that's ok!]
void mergeSort(std::vector<Stock*>& stocks, int first, int last)
{
	// Local variables (mid is the calculated midpoint to divide around)
	int mid = 0;

	// Check if the first index is smaller than the last index
	if (first < last)
	{
		// Get the middle elements index
		mid = (first + last) / 2;

		// Recursive call number 1 (Divide the left side)
		mergeSort(stocks, first, mid);
		// Recursive call number 2 (Divide the right side)
		mergeSort(stocks, mid + 1, last);

		// Merge the peices back together
		merge(stocks, first, mid, last);
	}
	return;
}

// HELPER FUNCTION FOR MERGE SORT (SORT BY LAST PRICE) [CITATION: I USED THE EXAMPLE FROM ZYBOOK FIGURE 2.5.1 "MERGE SORT ALGORITH" URL: https://learn.zybooks.com/zybook/UALRcpsc2380OrmeSummer2018/chapter/2/section/5 to help me get this algorithm working properly, I hope that's ok!]
void merge(std::vector<Stock*>& stocks, int first, int mid, int last)
{
	// Local variables (mergedSize is the size of the merged array, mergePos is the current index, leftPos is the left side index, rightPos is the right side index, and mergedStocks is a new stocks array)
	int mergedSize = last - first + 1, mergePos = 0, leftPos = 0, rightPos = 0;
	Stock* mergedStocks = new Stock[mergedSize];

	// Set the left index to the first element
	leftPos = first;
	// Set the right index to the index right of mid
	rightPos = mid + 1;

	// While the left side hasn't reached mid and the right side hasn't reached last
	while (leftPos <= mid && rightPos <= last)
	{
		// Check that the stocks last price on the left is smaller than the stocks last price on the right
		if (stocks[leftPos]->lastPrice < stocks[rightPos]->lastPrice)
		{
			// If it is, place it into the new array
			mergedStocks[mergePos] = *stocks[leftPos];
			// Move to the left one element and check next element
			leftPos++;
		}
		else
		{
			// If the right stock is smaller, place it into the new array
			mergedStocks[mergePos] = *stocks[rightPos];
			// Move to the right one element to check next element
			rightPos++;
		}
		// Increment the position for the merge array to check another element
		mergePos++;
	}

	// While the left side is not empty yet, add it's remaining elements to the merged array
	while (leftPos <= mid)
	{
		// Put the leftover stocks into merged stocks array
		mergedStocks[mergePos] = *stocks[leftPos];
		// Move over one element in both 
		leftPos++;
		mergePos++;
	}

	// While the right side is not empty yet, add it's remaining elements to the merged array
	while (rightPos <= last)
	{
		// Put the leftover stocks into merged stocks array
		mergedStocks[mergePos] = *stocks[rightPos];
		// Move over one element in both
		rightPos++;
		mergePos++;
	}

	// Loop through the merged stocks array
	for (mergePos = 0; mergePos < mergedSize; mergePos++)
	{
		// Place the stock from the merged stocks array into the vector of stocks
		*stocks[first + mergePos] = mergedStocks[mergePos];
	}
	return;
}

// SORT BY CHANGE (Quick Sort)  [CITATION: I USED THE EXAMPLE FROM ZYBOOK FIGURE 2.4.1 "MERGE SORT ALGORITH" URL: https://learn.zybooks.com/zybook/UALRcpsc2380OrmeSummer2018/chapter/2/section/4 to help me get this algorithm working properly, I hope that's ok!]
void quickSort(std::vector<Stock*>& stocks, int left, int right)
{
	// Local variables j holds the partition index
	int mid = 0;

	// Check that the left index is smaller than right index (return if not)
	if (left >= right)
	{
		return;
	}

	// Get the mid index from partition
	mid = partition(stocks, left, right);

	// Recursive call to divide the left
	quickSort(stocks, left, mid);
	// Recursive call to divide the right
	quickSort(stocks, mid + 1, right);

	return;
}

// HELPER FUNCTION FOR QUICKSORT (SORT BY CHANGE) [CITATION: I USED THE EXAMPLE FROM ZYBOOK FIGURE 2.4.1 "MERGE SORT ALGORITH" URL: https://learn.zybooks.com/zybook/UALRcpsc2380OrmeSummer2018/chapter/2/section/4 to help me get this algorithm working properly, I hope that's ok!]
int partition(vector<Stock*> & stocks, int left, int right)
{
	// Local variables (low is the index of smallest, high is index of largest, midpoint is the middle index, pivot is the value of the change at the midpoint index, temp is for swapping a stock, and done checks progress)
	int low = 0;
	int high = 0;
	int midpoint = 0;
	float pivot = 0;
	Stock* temp;
	bool done = false;

	// Set the midpoint index
	midpoint = left + (right - left) / 2;
	// Set the pivot value for comparing
	pivot = stocks[midpoint]->change;

	// Set low index to the left index
	low = left;
	// Set high index to the right index
	high = right;

	// Continue until we are done
	while (!done)
	{
		// While the change at the low index is smaller than pivot keep moving to the right
		while (stocks[low]->change < pivot)
		{
			// Move right and check again
			++low;
		}
		// While the change at the high index is larger than pivot keep moving to the left
		while (pivot < stocks[high]->change)
		{
			// Move left and check again
			--high;
		}

		// if low is greater than or equal to high we're down
		if (low >= high)
		{
			// Set done to true
			done = true;
		}
		else
		{
			// If not done, make the swap
			temp = stocks[low];
			stocks[low] = stocks[high];
			stocks[high] = temp;

			// Move low to the right
			low++;
			// Move high to the left
			high--;
		}
	}
	// Return the index of high
	return high;
}

// SORT BY VOLUME (Bubble Sort) [CITATION: I found the last sorting algorithm required at URL: https://www.tutorialspoint.com/data_structures_algorithms/bubble_sort_program_in_c.htm, I hope that's ok!]
void bubbleSort(std::vector<Stock*>& stocks)
{
	// Local variables (i is for looping forward, j is for looping forward one less element than i, and temp is for swapping stocks)
	int i, j;
	Stock* temp;

	// Loop forward through the stocks
	for (i = 0; i < stocks.size(); i++)
	{
		// Loop 1 less element than i
		for (j = 0; j < stocks.size() - 1; j++)
		{
			// If the element to the right of the current element in j is less than the current element in J
			if (stocks[j + 1]->volume < stocks[j]->volume)
			{
				// Swap the smaller element at j with the one to it's right
				temp = stocks[j];
				stocks[j] = stocks[j + 1];
				stocks[j + 1] = temp;
			}
		}
	}
	return;
}

void binarySearch(FIELD field, std::string key, std::vector<Stock*>& stocks, char answer)
{
	// Local variables (first is the first index, mid is the middle index, last is the last index, foundIt stops if key is found)
	int first = 0, mid, last = stocks.size() - 1, pos;
	bool foundIt;
	float searchKey;
	char correct;

	// SWITCH FOR SEARCH OPTIONS
	switch (field)
	{
		// SYMBOL
		case 1:
		{
			// Start by setting foundIt to false
			foundIt = false;
			// While found it is false and the first index is less than the last index
			while (!foundIt && first <= last)
			{
				// Set the mid index to the first + last divided by 2
				mid = (first + last) / 2;
	
				// If the search key is the middle index stock's symbol
				if (key == stocks[mid]->symbol)
				{
					// We found it
					foundIt = true;
					// Note the position it was found at
					pos = mid;
				}
				// If the key is less than the middle index stock's symbol
				else if (key < stocks[mid]->symbol)
				{
					// Move last index to mid - 1 (one place to the left)
					last = mid - 1;
				}
				// Else the key is large than middle index stock's symbol
				else
				{
					// Move the first index to mid + 1 (one place to the right)
					first = mid + 1;
				}
			}

			// Check if the stock was found
			if (foundIt)
			{
				// Found it? Print out it's data
				cout << endl << left << setw(8) << stocks[pos]->symbol << setw(32) << stocks[pos]->companyName << setw(8) << stocks[pos]->lastPrice << setw(8) << stocks[pos]->change << setw(5) << stocks[pos]->volume << endl << endl;

				// Call change price function if the user hit update on the initial menu
				if (answer == 'u' || answer == 'U')
				{
					// Verify it's correct before letting user change data
					cout << "Is this the correct stock?: ";
					cin >> correct;
					if (correct == 'y' || correct == 'Y')
					{
						// LET USER ENTER A NEW PRICE FOR THE STOCK AT POS
						changePrice(SYMBOL, pos, stocks);
					}
					else
					{
						// If it's not the correct one, return to main menu
						cout << endl;
						system("exit");
					}
				}
			}
			else
			{
				// Error message, could not find the symbol.
				cout << endl << "Sorry, a stock by the symbol " << key << " could not found. Returning to main menu." << endl << endl;
			}
			break;
		}
		// COMPANY NAME
		case 2:
		{
			foundIt = false;
			while (!foundIt && first <= last)
			{
				mid = (first + last) / 2;
	
				if (key == stocks[mid]->companyName)
				{
					foundIt = true;
					pos = mid;
				}
				else if (key < stocks[mid]->companyName)
				{
					last = mid - 1;
				}
				else
				{
					first = mid + 1;
				}
			}

			if (foundIt)
			{
				cout << endl << left << setw(8) << stocks[pos]->symbol << setw(32) << stocks[pos]->companyName << setw(8) << stocks[pos]->lastPrice << setw(8) << stocks[pos]->change << setw(5) << stocks[pos]->volume << endl << endl;
			}
			else
			{
				cout << endl << "Sorry, a stock by the company name " << key << " could not found. Returning to main menu." << endl << endl;
			}
			break;
		}
		// LAST PRICE
		case 3:
		{
			// Get the float to search for here, there wasn't a float param in this function and I couldn't figure out a conversion of string to float
			cout << "Please enter a last price to search by: ";
			cin >> searchKey;

			foundIt = false;
			while (!foundIt && first <= last)
			{
				mid = (first + last) / 2;
	
				if (searchKey == stocks[mid]->lastPrice)
				{
					foundIt = true;
					pos = mid;
				}
				else if (searchKey < stocks[mid]->lastPrice)
				{
					last = mid - 1;
				}
				else
				{
					first = mid + 1;
				}
			}

			if (foundIt)
			{
				cout << endl << left << setw(8) << stocks[pos]->symbol << setw(32) << stocks[pos]->companyName << setw(8) << stocks[pos]->lastPrice << setw(8) << stocks[pos]->change << setw(5) << stocks[pos]->volume << endl << endl;
			}
			else
			{
				cout << endl << "Sorry, a stock by the last price " << searchKey << " could not found. Returning to main menu." << endl << endl;
			}
			break;
		}
		// CHANGE
		case 4:
		{
			// Get the float to search for here, there wasn't a float param in this function and I couldn't figure out a conversion of string to float
			cout << "Please enter a change to search by: ";
			cin >> searchKey;

			foundIt = false;
			while (!foundIt && first <= last)
			{
				mid = (first + last) / 2;
	
				if (searchKey == stocks[mid]->change)
				{
					foundIt = true;
					pos = mid;
				}
				else if (searchKey < stocks[mid]->change)
				{
					last = mid - 1;
				}
				else
				{
					first = mid + 1;
				}
			}

			if (foundIt)
			{
				cout << endl << left << setw(8) << stocks[pos]->symbol << setw(32) << stocks[pos]->companyName << setw(8) << stocks[pos]->lastPrice << setw(8) << stocks[pos]->change << setw(5) << stocks[pos]->volume << endl << endl;
			}
			else
			{
				cout << endl << "Sorry, a stock by change " << searchKey << " could not found. Returning to main menu." << endl << endl;
			}
			break;
		}
		// VOLUME
		case 5:
		{
			// Get the float to search for here, there wasn't a float param in this function and I couldn't figure out a conversion of string to float
			cout << "Please enter a volume to search by: ";
			cin >> searchKey;

			foundIt = false;
			while (!foundIt && first <= last)
			{
				mid = (first + last) / 2;
	
				if (searchKey == stocks[mid]->volume)
				{
					foundIt = true;
					pos = mid;
				}
				else if (searchKey < stocks[mid]->volume)
				{
					last = mid - 1;
				}
				else
				{
					first = mid + 1;
				}
			}

			if (foundIt)
			{
				cout << endl << left << setw(8) << stocks[pos]->symbol << setw(32) << stocks[pos]->companyName << setw(8) << stocks[pos]->lastPrice << setw(8) << stocks[pos]->change << setw(5) << stocks[pos]->volume << endl << endl;
			}
			else
			{
				cout << endl << "Sorry, a stock by the volume of " << searchKey << " could not found. Returning to main menu." << endl << endl;
			}
			break;
		}
		//QUIT
		case 6:
		{
			system("exit");
			break;
		}
		default:
		{
			cout << endl << "Error: Please select a number between 1 - 6!" << endl << endl;
			system("pause");
			break;
		}
	}
	return;
}

void changePrice(FIELD field, int pos, std::vector<Stock*>& stocks)
{
	float price;
	bool updated = false;

	// Get the new price for the stock
	cout << endl << "Please enter a new price for the stock: ";
	cin >> price;

	// Change the stock price for the stock the user entered
	for (unsigned int i = 0; i < stocks.size(); i++)
	{
		// Update the price
		stocks[pos]->lastPrice = price;
		updated = true;
	}

	// Tell the user the price was sucessfully updated
	if (updated)
	{
		// Let the user know the price has been updated
		cout << endl << "Successfully updated the price to " << price << ". Thank you." << endl << endl;
	}
	return;
}

void saveStocks(std::string fileName, std::vector<Stock*>& stocks)
{
	// Local variables
	string symbol, companyName;
	float lastPrice, change, volume;

	// Instantiate a filestream out
	ofstream fout;
	// Open the file stocks.txt
	fout.open(fileName);

	// Verify that the filestream was able to open the file
	if (!fout.is_open())
	{
		// Tell user unable to open file
		cerr << "Error opening " << fileName << "." << endl;
		// Pause to view results
		system("pause");
		// Return semicolon after warning unable to open
		return;
	}

	// Loop through every stock
	for (unsigned int i = 0; i < stocks.size(); i++)
	{
		// Get each stocks data into local variables
		symbol = stocks[i]->symbol;
		companyName = stocks[i]->companyName;
		lastPrice = stocks[i]->lastPrice;
		change = stocks[i]->change;
		volume = stocks[i]->volume;

		// Instantiate a new Stock object with the same member variables that already exist in the vector<Stock*> stocks
		Stock* newStock = new Stock(symbol, companyName, lastPrice, change, volume);

		// Insert underscores back into the company names for each stock
		insert_(newStock);

		// Store the newStock in place of the old stock with "_" instead of " " 
		stocks[i] = newStock;

		if (i < stocks.size() - 1)
		{
			// Write each stocks symbol, company name, last price, change, and volume (as it was at start, but pretty printed with setw and left alignment from iomanip library)
			fout << left << setw(8) << stocks[i]->symbol << setw(32) << stocks[i]->companyName << setw(8) << stocks[i]->lastPrice << setw(8) << stocks[i]->change << setw(5) << stocks[i]->volume << endl;
		}
		else
		{
			// Write the last one to file WITHOUT a new line after it. I had a super annoying bug because of my ocd and pretty printing, this fixes that issue
			fout << left << setw(8) << stocks[i]->symbol << setw(32) << stocks[i]->companyName << setw(8) << stocks[i]->lastPrice << setw(8) << stocks[i]->change << setw(5) << stocks[i]->volume;
		}
	}

	// Close after saving
	fout.close();
	return;
}