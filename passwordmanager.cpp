#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class EncryptionManager
{
public:
    string encrypt(string text)
    {
        for (int i = 0; i < (int)text.size(); i++)
            text[i] = text[i] + 3;
        return text;
    }
    string decrypt(string text)
    {
        for (int i = 0; i < (int)text.size(); i++)
            text[i] = text[i] - 3;
        return text;
    }
};

class Credential
{
public:
    string website, username, password;

    Credential(string w, string u, string p)
    {
        website = w;
        username = u;
        password = p;
    }
};

class User
{
public:
    string username = "Saad";
    string password = "1234";
};

class StorageManager
{
public:
    void save(vector<Credential> &list)
    {
        ofstream f("passwords.txt");
        for (int i = 0; i < (int)list.size(); i++)
            f << list[i].website << " " << list[i].username << " " << list[i].password << "\n";
        f.close();
    }

    void load(vector<Credential> &list)
    {
        list.clear();
        ifstream f("passwords.txt");
        string w, u, p;
        while (f >> w >> u >> p)
            list.push_back(Credential(w, u, p));
        f.close();
    }

    void log(string msg)
    {
        ofstream f("log.txt", ios::app);
        time_t now = time(0);
        string t = ctime(&now);
        t.pop_back(); // remove newline
        f << "[" << t << "] " << msg << "\n";
        f.close();
    }

    void saveLastLogin(string user)
    {
        ofstream f("lastlogin.txt");
        time_t now = time(0);
        string t = ctime(&now);
        t.pop_back();
        f << user << " at " << t << "\n";
        f.close();
    }

    string getLastLogin()
    {
        ifstream f("lastlogin.txt");
        string line = "No record found";
        getline(f, line);
        return line;
    }

    void showLogs()
    {
        ifstream f("log.txt");
        vector<string> lines;
        string line;
        while (getline(f, line))
            lines.push_back(line);
        f.close();

        int start = max(0, (int)lines.size() - 5);
        for (int i = start; i < (int)lines.size(); i++)
            cout << "  " << lines[i] << "\n";
    }
};

class PasswordManagerSystem
{

    User master;
    vector<Credential> list;
    EncryptionManager enc;
    StorageManager store;

public:
    PasswordManagerSystem()
    {
        store.load(list);
    }

    bool login()
    {
        string u, p;
        int tries = 0;

        while (tries < 3)
        {
            cout << "\nUsername : ";
            cin >> u;
            cout << "Password : ";
            cin >> p;

            if (u == master.username && p == master.password)
            {
                cout << "\nWelcome, " << u << "!\n";
                store.log("Login successful - " + u);
                store.saveLastLogin(u);
                return true;
            }

            tries++;
            store.log("Wrong login attempt");
            cout << "Incorrect! Attempts left: " << 3 - tries << "\n";
        }

        cout << "\nAccount locked! Too many wrong attempts.\n";
        store.log("Account LOCKED");
        return false;
    }

    void addPassword()
    {
        string w, u, p;
        cout << "\nWebsite  : ";
        cin >> w;
        cout << "Username : ";
        cin >> u;
        cout << "Password : ";
        cin >> p;
        list.push_back(Credential(w, u, enc.encrypt(p)));
        store.save(list);
        store.log("Added: " + w);
        cout << "Saved!\n";
    }

    void viewPasswords()
    {
        if (list.empty())
        {
            cout << "\nNothing saved yet!\n";
            return;
        }
        cout << "\n--- Your Passwords ---\n";
        for (int i = 0; i < (int)list.size(); i++)
        {
            cout << i + 1 << ". " << list[i].website << "\n";
            cout << "   Username : " << list[i].username << "\n";
            cout << "   Password : " << enc.decrypt(list[i].password) << "\n\n";
        }
    }

    void updatePassword()
    {
        viewPasswords();
        if (list.empty())
            return;
        int n;
        cout << "Which number to update? ";
        cin >> n;
        if (n < 1 || n > (int)list.size())
        {
            cout << "Invalid!\n";
            return;
        }
        string np;
        cout << "New password: ";
        cin >> np;
        list[n - 1].password = enc.encrypt(np);
        store.save(list);
        store.log("Updated: " + list[n - 1].website);
        cout << "Done!\n";
    }

    void deletePassword()
    {
        viewPasswords();
        if (list.empty())
            return;
        int n;
        cout << "Which number to delete? ";
        cin >> n;
        if (n < 1 || n > (int)list.size())
        {
            cout << "Invalid!\n";
            return;
        }
        store.log("Deleted: " + list[n - 1].website);
        list.erase(list.begin() + n - 1);
        store.save(list);
        cout << "Deleted!\n";
    }

    void showReport()
    {
        cout << "\n--- Report ---\n";
        cout << "Total accounts : " << list.size() << "\n";
        cout << "Last login     : " << store.getLastLogin() << "\n";
        cout << "\nRecent activity:\n";
        store.showLogs();
    }

    void run()
    {
        cout << "==============================\n";
        cout << "    Secure Password Manager\n";
        cout << "==============================\n";
        cout << "(username: Saad | password: 1234)\n";

        if (!login())
            return;

        int ch;
        do
        {
            cout << "\n--- Menu ---\n";
            cout << "1. Add password\n";
            cout << "2. View passwords\n";
            cout << "3. Update password\n";
            cout << "4. Delete password\n";
            cout << "5. Report\n";
            cout << "6. Exit\n";
            cout << "Choice: ";
            cin >> ch;

            if (ch == 1)
                addPassword();
            else if (ch == 2)
                viewPasswords();
            else if (ch == 3)
                updatePassword();
            else if (ch == 4)
                deletePassword();
            else if (ch == 5)
                showReport();

        } while (ch != 6);

        store.log("Logged out");
        cout << "Bye!\n";
    }
};

int main()
{
    PasswordManagerSystem pm;
    pm.run();
    return 0;
}