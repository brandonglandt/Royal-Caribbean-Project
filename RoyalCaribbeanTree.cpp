#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct CruiseNode
{
  int year;
  string shipname;
  int capacity;
  string destination;
  int length;
  int price;

  CruiseNode *parent;
  CruiseNode *left;
  CruiseNode *right;

  CruiseNode() {};

  CruiseNode(int year, string shipname, int capacity, string destination, int length, int price)
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
  void addCruise(int year, string shipname, int capacity, string destination, int length, int price);
  //void minValueNode(struct Node* node);
  void deleteCruise(string shipname);
  void findCruise(string shipname);
private:
  void iterateTree(CruiseNode *node);
  void postOrderDelete(CruiseNode *node);
  CruiseNode *treeMinimum(CruiseNode *node);
  CruiseNode *search(string shipname);
  CruiseNode *root;
};

CruiseTree::CruiseTree()
{
  root = NULL;
}

CruiseTree::~CruiseTree()
{
  //postOrderDelete(root);
}

void CruiseTree::iterateTree(CruiseNode *node)
{
    if(node != NULL)
    {
      iterateTree(node -> left);
      cout << node -> year << " " << node -> shipname << node -> capacity << node -> destination << node -> length << node -> price << endl;
      iterateTree(node -> right);
    }
}

void CruiseTree::printCruiseInventory()
{
  iterateTree(root);
}

void CruiseTree::addCruise(int year, string shipname, int capacity, string destination, int length, int price)
{
  CruiseNode *addCruise = new CruiseNode();
  addCruise -> year = year;
  addCruise -> shipname = shipname;
  addCruise -> capacity = capacity;
  addCruise -> destination = destination;
  addCruise -> length = length;
  addCruise -> price = price;

  addCruise -> parent = NULL;
  addCruise -> left = NULL;
  addCruise -> right = NULL;
  if(root == NULL)
  {
    root = addCruise;
  }
  else
  {
    CruiseNode *temp = root;
    while(temp != NULL)
    {
       if(shipname.compare(temp -> shipname) < 0)
       {
         if(temp -> left != NULL)
         {
           temp = temp -> left;
         }
         else
         {
           temp -> left = addCruise;
           addCruise -> parent = temp;
           temp = NULL;
         }
       }
       else
       {
         if(temp -> right != NULL)
         {
           temp = temp -> right;
         }
         else
         {
           temp -> right = addCruise;
           addCruise -> parent = temp;
           temp = NULL;
         }
       }
    }
  }
}

void postOrderDelete(CruiseNode *node)
{
  if(node == NULL)
  {
    return;
  }
  postOrderDelete(node -> left);
  postOrderDelete(node -> right);
  delete node;
  //root = NULL;
}

void CruiseTree::deleteCruise(string shipname)
{
  CruiseNode *current = root;
  while(current != NULL)
  {
    if(current -> shipname == shipname)
    {
      break;
    }
    else if(shipname < current -> shipname)
    {
      current = current -> left;
    }
    else
    {
      current = current -> right;
    }
  }

  if(current == NULL)
  {
    cout << "Cruise " << shipname << " lost at sea" << endl;
    return;
  }
  if(current -> left == NULL && current -> right == NULL)
  {
    if(current == root)
    {
      root = NULL;
    }
    else
    {
      if(current -> parent -> left == current)
      {
        current -> parent -> left = NULL;
      }
      else
      {
        current -> parent -> right = NULL;
      }
    }
    delete current;
  }
  else if(current -> left == NULL && current -> right != NULL)
  {
    if(current == root)
    {
      root = current -> right;
    }
    else
    {
      if(current -> parent -> left == current)
      {
        current -> parent -> left = current -> right;
      }
      else
      {
        current -> parent -> right = current -> right;
      }
    }

    current -> right -> parent = current -> parent;
    delete current;
  }
  else if(current -> left != NULL && current -> right == NULL)
  {
    if(current == root)
    {
      root = current -> left;
    }
    else
    {
      if(current -> parent -> left == current)
      {
        current -> parent -> left = current -> left;
      }
      else
      {
        current -> parent -> right = current -> left;
      }
    }
    current -> left -> parent = current -> parent;
    delete current;
  }
  else
  {
    CruiseNode *succ = current -> right;
    while(succ -> left != NULL)
    {
      succ = succ -> left;
      CruiseNode copy = *succ;
      deleteCruise(succ -> shipname);
      current -> year = copy.year;
      current -> shipname = copy.shipname;
      current -> capacity = copy.capacity;
      current -> destination = copy.destination;
      current -> length = copy.length;
      current -> price = copy.price;
    }
  }
}

