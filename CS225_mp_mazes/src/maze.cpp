/* Your code here! */
#include "maze.h"
#include <vector>
#include <queue>

SquareMaze::SquareMaze() {
    // blank itialization
    w = 0;
    h = 0;
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    int x_ = x;
    int y_ = y;
    // according to the direction of travel
    // update the x or y coordinate accordingly
    if(dir == 0) ++x_;
    if(dir == 1) ++y_;
    if(dir == 2) --x_;
    if(dir == 3) --y_;

    //check if coordinates are our of bounds
    if(x_ >= w || x_ < 0) return false;
    if(y_ >= h || y_ < 0) return false;

    // according to the direction, check the right or bottom walls
    // if no walls then return true
    if(dir == 0 && right[(w*x) + y] == 0) return true;
    if(dir == 1 && down[(w*x) + y] == 0) return true;
    if(dir == 2 && right[(w*x_) + y_] == 0) return true;
    if(dir == 3 && down[(w*x_) + y_] == 0) return true;
    // if all else fails bad input so return false
    return false;
}

cs225::PNG* SquareMaze::drawMaze() const {
    cs225::PNG* image = new cs225::PNG(w*10 + 1, h*10 + 1);
    // color top row black starting at 10,0
    for(int i = 10; i < (w*10 + 1); i++) {
        cs225::HSLAPixel & curr = image->getPixel(i, 0);
        curr.l = 0;
    }
    // color leftmost column black
    for(int i = 0; i < (h*10 + 1); i++) {
        cs225::HSLAPixel & curr = image->getPixel(0, i);
        curr.l = 0;
    }
    // color based on if bottom or right wall exists
    for(int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            if(right[w*x + y] == 1) {
                for(int i = 0; i <= 10; i++) {
                    cs225::HSLAPixel & curr = image->getPixel((x+1)*10, y*10 + i);
                    curr.l = 0;
                }
            }
            if(down[w*x + y] == 1) {
                for(int i = 0; i <= 10; i++) {
                    cs225::HSLAPixel & curr = image->getPixel(x*10 + i, (y+1)*10);
                    curr.l = 0;
                }
            }
        }
    }
    return image;
}

cs225::PNG* SquareMaze::drawMazeWithSolution() {
    // gather the image of the maze and the solution
    cs225::PNG* image= drawMaze();
    std::vector<int> solve = solveMaze();
    // start our position at (5,5)
    int x_start = 5;
    int y_start = 5;
    // now go through the solution vector
    // based on the direction of moves we color pixels 0-10 accordingly
    // make sure to update the x and y coordinate by 10 according to move
    for(unsigned i = 0; i < solve.size(); i++) {
        if(solve[i] == 0) {
            for(int i = 0; i <= 10; i++) {
                cs225::HSLAPixel & curr = image->getPixel(x_start + i, y_start);
                curr.h = 0;
                curr.s = 1;
                curr.l = 0.5;
                curr.a = 1;
            }
            x_start = x_start + 10;
        }
        if(solve[i] == 1) {
            for(int i = 0; i <= 10; i++) {
                cs225::HSLAPixel & curr = image->getPixel(x_start, y_start + i);
                curr.h = 0;
                curr.s = 1;
                curr.l = 0.5;
                curr.a = 1;
            }
            y_start = y_start + 10;
        }
        if(solve[i] == 2) {
            for(int i = 0; i <= 10; i++) {
                cs225::HSLAPixel & curr = image->getPixel(x_start - i, y_start);
                curr.h = 0;
                curr.s = 1;
                curr.l = 0.5;
                curr.a = 1;
            }
            x_start = x_start - 10;
        }
        if(solve[i] == 3) {
            for(int i = 0; i <= 10; i++) {
                cs225::HSLAPixel & curr = image->getPixel(x_start, y_start - i);
                curr.h = 0;
                curr.s = 1;
                curr.l = 0.5;
                curr.a = 1;
            }
            y_start = y_start - 10;
        }
    }
    // whiten the destination square
    // since we have no idea what our destination coordinate is:
    // create new private var that saves destination when solving the maze
    int x_dest = destination % w;
    int y_dest = destination / w;
    for(int i =1; i < 10; i++) {
        cs225::HSLAPixel & curr = image->getPixel(x_dest*10 + i, (y_dest + 1) * 10);
        curr.l = 1;
    }
    return image;
}

