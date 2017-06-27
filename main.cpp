//-----------------------------
//----- INCLUDE 	  -----
//-----------------------------
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <string>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "Redis.h"

//-----------------------------
//----- DEFINE 		  -----
//-----------------------------
#define PREFIX "config_"
#define PATH_DIAGNOSTIC "/home/pi/appli/Diagnostic/diagnostic_debug"
#define PATH_IMU "/home/pi/appli/IMU/avionic_debug"
#define PATH_LINK_EARTHSTATION "/home/pi/appli/Link_earthstation/sock_client_debug"

//-----------------------------
//----- Namespace 	  -----
//-----------------------------
using namespace std;
using namespace boost;

//-----------------------------
//----- Prototypes 	  -----
//-----------------------------
void diagnostic_thread();
void imu_thread();
void link_thread();

//-----------------------------
//----- Fonction Main	  -----
//-----------------------------

int main(int argc, char** argv) {

    /*
     * On traite le fichier de configuration pour ajouter les éléments sous redis
     */
    // Ouverture du fichier ini
    ifstream fichier("./config.ini", ios::in);

    // Redis : On instancie l'objet (Connexion Redis)
    Redis objRedis;

    if (fichier) // si l'ouverture a réussi
    {
        // Contenu de la ligne en cours
        string line;
        // Contenu de la section en cours
        string currentPrefixKey = "";

        // On scrute l'ensemble du fichier
        while (getline(fichier, line)) {

            // On cherche une section
            std::size_t firstSection = line.find("[");
            std::size_t lastSection = line.find("]");

            vector<string> strs;

            // On teste si on trouve un nom de section
            if (firstSection != std::string::npos && lastSection != std::string::npos) {
                currentPrefixKey = PREFIX + line.substr(1, line.find("]") - 1);
                cout << currentPrefixKey << endl;

            } else {
                // Sinon, c'est une valeur de paramétrage
                boost::split(strs, line, boost::is_any_of("="));

                if (strs.size() == 2) {
                    string key;
                    key = currentPrefixKey + "_" + strs[0];
                    objRedis.setDataSimple(key, strs[1]);
                }
            }
        }

        fichier.close(); // on ferme le fichier
    } else {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }

    // On initialise un vol, pour l'instant, nous le lançons en dur.
    // A terme, la station sol s'en occupera
    objRedis.setDataSimple("current_flight_inprogress", "1");

    /*
     * On initialise le reste du système
     */
    // Lancement du Thread Diagnostic
    std::thread t1(diagnostic_thread);
    // Lancement du Thread Link EarthStation
    std::thread t2(link_thread);
    // Lancement du Thread IMU
    std::thread t3(imu_thread);


    // On Attente la fin des Thread pour finir le programme
    t1.join();
    t2.join();
    t3.join();


    return EXIT_SUCCESS;
}


//-----------------------------
//----- Diagnostique	  -----
//-----------------------------

void diagnostic_thread() {
    
    cout << "DIAGNOSTIC" << endl;

    int indexNbrExecSystem = 0;
    bool flagContinueExecution = true;

    while (flagContinueExecution) {
        system(PATH_DIAGNOSTIC);
        indexNbrExecSystem++;

        if (indexNbrExecSystem == 2) {
            flagContinueExecution = false;
        }
    }
}


//-----------------------------
//----- IMU               -----
//-----------------------------

void imu_thread() {
    
    cout << "IMU" << endl;

    int indexNbrExecSystem = 0;
    bool flagContinueExecution = true;

    while (flagContinueExecution) {
        system(PATH_IMU);
        indexNbrExecSystem++;

        if (indexNbrExecSystem == 2) {
            flagContinueExecution = false;
        }
    }
}

//-----------------------------
//----- Link EarthStation -----
//-----------------------------

void link_thread() {
    
    cout << "LINK" << endl;
    
    int indexNbrExecSystem = 0;
    bool flagContinueExecution = true;

    while (flagContinueExecution) {
        system(PATH_LINK_EARTHSTATION);
        indexNbrExecSystem++;

        if (indexNbrExecSystem == 2) {
            flagContinueExecution = false;
        }
    }
}