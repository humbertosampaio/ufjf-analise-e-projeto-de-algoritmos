/*
 * Nome: Humberto de Oliveira Sampaio
 * Matrícula: 201635012
 */

#include <iostream>
#include <sstream>

#include "Golomb.h"
#include "QuickSort.h"
#include "QuickSort.cpp"
#include "HeapSort.h"
#include "FileHandler.h"
#include "Kruskal.h"

constexpr auto SORT_PREFIX = "sort-";
constexpr auto MST_PREFIX = "grafo-";
constexpr auto INSTANCES_EXTENSION = ".txt";
constexpr auto GOLOMB_FILE_NAME = "golomb.txt";
constexpr auto RESULT_FILE_NAME = "result.txt";

using namespace std;

void showRootMenu(string instancePath, bool showHeader);
void showHeader();
void showParadigmOptions();
void execHeapSort(string &instancePath);
void execQuickSort(string &instancePath);
void execGolomb(string &instancePath);
void execKruskal(string &instancePath);
void getStreamForVector(vector<unsigned long int> vec, stringstream& output);
void getStreamForEdges(vector<Edge> vec, stringstream& output);

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Argumentos invalidos!" << endl;
		cout << "- Eh necessario passar o path para as instancias como argumento." << endl;
		cout << "- Os nomes das instacias de ordenacao devem estar no formato com \"" << SORT_PREFIX << "[id_instancia]" << INSTANCES_EXTENSION << "\"" << endl;
		cout << "- Os nomes das instacias de AGM devem estar no formato com \"" << MST_PREFIX << "[id_instancia]" << INSTANCES_EXTENSION << "\"" << endl;
		cout << "- Por ter uma entrada mais simples, o algoritmo da Sequencia de Golomb possui apenas um arquivo de entrada,";
		cout << " que deve possuir o nome " << GOLOMB_FILE_NAME << "\"" << endl;
		cout << "- Os [id_instancia] devem estar entre 0 e 100" << endl;
		return 0;
	}

	string fullOutputPath = argv[1];
	fullOutputPath += "\\";
	fullOutputPath += RESULT_FILE_NAME;

	FileHandler::clearOutputFileContents(fullOutputPath);
	showRootMenu(argv[1], true);
	return 0;
}

void showRootMenu(string instancePath, bool showHeaderString)
{
	if (showHeaderString)
		showHeader();

	showParadigmOptions();
	int paradigm;
	cin >> paradigm;

	do
	{
		switch (paradigm)
		{
			case 0:
				return;
			case 1:
				execHeapSort(instancePath);
				break;
			case 2:
				execQuickSort(instancePath);
				break;
			case 3:
				execGolomb(instancePath);
				break;
			case 4:
				execKruskal(instancePath);
				break;
			default:
				cout << "Opcao invalida. Por favor, insira um numero entre 1 e 4" << endl;
				showParadigmOptions();
				cin >> paradigm;
				break;
		}
	} while (paradigm < 0 || paradigm > 4);

	cout << "----------------------------------------------------------------------";
	showRootMenu(instancePath, false);
}

void showHeader()
{
	cout << endl << "----------------------------------------------------------------------";
	cout << endl << "|| ---------------- ANALISE E PROJETO DE ALGORITMOS --------------- ||";
	cout << endl << "----------------------------------------------------------------------";
	cout << endl << "|| Nome: Humberto de Oliveira Sampaio                               ||";
	cout << endl << "|| Matricula: 201635012                                             ||";
	cout << endl << "|| ---------------------------------------------------------------- ||" << endl << endl;
}

void showParadigmOptions()
{
	cout << endl << "Escolha o paradigma: ";
	cout << endl << "0 - Sair" << endl << "1 - Incremental" << endl << "2 - Divisao e conquista";
	cout << endl << "3 - Programacao Dinamica" << endl << "4 - Algoritmo guloso" << endl << endl;
}

void execHeapSort(string &instancePath)
{
	cout << endl << "----------------------------------------------------------------------";
	cout << endl << "|| ---------------------------- Heap Sort ------------------------- ||";
	cout << endl << "----------------------------------------------------------------------" << endl << endl;

	vector<unsigned long int> vec;
	stringstream ss;
	ss << "----------------------------\nHeap Sort:\n\n";
	string fullOutputPath = instancePath + "\\" + RESULT_FILE_NAME;
	FileHandler::writeToOutputFile(fullOutputPath, ss);

	for (int id = 0; id < 100; ++id)
	{
		string fileName = SORT_PREFIX + to_string(id) + INSTANCES_EXTENSION;
		string fullPath = instancePath + "\\" + fileName;
		unsigned long int size = FileHandler::readSortInstanceSize(fullPath);

		if (size == 0)
			continue;

		cout << "Instancia " << fileName << ":";
		FileHandler::readSortInstance(vec, fullPath);
		HeapSort::sort(vec);

		ss << "Intancia " + fileName + ":\n";
		getStreamForVector(vec, ss);
		FileHandler::writeToOutputFile(fullOutputPath, ss);

		vec.clear();
	}
}

