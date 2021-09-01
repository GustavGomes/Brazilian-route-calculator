//
// Created by gustavo on 27/03/2021.
//

#ifndef MAIN_CPP_HEADER_H
#define MAIN_CPP_HEADER_H

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cout, std::cin, std::endl, std::string, std::vector, std::getline, std::ifstream,
    std::stringstream;
using Map = std::map<string, uint32_t>;
using Array2D = vector<vector<string>>;

Array2D ReadCsv(string filename) { // filename string como argumeento
    ifstream data(filename);    // Criar um input filestream
    string line;    // Auxiliar
    Array2D parsed_csv;  // Declaração da array 2D que vai armazenar os dados finais

    while (getline(data, line)) {      // Ciclo while para extrair o conteúdo linha por linha
        stringstream line_stream(line);        // Criar um stringstream da linha atual
        string cell;     // Auxiliar para delimitação
        vector<string> parsed_row;    // Declaração do vector de strings que vai armazenar a linha
        while (getline(line_stream, cell, ';')) {   // Extrair cada nome da coluna por
            parsed_row.push_back(cell);                         // um delimitador ;
        }
        parsed_csv.push_back(parsed_row);  // Preencher vector de linhas com todas as palavras
    }

    for (size_t i = 0; i < parsed_csv.size(); i++) { //Solução de um bug que deixava a última coluna
        parsed_csv[i].pop_back();                    // duplicada e ilegível, ainda não sei a causa
    }                                                // com precisão, mas tirar o ultimo vetor extra resolve
    return parsed_csv;
}

Map CreateMap(const Array2D& arr) {
    Map map;    // Declarar map
    uint32_t counter = 0; // Declarar i inicializar contador que vai atribuir os valores de índice

    for (size_t i = 0; i < arr.size(); i++) {
        map[arr[0][i]] = counter;   // Atribui cada key com uma cidade, e cada value com um index
        counter++;
    }
    return map;
}

double InputCostPerKm() {
    cout << "Informe o custo por Km:" << endl;
    double cost_per_km;
    cin >> cost_per_km;    // Apenas input para o custo por quilômetro
    return cost_per_km;
}

uint32_t CheckRoadStretch(const Array2D& arr, const Map& map, string city1, string city2) {
    uint32_t index_origin = map.at(city1);    // Seleciona index representado pela cidade city1.
    uint32_t index_destine = map.at(city2);   // Seleciona index representado pela cidade city2.
    uint32_t distance = std::stoi(arr[index_destine + 1][index_origin]); // Extrai o valor exato
    return distance;                             // do array 2D e converte para inteiro usando stoi.
}

uint32_t CheckRoute(vector<string> multiple_cities, const Array2D& arr, const Map& map) {
    uint32_t total_distance = 0;    // Inicializar distância total
    for (size_t i = 0; i < multiple_cities.size() - 1; i++) {
        // Adiciona o valor de cada trecho entre duas cidades para calcular o total da rota.
        uint32_t stretch_distance =
            CheckRoadStretch(arr, map, multiple_cities[i], multiple_cities[i + 1]);
        cout << multiple_cities[i] << " -> " << multiple_cities[i + 1] << " (" << stretch_distance
             << " Km)." << endl;  // Printa trechos da rota
        total_distance += stretch_distance;  // Valor final da distância total
    }
    return total_distance;
}

double ComputeCostByStretch(const Array2D& arr, const Map& map, double cost_per_km,
                            uint32_t road_stretch, string city1, string city2) {
    double cost_by_stretch = cost_per_km * static_cast<double>(road_stretch);
    // Multiplica custo por quilometragem para obter o custo final.
    cout << "Distancia entre " << city1 << " e " << city2 << " é de "
         << CheckRoadStretch(arr, map, city1, city2) << " Km." << endl;
    cout << "Custo de R$ " << cost_by_stretch << endl;
    return cost_by_stretch;
}

double ComputeRouteCosts(double cost_per_km, uint32_t total_distance) {
    double route_cost = cost_per_km * static_cast<double>(total_distance);
    double gas_liters = static_cast<double>(total_distance) * (2.57);
    uint32_t days = total_distance / 283; // Multiplicações triviais para obter valores dos custos.

    cout << "Distancia total: " << total_distance << " Km." << endl;
    cout << "O custo total é de R$ " << route_cost << endl;
    cout << "O total de litros gastos foi de: " << gas_liters << " litros." << endl;
    cout << "A viagem durou " << days << " dias." << endl;

    return route_cost;
}

std::vector<std::string> InputTwoCities() {
    vector<string> cities; // Declara vetor de strings que vai armazenar origem e destino
    string origin;
    string destine;

    cout << "Digite o nome da cidade de origem:" << endl;
    getline(cin, origin);   // Função getline para também ser capaz de inserir nome de cidade
    cin.clear();                  // compostas como "Campo Grande".
                                  // cin.clear deve ser utilizado para usar dois getline consecutivos
    cout << "Digite o nome da cidade de destino:" << endl;
    getline(cin, destine);  // Função getline para segunda cidade
    cin.clear();

    std::transform(origin.begin(), origin.end(), origin.begin(), ::toupper); // Mudar para UPPERCASE
    std::transform(destine.begin(), destine.end(), destine.begin(), ::toupper); //

    cities.push_back(origin);  // Inserir cidades no vector final.
    cities.push_back(destine);
    cout << endl;
    return cities;
}

std::vector<std::string> InputMultipleCities() {
    string raw_cities; // String que armazenar o raw input
    cout << "Digite o nome de duas ou mais cidades separadas por virgula:" << endl;
    getline(cin, raw_cities);
    cin.clear();
    vector<string> cities;  // Vector final para armazenar cidades

    string delimiter = ", ";  // Declarando e inicializando delimitador
    size_t pos;   // Auxiliares para delimitação por string
    string token; //
    while ((pos = raw_cities.find(delimiter)) != std::string::npos) {
        token = raw_cities.substr(0, pos); // Delimitar token
        cities.push_back(token); // Adicionando token delimitado no vector final
        raw_cities.erase(0, pos + delimiter.length());  // Apagar parte da delimitação
    }
    cities.push_back(raw_cities); // Adicionar valores finais no vector.

    for (size_t i = 0; i < cities.size(); i++) {
        std::transform(cities[i].begin(), cities[i].end(), cities[i].begin(), ::toupper);
    }                                  // Transformar tudo em UPPERCASE
    cout << endl;
    return cities;
}

#endif  // MAIN_CPP_HEADER_H
