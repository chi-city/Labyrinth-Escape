// -----------------------------------------------------------------------

// Project 4 - Labyrinth Escape II, grid.h
//
// grid.h is the abstraction designed to support
// a 2D grid (maze).
//
// Author: Zaid Awaidah
// Date: 2 / 23 / 2022
// Class: CS 251, Spring 2022, UIC

// -----------------------------------------------------------------------

#pragma once
#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>
using namespace std;

// -----------------------------------------------------------------------

template<typename T>
class Grid {
 private:
    struct CELL {
        CELL* Next;
        T Val;
        size_t NumCols;  // total # of columns (0..NumCols-1)
        CELL(CELL* _Next = nullptr, T _Val = T(), size_t _NumCols = 0) {
            Next = _Next;
            Val = _Val;
            NumCols = _NumCols;
        }
    };
    size_t NumRows;  // total # of rows (0..NumRows-1)
    CELL** Rows;     // C array of linked lists

 public:
    /* default constructor :
     *
     * Called automatically by C++ to construct a 4x4 Grid.
     * All elements are initialized to the default value of T.
    */
    Grid() {
        // initialize 4 rows
        Rows = new CELL*[4];
        NumRows = 4;

        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; ++r) {
            Rows[r] = new CELL(nullptr, T(), 4);
            CELL* cur = Rows[r];

            // create the linked list for this row.
            for (size_t c = 1; c < Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, T());
                cur = cur->Next;
            }
        }
    }

    // ----------------------------------

    /* parameterized constructor :
     *
     * Called automatically by C++ to construct a RxC Grid Matrix 
     * All elements are initialized to the default value of T.
    */
    Grid(size_t R, size_t C) {
        // error checking
        if (R == 0 || C == 0)
            throw out_of_range("Number of rows/columns cannot be zero");

        // initialize R rows
        Rows = new CELL * [R];
        NumRows = R;

        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; ++r) {
            Rows[r] = new CELL(nullptr, T(), C);
            CELL* cur = Rows[r];

            // create the linked list for current row.
            for (size_t c = 1; c < Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, T());
                cur = cur->Next;
            }
        }
    }

    // ----------------------------------

    /* destructor:
     * Called automatically by C++ to free 
     * the memory associated for the linked list.
    */
    virtual ~Grid() {
        for (size_t r = 0; r < NumRows; ++r) {
            CELL* node = Rows[r];
            CELL* next;
            while (node != nullptr) {
                next = node->Next;
                delete node;
                node = next;
            }
        }
        delete[] Rows;
    }

    // ----------------------------------

    /* copy constructor :
     *
     * Called automatically by C++ to construct a Grid that contains a
     * copy of an existing Grid. Example: this occurs when passing
     * Grid as a parameter by value
    */
    Grid(const Grid<T>& other) {
        // set size and allocate memory for rows
        this->NumRows = other.NumRows;
        this->Rows = new CELL* [this->NumRows];

        for (size_t r = 0; r < NumRows; ++r) {
            // allocate memory for first cell
            Rows[r] = new CELL(other.Rows[r],
                other.Rows[r]->Val, other.Rows[r]->NumCols);
            CELL* thisCurr = Rows[r];
            CELL* otherCurr = other.Rows[r];

            // create linked list
            for (size_t c = 1; c < Rows[r]->NumCols; ++c) {
                thisCurr->Next = new CELL(nullptr,
                    otherCurr->Next->Val);
                thisCurr = thisCurr->Next;
                otherCurr = otherCurr->Next;
            }
        }
    }

    // ----------------------------------

    /* copy operator=
     * Called when you assign one Grid into another,
     * i.e. this = other;
    */
    Grid& operator=(const Grid& other) {
        // not a self assignment
        if (this == &other)
            return *this;

        // deallocate prev memory
        this->~Grid();

        // set size and allocate memory for rows
        this->NumRows = other.NumRows;
        this->Rows = new CELL * [this->NumRows];

        for (size_t r = 0; r < NumRows; ++r) {
            // allocate memory for first cell
            Rows[r] = new CELL(other.Rows[r],
                other.Rows[r]->Val, other.Rows[r]->NumCols);
            CELL* thisCurr = Rows[r];
            CELL* otherCurr = other.Rows[r];

            // create linked list
            for (size_t c = 1; c < Rows[r]->NumCols; ++c) {
                thisCurr->Next = new CELL(nullptr,
                    otherCurr->Next->Val);
                thisCurr = thisCurr->Next;
                otherCurr = otherCurr->Next;
            }
        }
        return *this;
    }

    // ----------------------------------

    /* numrows
     *
     * Returns the # of rows in the Grid. 
     * The indices for these rows are 0..numrows-1.
    */
    size_t numrows() const { return NumRows; }

    // ----------------------------------

    /* numcols
     *
     * Returns the # of columns in row r. 
     * The indices for these columns are 0..numcols-1.
     * For now, each row will have the same number of columns.
    */
    size_t numcols(size_t r) const { return Rows[r]->NumCols; }

    // ----------------------------------

    /*size
     * Returns the total # of elements in the grid.
    */
    size_t size() const { return NumRows * numcols(0); }

    // ----------------------------------

    /* operator ()
     *
     * Returns a reference to the element at location (r, c); this
     * allows you to access the element or change it.
     * 
     * Acts as a setter and a getter
    */
    T& operator()(size_t r, size_t c) {
        // error checking
        if ((r >=  this->numrows() || r < 0)
            || (c >= this->numcols(r) || c < 0))
            throw out_of_range("grid.h: row/column out of range");

        CELL* head = Rows[r];
        for (int i = 0; i < c; i++)
            head = head->Next;

        return head->Val;
    }

    // ----------------------------------

    /* _output
     * Outputs the contents of the grid; for debugging purposes.
     * valgrind error from setw()?
    */
    void _output() {
        cout << "*** OUTPUT START ***\n";
        cout << " ## Size of grid: " << this->numrows()
            << " x " << this->numcols(0) << endl;

        // displaying columns
        cout << "        ";
        for (int i = 0; i < numcols(0); i++)
            cout << "<" << i << "> ";
        cout << endl;

        // displaying rows & values
        for (int i = 0; i < this->numrows(); i++) {
            cout << "    <" << i << ">";

            CELL* temp = Rows[i];
            while (temp != nullptr) {
                cout << " " << temp->Val << " ";
                temp = temp->Next;
            }cout << endl;
        }
        cout << "**** OUTPUT END ****\n";
    }
};
// -----------------------------------------------------------------------
