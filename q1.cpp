#include <iostream>
#include <cassert>
#include "header.h"

// Define non-primitive classes
class Person {
public:
    Person() : id(0), name("") {}
    Person(int id, std::string name) : id(id), name(name) {}
    int getId() const { return id; }
    std::string getName() const { return name; }

private:
    int id;
    std::string name;
};

class ContactInfo {
public:
    ContactInfo() : email(""), phone("") {}
    ContactInfo(std::string email, std::string phone) : email(email), phone(phone) {}

    std::string getEmail() const { return email; }
    std::string getPhone() const { return phone; }

private:
    std::string email;
    std::string phone;
};

int main() {
    QuartenarySearchTree<int, Person> personTree;
    QuartenarySearchTree<int, ContactInfo> contactTree;

    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1. Insert Person\n";
        std::cout << "2. Insert Contact Info\n";
        std::cout << "3. Search Person\n";
        std::cout << "4. Search Contact Info\n";
        std::cout << "5. Delete Person\n";
        std::cout << "6. Delete Contact Info\n";
        std::cout << "7. Print Preorder\n";
        std::cout << "8. Print Postorder\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (!(std::cin >> choice)) {
                // Invalid input, clear the input stream and ignore the input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw InvalidChoiceException();
        }

        
        if (choice < 1 || choice > 9) {
                throw InvalidChoiceException();
        }

        if (choice == 9) {
                std::cout << "Exiting program...\n";
                break; // Exit the loop
        }

        switch (choice) {
            case 1: {
                int id;
                std::string name;
                std::cout << "Enter Person ID: ";
                std::cin >> id;
                std::cout << "Enter Person Name: ";
                std::cin >> name;
                personTree.insert(id, Person(id, name));
                break;
            }
            case 2: {
                int id;
                std::string email, phone;
                std::cout << "Enter Person ID: ";
                std::cin >> id;
                std::cout << "Enter Email: ";
                std::cin >> email;
                std::cout << "Enter Phone: ";
                std::cin >> phone;
                contactTree.insert(id, ContactInfo(email, phone));
                break;
            }
            case 3: {
                int id;
                std::cout << "Enter Person ID to search: ";
                std::cin >> id;
                Person person = personTree.search(id);
                std::cout << "Person ID: " << person.getId() << ", Name: " << person.getName() << std::endl;
                break;
            }
            case 4: {
                int id;
                std::cout << "Enter Person ID to search: ";
                std::cin >> id;
                ContactInfo contactInfo = contactTree.search(id);
                std::cout << "Email: " << contactInfo.getEmail() << ", Phone: " << contactInfo.getPhone() << std::endl;
                break;
            }
            case 5: {
                int id;
                std::cout << "Enter Person ID to delete: ";
                std::cin >> id;
                assert(personTree.deleteKey(id) && "Person not found");
                break;
            }
            case 6: {
                int id;
                std::cout << "Enter Person ID to delete: ";
                std::cin >> id;
                assert(contactTree.deleteKey(id) && "Contact Info not found");
                break;
            }
            case 7:
                std::cout << "Preorder traversal of Person Tree: ";
                personTree.printPreorder();
                std::cout << "Preorder traversal of Contact Info Tree: ";
                contactTree.printPreorder();
                break;
            case 8:
                std::cout << "Postorder traversal of Person Tree: ";
                personTree.printPostorder();
                std::cout << "Postorder traversal of Contact Info Tree: ";
                contactTree.printPostorder();
                break;
            case 9:
                std::cout << "Exiting program...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
        } catch (const InvalidChoiceException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const ElementNotFoundException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    

    return 0;
}
  