//
//  main.cpp
//  homework2
//
//  Created by Gülşah Önen on 6.04.2021.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include "BinarySearchTree.h"
#include "AvlTree.h"

using namespace std;

/*struct Notebook{
    string title;
    string item_title;
    string item_info;
};*/
string section_title;



void MainMenu(){
    cout <<"MENU" << endl;
    cout << "Please enter an input between [1 - 6]::"<<  endl;
    cout <<"1- Display the sections [AVL]" << endl;
    cout <<"2-Display the sections [BST]" << endl;
    cout <<"3- Select a section" << endl;
    cout <<"4- Add new section" << endl;
    cout <<"5- Delete a section" << endl;
    cout<<"6- Exit" << endl;
    cout << "input: " ;
}

void SectionMenu(){
    cout << "Please enter an input between [1 - 7]:"<<  endl;
    cout <<"1- Display the items [AVL]" << endl;
    cout <<"2- Display the items [BST]" << endl;
    cout <<"3- Display the information of a item" << endl;
    cout <<"4- Add new item" << endl;
    cout <<"5- Update the information of a item" << endl;
    cout<<"6- Delete an item" << endl;
    cout <<"7- Return to main menu" << endl;
    cout << "input: " ;

}

void readingFromFile (BinarySearchTree <string> &bstree, AvlTree <string> &avltree, BinarySearchTree <string> &outer_bstree){
    string line;
    string text;
    int bst_time=0, avl_time=0;
    string dataFileName ;
    dataFileName = "data.txt";

    ifstream input;
    input.open(dataFileName.c_str());       //open data file
    if (input.fail()){
        cout << "data file cannot be open!" << endl;     // check opened file
    }
    else{

        //  ifstream infile(input);

        cout << "Welcome to the the Notes"<<endl;
        std::chrono::time_point<std::chrono::system_clock> startTime1;
        std::chrono::time_point<std::chrono::system_clock> endTime1;
        std::chrono::time_point<std::chrono::system_clock> startTime2;
        std::chrono::time_point<std::chrono::system_clock> endTime2;
        BinaryNode<string> *current_outer;
        while (getline(input, line)) {
            if(line[0]!= '-'){
                bstree.root = nullptr;
                cout<< "Section \"" + section_title +"\" has been inserted into the AVL notebook." << endl;
                startTime1=std::chrono::system_clock::now();
                endTime1=std::chrono::system_clock::now();
                bst_time+=std::chrono::duration_cast<std::chrono::milliseconds>(endTime1-startTime1).count()/1000.0;
                cout <<"[BST] Elapsed time: " << bst_time <<" microseconds" << endl;
                // insert the section title
                section_title = line;
                current_outer = outer_bstree.insert(line);
                getline(input, line);
                bstree.insert(line);
                current_outer->inner_bst = bstree.root;

            }
            else{
                bstree.insert(line);

            }
        }


        input.clear();
        input.seekg(0);
        section_title = "";
       /* while (getline(input, line)) {
            if(line[0]!= '-'){
                cout<< "Section \"" + section_title +"\" has been inserted into the BST notebook." << endl;
                startTime2=std::chrono::system_clock::now();
                endTime2=std::chrono::system_clock::now();
                avl_time+=std::chrono::duration_cast<std::chrono::milliseconds>(endTime1-startTime1).count()/1000.0;
                cout <<"[BST] Elapsed time: " << avl_time <<" microseconds" << endl;

                section_title = line;
                bstree.insert(line);

            }
            else{
               bstree.insert(line);
            }
        }*/
    }
    input.close();
}
int main() {
    int option;

    string first;
    BinarySearchTree<string> bstree(first);
    BinarySearchTree<string> outer_bstree(first);

    AvlTree<string> avltree (first);
    readingFromFile (bstree, avltree, outer_bstree);





    MainMenu();
    cin >> option;

    if(option==2){
        outer_bstree.printInorderBST(outer_bstree.root);
    }
    if(option == 3){
        cout<< "Enter the title of the section: ";
        cin >> section_title;
        cout << "Selected section " + section_title << endl;
        SectionMenu();
        cin >> option;

        if(option==2){
            BinaryNode<string> *found_node = outer_bstree.find(section_title);
            outer_bstree.printInorderBST(found_node->inner_bst);
        }

    }


    return 0;
}
