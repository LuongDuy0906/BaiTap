#include <iostream>
#include <ctime>//ham time()
#include <cstdlib>// ham srand(), rand()
#include <string>
#include <unordered_map>//ham unordered_map()

using namespace std;

// khoi tao lop nguoi choi
class Player {
	private:
	    string username;
	
	public:
	    Player(const string& name) : username(name) {}
	
	    const string& getUsername() const {
	        return username;
	    }
	
	    virtual int getChoice() const = 0;
	    virtual ~Player() {}
};

// khoi tao lop ngui choi(player) 
class HumanPlayer : public Player {
	public:
	    HumanPlayer(const string& name) : Player(name) {}
		
		//ham lua chon cua nguoi choi
	    int getChoice() const override {
	        int choice;
	        do {
	            cout << getUsername() << ", Choice: 1 (Scissor), 2 (Rock), 3 (Paper): ";
	            cin >> choice;
	
	            if (choice < 1 || choice > 3) {
	                cout << "Invalid choice! Please choose again." << endl;
	            }
	
	        } while (choice < 1 || choice > 3);
	
	        return choice;
	    }
};

//khoi tao lop nguoi choi(system)
class ComputerPlayer : public Player {
	public:
	    ComputerPlayer() : Player("System") {}
	
	    int getChoice() const override {
	        return rand() % 3 + 1;  // Chon ngau nhien 1, 2 hoac 3
	    }
};

// khoi tao lop quan li tai khoan nguoi choi
class PlayerManager {
	private:
	    unordered_map<string, string> playerCredentials;// bang bam lu tru thong tin nguoi choi(player)
	    unordered_map<string, Player*> players;//bang bam lu tru danh sach nguoi choi(player)
	
	public:
		//ham huy nguoi choi(system)
	    ~PlayerManager() {
	        for (auto& pair : players) {
	            delete pair.second;
	        }
	    }
	
		//ham dang nhap
	    Player* login() {
	        string username;
	        string password;
	
	        cout << "Player name: ";
	        cin >> username;
	        cout << "Password: ";
	        cin >> password;
	
	        auto it = players.find(username);//t dong tim ten nguoi choi(player)
	        if (it != players.end() && playerCredentials[username] == password) {
	            cout << "Sign in success for: " << username << endl;
	            return it->second;
	        } else {
	            cout << "Player name or password incorrect." << endl;
	            return nullptr;
	        }
	    }
	
		//ham dang ki
	    bool registerPlayer() {
	        string username;
	        string password;
	
	        cout << "Player name: ";
	        cin >> username;
	        cout << "Passwword: ";
	    	cin >> password;
	
	        auto it = players.find(username);
	        if (it != players.end()) {
	            cout << "Player has already create, sign up failed." << endl;
	            return false;
	        } else {
	            cout << "Sign up success for: " << username << endl;
	            playerCredentials[username] = password;
	
	            // Tao nguoi choi moi va them vao danh sach
	            Player* newPlayer = new HumanPlayer(username);
	            players[username] = newPlayer;
	
	            return true;
	        }
	    }
	
		//ham hien thi cac lua chon
	    void showMenu() {
	        cout << "Choice:" << endl;
	        cout << "1. Sign Up" << endl;
	        cout << "2. Sign In" << endl;
	        cout << "3. Exit" << endl;
	    }
};

//khoi tao lop tro choi
class Game {
	private:
	    int winCountPlayer1;//so lan nguoi choi(player) thang
	    int winCountPlayer2;//so lan nguoi choi(system) thang
	
	public:
	    Game() : winCountPlayer1(0), winCountPlayer2(0) {}
		
		//ham hoat dong cua tro choi
	    void play(Player* player1, Player* player2) {
	        int choice1 = player1->getChoice();
	        int choice2 = player2->getChoice();
	
	        cout << "Player choice: " << choice1 << endl;
	       	cout << "System choice: " << choice2 << endl;
	
	        if (choice1 == choice2) {
	            cout << "Draw!" << endl;
	        } else if ((choice1 == 1 && choice2 == 3) ||
	                   (choice1 == 2 && choice2 == 1) ||
	                   (choice1 == 3 && choice2 == 2)) {
	            cout << "Player Win!" << endl;
	            ++winCountPlayer1;
	        } else {
	            cout << "System Win!" << endl;
	            ++winCountPlayer2;
	        }
	    }
	
		//ham in ket qua
	    void printSummary() const {
	        cout << "Result:" << endl;
	        cout << "Player win " << winCountPlayer1 << " time." << endl;
	        cout << "System win " << winCountPlayer2 << " time." << endl;
	    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    PlayerManager playerManager;
    Game game;

    bool exitProgram = false;
    while (!exitProgram) {
        playerManager.showMenu();
        int choice;
        
        //lua chun
        cout << "Type your choice: ";
        cin >> choice;

        Player* player1 = nullptr;
        switch (choice) {
            case 1:
                playerManager.registerPlayer();
                break;
            case 2:
                player1 = playerManager.login();
                if (player1 != nullptr) {
                    Player* player2 = new ComputerPlayer();
                    for (int i = 0; i < 3; ++i) {
                        cout << "Game " << i + 1 << endl;
                        game.play(player1, player2);
                        cout << "----------------------------------------" << endl;
                    }
                    
                    game.printSummary();
                    
                    //bao ton dung luong
                    delete player2;
                }
                break;
            case 3:
                exitProgram = true;
                break;
            default:
                cout << "Invalid choice! Please choose again." << endl;
        }
    }

    return 0;
}

