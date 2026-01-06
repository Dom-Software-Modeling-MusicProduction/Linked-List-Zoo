#include <iostream>
#include <string>

using namespace std;

/**

 * It represents an animal with its name, age, species, and a pointer to the next animal in a linked list.
 */
struct Animal {
    string name;
    int age;
    string species;
    Animal* next;
};

//Create an animal pointer called head and initialize it to nullptr
Animal* head = nullptr; //pointer to first element in list; if the first element is none, the list is empty


void addAnimal();
void displayList();
void findOldestAnimal();
void processAnimalData();
void searchAnimal();
Animal* searchAnimalRecursive(Animal* current, const string& name);
void deleteList();
void deleteListRecursive(Animal* current);
void deleteAnimal();
void deleteAnimalRecursive(Animal* previous, Animal* current, const string& name);


/*
This function prompts the user for a name, age, and species, and adds a
new animal to the linked list.

If the linked list is empty, then this new animal is the 'head' of the 
list. Otherwise, it iterates through the list until it reaches the end,
then adds the new node.
*/
void addAnimal() { //asks the user for the name, the age, and species of the animal
    string name;
    int age;
    string species;
    cout << "Enter the name of the animal: ";
    cin >> name;
    cout << "Enter the age of the animal: ";
    cin >> age;
    cout << "Enter the species of the animal: ";
    cin >> species;

    //Create a new animal with the collected details
    Animal* newAnimal = new Animal{name, age, species, nullptr}; //create a new node dynamically
    //Set the new animal's next pointer to be a null pointer
    newAnimal->next = nullptr;
    //if the list is empty, make this the head
    if (head == nullptr) {
        head = newAnimal; //if the list is empty, make the head = newAnimal
    } else {
        /*if the list isn't empty, iterate through the list until 
        you reach the last node, then add the new node to the end*/
        Animal* current = head;
        while (current->next != nullptr)
            current = current->next;
        current->next = newAnimal;
    }

    cout << "Animal added successfully." << endl;
}

/*
This function will display all animals in the list.
If the list is empty, it prints out an error message, 
otherwise it prints out each node's information.
*/
void displayList() {
    
    if (head == nullptr) { //if the list is empy
        cout << "List empty." << endl;
        return;
    }
    Animal* current = head; //otherwise start at the head of the list
    while (current != nullptr) { //while the current animal is not nullptr, print it's fields and go to the next element
        cout << "Name: " << current->name << ", Age: " << current->age << ", Species: " << current->species << endl;
        current = current->next;
    }
}

/*
This function deletes an animal from the list (identified by name).
If the list is empty it reports an error, otherwise it checks to see 
if the head is supposed to be deleted. Otherwise, it calls deleteAnimalRecursive.

To delete a node from the linked list, you must take the following steps:
1) Get a pointer that temporarily points to the node to be deleted
2) Shift the previous node's 'next' attribute to the node after the one to be deleted.
For example, if you were deleting 'Bessy' from the list of Ali -> Bessy -> Chan, you 
need to move the Ali node's next attribute so it points to Chan (Ali -> Chan).
3) Delete the temporary pointer and report a successful delete
*/
void deleteAnimal() { //deletes one animal by name
    //Handle the empty list
    if (head == nullptr) {
        cout << "List empty. No animal to delete." << endl;
        return;
    }

    string name;
    cout << "Enter the name of the animal to delete: ";
    cin >> name;

    //If the head node is the one to be deleted,
    //delete it using the steps listed above and return
    if (head->name == name) {
        Animal* temp = head; //save temporary pointer
        head = head->next; //update the head to the next node
        delete temp; //delete the temporary pointer
        cout << "Animal deleted successfully." << endl;
        return;
    }

    //Call deleteAnimalRecursive
    deleteAnimalRecursive(nullptr, head, name);
}

/*
This recursive function searches for a named animal from the list to delete.
Each time deleteAnimalRecursive is called, there are 3 possibilities:
1) You have reached the end of the list, in which case the animal was not found;
report this message to the user.
2) The current node is the one to be deleted, so delete it using the 
same 3 step process for deleting a node that was used in deleteAnimal, 
and report that the animal was deleted successfully.
3) Move to the node after the current one.
*/
//void deleteAnimalRecursive(Animal* previous, Animal* current, const string& name) {
void deleteAnimalRecursive(Animal* previous, Animal* current, const string& name) { //recursively finds the animal to delete and deletes it
    
    if (current == nullptr) { //if the animal is not found
        cout << "Animal not found." << endl;
        return;
    }
    if (current->name == name) { //if it finds the animal to delete, delete it
        previous->next = current->next; //set the next element in the list to the current element
        delete current;
        cout << "Animal deleted successfully." << endl;
        return;
    }
    deleteAnimalRecursive(current, current->next, name); //otherwise recursively call the rest function again
}



/*
This function deletes all animals from the list. If the list is already empty,
it prints an error message.
Otherwise, it calls deleteListRecursive starting with the head node, then assigns the 
'head' variable to a null pointer and reports that it has deleted the list.
*/

