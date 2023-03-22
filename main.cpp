#include <iostream> 
#include <string>
#include <vector> 
#include <fstream> 
#include <algorithm> 

using namespace std;

struct PhoneNumber{
  string number;
  char phoneType; // W = Work, H = Home, C = Cell
};

class Contact{

  private:
    char contactType; // P = personal, W = Work
    string firstName, lastName, streetName, city, state, email, dateOfBirth;
    int streetNumber, postalCode; 
    vector<PhoneNumber> phoneNumbers;

  public: 
    // Constructors 
    Contact(char contactType, string firstName, string lastName); 
    Contact(char contactType, string phoneNumber);

    // Accessors 
    string getFirstName();
    string getLastName(); 
    char getContactType();
    string getState();
    string getEmail();
    string getDateOfBirth();

    // Mutators
    void setFirstName(string newFirstName);
    void setLastName(string newLastName);
    void setContactType(char newContactType);
    void setEmail(string newEmail);
    void setDateOfBirth(string newDateOfBirth);
    void setAddress(int newStreetNumber, string newStreetName, string newCity, string newState, int newPostalCode);

    // Other Member Functions
    string getName(); // returns last name and first name 
    string getAddress(); // returns number, street, city, state, postalcode 
    string addPhone(char type, string number); // should this be boolean or void?
    string deletePhone(int index); // index in vector of phoneNumbers
    string getAsString(); // returns contact as string in special format (see document)
    string tester();


  
};

string Contact::deletePhone(int index){
  if(index < phoneNumbers.size() && index >= 0){
    string toReturn = "success: deleted phone " + to_string(index);
    phoneNumbers.erase(phoneNumbers.begin()+index);
    return toReturn;
  }
  else{
    string error = "failure: unable to delete phone " + to_string(index);
    return error;
  }
}

string Contact::getAsString(){

  string firstNum;
  bool finished = false;
  string secondNum;


  for(int i = 0; i < phoneNumbers.size(); i++){
    
    if(phoneNumbers.at(i).phoneType == 'H' && finished == false){
      //cout << endl << phoneNumbers.at(i).phoneType << endl;
      firstNum = "Home: " + phoneNumbers.at(i).number;
      finished = true;
    }
    else if(phoneNumbers.at(i).phoneType == 'C' && finished == false){
      //cout << endl << phoneNumbers.at(i).phoneType << endl;
      firstNum = "Cell: " + phoneNumbers.at(i).number;
      finished = true;
    }
    else if(phoneNumbers.at(i).phoneType == 'H' && finished == true){
      secondNum = "Home: " + phoneNumbers.at(i).number;
    }
    else if(phoneNumbers.at(i).phoneType == 'C' && finished == true){
      secondNum = "Cell: " + phoneNumbers.at(i).number;
    }
    
  }
  
  char type = this->getContactType();
  string res = "";
  
  if(type == 'W'){
    res = "Work";
  }
  else if(type == 'P'){
    res = "Personal";
  }

  
  return this->getName() + "\n" + res + "\n" + this->getAddress() + "\n" + this->getDateOfBirth() + "\n" + this->getEmail() + "\n" + firstNum + "\n" + secondNum + "\n"; 
  
}

string Contact::getName(){
  string toReturn = this->lastName + ", " + this->firstName;
  return toReturn;
}

bool operator<(Contact& lhs, Contact& rhs){
  if(lhs.getName() < rhs.getName()){
    return true;
  }
  else{
    return false;
  }
}



string Contact::addPhone(char type, string phoneNum){

  if(type == 'C' || type == 'H' || type == 'W'){
    PhoneNumber tempNumber;
    tempNumber.phoneType = type;
    tempNumber.number = phoneNum;
    this->phoneNumbers.push_back(tempNumber);
    string phType;

    if(type == 'C'){
      phType = "Cell";
    }
    else if(type == 'H'){
      phType = "Home";
    }
    else if(type == 'W'){
      phType = "Work";
    }

    string toReturn = "success: added number " + phoneNum + " " + phType;
    return toReturn;
  }
  else{
    string s(1, type);
    string toReturn = "failure: invalid phone type - " + s;
    return toReturn;
  }
  
}


