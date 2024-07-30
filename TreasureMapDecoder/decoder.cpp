#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {

    vector<vector<bool>> visited(mapImg.width(), vector<bool>(mapImg.height(), false));
    vector<vector<int>> distance(mapImg.width(), vector<int>(mapImg.height(), -1));
    vector<vector<pair<int,int>>> prev(mapImg.width(), vector<pair<int,int>>(mapImg.height(), {-1,-1}));
    Queue<pair<int,int>> q;

    visited[start.first][start.second] = true;
    distance[start.first][start.second] = 0;
    q.enqueue(start);
    pair<int,int> last = start;

    while (!q.isEmpty()) {
        pair<int,int> curr = q.dequeue();

        vector<pair<int,int>> currNeighbors = neighbors(curr);
        for (pair<int,int> next : currNeighbors) {
            if (good(visited, distance, curr, next)) {
                visited[next.first][next.second] = true;
                distance[next.first][next.second] = distance[curr.first][curr.second] + 1;
                prev[next.first][next.second] = curr;
                last = next;
                q.enqueue(next);
            }
        }
    }

    while (last != start) {
        pathPts.push_back(last);
        last = prev[last.first][last.second];
    }
    pathPts.push_back(start);
}

PNG decoder::renderSolution(){
 PNG result = mapImg;
    for (pair<int,int> point : pathPts) {
        RGBAPixel * pixel = result.getPixel(point.first, point.second);
        pixel->r = 255;
        pixel->g = 0;
        pixel->b = 0;
    }
    return result;

}

PNG decoder::renderMaze(){

 PNG result = mapImg;
 int width = (int)result.width();
 int height = (int)result.height();

    vector<vector<bool>> visited(mapImg.width(), vector<bool>(mapImg.height(), false));
    vector<vector<int>> length(mapImg.width(), vector<int>(mapImg.height(), -1));
    Queue<pair<int,int>> locations;
    visited[start.first][start.second] = true;
    length[start.first][start.second] = 0;
    locations.enqueue(start);

    while (!locations.isEmpty()) {
        pair<int,int> curr = locations.dequeue();

        vector<pair<int,int>> currNeighbors = neighbors(curr);
        for (pair<int,int> p : currNeighbors) {
            if (good(visited, length, curr, p)) {
                visited[p.first][p.second] = true;
                length[p.first][p.second] = (length[curr.first][curr.second] + 1);
                locations.enqueue(p);
                setGrey(result, p);
            }
        }
    }
    
    // 7x7 Red square around start
    for (int i = start.first - 3; i <= start.first + 3; i++) {
        for (int j = start.second - 3; j <= start.second + 3; j++) {
            if (i >= 0 && i <= width && j>= 0 && j <= height){
                RGBAPixel* pixel = result.getPixel(i, j);
                pixel->r = 255;
                pixel->g = 0;
                pixel->b = 0;
            }
        }
    } 
    return result;

}

void decoder::setGrey(PNG & im, pair<int,int> loc){

 RGBAPixel * pixel = im.getPixel(loc.first, loc.second);
    pixel->r = 2 * (pixel->r / 4);
    pixel->g = 2 * (pixel->g / 4);
    pixel->b = 2 * (pixel->b / 4);

}

pair<int,int> decoder::findSpot(){

return pathPts[0];

}

int decoder::pathLength(){

return pathPts.size();
}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){

 if (next.first < 0 || next.first >= (int)mapImg.width() ||
        next.second < 0 || next.second >= (int)mapImg.height()) return false;

    if (v[next.first][next.second]) return false;

    RGBAPixel * pixel = mapImg.getPixel(next.first, next.second);
    int expected = (d[curr.first][curr.second] + 1) % 64;

    return compare(*pixel, expected);

}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {

   vector<pair<int,int>> result;
    result.push_back(make_pair(curr.first - 1, curr.second));
    result.push_back(make_pair(curr.first + 1, curr.second));
    result.push_back(make_pair(curr.first, curr.second - 1));
    result.push_back(make_pair(curr.first, curr.second + 1));
    return result;

}


bool decoder::compare(RGBAPixel p, int d){

  int value = (p.r % 4) * 16 + (p.g % 4) * 4 + (p.b % 4);
    return value == d;

}