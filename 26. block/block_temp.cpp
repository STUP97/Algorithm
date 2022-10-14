#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Block {
public:
    int x1, x2;
    int y1, y2;
    int index;
    Block (int x1, int x2, int y1, int y2, int index) {
        this->x1 = x1;
        this->x2 = x2;
        this->y1 = y1;
        this->y2 = y2;
        this->index = index;
    }
};

vector<Block> blocks;
int result_W = -1, result_H = -1;
bool flag = true;


int compare_X(const Block &A, const Block &B) {
    if (A.x1 == B.x1)
        return A.y1 < B.y1;
    else
        return A.x1 < B.x1;
}


int compare_Y(const Block &A, const Block &B) {
    if (A.y1 == B.y1)
        return A.x1 < B.x1;
    else
        return A.y1 < B.y1;
}


void move_down(const int num) {
    sort(blocks.begin(), blocks.end(), compare_Y);
    
    for (int i = 0; i < num; ++i) {
        if (blocks[i].y1 != 0) {
            int min = 0;
            for (int j = i - 1; j >= 0; --j) {
                if (blocks[i].x2 > blocks[j].x1 && blocks[j].x2 > blocks[i].x1) {
                    if (blocks[i].y1 >= blocks[j].y2) {
                        if (min < blocks[j].y2) min = blocks[j].y2;
                        if (min == blocks[i].y1)    break;
                    }
                }
            }
            if (blocks[i].y1 != min) {
                blocks[i].y2 = blocks[i].y2 - blocks[i].y1 + min;
                blocks[i].y1 = min;
                flag = true;
            }
        }
    }
}


void move_left(const int num) {
    sort(blocks.begin(), blocks.end(), compare_X);
    
    for (int i = 0; i < num; ++i) {
        if (blocks[i].x2 > result_W)    result_W = blocks[i].x2;
        if (blocks[i].y2 > result_H)    result_H = blocks[i].y2;
        if (blocks[i].x1 != 0) {
            int min = 0;
            for (int j = i - 1; j >= 0; --j) {
                if (blocks[i].y2 > blocks[j].y1 && blocks[j].y2 > blocks[i].y1) {
                    if (blocks[i].x1 >= blocks[j].x2) {
                        if (min < blocks[j].x2) min = blocks[j].x2;
                        if (min == blocks[i].x1)    break;
                    }
                }
            }
            if (blocks[i].x1 != min) {
                blocks[i].x2 = blocks[i].x2 - blocks[i].x1 + min;
                blocks[i].x1 = min;
                flag = true;
            }
        }
    }
}


int main() {
    ifstream ifs("block.inp");
    ofstream ofs("block.out");
    int cycle, rectan_cnt;
    int low_x, low_y, up_x, up_y;
    
    ifs >> cycle;
    
    while (cycle--) {
        ifs >> rectan_cnt;
        
        result_W = result_H = -1;
        flag = true;
        blocks.clear();
        
        for (int index = 0; index < rectan_cnt; ++index) {
            ifs >> low_x >> low_y >> up_x >> up_y;
            blocks.push_back(Block(low_x, up_x, low_y, up_y, index));
        }
        
        while (flag) {
            flag = false;   result_W = -1;  result_H = -1;
            move_down(rectan_cnt);
            move_left(rectan_cnt);
        }
        
        ofs << result_W << ' ' << result_H << '\n';
    }
    
    ifs.close();
    ofs.close();
    
    return 0;
}