string Contact::getAddress(){
  string conv = to_string(this->streetNumber);
  string format = conv + " " + this->streetName + ", " + this->city + ", " + this->state + " " + to_string(this->postalCode);
  return format;
}

string Contact::getFirstName(){
  return this->firstName;
}

string Contact::getLastName(){
  return this->lastName;
}

char Contact::getContactType(){
  return this->contactType;
}

string Contact::getState(){
  return this->state;
}

string Contact::getEmail(){
  return this->email;
}

string Contact::getDateOfBirth(){
  return this->dateOfBirth;
}


Contact::Contact(char type, string firstName, string lastName){
  this->contactType = type; 
  this->firstName = firstName; 
  this->lastName = lastName;
}

void Contact::setFirstName(string newFirstName){
  this->firstName = newFirstName;
}

void Contact::setLastName(string newLastName){
  this->lastName = newLastName;
}

void Contact::setContactType(char newContactType){
  this->contactType = newContactType;
}

void Contact::setEmail(string newEmail){
  this->email = newEmail;
}

void Contact::setDateOfBirth(string newDateOfBirth){
  this->dateOfBirth = newDateOfBirth;
}

void Contact::setAddress(int newStreetNumber, string newStreetName, string newCity, string newState, int newPostalCode){
  this->streetNumber = newStreetNumber;
  this->streetName = newStreetName;
  this->city = newCity;
  this->state = newState;
  this->postalCode = newPostalCode;
}



bool operator<(const Contact& lhs, const Contact& rhs){
  // IS THIS CORRECT TO OVERLOAD '<' OPERATOR? 
  return true;
}

class ContactList{

  private:
    vector<Contact> contacts;

  public: 
    string loadContactsFromFile(string filename);
    int getCount();
    string sortContacts(); 
    vector<int> findContactsByName(string search);
    void printContacts(vector<int> index);
    string addContact(Contact obj);
    string deleteContact(int index);
    string tester();
};


string ContactList::deleteContact(int index){
  string toReturn = "success: deleted contact " + contacts.at(index).getName();
  contacts.erase(contacts.begin() + index);
  return toReturn;
}

string ContactList::addContact(Contact obj){
  contacts.push_back(obj);
  return "sucess: contact " + obj.getLastName() + ", " + obj.getFirstName() + " added";
}


void ContactList::printContacts(vector<int> index){
  
  for(int i = 0; i < index.size(); i++){

    int currIndex = index.at(i);
    
    if(i == 0){
      cout << "--------------------" << endl;
      cout << endl;
      cout << contacts.at(currIndex).getAsString();
      cout << endl;
      cout << "--------------------" << endl;
    }
    else if(i == (index.size()-1)){
      cout << endl;
      cout << contacts.at(currIndex).getAsString();
      cout << endl; 
    }
    else{
      cout << endl;
      cout << contacts.at(currIndex).getAsString();
      cout << endl;
      cout << "--------------------" << endl;
    }
    
    
  }
  
}

vector<int> ContactList::findContactsByName(string search){

  vector<int> index;

  for(int i = 0; i < search.size(); i++){
    search[i] = toupper(search[i]);
  }


  for(int i = 0; i < contacts.size(); i++){

    string currName = contacts.at(i).getName();
    
    for(int x = 0; x < currName.size(); x++){
      currName[x] = toupper(currName[x]);
    }

    if(currName.find(search) != string::npos){
      index.push_back(i);
    }
    
  }

  
  return index;
  
}

string ContactList::sortContacts(){
  sort(contacts.begin(), contacts.end());
  return "success";
}

int ContactList::getCount(){
  return this->contacts.size();
}



