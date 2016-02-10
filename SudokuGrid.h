//
//  SudokuGrid.h
//  SudokuSolver
//
//  Created by Spencer Kitchen on 2/5/16.
//  Copyright © 2016 Spencer Kitchen. All rights reserved.
//

#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include <array>
#include <bitset>
#include <string>
#include <cmath>    // floor()
// For debugging, needed for print statements
#include <iostream>
//using namespace std;

class SudokuGrid {
private:
    // private class instance vars go here
    // Holds one cell of sudoku board
    struct Cell {
        int number;             // holds value, 0 = .
        bool solved;            // if solved
        bool fixed;             // if initial input
        std::bitset<9> pencils; // pencils 1-9, bits 0-8
        
    };
    std::array<std::array<Cell, 9>, 9> board;   // Gameboard
    
public:
    // implement the following
    // constructor
    SudokuGrid(std::string s) {
        int k = 0;
        struct Cell cell;
        for (int i = 0; i<9; i++) {
            for (int j = 0; j<9; j++) {
                if (s[k] == '.') {
                    cell.number = 0;            // . = 0
                    cell.solved = false;
                    cell.fixed  = false;
                    board[i][j] = cell;
                    k++;
                } else {
                    cell.number = s[k]-'0';     // converts to int, ascii math
                    cell.solved = false;
                    cell.fixed = true;
                    board[i][j] = cell;
                    k++;
                }
            }
        }
    }
    
    int number(int row, int col) const {
        Cell returnNumber = board[row][col];
        return returnNumber.number;
    }
    
    void setNumber(int row, int col, int number) {
        if (number == 0) {
            board[row][col].number = 0;
        } else board[row][col].number = number;
    }
    
    bool isFixed(int row, int col) const {
        Cell returnFixed = board[row][col];
        return returnFixed.fixed;
    }
    
    bool isSolved(int row, int col) const {
        Cell returnSolved = board[row][col];
        return returnSolved.solved;
    }
    
    void setSolved(int row, int col) {
        board[row][col].solved = true;
    }
    
    bool isPencilSet(int row, int col, int n) const {
        if (board[row][col].pencils[n-1] == 1) {
            return true;
        } else return false;
    }
    
    bool anyPencilsSet(int row, int col) const {
        bool flag = false;
        for (int i = 0; i<9; i++) {
            if (board[row][col].pencils[i] == 1){
                flag = true;
            }
        }
        return flag;
    }
    
    void setPencil(int row, int col, int n) {
        board[row][col].pencils[n-1] = 1;
        //std::cout<<board[row][col].pencils<<"\n";
    }
    
