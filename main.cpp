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
#include <fstream>
#include "Redis.h"

//-----------------------------
//----- DEFINE 		  -----
//-----------------------------

#define PATH_DIAGNOSTIC         "/home/pi/appli/avionic_diagnostic/diagnostic_debug"
#define PATH_IMU                "/home/pi/appli/avionic_imu/avionic_debug"
#define PATH_LINK_EARTHSTATION  "/home/pi/appli/avionic_link_earthstation/link_debug"
#define PATH_SHUTDOWN           "/home/pi/appli/avionic_shutdown/shutdown_debug"

#define PATH_LOG_IMU_SENSEHAT   "/home/pi/log/sensehat.log"
#define PATH_LOG_IMU_GPS        "/home/pi/log/gps.log"
#define PATH_LOG_IMU_LINK       "/home/pi/log/link.log"
#define PATH_LOG_THREAD         "/home/pi/log/thread.log"

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

    // Ouverture des différents fichiers de log
    ofstream fileImuSenseHat(PATH_LOG_IMU_SENSEHAT, ios::out | ios::trunc);
    ofstream fileImuGps(PATH_LOG_IMU_GPS, ios::out | ios::trunc);
    ofstream fileImuLink(PATH_LOG_IMU_LINK, ios::out | ios::trunc);
    ofstream fileThread(PATH_LOG_THREAD, ios::out | ios::trunc);

    if (fileImuSenseHat.is_open()) {
        fileImuSenseHat.close();
    }
    if (fileImuGps.is_open()) {
        fileImuGps.close();
    }
    if (fileImuLink.is_open()) {
        fileImuLink.close();
    }
    if (fileThread.is_open()) {
        fileThread.close();
    }

    //On initialise les données sous Redis
    Redis objRedis;
    objRedis.setDataConfig();

    /*
     * On initialise le reste du système
     */
    // Lancement du Thread IMU
    std::thread t1(imu_thread);
    // Lancement du Thread Diagnostic
    //std::thread t2(diagnostic_thread);
    // Lancement du Thread Link EarthStation
    std::thread t3(link_thread);

    // On Attente la fin des Thread pour finir le programme
    t1.join();
    //t2.join();
    t3.join();

    // On coupe l'ensemble du système
    system(PATH_SHUTDOWN);

    return EXIT_SUCCESS;
}


//-----------------------------
//----- Diagnostique	  -----
//-----------------------------

void diagnostic_thread() {
    int indexNbrExecSystem = 0;
    bool flagContinueExecution = true;

    // On lance la boucle d'exécution du module
    // Celle-ci relance le module 2 fois en cas de plantage
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
    int indexNbrExecSystem = 0;
    bool flagContinueExecution = true;

    // On lance la boucle d'exécution du module
    // Celle-ci relance le module 2 fois en cas de plantage
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
    int indexNbrExecSystem = 0;
    bool flagContinueExecution = true;

    // On lance la boucle d'exécution du module
    // Celle-ci relance le module 2 fois en cas de plantage
    while (flagContinueExecution) {
        system(PATH_LINK_EARTHSTATION);
        indexNbrExecSystem++;

        if (indexNbrExecSystem == 2) {
            flagContinueExecution = false;
        }
    }
}
