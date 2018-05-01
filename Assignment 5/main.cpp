#include <iostream>
#include <climits>
#include <string>

using namespace std;


class node {
public:
    int cityno;
    char timein[5];
    char timeout[5];
    string flight;
    int price;
    node *next; // to create an adjacency list

    node(int x, char s1[], char s2[], string fno, int cost) {
        cityno = x;
        flight = fno;
        price = cost;
        next = NULL;

        for (int i = 0; i <= 4; i++) {
            timein[i] = s1[i];
            timeout[i] = s2[i];

        }
    };
};

void insertNode(node *a[], node *r, int x) {
    node *temp;
    temp = a[x];

    if (temp == NULL) {
        a[x] = r;
        return;
    }
    while ((temp->next) != NULL)
        temp = temp->next;

    temp->next = r;
}

void convertTimeInInt(char *s1, int &hour, int &minute) {
    hour = (s1[0] - '0') * 10 + (s1[1] - '0');
    minute = (s1[2] - '0') * 10 + (s1[3] - '0');

}

int minimumPrice(node *a[], int x1, int x2, char *s1, char *s2, int n, bool *vis) {


    node *temp = a[x1]; // temp stores the adjacency list of city x1

    if (x1 == x2)  // if source and destination are same, base case
        return 0;

    if (temp == NULL) // if the adjacency list is empty
        return -1;

    vis[x1] = true; // mark x1 as visited

    int h1, m1, h2, m2;  // trip's departure time and arrival time
    convertTimeInInt(s1, h1, m1); // convert time formats in integers
    convertTimeInInt(s2, h2, m2);

    int h_next_time_in, m_next_time_in, h_next_time_out, m_next_time_out;
    int nextCity, minPrice = INT_MAX, finalPrice;
    char nextCityTimeIn[5], nextCityTimeOut[5];

    while (temp != NULL) { // while the adjacency list is traversed completely

        nextCity = temp->cityno; // city which is being visited adjacent to x1
        if (vis[nextCity] == false) {

            for (int i = 0; i <= 4; i++) {
                nextCityTimeIn[i] = (temp)->timein[i]; // store the departure time and arrival times
                nextCityTimeOut[i] = (temp)->timeout[i];
            }
            convertTimeInInt(nextCityTimeIn, h_next_time_in, m_next_time_in);
            convertTimeInInt(nextCityTimeOut, h_next_time_out, m_next_time_out);

            char timeString[5];
            if ((h1 < h_next_time_in || ((h1 == h_next_time_in) && m1 <= m_next_time_in))
                && (h_next_time_out < h2 || (h_next_time_out == h2 && m_next_time_out <= m2))) {
                vis[nextCity] = true;

                // changes to be made so that 30 minutes are added to the current arrival time to transition city
                m_next_time_out = m_next_time_out + 30;
                int r = m_next_time_out / 60;
                m_next_time_out = m_next_time_out % 60;
                h_next_time_out = h_next_time_out + r;

                // converting time in integer to time in string
                timeString[1] = (char) h_next_time_out % 10 + 48;
                h_next_time_out = h_next_time_out / 10;
                timeString[0] = (char) h_next_time_out + 48;

                timeString[3] = (char) m_next_time_out % 10 + 48;
                m_next_time_out = m_next_time_out / 10;
                timeString[2] = (char) m_next_time_out + 48;

                // by using recursion get the min time to reach x2 from this city
                // starting after timeString and reaching before s2
                int nextPrice = minimumPrice(a, nextCity, x2, timeString, s2, n, vis);
                finalPrice = temp->price + nextPrice;
                if (finalPrice < minPrice && nextPrice != -1)
                    minPrice = finalPrice;
                vis[x2] = false;
            }

        }
        temp = temp->next;

    }

    vis[x1] = false;
    if (minPrice != INT_MAX)
        return minPrice;
    else
        return -1;
}

int main() {

    int n;
    cin >> n; // number of cities
    int inf;
    cin >> inf; // number of flights

    bool visited[n+1];
    node *adjList[n+1] = {NULL};

    int c1, c2; //city 1 and city 2
    string fnum; // flight number
    char tin[5], tout[5]; // departure time and arrival time
    int cost; // price of city

    for (int i = 1; i <= inf; i++) {
        cin >> c1 >> c2 >> tin >> tout >> fnum >> cost;
        node *a = new node(c2, tin, tout, fnum, cost); // creates a new node a
        insertNode(adjList, a, c1); // inserts it into adjacency list of c1
    }

    /* JUST TO CHECK WHETHER ADJACENCY LIST IS MADE PROPERLY
     * node *temp = adjList[2];
    while ((temp) != NULL) {

        cout << temp->price;
        cout << endl;
        temp = temp->next;

    }*/

    int q, result; // number of queries and the result
    cin >> q;

    for (int i = 1; i <= q; i++) {
        // mark all cities unvisited before each query
        for (int j = 1; j <= n; j++) {
            visited[j] = false;
        }
        cin >> c1 >> c2; // city 1 and city 2
        cin >> tin >> tout; // times t1 & t2 where input in the order: t1 < t2

        result = minimumPrice(adjList, c1, c2, tin, tout, n, visited);
        cout << result << "\n";
    }


    return 0;
}
