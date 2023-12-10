#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class User {
private:
    string username;
    string password;
    string email;
    int birthYear;

public:
    User(const string& uname, const string& pwd, const string& mail, int year)
        : username(uname), password(pwd), email(mail), birthYear(year) {}

    const string& getUsername() const {
        return username;
    }

    const string& getEmail() const {
        return email;
    }

    int getBirthYear() const {
        return birthYear;
    }

    // Function to display user information (excluding password)
    void displayUserInfo() const {
        cout << left << setw(20) << "| " + username
                  << setw(30) << "| " + email
                  << setw(15) << "| " + to_string(birthYear) + " |" << endl;
    }

    bool checkPassword(const string& pwd) const {
        return password == pwd;
    }

    // Function to change user password
    void changePassword(const string& newPassword) {
        password = newPassword;
    }
};

class AuthenticationSystem {
private:
    vector<User> users;

public:
    bool registerUser() {
        string username, password, email;
        int birthYear;

        // Input username
        cout << "Enter username: ";
        cin >> username;

        // Check if the username is already taken
        for (const User& user : users) {
            if (user.getUsername() == username) {
                cout << "Username is already taken. Please choose another one." << endl;
                return false;
            }
        }

        // Input email
        cout << "Enter email: ";
        cin >> email;

        // Input birth year
        cout << "Enter birth year: ";
        cin >> birthYear;

        // Input password
        cout << "Enter password: ";
        cin >> password;

        // If not taken, create a new user and add it to the vector
        users.emplace_back(username, password, email, birthYear);
        cout << "Registration successful for user: " << username << endl;
        return true;
    }

    bool loginUser() {
        string username, password;

        // Input username
        cout << "Enter username: ";
        cin >> username;

        // Find the user with the given username
        for (const User& user : users) {
            if (user.getUsername() == username) {
                // Input password
                cout << "Enter password: ";
               	cin >> password;

                // Check if the entered password matches the user's password
                if (user.checkPassword(password)) {
                    cout << "Login successful. Welcome, " << username << "!" << endl;
                    return true;
                } else {
                    cout << "Incorrect password. Please try again." << endl;
                    return false;
                }
            }
        }

        // If the username is not found
        cout << "User not found. Please check your username." << endl;
        return false;
    }

  	void displayUserList() const {
        // Print table header with border
        cout << setw(70) << setfill('-') << "-" << setfill(' ') << endl;
        cout << left << setw(20) << "| Username"
                  << setw(30) << "| Email"
                  << setw(15) << "| Birth Year |" << endl;
        cout << setw(70) << setfill('-') << "-" << setfill(' ') << endl;

        // Print user information
        for (const User& user : users) {
            user.displayUserInfo();
        }

        // Print table footer with border
        cout << setw(70) << setfill('-') << "-" << setfill(' ') << endl;
    }
    
    // Function to change user password
    void changeUserPassword() {
        string username, currentPassword, newPassword;

        // Input username
        cout << "Enter username: ";
        cin >> username;

        // Find the user with the given username
        for (User& user : users) {
            if (user.getUsername() == username) {
                // Input current password
                cout << "Enter current password: ";
                cin >> currentPassword;

                // Check if the entered current password matches the user's password
                if (user.checkPassword(currentPassword)) {
                    // Input new password
                    cout << "Enter new password: ";
                    cin >> newPassword;

                    // Change user password
                    user.changePassword(newPassword);
                    cout << "Password changed successfully for user: " << username << std::endl;
                    return;
                } else {
                    cout << "Incorrect current password. Password change failed." << std::endl;
                    return;
                }
            }
        }

        // If the username is not found
        cout << "User not found. Please check your username." << endl;
    }
};

int main() {
    AuthenticationSystem authSystem;
    int choice;

    do {
        // Display menu
        cout << "Menu:" << endl;
        cout << "1. Register\n2. Login\n3. Display User List\n4. Change Password\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                authSystem.registerUser();
                break;
            case 2:
                authSystem.loginUser();
                break;
            case 3:
                authSystem.displayUserList();
                break;
            case 4:
                authSystem.changeUserPassword();
                break;
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
