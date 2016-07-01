#ifndef Specimen_H
#define Specimen_H

//includes
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>

//files
#include "./IOMananger.hpp"

//define

typedef struct timeval time_us;
typedef unsigned long long int ulint;

//namespaces
using namespace std;

class Specimen{
    static uint _num_inputs;
    static uint _num_outputs;

    static uint _num_neurons;
    static uint _net_size;

    
    static int* _types;

    static double **_dataset;
    static uint _dataset_size;


    double *_in_layer;

    double execute(double*, double);
    double _error(double, double);
public:

    double acuracy;

    Specimen(double**, uint);
    Specimen(string, double**, uint);
    ~Specimen();
    double mimAbsError();
    double mimRelError();
    double mimSquaAbsError();
    double mimSquaRelError();
    string getNeural();
    double testAcuracy();

    void evaluate();
    static bool compare(const Specimen&, const Specimen&);
    void recreate(Specimen&, Specimen&);
};

#endif
