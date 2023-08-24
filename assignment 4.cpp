#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
enum Genre {unknown,fiction, nonfiction ,periodical, biography, children};
class Book
{
private:
    string ISBN;
    string Title;
    string Author;
    int Copyright_date;
    bool Checked_out;
    Genre Genre_of_book;
public:
    //Default constructor
    Book();            

    //Parameterized constructor
    Book ( const string& ISBN, const string& Name , const string& get_Author ,
     const int& get_copyright_Date , const Genre genre_of_book , 
     const bool& checked_out=false );

    //Copy constructor
    Book ( const Book& book_p);

    //Default destructor
    ~Book();

    //Activities
    void Check_book_out ();
    void Check_book_in  ();

    //Getter functions prototyping
    string get_name () const;
    string get_Isbn () const;
    string get_Author () const;
    int get_copyright_Date () const;
    bool get_checked_out () const;
    Genre get_genre_of_book () const;

    //overloading '==' operator
    bool operator== (const Book& book_n) const
    {
        return (ISBN==book_n.ISBN);
    }

    //Overlooding != operator
    bool operator!= (const Book& book_m) const
    {
        return !(ISBN == book_m.ISBN);
    }

    //overloading '<<'operator
    
    friend ostream& operator<< (ostream& et, const Book& bn);
   
};


 ostream& operator<< (ostream& et, const Book& bn)
 {
     et<<"\nISBN: "<<bn.ISBN;
     et<<"\nTitle  "<<bn.Title;
     et<<"\nAuthor"<<bn.Author;
     et<<"\nGenre "<<bn.Genre_of_book;
     return et;
 }

//Defining getter functions
string Book:: get_name () const
{
    return Title;
}
string Book::get_Isbn () const
{
    return ISBN;
}
string Book::get_Author () const
{
    return Author;
}
int Book:: get_copyright_Date () const
{
    return Copyright_date;
}
bool Book :: get_checked_out () const
{
    return Checked_out;
}
Genre Book :: get_genre_of_book () const
{
    return Genre_of_book;
}

//defining default constructor
Book::Book()
{
    ISBN="--NONE--";
    Title="--NO NAME--";
    Author="--NOT YET KNOWN--";
    Copyright_date=NULL;
    Checked_out=false;
    Genre_of_book=unknown;
}

//defining parameterized constructer
Book::Book ( const string& ISBN, const string& Name , const string& get_Author ,
 const int& get_copyright_Date , const Genre genre_of_book , 
 const bool& checked_out)
 :ISBN(ISBN),Title(Name),Author(get_Author),Copyright_date(get_copyright_Date),
 Genre_of_book(genre_of_book),Checked_out(checked_out)
{}

//defining copy constructor
Book::Book(const Book& book_n) 
{
    ISBN=book_n.ISBN;
    Title=book_n.Title;
    Author=book_n.Author;
    Copyright_date=book_n.Copyright_date;
    Checked_out=book_n.Checked_out;
    Genre_of_book=book_n.Genre_of_book;
}
Book::~Book()
{
}

//checking book out
void Book::Check_book_out ()
{
    Checked_out=true;
}

//checking book in
void Book::Check_book_in()
{
    Checked_out=false;
}


//CLASS PATRON
class Patron
{
private:
    string username;
    string card_number;
    int owed_fees;
public:
    //Constructer
    Patron(const string& Name="No-Name", const string& cardNo="Not known", const int& Fees=0)
    :username(Name), card_number(cardNo), owed_fees(Fees) {}

    //Getter functions
    string traverse_p_name () const;
    string traverse_p_card_number () const;
    int traverse_owed_fees () const;

    //Other methods
    bool patron_owes_fees () const;//Checking if a patron owes fees
    void set_fees (const int& fees);//Fees setter

};

//Defining Other methods
bool Patron::patron_owes_fees() const
{
    return (owed_fees>0);
}
void Patron::set_fees(const int& fees)
{
    owed_fees=fees;
}


//Getter funcctions definition
string Patron::traverse_p_name () const
{
    return username;
}
string Patron :: traverse_p_card_number () const
{
    return card_number;
}
int Patron :: traverse_owed_fees () const
{
    return owed_fees;
}

//CLASS TRANSATION
class Transaction 
{
private:
  Book book;
  Patron patron;
  string activity;
  int date;
public:
    Transaction(const Book& b,const Patron& p,const string& act)
    : book(b),patron(p),activity(act) {}
};


//CLASS LIBRARY
class Library
{
private:
  vector<Book>books;
  vector<Patron>patrons;
  vector<Transaction>transactions;  
public:
void addbook(const Book& book);
void addpatron(const Patron& patron);
void Check_out_book (Book& book, const Patron& patron);
vector<Patron> users_owes_fees() const;
};
// function to add book

void Library :: addbook(const Book& book)
{
    books.push_back(book);
}
void Library :: addpatron(const Patron& patron)
{
    patrons.push_back(patron);
}
// function to check out book

void Library :: Check_out_book(Book& book, const Patron& ptrn)
{
    if ((find(books.begin(),books.end(),book)==books.end()) && (find(patrons.begin(),patrons.end(),ptrn)==patrons.end()))
    {
        cout<<"\n\n!ERROR   Either book or patron is not registered\n";
        return;
    }
    if (ptrn.patron_owes_fees())
    {
        cout<<"\n!ERROR the user owes fees\n";
        return;
    }
    
    book.Check_book_out();
    transactions.push_back();
}

//Creating vector of users who owes fees
vector<Patron> Library:: users_owes_fees() const
{
    vector<Patron> Them;
    for (Patron User : patrons)
    {
        if (User.patron_owes_fees())
        {
            Them.push_back(User);
        }
    }
    return Them;
}

int main ()
{
       vector<Patron> users_owes_fees();
};

int main() {
    Library library;

    // Adding books and patrons to the library
    Book book1("123456", "Sample Book 1", "Author 1", 2023, fiction, false);
    Book book2("789012", "Sample Book 2", "Author 2", 2021, nonfiction, false);
    Patron patron1{"User1", "Card001", 0};
    Patron patron2{"User2", "Card002", 10};

    library.addbook(book1);
    library.addbook(book2);
    library.addpatron(patron1);
    library.addpatron(patron2);

    // Checking out books
    library.Check_out_book(book1, patron1);
    library.Check_out_book(book2, patron2);

    // Displaying users who owe fees
    vector<Patron> owingPatrons = library.users_owes_fees();
    cout << "Users who owe fees:\n";
    for (const Patron& patron : owingPatrons) {
        cout << patron.traverse_p_name() << " (" << patron.traverse_p_card_number() << ")\n";
    }

    return 0;

}
