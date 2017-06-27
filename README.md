# avionic_system_initialization

__Avionique sur Raspberry Pi - Partie Initialisation du syst�me__

D�veloppement d'un syst�me avionique complet pour raspberry PI.  
  
Objectif :  
- Entr�e des donn�es du fichier de configuration .ini sous Redis
- Lancement du script [avionic_diagnostic](https://github.com/deletom/avionic_diagnostic)
- Lancement du script [avionic_link_earthstation](https://github.com/deletom/avionic_link_earthstation)
- Lancement du script [avionic_imu](https://github.com/deletom/avionic_imu)

 
Articles sur le sujet :  
- [Pr�sentation du projet](https://medium.com/@deletom/projet-avionique-pr%C3%A9sentation-f9af9e9d1aae)
- [Le mod�le](https://medium.com/@deletom/projet-avionique-le-mod%C3%A8le-c2984ce23c3e)
- [Etat d'avancement](https://medium.com/@deletom/projet-avionique-etat-davancement-ac80b06f38f0)
  
Pr�-requis : 
- [boost](http://www.boost.org/) (Parce que �a simplifie la vie :p)
- [Redis3m](https://github.com/luca3m/redis3m) (pour les acc�s redis)