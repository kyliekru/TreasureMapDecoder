#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{
    base = baseim;
    maze = mazeim;
    start = s;
    

}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){

    RGBAPixel* pixel = im.getPixel(loc.first, loc.second);

    int redVal = pixel->r;
    int blueVal = pixel->b;
    int greenVal = pixel->g;

    pixel->r = 2 * (redVal / 4);
    pixel->b = 2 * (blueVal / 4);
    pixel->g = 2 * (greenVal / 4);
}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){

    RGBAPixel* pixel = im.getPixel(loc.first, loc.second);

    d = d % 64;

    int dRed = (d >> 4) & 3;
    int dGreen = (d >> 2) & 3;
    int dBlue = d & 3;

    pixel->r = (pixel->r & 0xFC) | dRed;
    pixel->g = (pixel->g & 0xFC) | dGreen;
    pixel->b = (pixel->b & 0xFC) | dBlue;

}

PNG treasureMap::renderMap(){

 PNG result = base; 

 
    vector<vector<bool>> visited(maze.width(), vector<bool>(maze.height(), false));
    vector<vector<int>> distance(maze.width(), vector<int>(maze.height(), -1));

    Queue<pair<int, int>> q;


    visited[start.first][start.second] = true;
    distance[start.first][start.second] = 0;
    setLOB(result, start, 0); 
    q.enqueue(start);

    while (!q.isEmpty()) {
        pair<int, int> curr = q.peek();
        q.dequeue();

        vector<pair<int, int>> currNeighbors = neighbors(curr);
        for (pair<int, int> next : currNeighbors) {
            if (good(visited, curr, next)) {
                visited[next.first][next.second] = true;
                distance[next.first][next.second] = distance[curr.first][curr.second] + 1;
                setLOB(result, next, distance[next.first][next.second]); 
                q.enqueue(next);
            }
        }
    }

    return result;

}


PNG treasureMap::renderMaze(){

 PNG result = base; 

    vector<vector<bool>> visited(maze.width(), vector<bool>(maze.height(), false));
    Queue<pair<int, int>> q;

    q.enqueue(start);
    visited[start.first][start.second] = true;
    setGrey(result, start);

    while (!q.isEmpty()) {
        pair<int, int> curr = q.peek();
        q.dequeue();

        vector<pair<int, int>> currNeighbors = neighbors(curr);
        for (pair<int, int> next : currNeighbors) {
            if (good(visited, curr, next)) {
                setGrey(result, next);
                visited[next.first][next.second] = true;
                q.enqueue(next);
            }
        }
    }

    for (int i = -3; i <= 3; i++) {
        for (int j = -3; j <= 3; j++) {
            int x = start.first + i;
            int y = start.second + j;
            if (x >= 0 && x < int(result.width()) && y >= 0 && y < int(result.height())) {
                RGBAPixel* pixel = result.getPixel(x, y);
                pixel->r = 255;
                pixel->g = 0;
                pixel->b = 0;
            }
        }
    }

    return result;

}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

    if (next.first < 0 || next.first >= int(maze.width()) || 
        next.second < 0 || next.second >= int(maze.height())) {
        return false; 
    }

    if (v[next.first][next.second]) {
        return false; 
    }

    RGBAPixel* currPixel = maze.getPixel(curr.first, curr.second);
    RGBAPixel* nextPixel = maze.getPixel(next.first, next.second);

    return *currPixel == *nextPixel;

}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {

vector<pair<int, int>> n;

    n.push_back(make_pair(curr.first - 1, curr.second)); // Left
    n.push_back(make_pair(curr.first, curr.second + 1)); // Below
    n.push_back(make_pair(curr.first + 1, curr.second)); // Right
    n.push_back(make_pair(curr.first, curr.second - 1)); // Above

    return n;

}

