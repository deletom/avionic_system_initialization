/**
 * Module d'initialisation de l'avionique
 * Auteur : Thomas DELECOURT
 */

//-----------------------------
//----- INCLUDE 	  -----
//-----------------------------
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <string>
#include <vector>
#include "Redis.h"

//-----------------------------
//----- DEFINE 		  -----
//-----------------------------

#define PATH_DIAGNOSTIC         "/home/pi/appli/avionic_diagnostic/diagnostic_debug"
#define PATH_IMU                "/home/pi/appli/avionic_imu/avionic_debug"
#define PATH_LINK_EARTHSTATION  "/home/pi/appli/avionic_link_earthstation/link_debug"
#define PATH_SHUTDOWN           "/home/pi/appli/avionic_shutdown/shutdown_debug"

//-----------------------------
//----- Namespace 	  -----
//-----------------------------
using namespace std;

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

    //On initialise les donn�es sous Redis
    Redis objRedis;
    objRedis.setDataConfig();

    /*
     * On initialise le reste du syst�me
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

    // On coupe l'ensemble du syst�me
    system(PATH_SHUTDOWN);
    
    return EXIT_SUCCESS;
}


//-----------------------------
//----- Diagnostique	  -----
//-----------------------------

void diagnostic_thread() {
    Redis objRedis;

    // V�rification si la configuration autorise le lancement du module diagnostique
    if (objRedis.getDataSimple("config_system_module_enabled_diagnostic") == "true") {
        int indexNbrExecSystem = 0;
        bool flagContinueExecution = true;
        
        // Pose d'un flag montrant que le module est encore en vie
        objRedis.setDataSimple("proc_diag", "1");

        // On lance la boucle d'ex�cution du module
        // Celle-ci relance le module 2 fois en cas de plantage
        while (flagContinueExecution) {
            system(PATH_DIAGNOSTIC);
            indexNbrExecSystem++;

            if (indexNbrExecSystem == 2) {
                flagContinueExecution = false;
            }
        }
    }
    objRedis.setDataSimple("proc_diag", "0");
}


//-----------------------------
//----- IMU               -----
//-----------------------------

void imu_thread() {
    Redis objRedis;

    // V�rification si la configuration autorise le lancement de la centrale inertielle
    if (objRedis.getDataSimple("config_system_module_enabled_imu") == "true") {
        int indexNbrExecSystem = 0;
        bool flagContinueExecution = true;

        // Pose d'un flag montrant que le module est encore en vie
        objRedis.setDataSimple("proc_imu", "1");

        // On lance la boucle d'ex�cution du module
        // Celle-ci relance le module 2 fois en cas de plantage
        while (flagContinueExecution) {
            system(PATH_IMU);
            indexNbrExecSystem++;

            if (indexNbrExecSystem == 2) {
                flagContinueExecution = false;
            }
        }
    }
    objRedis.setDataSimple("proc_imu", "0");
}

//-----------------------------
//----- Link EarthStation -----
//-----------------------------

void link_thread() {
    Redis objRedis;

    // V�rification si la configuration autorise le lancement de la t�l�m�trie
    if (objRedis.getDataSimple("config_system_module_enabled_link") == "true") {
        int indexNbrExecSystem = 0;
        bool flagContinueExecution = true;

        // Pose d'un flag montrant que le module est encore en vie
        objRedis.setDataSimple("proc_link", "1");

        // On lance la boucle d'ex�cution du module
        // Celle-ci relance le module 2 fois en cas de plantage
        while (flagContinueExecution) {
            system(PATH_LINK_EARTHSTATION);
            indexNbrExecSystem++;

            if (indexNbrExecSystem == 2) {
                flagContinueExecution = false;
            }
        }
    }
    objRedis.setDataSimple("proc_link", "0");
}
