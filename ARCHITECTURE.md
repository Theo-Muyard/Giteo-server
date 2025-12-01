# Architecture du projet v0.1

## Vue d'ensemble
Le projet est un serveur de gestion de dépôts avec :
- Un système de gestion des utilisateurs
- Un protocole TCP personnalisé pour interagir avec les dépôts
- Une persistance simple via JSON

## Structure
- **Core** : fonctions utilitaires pour fichiers, logs, chemins et processus
- **Services** : logique métier (ex : gestion des utilisateurs)
- **Storage** : persistance des données (JSON)
- **Commands** : commandes exécutables (ex : ajouter/supprimer un utilisateur, setup)
- **Handler** : traitement et dispatch des commandes reçues via TCP
- **Main** : initialisation et boucle principale du serveur

## Flux
1. Initialisation du système
2. Écoute TCP et réception des commandes
3. Dispatch vers le service correspondant
4. Persistance des changements