void execQuickSort(string &instancePath)
{
	cout << endl << "----------------------------------------------------------------------";
	cout << endl << "|| --------------------------- Quick Sort ------------------------- ||";
	cout << endl << "----------------------------------------------------------------------" << endl << endl;

	vector<unsigned long int> vec;
	stringstream ss;
	ss << "----------------------------\nQuick Sort:\n\n";
	string fullOutputPath = instancePath + "\\" + RESULT_FILE_NAME;
	FileHandler::writeToOutputFile(fullOutputPath, ss);

	for (int id = 0; id < 100; ++id)
	{
		string fileName = SORT_PREFIX + to_string(id) + INSTANCES_EXTENSION;
		string fullPath = instancePath + "\\" + fileName;
		unsigned long int size = FileHandler::readSortInstanceSize(fullPath);

		if (size == 0)
			continue;

		cout << "Instancia " << fileName << ":";
		FileHandler::readSortInstance(vec, fullPath);
		//QuickSort::sort(vec, true);

		ss << "Intancia " + fileName + ":\n";
		getStreamForVector(vec, ss);
		FileHandler::writeToOutputFile(fullOutputPath, ss);

		vec.clear();
	}
}

void execGolomb(string &instancePath)
{
	cout << endl << "----------------------------------------------------------------------";
	cout << endl << "|| ----------------------- Sequencia de Golomb -------------------- ||";
	cout << endl << "----------------------------------------------------------------------" << endl << endl;

	string fullInputPath = instancePath + "\\" + GOLOMB_FILE_NAME;
	vector<unsigned long int> inputVec = FileHandler::readGolombInstance(fullInputPath);

	if (inputVec.size() == 0)
		return;

	stringstream ss;
	ss << "----------------------------\nSequencia de Golomb:\n\n";
	string fullOutputPath = instancePath + "\\" + RESULT_FILE_NAME;
	FileHandler::writeToOutputFile(fullOutputPath, ss);
	vector<unsigned long int> outputVec;

	for (auto it = inputVec.begin(); it != inputVec.end(); it++)
	{
		cout << "Sequencia com " << *it << " numeros:";
		Golomb::golombSequence(outputVec, *it);

		ss << "Sequencia com " << *it << " numeros:\n";
		getStreamForVector(outputVec, ss);
		FileHandler::writeToOutputFile(fullOutputPath, ss);
	}

	inputVec.clear();
	outputVec.clear();
}

void execKruskal(string &instancePath)
{
	cout << endl << "----------------------------------------------------------------------";
	cout << endl << "|| ------------------------ AGM por Kruskal ----------------------- ||";
	cout << endl << "----------------------------------------------------------------------" << endl << endl;

	stringstream ss;
	ss << "----------------------------\AGM por Kruskal:\n\n";
	string fullOutputPath = instancePath + "\\" + RESULT_FILE_NAME;
	FileHandler::writeToOutputFile(fullOutputPath, ss);

	for (int id = 0; id < 100; ++id)
	{
		string fileName = MST_PREFIX + to_string(id) + INSTANCES_EXTENSION;
		string fullInputPath = instancePath + "\\" + fileName;
		unsigned long int size = FileHandler::readMSTInstanceSize(fullInputPath);

		if (size == 0)
			continue;

		Graph g = Graph(size);
		cout << "Instancia " << fileName << ":";
		Graph::readMSTInstance(g, fullInputPath);
		g.generateKruskalMST(false);

		ss << "Intancia " + fileName + ":\n";
		getStreamForEdges(g.mstEdges, ss);
		FileHandler::writeToOutputFile(fullOutputPath, ss);
	}
}

void getStreamForVector(vector<unsigned long int> vec, stringstream& output)
{
	for (auto it = vec.begin(); it != vec.end(); ++it)
		output << *it << ' ';

	output << "\n\n";
}

void getStreamForEdges(vector<Edge> vec, stringstream& output)
{
	for (auto it = vec.begin(); it != vec.end(); ++it)
		output << (*it).second.first << " - " << (*it).second.second << " (W:" + (*it).first << ")\n";

	output << "\n\n";
}