#include "parseCmdLine.h"
#include <string>
#include <iostream>
#include "tests.h"

using namespace std;

int parseCallback(char* key, char* value, void* userData);

int main (void) {
    int result;    
    
    //****************************************************************************
    //*                              TEST 1                                      *
    //****************************************************************************

    char* test1[] = {"my_exe", "-maxclients", "2", "hello", NULL};
    int argc = 4;

    arg_struct test1_data[5]; // Stored data array 
    arg_struct* data1_pointer = test1_data; // Store data pointer
    arg_struct** pointer1 = &data1_pointer; // Pointer to data pointer that makes easy to move the pointer

    result = parseCmdLine(4, test1, parseCallback, pointer1);

    if (result != -1) {
        cout << "Test 1 successful!!" << endl << "Total arguments: " << result << endl;
        cout << "Data: {" << endl << "key: " << test1_data[0].clave<< endl << "parameter: " << test1_data[0].parametro << endl ;
        cout <<"key: " << test1_data[1].clave << endl << "parameter: " << test1_data[1].parametro << endl << "}" << endl;
    }
    else {
        cout << "Test 1 unsuccessful!" << endl;
    }

    //****************************************************************************
    //*                              TEST 2                                      *
    //****************************************************************************

    char* test2[] = { "my_exe","-maxclients", NULL};

    arg_struct test2_data[5]; // Stored data array 
    arg_struct* data2_pointer = test2_data; // Store data pointer
    arg_struct** pointer2 = &data2_pointer; // Pointer to data pointer


    if ((result = parseCmdLine(2, test2, parseCallback, pointer2)) == -1) {
        cout << "Test 2 successful!!" << endl << "Invalid syntax: Error type 1." << endl;
    }
    else {
        cout << "Test 2 unsuccessful! Didn't detect error type 1." << endl;
    }

    //****************************************************************************
    //*                              TEST 3                                      *
    //****************************************************************************


    char* test3[] = { "my_exe","-", "hello", NULL};

    arg_struct test3_data[5];
    arg_struct* data3_pointer = test3_data; // Store data pointer
    arg_struct** pointer3 = &data3_pointer; // Pointer to data pointer

    if ((result = parseCmdLine(3, test3, parseCallback, pointer3)) == -1) {
        cout << "Test 3 successful!!" << endl << "Invalid syntax: Error type 2." << endl;
    }
    else {
        cout << "Test 3 unsuccessful! Didn't detect error type 2." << endl;
    }

    //****************************************************************************
    //*                              TEST 4                                      *
    //****************************************************************************


    char* test4[] = { "my_exe","-its_a_key", "its_a_value", "its_a_parameter", "another_parameter", "-another_key?", "yes_and_another_value!", NULL};
    
    arg_struct test4_data[5];
    arg_struct* data4_pointer = test4_data; // Store data pointer
    arg_struct** pointer4 = &data4_pointer; // Pointer to data pointer

    if ((result = parseCmdLine(7, test4, parseCallback, pointer4)) == -1) {
        cout << "Test 4 successful!!" << endl << "Didn't accept a key that wasn't maxclients (a morphological error)." << endl;
    }
    else {
        cout << "Test 4 unsuccessful! Didn't pick up a morphological error." << endl;
    }

    // Just to wait until the user tap a key
    getchar();

    return 0;
}



int parseCallback(char* key, char* value, void* userData) {

    int success = 1;
    arg_struct* argumentos = *(arg_struct**)userData;
    string my_key;
    if (key != NULL) {
        my_key = key;
    }
    else {
        my_key = "";
    }
    string my_value = value;

    if (key) {

        if (!strcmp(key, "maxclients")) {  // maxclients is the only valid key
            argumentos->clave = my_key;
        }
        else {
            success = 0;
        }
    }

    if (value) {
        argumentos->parametro = my_value;
    }
    else {
        success = 0;
    }

    // I increment the pointer to point to the next storage place in my array
    (*(arg_struct**)userData)++;

    return success;

}