void SquareMaze::makeMaze(int width, int height) {
    // save width and height in private variables
    w = width;
    h = height;
    // add walls up everywhere
    walls.addelements(width*height);
    //set up walls everywhere
    for(int i = 0; i < width*height; i++) {
        right.push_back(1);
        down.push_back(1);
    }
    // random selection of deleting walls
    // check if wall is out of bounds
    // check if cycle will occur, if points are in same disjoint set
    // if passes both then we delete the wall by joining the points into a set
    // also if it is a right or down wall of a point we make sure to update that vector
    // repeat until we've checked very wall
    for(int x = 0; x < w; x++) {
        for(int y  = 0; y < h; y++) {
            // for every coordinate besides the very last
            if(x+1 == w && y+1 == h) break;
            bool check_move = true;
            std::vector<int> moves;
            for(int i = 0; i < 4; i++) moves.push_back(i);
            int move = 0;
            // loop until we find a random valid move
            while(check_move) {
                int rand = std::rand() % moves.size();
                //std::cout << rand << " ";
                move = moves[rand];
                if(move == 0 && ((x+1) < w) && (walls.find(x*w + y) != walls.find((x+1)*w + y))) check_move = false;
                if(move == 1 && ((y+1) < h) && (walls.find(x*w + y) != walls.find(x*w + y + 1))) check_move = false;
                if(move == 2 && ((x-1) >= 0) && (walls.find(x*w + y) != walls.find((x-1)*w + y))) check_move = false;
                if(move == 3 && ((y-1) >= 0) && (walls.find(x*w + y) != walls.find(x*w + y - 1))) check_move = false;
            }

            // based on our direction we update right or down accordingly
            // join the disjoint sets
            // this effectively "breaks" the walls we set up above
            if(move == 0) {
                right[x*w + y] = 0;
                walls.setunion(x*w + y, (x+1)*w + y);
            }else if(move == 1) {
                down[x*w + y] = 0;
                walls.setunion(x*w + y, x*w + y + 1);
            }else if(move == 2) {
                right[(x-1)*w + y] = 0;
                walls.setunion(x*w + y, (x-1)*w + y);
            }else if(move == 3) {
                down[x*w + y - 1] = 0;
                walls.setunion(x*w + y, x*w + y - 1);
            }
            //std::cout << "made it out of for loop!" << std::endl;
        }
    }
}
bool SquareMaze::connected(int one, int two) {
    // if disjoint sets are the same they are connected
    int o = walls.find(one);
    int t = walls.find(two);
    if(o == t) return true;
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    // if the wall exists set up the wall in right or down vector
    // only dealing with right or down moves here
    if(exists) {
        if(dir == 0) {
            right[x*this->w + y] = 1;
        }
        if(dir == 1) {
            down[x*this->w + y] = 1;
        }
    } else {
        if(dir == 0) {
            right[x*this->w + y] = 0;
        }
        if(dir == 1) {
            down[x*this->w + y] = 0;
        }
    }
}

std::vector<int> SquareMaze::solveMaze() {
    //std:: cout << w << " w " << h << " h " << std::endl;
    // return vector
    std::vector<int> ret;
    //queue that stores the position of maze spot
    std::queue<int> q; // queue for bfs
    std::vector<int> visited; // check if cells have been visited
    std::vector<int> dist; // to keep track of longest distance
    for(int i = 0; i < h*w; i++) {
        visited.push_back(-1); // none visited
        dist.push_back(0); // all cells have a distance of 0 from end initially
    }
    // mark initial as visited and push first square
    visited[0] = 0;
    q.push(0);
    destination = 0;
    while(!q.empty()) {
        // attain first square
        int curr = q.front();
        q.pop();
        // for loop to test each move 0-3
        for(int i = 0; i < 4; i++) {
            // make sure we can travel to new square
            if(canTravel(curr % w, curr / w, i)) {
                int x_ = curr % w;
                int y_ = curr / w;
                //std::cout << x_ << " " << y_ << " x,y ";
                // to catch each case in the for loop
                // once caught we ensure the next square hasn't been visited
                // change x or y accordingly
                // mark visited of our next square as previous to keep track of path
                // add to queue
                // update distance of that square
                // update destination if dist is larger or equal and x is less than current x
                switch(i) {
                    case 0:
                        if(visited[curr + 1] == -1) { // check next square is visited
                            ++x_;  // increment x or y accordingly
                            visited[curr + 1] = curr;  // set visited of new square to be previous to manage steps
                            q.push(curr + 1);  // add to queue
                            dist[curr + 1] = dist[curr] + 1;  // update distance in a recursive sense
                            if(y_ + 1 == h && dist[curr + 1] > dist[destination]) destination = curr + 1;  // update destination if dist is larger
                            if(y_ + 1 == h && dist[curr + 1] == dist[destination] && x_ < (destination % w)) destination = curr + 1;
                            // update destination if dist is equal but x is smaller than destination x
                        }
                        break;
                    case 1:
                        if(visited[curr + w] == -1) {
                            ++y_;
                            visited[curr + w] = curr;
                            q.push(curr + w);
                            dist[curr + w] = dist[curr] + 1;
                            if(y_ + 1 == h && dist[curr + w] > dist[destination]) destination = curr + w;
                            if(y_ + 1 == h && dist[curr + w] == dist[destination] && x_ < (destination % w)) destination = curr + w;
                        }
                        break;
                    case 2:
                        if(visited[curr - 1] == -1) {
                            --x_;
                            visited[curr - 1] = curr;
                            q.push(curr - 1);
                            dist[curr - 1] = dist[curr] + 1;
                            if(y_ + 1 == h && dist[curr - 1] > dist[destination]) destination = curr - 1;
                            if(y_ + 1 == h && dist[curr - 1] == dist[destination] && x_ < (destination % w)) destination = curr - 1;
                        }
                        break;
                    case 3:
                        if(visited[curr - w] == -1) {
                            --y_;
                            visited[curr - w] = curr;
                            q.push(curr - w);
                            dist[curr - w] = dist[curr] + 1;
                            if(y_ + 1 == h && dist[curr - w] > dist[destination]) destination = curr - w;
                            if(y_ + 1 == h && dist[curr - w] == dist[destination] && x_ < (destination % w)) destination = curr - w;
                        }
                        break;
                }
                
            }
        }
    }
    int max = destination;
    //std::cout << std::endl << dist[max] << "picked out max";
    // work backward through visited adding each move starting from
    // destination all the way to start
    while(max != 0) {
        if(visited[max] == max - 1) ret.push_back(0);  // if the previous was -1, means we moved right
        if(visited[max] == max - w) ret.push_back(1);  // if previous was -w, means me moved down
        if(visited[max] == max + 1) ret.push_back(2);  // if previous was +1, means we moved left
        if(visited[max] == max + w) ret.push_back(3);  // if previous was +w, means we moved up
        //std::cout << max << " max ";
        max = visited[max];
    }
    // reverse moves since we added them initially from end to start
    std::vector<int> temp;
    for(int i = ret.size() - 1; i >= 0; i--) {
        temp.push_back(ret[i]);
    }
    return temp;
}