    void setAllPencils(int row, int col) {
        board[row][col].pencils = 0x1FF;            // pencils = 11111111
        //std::cout<<board[row][col].pencils<<"\n";
    }
    void clearPencil(int row, int col, int n) {
        board[row][col].pencils[n-1] = 0;
        //std::cout<<board[row][col].pencils<<"\n";
    }
    void clearAllPencils(int row, int col) {
        board[row][col].pencils = 0x0;              // pencils = 00000000
        //std::cout<<board[row][col].pencils<<"\n";
    }
    //---------------------------------------------------
    // provided by assignment
    void autoPencil(SudokuGrid& grind) {
        for (int r = 0; r<9; r++) {
            for (int c= 0; c<9; c++) {
                if(grind.number(r, c)== 0){
                    grind.setAllPencils(r, c);
                    for (int n =1; n<=9; n++) {
                        if (conflictingNumber(grind, r, c, n)) {
                            grind.clearPencil(r, c, n);
                        }
                    }
                }
            }
        }
    }
    //----------------------------------------------------
    // Checks if there are any conflicting number in row, col,
    //  and small square. Returns TRUE if there is a conflict
    //   and FALSE is the number is safe to insert
    //
    bool conflictingNumber(SudokuGrid grid, int row, int col, int number) {
        bool conflict = false;  // assume no conflict
        
        // test horizontal
        for (int j = 0; j<9; j++) {
            int num= grid.number(row, j);
            //std::cout<<"num: "<<num<<"\n";
            if (num == number) {
                conflict = true;
            }
        }
        // test virtical
        for (int i = 0; i<9; i++) {
            int num= grid.number(i, col);
            //std::cout<<"num: "<<num<<"\n";
            if (num == number) {
                conflict = true;
            }
        }
        // test square
        float r, c;
        /*  row / 3 returns x.00, x.33, x.66. Floor of return will
         always be 0, 1, 2. Multiply by 3 and they turn into
         0, 3, 6 respectivly. Now its equal to start point
         of each small square.*/
        r = (std::floor(row / 3))*3;
        c = (std::floor(col / 3))*3;
        //std::cout<<"row: "<<r<<" col: "<<c<<"\n";
        
        // r is start of small square, r+3 is end of small square
        for (int i = r; i<r+3; i++) {
            for (int j = c; j<c+3; j++) {
                int num = grid.number(i,j);
                //std::cout<<"num: "<<num<<"\n";
                if (num == number) {
                    conflict = true;       // have conflict
                }
            }
        }
        return conflict;
    }
    //------------------------------------------------------
    // provided by assignment
    bool  solveSudoku(SudokuGrid& grid) {
        int row, col;
        if (!findUnassignedLocation(grid, row, col)) {
            return true; // puzzle filled, solution found!
        }
        for (int num = 1; num <= 9; num++)
            if (!conflictingNumber(grid, row, col, num)) {
                grid.setNumber(row, col, num); // try next number
                if (solveSudoku(grid)) {
                    return true;                 // solved!
                }
                grid.setNumber(row, col, 0);   // not solved, clear number
            }
        return false;
    }
    //--------------------------------------------------------
    bool  findUnassignedLocation(SudokuGrid& grid, int &row, int &col){
        for (row = 0; row<9; row++) {
            for (col=0; col<9; col++) {
                if (grid.number(row, col) == 0) {
                    return true;
                }
            }
        }
        return false;
    }
    //---------------------------------------------------------
    // Provided by assignment
    void deduce(SudokuGrid& grid) {
        bool changed;
        do { // repeat until no changes made
            autoPencil(grid);
            changed = false;
            for (int row = 0; row < 9; row++)
                for (int col = 0; col < 9; col++)
                    for (int n = 1; n <= 9; n++)
                        if (grid.isPencilSet(row, col, n) &&
                            (numPencilsInRow(row, n) == 1 ||
                             numPencilsInColumn(col, n) == 1 ||
                             numPencilsInBlock(row, col, n) == 1)) {
                                grid.clearAllPencils(row, col);
                                grid.setNumber(row,col,n);
                                grid.setSolved(row,col);
                                autoPencil(grid);
                                changed = true;
                                break;
                            }
        } while(changed);
    }
    //----------------------------------------------------
    int numPencilsInRow(int row, int n){
        int count =0;
        int bitPlace = n-1;
        for (int i = 0; i<9; i++) {
            if(board[row][i].pencils[bitPlace] ==1) count= count +1;
        }
        return count;
    }
    //----------------------------------------------------
    int numPencilsInColumn(int col, int n){
        int count = 0;
        int bitPlace = n-1;
        for (int i = 0; i<9; i++) {
            if (board[i][col].pencils[bitPlace] ==1) count = count +1;
        }
        return count;
    }
    //-------------------------------------------------------
    int numPencilsInBlock( int row, int col, int n){
        int count =0;
        int bitPlace=n-1;
        
        // test square
        float r, c;
        /*  row / 3 returns x.00, x.33, x.66. Floor of return will
         always be 0, 1, 2. Multiply by 3 and they turn into
         0, 3, 6 respectivly. Now its equal to start point
         of each small square.*/
        r = (std::floor(row / 3))*3;
        c = (std::floor(col / 3))*3;
        //std::cout<<"row: "<<r<<" col: "<<c<<"\n";
        
        // r is start of small square, r+3 is end of small square
        for (int i = r; i<r+3; i++) {
            for (int j = c; j<c+3; j++) {
                //std::cout<<"num: "<<num<<"\n";
                if (board[i][j].pencils[bitPlace] ==1) count = count +1;
            }
        }
        return count;
    }
};

#endif // SUDOKUGRID_H

