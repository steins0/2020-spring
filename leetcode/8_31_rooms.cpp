#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int num = 0;
        vector<int> visit(rooms.size() , 1);
        visit[0] = 0;
        queue<int> myqueue;
        myqueue.push(0);

        while (!myqueue.empty())
        {
            int key = myqueue.front();
            myqueue.pop();
            num++;
            vector<int> keys = rooms[key];
            for (int key : keys)
            {
                if (visit[key])
                {
                    myqueue.push(key);
                    visit[key] = 0;
                    //vis.
                }
            }
        }
        /*
        for(int i : visit)
        {
            if (i == 1)
            {
                return false;
            }
        }
        */
        if(num==rooms.size())
        return true;
        return false;
    }
};