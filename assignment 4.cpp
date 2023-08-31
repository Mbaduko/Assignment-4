#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
enum Genre {fiction, nonfiction ,periodical, biography, children};
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
    //Parameterized constructor
    Book ( const string& ISBN="--NONE--", const string& Name="--NO NAME--" ,
     const string& get_Author="--NOT YET KNOWN--",
     const int& get_copyright_Date=0 , const Genre genre_of_book=children, 
     const bool& checked_out=false )
      :ISBN(ISBN),Title(Name),Author(get_Author),Copyright_date(get_copyright_Date),
      Genre_of_book(genre_of_book),Checked_out(checked_out)
{}

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
     et<<"\nTitle: "<<bn.Title;
     et<<"\nAuthor: "<<bn.Author;
     et<<"\nGenre: ";
    switch (bn.Genre_of_book)
    {
        case 0:
            et<<"Fiction";
            break;
        case 1:
            et<<"Nonfiction";
            break;
        case 2:
            et<<"periodical";
            break;
        case 3:
            et<<"biography";
            break;
        case 4:
            et<<"Children";
            break;
        default:
            break;
    }
    et<<"\n";
    
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

    //overloading == operator so as to be able to compare patrons while checking out book
    bool operator==(const Patron& other) const {
    return (username == other.username && card_number == other.card_number);
}


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
  string Date;
public:
    Transaction(const Book& b,const Patron& p,const string& act, const string& date)
    : book(b),patron(p),activity(act), Date(date) {}
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
void Check_out_book (Book& book, const Patron& patron, const string& date);
vector<Patron> users_who_owe_fees() const;
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

void Library :: Check_out_book(Book& book, const Patron& ptrn , const string& date)
{
    if ((find(books.begin(),books.end(),book)==books.end()) || (find(patrons.begin(),patrons.end(),ptrn)==patrons.end()))
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
    transactions.push_back(Transaction(book,ptrn,"check out",date));
    cout<<"\nChecking book out successful";
}

//Creating vector of users who owes fees
vector<Patron> Library:: users_who_owe_fees() const
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

int main() {
    Library Progaramming_library;

    Book programming_1("12345", "Progammers' mind", "Mbaduko", 2021, nonfiction);
    Book programming_2("12346", "Advanced c++ programming", "Emmanuel", 2021, nonfiction);
    Book programming_3("12347", "Python for beginner", "Dr claude", 2002, nonfiction);
    Book story_1("a12734_c1", "Programmed man", "Mr Eaggle",1998, fiction,true);
    Book story_2 ("S23_F4265352", "Progarmmer mom", "Pascal", 2023, children);

    //Displaying a book
    cout<<story_1<<"\n\n\n";

    //Inserting book in the library
    Progaramming_library.addbook(programming_1);
    Progaramming_library.addbook(programming_2);
    Progaramming_library.addbook(programming_3);
    Progaramming_library.addbook(story_2);

    Patron p_1 ("Edson", "3001", 70098);
    Patron p_2 ("Peter", "895753");
    Patron p_3 ("John", "977");

    //Inserting patrons to library
    Progaramming_library.addpatron(p_1);
    Progaramming_library.addpatron(p_2);
    
    // ....Checking book out... 
    //Trying it with not registered user
    Progaramming_library.Check_out_book(programming_1, p_3, "1/1/2023");
    //Trying it with user who owe fees
    Progaramming_library.Check_out_book(story_2, p_1, "1/1/2020");
    //Successful action
    Progaramming_library.Check_out_book(programming_2, p_2,"1/1/20290");
    return 0;
}
