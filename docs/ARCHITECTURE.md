# Architecture du Jeu

## Fichiers Sources

### Fichiers C++ (.cpp)
- `main.cpp` : Point d'entrée du programme, initialise le jeu et gère la boucle principale.
- `personnage.cpp` : Implémente la logique du personnage joueur, y compris les mouvements et les interactions.
- `frameanimation.cpp` : Gère l'animation des sprites en fonction des actions du personnage.
- `Collision.cpp` : Gère les collisions entre les objets du jeu.
- `Little_Physics_Engine.cpp` : Implémente le moteur de physique basique du jeu.
- `globales.cpp` : Contient les variables globales utilisées dans le projet.
- `settings.cpp` : Gère les paramètres du jeu comme les résolutions d'écran et les configurations.
- `source.cpp` : Contient les sources ou les éléments de base du jeu.

### Fichiers d'En-tête (.h)
- `personnage.h` : Déclare les fonctions et variables liées au personnage joueur.
- `frameanimation.h` : Déclare les fonctions pour l'animation des sprites.
- `Collision.h` : Déclare les fonctions de gestion des collisions.
- `Little_Physics_Engine.h` : Déclare les éléments du moteur de physique.
- `settings.h` : Déclare les variables et fonctions liées aux paramètres du jeu.
- `source.h` : Déclare les éléments de base du jeu.
- `globales.h` : Déclare les variables globales du projet.

## Rôles des Classes

- **Personnage** : Gère les actions du personnage joueur (mouvements, attaques, etc.).
- **FrameAnimation** : Gère les animations des personnages et objets du jeu.
- **Collision** : Gère les collisions entre les objets du jeu.
- **Little_Physics_Engine** : Gère la physique du jeu (gravité, collisions, etc.).
- **Settings** : Gère les paramètres du jeu (résolution, etc.).
- **Source** : Gère les sources ou les éléments de base du jeu.
- **Globales** : Gère les variables globales du projet.

## Boucle Principale du Jeu

La boucle principale du jeu se trouve dans `main.cpp`. Elle gère les événements, met à jour l'état du jeu et dessine les éléments à l'écran. Elle est exécutée en continu tant que le jeu est en cours d'exécution.