#include <bits/stdc++.h>
using namespace std;

class Role
{
public:
    string role;
    vector<string> names;
    vector<Role *> subRoles;
    Role(string roleName)
    {
        this->role = roleName;
    }
};

Role *root = NULL;

Role *searchRole(string targetRole)
{
    queue<Role *> q;
    if (root->role == targetRole)
        return root;
    if (root->subRoles.size() > 0)
    {
        for (auto i : root->subRoles)
            q.push(i);
    }
    int count = q.size();
    while (count)
    {
        if (q.front()->role == targetRole)
            return q.front();
        if (q.front()->subRoles.size() > 0)
        {
            for (auto i : q.front()->subRoles)
                q.push(i);
        }
        q.pop();
        if (count = 0)
        {
            cout << endl;
            count = q.size();
        }
        count--;
    }
    Role *temp = NULL;
    return temp;
}

void Subrole()
{
    string subRoleName, reportingRoleName;
    cout << "Enter Sub role name:";
    cin >> subRoleName;
    cout << "Enter reporting role name:";
    cin >> reportingRoleName;
    Role *temp1 = searchRole(reportingRoleName);
    Role *temp2 = new Role(subRoleName);
    temp1->subRoles.push_back(temp2);
    cout << temp2->role << " added successfully-" << temp1->subRoles.size() << endl;
    return;
}
void DisplayRoles()
{
    queue<Role *> q;
    cout << root->role << endl;
    for (auto i : root->subRoles)
        q.push(i);
    int count = q.size();
    while (count)
    {
        cout << q.front()->role << " ";
        if (q.front()->subRoles.size() > 0)
        {
            for (auto i : q.front()->subRoles)
                q.push(i);
        }
        q.pop();
        count--;
        if (count == 0)
        {
            cout << endl;
            count = q.size();
        }
    }
    cout << endl;
    return;
}
void AddUser()
{
    string userName, role;
    cout << "Enter User Name: ";
    cin >> userName;
    cout << "Enter Role: ";
    cin >> role;
    Role *temp = searchRole(role);
    temp->names.push_back(userName);
    return;
}
void Printusers(Role *Root)
{
    queue<Role *> q;
    if (Root->names.size() > 0)
        for (auto i : Root->names)
            cout << i << " - " << Root->role << endl;
    for (auto i : Root->subRoles)
        q.push(i);

    int count = q.size();
    while (count--)
    {
        if (q.front()->names.size() > 0)
            for (auto i : q.front()->names)
                cout << i << " - " << q.front()->role << endl;
        if (q.front()->subRoles.size() > 0)
        {
            for (auto i : q.front()->subRoles)
                q.push(i);
        }
        q.pop();
        if (count = 0)
        {
            cout << endl;
            count = q.size();
        }
    }
    return;
}

void DeleteRole()
{
    string del_role, trans_role;
    cout << "Enter the role to be deleted:";
    cin >> del_role;
    cout << "Enter the role to be transferred : ";
    cin >> trans_role;
    Role *temp = searchRole(del_role);
    Role *dest = searchRole(trans_role);
    for (auto i : temp->subRoles)
        dest->subRoles.push_back(i);

    Role *prev;
    queue<Role *> q;
    bool flag = 1;
    for (auto i : temp->subRoles)
    {
        q.push(i);
    }
    while (q.size() && flag)
    {
        if (q.front()->subRoles.size() > 0)
        {
            for (auto i : q.front()->subRoles)
            {
                if (i->role == del_role)
                {
                    prev = q.front();
                    flag = 0;
                    break;
                }
            }
        }
        q.pop();
    }

    for (int i = 0; i < prev->subRoles.size(); i++)
    {
        if (prev->subRoles[i]->role == del_role)
            prev->subRoles.erase(prev->subRoles.begin() + i);
    }
    free(temp);
    return;
}
void PrintusersAndSubUsers()
{
    queue<Role *> q;
    if (root->names.size() > 0)
        for (auto i : root->names)
            cout << i << " - " << root->role << endl;
    for (auto i : root->subRoles)
        q.push(i);

    int count = q.size();
    while (count--)
    {
        if (q.front()->names.size() > 0)
            Printusers(q.front());
        if (q.front()->subRoles.size() != 0)
        {
            for (auto i : q.front()->subRoles)
                q.push(i);
        }
        q.pop();
        if (count = 0)
        {
            cout << endl;
            count = q.size();
        }
    }
    return;
}

