#ifndef GRID2D_H
#define GRID2D_H

#include <vector>

template <typename T>
class Grid2d {
    public:
        Grid2d(int width, int height, const T& default_val, const T& null_val);

        bool inBounds(int x, int y) const;
        
        T getAt(int x, int y) const;
        void setAt(int x, int y, const T& val);

        T resetTo(T reset);

        std::vector<T> getSurroundings(int x, int y) const;
        T getNeighbor(int direction, int x, int y) const;

        void fill(int x, int y, const T& old_t, const T& new_t);

        int getWidth() const {return width;}
        int getHeight() const {return height;}
        int getSize() const {return width*height;}

    protected:
        int width, height;
        T default_val, null_val;
        std::vector<std::vector<T> > layout;
};

template <typename T>
Grid2d<T>::Grid2d(int width, int height, const T& default_val, const T& null_val) :
    width(width), height(height), default_val(default_val), null_val(null_val)
{
    for (int y = 0; y < height; y++){
        std::vector<T> current_line;
        for (int x = 0; x < width; x++){
            current_line.push_back(default_val);
        }
        
        layout.push_back(current_line);
    }
}

template <typename T>
bool Grid2d<T>::inBounds(int x, int y){
    //TODO: throw error if not
    return !(x > width-1 || y > height-1 || x < 0 || y < 0);
}

template <typename T>
void Grid2d<T>::setAt(int x, int y, const T& val){
    if (!inBounds(x, y)){
        return;
    } else {
        layout[y][x] = val;
    }
}

template <typename T>
T Grid2d<T>::reset(T reset=default_val){
    //TODO: make this actually work (should take all of 4 seconds)
    for (int y = 0; y < height; y++){
        layout[y].clear();
        for (int x = 0; x < width; x++){
            layout[y].push_back(reset);
        }
    }
}

template <typename T>
std::vector<T> Grid2d<T>::getSurroundings(int x, int y){
    std::vector<T> out;
    for (int j = -1; j < 2; j++){
        for (int i = -1; i < 2; i++){
            if (x + i < 0 || x + i > width || y + j < 0 || y + j > height){
                continue;
            } else {
                out.push_back(getAt(x+i, y+j));
            }
        }
    }
}

template <typename T>
T Grid2d<T>::getNeighbor(int direction, int x, int y){
    switch (direction){
        case 7: //northwest
            return getAt(x-1, y-1);
        case 8: //north
            return getAt(x, y-1);
        case 9: //northeast
            return getAt(x+1, y-1);
        case 4: //west
            return getAt(x-1, y);
        case 6: //east
            return getAt(x+1, y);
        case 1: //southwest
            return getAt(x-1, y+1);
        case 2: //south
            return getAt(x, y+1);
        case 3: //southeast
            return getAt(x+1, y+1);
        default:
            //throw an error: invalid direction
            return null_val;
    }
}

template <typename T>
void Grid2d<T>::fill(int x, int y, const T& old_t, const T& new_t){
///textbook fill algorithm used to fill in isolated holes created in genBarren()
    if (!inBounds(x, y)){
        return;
    }

  //north
    if (getAt(x, y-1) == old_t){
        setAt(x, y-1, new_t);
        fill(x, y-1, old_t, new_t);
    }      
  //east
    if (getAt(x+1, y) == old_t){
        setAt(x+1, y, new_t);
        fill(x+1, y, old_t, new_t);
    }     
  //south{
    if (getAt(x, y+1) == old_t){
        setAt(x, y+1, new_t);
        fill(x, y+1, old_t, new_t);
    }      
  //west
    if (getAt(x-1, y) == old_t){
        setAt(x-1, y, new_t);
        fill(x-1, y, old_t, new_t);
    }
}

/*
template <typename T> int Grid2d<T>::getWidth (){return width;}
template <typename T> int Grid2d<T>::getHeight(){return height;}
template <typename T> int Grid2d<T>::getSize  (){return width*height;}
*/

#endif