string ContactList::loadContactsFromFile(string filename){

  // Reads lines from the filename provided and parses it. 

  ifstream inputStream;
  inputStream.open(filename);
  int count = 1;

  if(!inputStream.is_open()){  
    string toReturn = "failure: " + filename + " not found";
    return toReturn;
  }
  else{
    
    string line = "";
    int count = 0;

    while(getline(inputStream, line)){

      if(count == 0){
        count += 1;
        continue;
      }


      char type; 
      string firstName;
      string lastName;
      int streetNumber;
      string streetName; 
      string city; 
      string state;
      int postcode; 
      string email; 
      string dateOfBirth;
      string age; 
      string phoneNumber; 
      string cellNumber;

      int lastPos = 0;
      int section = 1;
      int length = 0;


      for(int i = 0; i < line.length(); i++){

        length += 1;

        
        if(line[i] == ','){
          
          if(section == 1){
            string current = line.substr(0, i);
            section += 1;
            lastPos = i;
            length = 0;
            type = toupper(current[0]);
          }
          else if(section == 2){
            string current = line.substr(lastPos + 1, length-1);
            section += 1;
            lastPos = i;
            length = 0;
            firstName = current;
          }
          else if(section == 3){
            string current = line.substr(lastPos + 1, length - 1);
            section += 1;
            lastPos = i;
            length = 0;
            lastName = current;
          }
          else if(section == 4){
            string current = line.substr(lastPos + 1, length-1);
            section += 1;
            lastPos = i;
            length = 0;
            streetNumber = stoi(current);
          }
          else if(section == 5){
            string current = line.substr(lastPos + 1, length-1);
            section += 1;
            lastPos = i;
            length = 0;
            streetName = current;
          }
          else if(section == 6){
            string current = line.substr(lastPos + 1, length-1);
            section += 1;
            lastPos = i;
            length = 0;
            city = current;
          }
          else if(section == 7){
            string current = line.substr(lastPos + 1, length-1);
            section += 1;
            lastPos = i;
            length = 0;
            state = current;
          }
          else if(section == 8){
            string current = line.substr(lastPos + 1, length-1);
            section += 1;
            lastPos = i;
            length = 0;
            postcode = stoi(current);
          }
          else if(section == 9){
            string current = line.substr(lastPos + 1, length-1);
            section += 1;
            lastPos = i;
            length = 0;
            email = current;
          }
          else if(section == 10){
            string current = line.substr(lastPos + 1, length-1);
            section += 1;
            lastPos = i;
            length = 0;
            dateOfBirth = current;
          }
          else if(section == 11){
            string current = line.substr(lastPos + 1, length-1);
            section += 1;
            lastPos = i;
            length = 0;
            age = current;
          }
          else if(section == 12){
            string current = line.substr(lastPos + 1, length-1);
            section += 1;
            lastPos = i;
            length = 0;
            phoneNumber = current;

            int lastStart = (lastPos + 1) + (length - 1);
            int lastLength = line.length() - lastStart;
            string final = line.substr(lastStart + 1 , lastLength-1);
            cellNumber = final;
            
          }
          
        }
      }

      count += 1;
      // creating contact objects here.
      Contact newContact(type, firstName, lastName);
      newContact.setAddress(streetNumber, streetName, city, state, postcode);
      newContact.setEmail(email);
      newContact.addPhone('H', phoneNumber); 
      newContact.addPhone('C', cellNumber); 
      newContact.setDateOfBirth(dateOfBirth);
      contacts.push_back(newContact);

    }

    string toReturn = "success: " + to_string(count) + " contacts added";
    return toReturn;
  }

  
}




int main()
{
  ContactList myContacts;
  
    myContacts.loadContactsFromFile("contacts.csv");
  
    myContacts.sortContacts();
  
    vector<int> v = myContacts.findContactsByName("a");
    
    myContacts.printContacts(v);
    
    return 0;
}