void CruiseTree::findCruise(string shipname)
{
  CruiseNode *findCruise = search(shipname);
  if(findCruise == NULL)
  {
    cout << "Cruise not found." << endl;
    return;
  }
  cout << "Cruise Itinerary: " << endl;
  cout << "Ship Name: " << findCruise -> shipname << endl;
  cout << "Year Ship Built: " << findCruise -> year << endl;
  cout << "Capacity of Ship: " << findCruise -> capacity << endl;
  cout << "Destination: " << findCruise -> destination << endl;
  cout << "Length of Cruise: " << findCruise -> length << endl;
  cout << "Price: " << findCruise -> price << endl;
}

CruiseNode* CruiseTree::search(string shipname)
{
  CruiseNode *findCruise = new CruiseNode;
  findCruise = root;
  while(findCruise != NULL)
  {
    if(shipname.compare(findCruise -> shipname) < 0)
    {
      findCruise = findCruise -> left;
    }
    else if(shipname.compare(findCruise -> shipname ) > 0)
    {
      findCruise = findCruise -> right;
    }
    else if(shipname.compare(findCruise -> shipname) == 0)
    {
      break;
    }
  }
  return findCruise;
}

int main()
{
  CruiseTree cruiseTree;
  ifstream infile;
  string a;
  int year;
  string shipname;
  int capacity;
  string destination;
  int length;
  int price;
  infile.open("ships.txt");
  if(infile.good())
  {
    while(getline(infile, a))
    {
      vector<string> result;
      istringstream iss(a);
      for (string s; iss >> s;)
      {
        result.push_back(s);
      }

      year = stoi(result.at(0));
      cout << year << endl;

      shipname = result.at(1);
      cout << shipname << endl;

      capacity = stoi(result.at(2));
      cout << capacity << endl;

      destination = result.at(3);
      cout << destination << endl;

      length = stoi(result.at(4));
      cout << length << endl;

      price = stoi(result.at(5));
      cout << price << endl;
      cout << "\n\n" << endl;

    }
  }
  int choice;
  char ch;
  bool run = true;
  while(run != false)
  {
    cout << "-- Look at the cruises offered above and enter the info of the ones you like --" << endl;
    cout << "1. Print Cruise Inventory" << endl;
    cout << "2. Find a Cruise" << endl;
    cout << "3. Add a Cruise" << endl;
    cout << "4. Delete a Cruise" << endl;
    cout << "5. Book Cruise" << endl;
    cin >> choice;
    switch(choice)
    {
      case 1:
      {
        cruiseTree.printCruiseInventory();
        break;
      }

      case 2:
      {
        cout << "Enter All Ship Info: " << endl;
        getline(cin, shipname);
        getline(cin, shipname);
        cruiseTree.findCruise(shipname);
        break;
      }

      case 3:
      {
        cout << "Enter All Ship Info: " << endl;
        string shipname = " ";
        getline(cin, shipname);
        getline(cin, shipname);
        cruiseTree.addCruise(year, shipname, capacity, destination, length, price);
        break;
      }

      case 4:
      {
        cout << "Enter All Ship Info: " << endl;
        string shipname = " ";
        getline(cin, shipname);
        getline(cin, shipname);
        cruiseTree.deleteCruise(shipname);
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
  getchar();
  infile.close();
  return 0;
}
