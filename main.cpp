#include "header.h"

Array2D ReadCsv(string filename); // Ler arquivo em array-2D
Map CreateMap(const Array2D& arr); // Criar map entre cidades e índicies
double InputCostPerKm(); // Input do custo por quilômetro
uint32_t CheckRoadStretch(const Array2D& arr, const Map& map, string city1, string city2); // Consultar trecho
uint32_t CheckRoute(vector<string> multiple_cities, const Array2D& arr, const Map& map);  // Consultar rota
double ComputeCostByStretch(const Array2D& arr, const Map& map, double cost_per_km, // Calcular curstos por trecho
                            uint32_t road_stretch, string city1, string city2);
double ComputeRouteCosts(double cost_per_km, uint32_t total_distance); // Calcular custos por rota
std::vector<std::string> InputTwoCities(); // Input duas cidades
std::vector<std::string> InputMultipleCities(); // Input várias cidades

int main() {
    string filename = "/home/gustavo/DellDesafio/DNIT-Distancias.csv"; //Path para o file a ser lido
    Array2D arr_2d = ReadCsv(filename); // Cria uma array 2-D com todos os dados da planilha
    Map city_to_index = CreateMap(arr_2d); // Cria um map que atribui um index para cada cidade

    double cost_per_km;                 //
    vector<string> two_cities;          //
    uint32_t road_stretch;              // Declaração de variáveis que serão utilizadas e
    vector<string> multiple_cities;     // inicializadas no durante runtime do console
    uint32_t total_distance;            //
    uint8_t exit_num = 0;               //

    while (exit_num == 0) {
        uint32_t menu_input;
        cout << "=== MENU ===" << endl
             << "1. Configurar custo por Km" << endl
             << "2. Consultar trecho" << endl
             << "3. Consultar rota" << endl
             << "4. Terminar o programa" << endl
             << endl
             << "Escolha uma das opcoes:" << endl;

        cin >> menu_input;
        cin.clear();   //  Inserir opção do menu e limpar o cin
        cin.ignore();  //
        switch (menu_input) {
            case 1: {
                cost_per_km = InputCostPerKm();  // Armazena valor do custo por quilômetro
                cout << endl;
                break;
            }
            case 2: {
                two_cities = InputTwoCities(); // Insere  e armazena os valores das cidades, e
                                               // depois armazena valores do trecho e calcula custo
                road_stretch =
                    CheckRoadStretch(arr_2d, city_to_index, two_cities[0], two_cities[1]);
                ComputeCostByStretch(arr_2d, city_to_index, cost_per_km, road_stretch,
                                     two_cities[0], two_cities[1]);
                cout << endl;
                break;
            }
            case 3: {
                multiple_cities = InputMultipleCities();  //Mesma coisa do caso 2, mas para a rota
                total_distance = CheckRoute(multiple_cities, arr_2d, city_to_index);
                ComputeRouteCosts(cost_per_km, total_distance);
                cout << endl;
                break;
            }
            case 4: {
                exit_num = 1;  // número de saída do ciclo while
                break;
            }
            default: {  // Caso em que um número inválido é inserido
                cout << "Escolha inválida." << endl;
                cout << endl;
                break;
            }
        }
    }
    return 0;
}
