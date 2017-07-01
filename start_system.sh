#!/bin/bash

# Informations pour les logs
LOG_PATH="/home/pi/appli/log/"
APPLI_PATH="/home/pi/appli/"
DATE=$(date +"%Y%m%d")
LOGFILE=${LOG_PATH}${DATE}.txt

echo "$(date +"%d/%m/%Y %H:%M:%S") Lancement du systeme" | tee -a ${LOGFILE}

# On se place dans le dossier de l'appli
echo "$(date +"%d/%m/%Y %H:%M:%S") Placement dans le dossier ${APPLI_PATH}" | tee -a ${LOGFILE}
cd $APPLI_PATH

# Ajout de la variable d'export.
LD_LIBRARY_PATH=/usr/local/lib && export LD_LIBRARY_PATH

# On lance l'initialisation du systeme
echo "$(date +"%d/%m/%Y %H:%M:%S") Initialisation du systeme" | tee -a ${LOGFILE}
cd System_initialization
./system_initialize_debug

exit 0
