#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<limits>
#include<string>
#include <sstream>
using namespace std;

//Creating the bookshop class with all of the necessary functions
class bookshop{
public:
    void control_panel(); // main menu
    void add_book(); // function to add a new book to the database
    void show_book(); // function to display ALL books from the library
    void check_book(); // function to display a specific book from the database
    void del_book(); // delete a book from the database
};

void bookshop::control_panel(){ // main menu
	cout<<"\n* * * * Control Panel * * * *";
    cout << "\n\n1. ADD BOOK";
    cout << "\n2. DISPLAY BOOKS";
    cout << "\n3. CHECK PARTICULAR BOOK";
    cout << "\n4. DELETE BOOK";
    cout << "\n5. EXIT";
}

void bookshop::add_book(){ // function to add a new book to the database
	fstream myFile;
	std::string book_name, author, book_id;
	cout<<"\n\n\t\tAdd a book\n\n";
	cout<<"Book ID: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, book_id);

	cout<<"Book name: ";
	std::getline(std::cin, book_name);

	cout<<"Book author: ";
	std::getline(std::cin, author);

	book_id.erase(book_id.length()-1); // remove the last element of the string which
	book_name.erase(book_name.length()-1); // is the new line, which break the code
	author.erase(author.length()-1);         // if it remains

	std::string res= book_id + " " + book_name + " " + author + " \n"; // creating a string to hold the new information

	myFile.open("books_library.txt", ios::out | ios::app); //write mode, to write to the file
	if(myFile.is_open()){
		myFile << res; // push the new book's data to the database
		myFile.close(); // close the database, the txt file
	}
}

void bookshop::show_book(){ // function to display ALL books from the library
	fstream myFile;
	cout<<"\nShowing the whole database: \n";
	cout<<"The format is:      ID      book name      book author\n";
	myFile.open("books_library.txt", ios::in); //reading from the file/database
	if(myFile.is_open()){
		string line;
		while(getline(myFile, line)){
			cout<<line<<endl;
		}
		myFile.close();
	}
}

void bookshop::check_book(){ // function to display a specific book from the database
    fstream myFile;
    int count = 0;
    string b_id, b_idd, line;

    cout << "\nChecking for a particular book\n";

    // Open the file in input mode
    myFile.open("books_library.txt", ios::in);
        cout << "\n\nBook ID : ";
        cin >> b_idd;
        myFile >> b_id; // read the first thing in the file and store it in b_id.
        				// The extraction stops when a whitespace character
        				// (space, tab, newline) is encountered

        while (getline(myFile, line)) { //while there's still some lines left
        	myFile >> b_id;
            if (b_idd == b_id) { // if the user's desired id matches the line's id, then
            	getline(myFile, line);   //get the whole line and
            	cout<<line<<endl;		// display it
                count++;
                break;
            }
        }
        myFile.close();
        if (count == 0) cout << "\n\nBook ID Not Found...";
}

void bookshop::del_book(){
	fstream myFile, tempFile;
	    string b_idd, b_id, line;

	    cout << "\nDeleting a particular book\n";

	    // Open the file in input mode
	    myFile.open("books_library.txt", ios::in); // open the database txt file

	    if (!myFile.is_open()) {   // if there's a problem opening the file
	        cerr << "Error opening file for reading." << endl;
	        return;
	    }

	    // Open a temporary file in output mode
	    tempFile.open("temp_library.txt", ios::out); // the TEMP file is opened

	    if (!tempFile.is_open()) { // if the file can't be opened, display error text
	        cerr << "Error opening temporary file for writing." << endl;
	        myFile.close();
	        return;
	    }

	    cout << "\n\nEnter the Book ID to delete: ";
	    cin >> b_idd; // user's desired ID

	    while (myFile >> b_id) { // loop is reading pairs of data from
	    						// the file: an ID (b_id) and the rest of
	    						// the line (line). The loop continues as
	    						// long as there is more data to be read from
	    						// the file.
	        getline(myFile, line);  // Read the rest of the line

	        if (b_idd != b_id) {  // if the desired by the user ID does NOT match
	        					  // the current line's ID, then
	            tempFile << b_id << " " << line << endl; // write the ID + a whitespace
	            										 // + the rest of the line
	            										 // + a new line
	        }
	    }

	    myFile.close(); // closing both opened files
	    tempFile.close();

	    // Remove the original file
	    if (remove("books_library.txt") != 0) {
	        cerr << "Error deleting original file." << endl;
	        return;
	    }

	    // Rename the temporary file to the original file
	    if (rename("temp_library.txt", "books_library.txt") != 0) {
	        cerr << "Error renaming temporary file." << endl;
	    }
	    cout<<"\n * * * * * * * * * * Book DELETED successfully! * * * * * * * * * *\n";
}

void bookShopRecord(){ // the main function holding the choice of the main menu
	int choice;
	bookshop b;
	char new_book{'y'};
	while(1){ // just a loop with an endless condition

		b.control_panel();

		cout<<"\n\nEnter your choice: ";
		cin>>choice;

		switch(choice){ // switching the different possible user input choices
		case 1: // in case the user wants to add a book to the database
			do {
			b.add_book();
			cout<<"Add another book? Enter 'y' for yes and 'n' for no: ";
			cin>>new_book;
			} while (new_book=='y');
			break;
		case 2:
			b.show_book();
			break;
		case 3:
			b.check_book();
			break;
		case 4:
			b.del_book();
			break;
		case 5:
			exit(0);
			break;
		default:
			cout << "\n\nINVALID CHOICE\n";
		}
	}
}

int main(){
	bookShopRecord();
	return 0;
}
