#include <iostream>
using namespace std;

struct Player
{
    string username;
    string password;
    int level;
};

int main()
{
    struct Player user = {"detayuli", "halo5678", 5};
    struct Player *ptr = &user;

    printf ("Username : %s\nPassword : %s\nLevel : %d", user.username.c_str(), user.password.c_str(), user.level);
    return 0;
}

