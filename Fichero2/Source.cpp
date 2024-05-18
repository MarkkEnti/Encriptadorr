#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
//declare variables
int main() {
    fstream file;
    string hash;
    string texto;
    vector<char> input;
    vector<char> escribir;
    char cha;
    int sum = 0;
    int sum2 = 0; 
    int sum3 = 0;
    bool nuevo = false;
    string line;
    

    //abro el archivo de texto
    file.open("texto.txt", ios::in | ios::out );
     
   //Detecto para ver si el archivo tiene algo escrito adentro o no 
    if (!(file >> cha)) {  
        if (file.eof()) {  
            nuevo = true;
           
            file.clear(); 
        }
    }


    //Si el archivo tiene texto escrito adentro puedo decidir ver lo hay escribiendo S y se me leera el contenido o puedo escribir N y empiezare a escribir en un archivo en blanco.
        if (nuevo == false) {
            cout << "Quieres que lea el texto del archivo o quieres empezar de nuevo? S/N" << endl;
            cin >> cha;
            if (cha == 'S') {
                
                //Si el usuario decide leer el contenido del archivo, se guarda el hash que esta escrito en la priemra linea a la variable sum2
                file.seekg(0, ios::beg);
                getline(file, hash);
                sum2 = stoi(hash);// El stoi, que transforma la tring hash a un int, lo he sacado del google ya que es la solucion mas facil para pasar la informacion del hash al int sum2.

                //Luego calculo el hash del archivo (sin contar el hash que esta escrito en la primera linea) para verificar luego
                while (file.get(cha)) {
                    escribir.push_back(cha);
                    sum3 = sum3 + cha;

                }



                // Aqui cojo el contenido del archivo y lo descodifico para que se pueda leer
                file.clear();
                file.seekg(0, ios::beg);
                getline(file, hash);
                while (getline(file, line)) {
                    for (int a = 0; a < line.size(); a++) {
                        if (line[a] != ' ') {
                            line[a] = line[a] + 3;  
                        }
                    }
                    cout << line << "\n";  
                }
                cout << endl;
                //Si los hashes no son lo mismo se anuncia que el documento ha sido alterado
                if (sum3 != sum2) {
                    cout << "Este archivo ha sido manipulado" << endl;
                }

               
                //Elimino todo el contenido ya que la informacio ya lo tengo guardado en la variable escribir. Esto hace el proces mas facil de escribir el nuevo hash en la priemra linea. 
                file.close();
                file.open("texto.txt", ios::out | ios::trunc);






            }
            else {
                //Si el usuario no quere leer el docuemnto se elimina todo el contenido, para que puedo escribir desde 0
                file.clear();
                file.close(); 
                
                file.open("texto.txt", ios::out | ios::trunc); 


                escribir.clear();
                sum3 = 0;
                
            }



        }    
     
        
    
//Cuando el usuario escribe se codifica y guarda en la  varible input. A la vez se calcula el nuevo hash.
    cout << "Escribe 'exit' para salir y guardar el archivo" << endl;
    while (getline(cin, texto)) {
        if (texto == "exit") {
            break;
        }
        
        for (int a = 0; a < texto.size(); a++) {
            if (texto[a] != ' ') {
                texto[a] = texto[a] - 3;  
            }
            input.push_back(texto[a]);
            sum =sum + texto[a];
        }
        input.push_back('\n');  
        sum += '\n';  
    }
    //Se suma el hash del documento anterior con el hash del contenido que el usuario ha escrito
    sum =sum + sum3;
    //Aqui se escribe en al archivo en order de: primero el nuevo hash del documento, luego el contenido antiguo y finalmente lo escrito mas recien.
    file.seekg(0, ios::beg);
    file << sum << "\n";
    for (int a = 0; a < escribir.size(); a++) {
        file << escribir[a];
    }
   
    for (int a = 0; a < input.size(); a++) {
        file << input[a];
    }

    file.close();
    return 0;
}
