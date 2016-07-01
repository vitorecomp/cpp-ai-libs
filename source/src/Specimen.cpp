#include "../header/Specimen.hpp"

uint Specimen::_net_size = 0;
uint Specimen::_num_inputs = 0;
uint Specimen::_num_outputs = 0;

uint Specimen::_num_neurons = 0;
int *Specimen::_types = NULL;

double **Specimen::_dataset = NULL;
uint Specimen::_dataset_size = 0;

Specimen::Specimen(double **dataset, uint dataset_size) {
	// basic
	this->acuracy = 0;

	// dataset
	_dataset = dataset;
	_dataset_size = dataset_size;

	// copy
	_num_inputs = io::configs.inputs;
	_num_outputs = io::configs.outputs;
	_num_neurons = io::configs.num_neurons;
	_types = io::configs.types;

	_net_size = _num_neurons * _num_inputs;

	_in_layer = (double *)calloc(_net_size, sizeof(double));
}

Specimen::Specimen(string seed_inter, double **dataset, uint dataset_size) {
	// basic
	this->acuracy = 0;

	// dataset
	this->_dataset = dataset;
	this->_dataset_size = dataset_size;

	// copy
	_num_inputs = io::configs.inputs;
	_num_outputs = io::configs.outputs;
	_num_neurons = io::configs.num_neurons;
	_types = io::configs.types;

	_net_size = _num_neurons * _num_inputs;

	_in_layer = (double *)calloc(_net_size, sizeof(double));

	uint seed = std::stoi(seed_inter);
	srand(seed);
	for (uint i = 0; i < _num_neurons; i++)
		_in_layer[i] = (double)(rand() % 100) / 100;
}

Specimen::~Specimen() {
}


double Specimen::mimAbsError() {
	return 0;
}

double Specimen::mimRelError() {
	return 0;
}

double Specimen::mimSquaAbsError() {
	return 0;
}

double Specimen::mimSquaRelError() {
	return 0;
}

string Specimen::getNeural() {
	return "0";
}

double Specimen::testAcuracy() {
	return 0;
}

double Specimen::execute(double *input, double output) {
	double valor = 0;
	double inter = 1;
	for (uint j = 0; j < _num_inputs; j++) {
		for (uint i = 0; i < _num_neurons; i++) {
			switch (_types[i]) {
				case 0:
					valor += _in_layer[i + _num_neurons * j] * input[j];
					break;
				case 1:
					valor += _in_layer[i + _num_neurons * j];
					break;
				case 2:
					valor += _in_layer[i + _num_neurons * j] * pow(input[j], 2);
					break;
				case 3:
					valor += _in_layer[i + _num_neurons * j] * pow(input[j], 3);
					break;
				case 4:
					valor += _in_layer[i + _num_neurons * j] * sqrt(input[j]);
					break;
				case 5:
					valor += _in_layer[i + _num_neurons * j] * log(input[j] + 1);
					break;
				case 6:
					valor += _in_layer[i + _num_neurons * j] * input[j] *
							 log(input[j] + 1);
					break;
				case 7:
					valor += _in_layer[i + _num_neurons * j] * input[j] *
							 log(input[j] + 1);
					break;
				case 8:
					valor += _in_layer[i + _num_neurons * j] * input[j] *
							 pow(log(input[j] + 1), 2);
					break;
				default:
					valor += _in_layer[i + _num_neurons * j] * input[j];
					break;
			}
		}
	}
	return _error(valor, output);
}

double Specimen::_error(double valor, double output) {
	return abs(output - valor);
}


void Specimen::evaluate() {
	double error_total = 0;
	for (uint i = 0; i < _dataset_size; i++) {
		error_total += execute(_dataset[i], _dataset[i][_num_inputs]);
	}
	this->acuracy = error_total / _dataset_size;
}

void Specimen::recreate(Specimen &pg1, Specimen &pg2) {
	uint neurons_pg1 = ceil(_net_size / 2);
	uint neurons_pg2 = _net_size - neurons_pg1;

	for (uint i = 0; i < neurons_pg1; i++)
		if (rand() % 10 > 6) {
			double adition = ((double)(rand() % 1000)) / 500.0;
			_in_layer[i] = pg1._in_layer[i] * adition;
		} else {
			this->_in_layer[i] = pg1._in_layer[i];
		}

	for (uint i = neurons_pg1; i < neurons_pg2; i++)
		if (rand() % 10 > 6) {
			double adition = ((double)(rand() % 1000)) / 500.0;
			_in_layer[i] = pg2._in_layer[i] * adition;
		} else
			this->_in_layer[i] = pg2._in_layer[i];
}

bool Specimen::compare(const Specimen &po1, const Specimen &po2) {
	return po1.acuracy < po2.acuracy;
}
