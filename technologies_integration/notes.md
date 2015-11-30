### ExTReme Programming

#Unit test
Passe des valeurs de tests et renvoie le retour, couvre les fonctionnalités de l'application
Travail en plus, crée une librairie de tests
Programmes pour ouvrir la DLL et lance les tests sur le programme
Tentative de couvrir les cas possibles
Créer un test pour chaque bug pour le couvrir

## Intérêts Unit test
- Non régression, on ne fait que progresser malgré les modifications
- Cas limites, réflexion sur des cas peut-être non prévus dans le code de base, évite des bugs
- Pas de peur de changer, les tests couvriront les changements
- Code modulaire

Règle : Tout les tests doivent être passés par du code avant sa release

## TDD

On crée les tests avant d'écrire les fonctionnalités
Refactor -> Red -> Green
Refactor -> Suppression du code dupliqué, etc...

## Tests d'acceptance

Définir avec le client, avant le dev, comment vérifier le développement d'une user story.
Qu'est-ce que le client va faire pour vérifier que le programme marche?

Les tests vont piloter l'application pour simuler les tests clients
Piloter internet explorer pour tester l'app dans des conditions réelles

Début de l'intération, le client définit les tests et vérifie le fonctionnement en fin de sprint

## Exploratory Testing

Ouvrir l'application et tester un peu tout n'importe où, explorer l'application

## Refactor Merilessly

Même code pour de meilleures fonctionnalités, les tests unitaires rassurent sur le fait que le système continuera à tourner même refactoré.

## Itération
2-3 semaines

## Planning
Planning grossier, on prend toutes les features et on estime un planning en gros
Pas de détails, flexibilité et obligation de revoir le planning à chaque itération
