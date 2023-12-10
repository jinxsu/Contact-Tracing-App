// Final Project ( Contact Tree implementation).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <string>
#include <deque>

using namespace std;
typedef string String;


struct TreeNode
{
    string medicareID;
    int directContact = 0;//direct children
    int totalCase = 1;//all children and descendants
    TreeNode* parentPtr;
    list<TreeNode*>directContactList;//list of pointers to the child of every node
    TreeNode(const String& medID) { medicareID = medID; parentPtr = nullptr; };
    TreeNode(TreeNode* parentPtr, const String& medID) { medicareID = medID; parentPtr = parentPtr; };
};
class ContactTree
{
public:
	ContactTree();
	~ContactTree();
    bool IsEmpty();
    int GetSize();
    void AddPatient0(const String&);
    void AddContact(const String&,const String&);
    TreeNode* LookUpContact(const String&);
    void DeleteContact(const String&);
    void DisplayContact(const String&);
    void DisplayContact(TreeNode*);
    void TraceSource(const String&);
    void PrintContactCases(const String&);
    void PrintContactTree();
    void PrintHierarchicalTree();//recursive

private:
    TreeNode* root;
    int size;
};

ContactTree::ContactTree()
{
    root = nullptr;
    size = 0;
}

ContactTree::~ContactTree()
{
    
    DeleteContact(root->medicareID);
   
}
bool ContactTree::IsEmpty()
{
    if (GetSize() == 0 || root==nullptr)
        return true;
    else
        return false;
}
int ContactTree::GetSize()
{
    return this->size;
}
void ContactTree::AddPatient0(const String& medID)
{
    TreeNode* patient0 = new TreeNode(medID);
    this->root = patient0;
    
    size++;
}
void ContactTree::AddContact(const String& parent, const String& medID)
{
    cout << "IN AddContact" << endl;
    //TreeNode* parentPtr;//TreeNode* parentPtr=this->lookUpContact(parent)
    TreeNode* lookupParentPtr = LookUpContact(parent);// michelle corrected 
    cout << lookupParentPtr << endl;
    if ( lookupParentPtr == nullptr)
    {
        cout << "Contact not found" << endl;
        return;
    }
    //parentPtr = this->LookUpContact(parent);
    TreeNode* contactPtr = new TreeNode(lookupParentPtr, medID);
    lookupParentPtr->directContactList.push_back(contactPtr);
    lookupParentPtr->directContact++;
 while (lookupParentPtr != nullptr)
 {
    lookupParentPtr->totalCase++;
    lookupParentPtr = lookupParentPtr->parentPtr;
    
 }
    
    size++;
    
}
TreeNode* ContactTree::LookUpContact(const String& medicareID)
{
    cout << " In Lookup" << endl; 
    deque<TreeNode*> contacts;
    contacts.push_back(root);
 
    while (!contacts.empty())
    {
        cout << " In Lookup1" << endl;
        if (contacts.front()->medicareID==medicareID)
        {
            cout << " In Lookup2" << endl;
            return contacts.front();
        }
            cout << " In Lookup3" << endl;

            for (list<TreeNode*>::iterator iterator = contacts.front()->directContactList.begin(); iterator != contacts.front()->directContactList.end(); ++iterator)
            {   
                cout << " In Lookup4: " << (*iterator)->medicareID << endl;
                contacts.push_back(*iterator);
                
                
               
            }
            contacts.pop_front();

            if (contacts.empty())
            {
                cout << "Deque is empty" << endl;
                return nullptr;
            }
           
    }
    return nullptr;
    
}
void ContactTree::DeleteContact(const String& medID)
{
    TreeNode* contact = this->LookUpContact(medID);
    deque<TreeNode*>contacts;
    
    if ( contact== nullptr)
    {
        cout << "Contact not found" << endl;
        return;
    }
    contacts.push_back(contact);
    while (!contacts.empty())
    {
        for (list<TreeNode*>::iterator iterator = contacts.front()->directContactList.begin(); iterator != contacts.front()->directContactList.end(); ++iterator)
        {


            //push the children 
            contacts.push_back(*iterator);
            //push the children's children
            //continue until there is no element left
            



        }
        //delete the first element 
        contacts.pop_front();
        size--;
    }
    
    contact->parentPtr->directContact--;
    while (contact!=nullptr)
    {
        contact->parentPtr->totalCase--;
        contact->parentPtr = contact->parentPtr->parentPtr;
    }
    if (contacts.empty())
    {
        cout << "The deque is empty" << endl;
        return;
    }

}
void ContactTree::DisplayContact(const String& contactID)
{
    TreeNode* temp = LookUpContact(contactID);
    
    if (temp!= nullptr)
    {
        DisplayContact(temp);
    }
    else
    {
        cout << "Contact Not Found" << endl;
    }
}
void ContactTree::DisplayContact(TreeNode*contactPtr)
{
    cout << contactPtr->medicareID << endl;
    cout << contactPtr->directContact << endl;
    cout << contactPtr->totalCase << endl; 

}
void ContactTree::TraceSource(const String& contact)
{
    TreeNode* contactPtr = LookUpContact(contact);
    
    if (contactPtr== nullptr)
    {
        cout << "Contact not found" << endl;
        return;
    }
    do
    {
        DisplayContact(contactPtr->parentPtr);
        

    } while (contactPtr!=nullptr);
    
    
}
void ContactTree::PrintContactCases(const String& contactID)
{
    TreeNode* contactPtr = LookUpContact(contactID);
    
    
    if (contactPtr != nullptr)
    {
        for (list<TreeNode*>::iterator iterator = contactPtr->directContactList.begin(); iterator != contactPtr->directContactList.end(); ++iterator)
        {
            DisplayContact(*iterator);
        }
    }
    else
    {
        cout << "Contact Not Found" << endl;
        return;
    }
}
void ContactTree::PrintContactTree()
{
    
    deque<TreeNode*> contactTree;
    if (contactTree.empty())
    {
        cout << "The Tree is empty" << endl;
    }
    for (list<TreeNode*>::iterator iterator = contactTree.front()->directContactList.begin(); iterator != contactTree.front()->directContactList.end(); ++iterator)
    {
        DisplayContact(*iterator);
    }
}
void ContactTree::PrintHierarchicalTree()
{

}


int main()
{
    ContactTree patient = ContactTree();
    cout << "Creating patient 0" << endl;
    patient.AddPatient0("12345");
    cout << "Adding Contact" << endl;
    patient.AddContact("12345", "6789");
        //consoles stops here;
    cout << "Adding Contact" << endl;
    patient.AddContact("000000", "2345");
    cout << "Displaying cases" << endl;
    patient.DisplayContact("12345");
    patient.PrintContactCases("6789");
    cout << "Printing contact Tree: " << endl;
    patient.PrintContactTree();

    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
