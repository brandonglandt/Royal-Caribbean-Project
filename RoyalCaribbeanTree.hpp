#ifndef ROYALCARIBBEANTREE_HPP
#define ROYALCARIBBEANTREE_HPP
#include <string>

struct CruiseNode
{
  int year;
  std::string shipname;
  int capacity;
  std::string destination;
  int length;
  int price;

  CruiseNode *parent;
  CruiseNode *left;
  CruiseNode *right;

  CruiseNode() {};

  CruiseNode(int year, std::string shipname, int capacity, std::string destination, int length, int price)
  {
    year = year;
    shipname = shipname;
    capacity = capacity;
    destination = destination;
    length = length;
    price = price;
  }
};

class CruiseTree
{
public:
  CruiseTree();
  ~CruiseTree();
  void printCruiseInventory();
  void addCruise(int year, std::string shipname, int capacity, std::string destination, int length, int price);
  void minValueNode(struct Node* node);
  void deleteCruise(std::string shipname);
  void findCruise(std::string shipname);
private:
  void postOrderDelete(CruiseNode *node);
  CruiseNode *treeMinimum(CruiseNode *node);
  CruiseNode *search(std::string shipname);
  CruiseNode *root;
};
#endif


int main()
{
  CruiseTree Cruises;
  int input_year;
  string input_shipname;
  int input_capacity;
  string input_destination;
  int input_length;
  int input_price;

  ifstream infile;
  infile.open("ships.txt");
  if(infile.good())
  {
    while(!infile.eof())
    {
      int choice;
      string shipname;
      bool run = true;
      while(run != false)
      {
        cout << "--- Main ---" << endl;
        cout << "1. Print Cruise Inventory" << endl;
        cout << "2. Find a Cruise" << endl;
        cout << "3. Add a Cruise" << endl;
        cout << "4. Delete a Cruise" << endl;
        cout << "5. Quit" << endl;
        cin >> choice;
        switch(choice)
        {
          case 1:
          {
            Cruises.printCruiseInventory();
            break;
          }

          case 2:
          {
            cout << "Enter Ship: " << endl;
            getline(cin, input_shipname);
            getline(cin, input_shipname);
            Cruises.findCruise(input_shipname);
            break;
          }

          case 3:
          {
            cout << "Enter Ship Info(Year, Name, Capacity, Destination, Length, Price): " << endl;
            string shipname = " ";
            getline(cin, shipname);
            getline(cin, shipname);
            Cruises.addCruise(input_year, input_shipname, input_capacity, input_destination, input_length, input_price);
            break;
          }

          case 4:
          {
            cout << "Enter Ship: " << endl;
            string shipname = " ";
            getline(cin, shipname);
            getline(cin, shipname);
            Cruises.deleteCruise(shipname);
            break;
          }

          case 5:
          {
            cout << "Bon Voyage!" << endl;
            run = false;
            break;
          }
        }
      }
      infile.close();
      return 0;
    }
  }
}