void deleteList() { //deletes the entire linked list
   
    if (head == nullptr) { //if the list is empty, throw an error
        cout << "List already empty." << endl;
        return;
    }
    deleteListRecursive(head); //call the recursive function starting at the head
    head = nullptr; //after recursion returns, set the head = nullptr
    cout << "List deleted successfully." << endl;
}

/*
This recursive function first checks to see if the current node exists
(if not, terminate).
If it does, it makes a recursive call to itself using the next node, 
then deletes the current one.
*/

void deleteListRecursive(Animal* current) { //deletes animals from start to end using recursion
    
    if (current == nullptr){ //if the current element is nullptr, then stop
        return;
    }
    deleteListRecursive(current->next); //call the recursive function again
    delete current; //delete the current animal
}

/*
This function searches for an animal in the list to print its details.
If the list is empty, it reports this.
Otherwise, it asks the user for an animal's name, then searches
the list using searchAnimalRecursive.
If searchAnimalRecursive returns a null pointer, then it reports
the animal wasn't found. Otherwise, it uses the result of 
searchAnimalRecursive to print out the details.
*/
void searchAnimal() { 
    //Handle the empty list
    if (head == nullptr) {
        cout << "List empty." << endl;
        return;
    }

    string name;
    cout << "Enter the name of the animal to search for: ";
    cin >> name;

    //Call searchAnimalRecursive and assign it to a pointer
    Animal* result = searchAnimalRecursive(head, name); 
    
    //If the animal was found, print its details, otherwise
    //print an error
    if (result != nullptr) {
        cout << "Name: " << result->name << ", Age: " << result->age << ", Species: " << result->species << endl;
    } 
    else {
        cout << "Animal not found." << endl;
    }
}

/*
This function searches the linked list recursively to find the named animal.
If the current node doesn't exist, it returns a null pointer. 
Otherwise if the name matches, it returns the current node.
Otherwise it makes a recursive call to itself using the next node.
*/

Animal* searchAnimalRecursive(Animal* current, const string& name) { //recursively search list
    
    if (current == nullptr){ 
        return nullptr;
    }
    if (current->name == name){ //if the name matches the current animal at that index
        return current; //return the current animal
    }
    return searchAnimalRecursive(current->next, name); //else recursively call the next element in the list
}

/*
This is a non-recursive function to collect aggregate data about the animals.
If the list is empty, it reports this and returns immediately. 
Otherwise, it uses a loop to iterate through each node, adding to the count
of animals and the total age of all animals.
It uses these numbers to output the total number of animals and their average
age.
*/
void processAnimalData() { 
    //Handle the empty list
    if (head == nullptr) {
        cout << "The list is empty." << endl;
        return;
    }

    int totalAge = 0;
    int animalCount = 0;

    //Iterate through the list and add to the totalAge and
    //animalCount
    Animal* current = head; //set the current animal as a pointer to the head of the list
    while (current != nullptr) { //while current animal is not the end
        totalAge += current->age; //adds up to the total age
        animalCount++; //adds to the animal count
        current = current->next; //process the next element
    }

    double averageAge = static_cast<double>(totalAge) / animalCount;
    
    cout << "Total animals: " << animalCount << endl;
    cout << "Average age: " << averageAge << endl;
}

/*
This non-recursive function searches for the oldest animal in the list
and provides its details. 
If the list is empty, it reports this and returns immediately.
Otherwise, it tracks the oldestAnimal as it iterates through the list
using a loop. 
Once it has been through the entire list, it reports the oldest animal.
*/
void findOldestAnimal() { 
    
    if (head == nullptr) {
        cout << "The list is empty." << endl;
        return;
    }

    //Assume the initial oldest animal is the head node
    Animal* oldest = head; //oldest is a pointer to the current oldest animal

    //Iterate through the other nodes, and update 
    //your variable[s] if you find an older animal
    Animal* current = head->next; //set the animal pointer to the next element in the list
    while (current != nullptr) { //while the pointer is not null (current is a pointer that moves through the list an element at a time)
        if (current->age > oldest->age){ //if the current animal's age is greater than the previously defined older age
            oldest = current; 
        }
        current = current->next; //process next element
    }

    //Print out the oldest animal
    cout << "Name: " << oldest->name << ", Age: " << oldest->age << ", Species: " << oldest->species << endl;
}

int main() {
    int choice;

    do {
        cout << "Menu:" << endl;
        cout << "1. Add an animal" << endl;
        cout << "2. Delete an animal" << endl;
        cout << "3. Display list of animals" << endl;
        cout << "4. Search for an animal" << endl;
        cout << "5. Process animal data" << endl;
        cout << "6. Find the oldest animal" << endl;
        cout << "7. Delete the entire list" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addAnimal();
                break;
            case 2:
                deleteAnimal();
                break;
            case 3:
                displayList();
                break;
            case 4:
                searchAnimal();
                break;
            case 5:
                processAnimalData();
                break;
            case 6:
                findOldestAnimal();
                break;
            case 7:
                deleteList();
                break;
            case 8:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    } while (choice != 8);

    return 0;
}