void DeleteUser()
{
    string userName;
    cout << "Enter username to be deleted :";
    cin >> userName;
    queue<Role *> q;
    q.push(root);
    for (auto i : root->subRoles)
        q.push(i);
    for (int i = 0; i < q.size(); i++)
    {
        Role *temp = q.front();
        for (int i = 0; i < temp->names.size(); i++)
        {
            if (temp->names[i] == userName)
            {
                temp->names.erase(temp->names.begin() + i);
                return;
            }
        }
        q.pop();
        i--;
        if (temp->subRoles.size() != 0)
        {
            for (auto j : temp->subRoles)
                q.push(j);
        }
    }
    return;
}

void NumberOfUsersFromTop()
{
    string userName;
    cout << "Enter user name : ";
    cin >> userName;
    int result = 1;
    queue<Role *> q;
    for (auto i : root->subRoles)
        q.push(i);
    int count = q.size();
    while (count--)
    {
        for (auto i : q.front()->names)
        {
            if (i == userName)
            {
                cout << "Number of users from top : " << result << endl;
                return;
            }
        }
        if (q.front()->subRoles.size() != 0)
        {
            for (auto i : q.front()->subRoles)
                q.push(i);
        }
        q.pop();
        if (count = 0)
        {
            result++;
            count = q.size();
        }
    }
    return;
}

void HeightOfRoleHierarchy()
{
    int result = 1;
    queue<Role *> q;
    for (auto i : root->subRoles)
        q.push(i);
    int count = q.size();
    while (count--)
    {
        if (q.front()->subRoles.size() != 0)
        {
            for (auto i : q.front()->subRoles)
                q.push(i);
        }
        q.pop();
        if (count = 0)
        {
            result++;
            count = q.size();
        }
    }
    cout << "height - " << result << endl;
    return;
}

void CommonBossOfUsers()
{
    string user1, user2;
    cout << "user1 - " << user1;
    cin >> user1;
    cout << "user2 - " << user2;
    cin >> user2;
    int k = 0;
    queue<Role *> q;
    for (auto i : root->subRoles)
        q.push(i);
    int count = q.size();
    while (count--)
    {
        for (auto i : q.front()->subRoles)
        {
            for (auto j : i->names)
            {
                if (j == user1 || j == user2)
                    k++;
            }
        }
        if (k == 2)
        {
            for (auto i : q.front()->names)
                cout << "Top most common boss :" << i << endl;
            return;
        }
        k = 0;
        if (q.front()->subRoles.size() > 0)
        {
            for (auto i : q.front()->subRoles)
                q.push(i);
        }
        q.pop();
        if (count = 0)
            count = q.size();
    }
    cout << "Top most common boss :" << k << endl;
    return;
}

int main()
{
    string rootRole;
    cout << "Enter root role name : ";
    cin >> rootRole;
    root = new Role(rootRole);
    int choice;
    while (true)
    {
        cout << "Operations :" << endl;
        cout << "1. Add Sub Role." << endl;
        cout << "2. Display Roles." << endl;
        cout << "3. Delete Role." << endl;
        cout << "4. Add User." << endl;
        cout << "5. Display Users." << endl;
        cout << "6. Display Users and Sub Users." << endl;
        cout << "7. Delete User." << endl;
        cout << "8. Number of users from top." << endl;
        cout << "9. Height of role hierachy." << endl;
        cout << "10. Common boss of users." << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            Subrole();
            break;
        case 2:
            DisplayRoles();
            break;
        case 3:
            DeleteRole();
            break;
        case 4:
            AddUser();
            break;
        case 5:
            Printusers(root);
            break;
        case 6:
            PrintusersAndSubUsers();
            break;
        case 7:
            DeleteUser();
            break;
        case 8:
            NumberOfUsersFromTop();
            break;
        case 9:
            HeightOfRoleHierarchy();
            break;
        case 10:
            CommonBossOfUsers();
            break;
        default:
            return 0;
        }
    }
    return 0;
}