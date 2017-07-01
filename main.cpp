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

#define PATH_DIAGNOSTIC "/home/pi/appli/Diagnostic/diagnostic_debug"
#define PATH_IMU "/home/pi/appli/IMU/avionic_debug"
#define PATH_LINK_EARTHSTATION "/home/pi/appli/Link_earthstation/sock_client_debug"

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

    /*
     * On initialise les données sous Redis
     */
    Redis objRedis;
    objRedis.setDataConfig();

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
    Redis objRedis;

    if (objRedis.getDataSimple("config_system_module_enabled_diagnostic") == "true") {
 
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
}


//-----------------------------
//----- IMU               -----
//-----------------------------

void imu_thread() {
    Redis objRedis;

    if (objRedis.getDataSimple("config_system_module_enabled_imu") == "true") {

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
}

//-----------------------------
//----- Link EarthStation -----
//-----------------------------

void link_thread() {
    Redis objRedis;

    if (objRedis.getDataSimple("config_system_module_enabled_link") == "true") {

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
}