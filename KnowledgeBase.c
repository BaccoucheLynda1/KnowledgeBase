#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIVRES 100
#define MAX_ETUDIANTS 100
#define MAX_ENSEIGNANTS 50
#define MAX_EMPRUNTS 300



//structures
//structure livre
typedef struct {
    int id;
    char titre[100];
    char auteur[100];
    char categorie[50];
    int annee;
    int exemplaires;
} Livre;
//structure etudiant
typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char num_inscription[20];
    char filiere[50];
    int niveau;
    char telephone[20];
    char email[50];
} Etudiant;
//structure enseignant
typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char departement[50];
    char grade[30];
    char telephone[20];
    char email[50];
} Enseignant;
//structure emprunt
typedef struct {
    int id;
    int livre_id;
    int utilisateur_id;
    char type_utilisateur;
    char date_emprunt[20];
} Emprunt;
//structure bibliotheque
typedef struct {
    char nom[100];
    char adresse[150];
    char telephone[20];
    char email[50];
    char horaires[50];
    int duree_max_pret;
} Bibliotheque;

//VARIABLES GLOBALES
Bibliotheque biblio;
Livre livres[MAX_LIVRES];
Etudiant etudiants[MAX_ETUDIANTS];
Enseignant enseignants[MAX_ENSEIGNANTS];
Emprunt emprunts[MAX_EMPRUNTS];
int nb_livres = 0;
int nb_etudiants = 0;
int nb_enseignants = 0;
int nb_emprunts = 0;


//les fonctions
// Fonctions utilitaires
void afficher_ligne(void);
void afficher_separateur(void);
void pause_menu(void);
int chercher_livre_par_id(int id);
int chercher_etudiant_par_id(int id);
int chercher_enseignant_par_id(int id);
// Fonctions administrateur
void admin_gestion_biblio(void);
void admin_ajouter_livre(void);
void admin_afficher_livres(void);
void admin_modifier_livre(void);
void admin_supprimer_livre(void);
void admin_gestion_etudiants(void);
void admin_gestion_enseignants(void);
void admin_tableau_bord(void);
void menu_admin(void);
// Fonctions etudiant
void etudiant_consulter_catalogue(void);
void etudiant_emprunter_livre(int id_etudiant);
void etudiant_retourner_livre(int id_etudiant);
void etudiant_consulter_compte(int id_etudiant);
void menu_etudiant(void);
// Fonctions enseignant
void enseignant_consulter_catalogue(void);
void enseignant_emprunter_livre(int id_enseignant);
void enseignant_retourner_livre(int id_enseignant);
void enseignant_consulter_compte(int id_enseignant);
void menu_enseignant(void);

///////////////////////////

void afficher_ligne() {
    printf("**********************************************\n");
}

void afficher_separateur() {
    printf("**********************************************\n");
}

void pause_menu() {
    printf("\nAppuyez sur Entree pour continuer...");
    getchar();
}

int chercher_livre_par_id(int id) {
    for (int i = 0; i < nb_livres; i++) {
        if (livres[i].id == id) return i;
    }
    return -1;
}

int chercher_etudiant_par_id(int id) {
    for (int i = 0; i < nb_etudiants; i++) {
        if (etudiants[i].id == id) return i;
    }
    return -1;
}

int chercher_enseignant_par_id(int id) {
    for (int i = 0; i < nb_enseignants; i++) {
        if (enseignants[i].id == id) return i;
    }
    return -1;
}
//FONCTIONS ADMINISTRATEUR

void admin_gestion_biblio() {
    int choix;

    printf("\n**********************************************\n");
    printf("GESTION DE LA BIBLIOTHEQUE\n");
    printf("**********************************************\n");

    printf("\n1. Afficher les informations actuelles\n");
    printf("2. Modifier les informations\n");
    printf("3. Retour\n");
    afficher_separateur();
    printf("Choisissez une option: ");
    scanf("%d", &choix);
    getchar();

    switch(choix) {
        case 1: {
            printf("\n**********************************************\n");
            printf("INFORMATIONS DE LA BIBLIOTHEQUE\n");
            printf("**********************************************\n");
            if (strcmp(biblio.nom, "") == 0) {
                printf("\nAucune bibliotheque configuree. Veuillez d'abord configurer les informations.\n");
            } else {
                printf("\nNom: %s\n", biblio.nom);
                printf("Adresse: %s\n", biblio.adresse);
                printf("Telephone: %s\n", biblio.telephone);
                printf("Email: %s\n", biblio.email);
                printf("Horaires: %s\n", biblio.horaires);
                printf("Duree maximale de pret: %d jours\n", biblio.duree_max_pret);
            }
            afficher_separateur();
            pause_menu();
            break;
        }
        case 2: {
            printf("\n**********************************************\n");
            printf("MODIFIER LES INFORMATIONS\n");
            printf("**********************************************\n\n");
            printf("Nom: "); fgets(biblio.nom, 100, stdin);
            printf("Adresse: "); fgets(biblio.adresse, 150, stdin);
            printf("Telephone: "); fgets(biblio.telephone, 20, stdin);
            printf("Email: "); fgets(biblio.email, 50, stdin);
            printf("Horaires: "); fgets(biblio.horaires, 50, stdin);
            printf("Duree maximale de pret (jours): "); scanf("%d", &biblio.duree_max_pret);
            getchar();
            printf("\nInformations modifiees avec succes!\n");
            pause_menu();
            break;
        }
        case 3:
            return;
    }
}

void admin_ajouter_livre() {
    if (nb_livres >= MAX_LIVRES) {
        printf("Limite de livres atteinte!\n");
        pause_menu();
        return;
    }

    printf("\n**********************************************\n");
    printf("AJOUTER UN LIVRE\n");
    printf("**********************************************\n");

    Livre *l = &livres[nb_livres];

    printf("\nID du livre: "); scanf("%d", &l->id);
    getchar();

    if (chercher_livre_par_id(l->id) != -1) {
        printf("Cet ID existe deja!\n");
        pause_menu();
        return;
    }

    printf("Titre: "); fgets(l->titre, 100, stdin);
    printf("Auteur: "); fgets(l->auteur, 100, stdin);
    printf("Categorie: "); fgets(l->categorie, 50, stdin);
    printf("Annee de publication: "); scanf("%d", &l->annee);
    printf("Nombre d'exemplaires: "); scanf("%d", &l->exemplaires);
    getchar();

    nb_livres++;
    printf("\nLivre ajoute avec succes!\n");
    pause_menu();
}

void admin_afficher_livres() {
    printf("\n**********************************************\n");
    printf("LISTE DE TOUS LES LIVRES\n");
    printf("**********************************************\n");

    if (nb_livres == 0) {
        printf("\nAucun livre enregistre.\n");
    } else {
        printf("\nID                    | Titre                         | Auteur              | Annee | Exemplaires\n");
        afficher_separateur();

        for (int i = 0; i < nb_livres; i++) {
            printf("%-3d | %-29s | %-19s | %-5d | %d\n",
                   livres[i].id,
                   livres[i].titre,
                   livres[i].auteur,
                   livres[i].annee,
                   livres[i].exemplaires);
        }
    }
    afficher_separateur();
    pause_menu();
}

void admin_modifier_livre() {
    int id;

    printf("\n**********************************************\n");
    printf("MODIFIER UN LIVRE\n");
    printf("**********************************************\n");

    printf("\nID du livre a modifier: ");
    scanf("%d", &id);
    getchar();

    int idx = chercher_livre_par_id(id);
    if (idx == -1) {
        printf("Livre non trouve!\n");
        pause_menu();
        return;
    }

    printf("Nouveau titre: "); fgets(livres[idx].titre, 100, stdin);
    printf("Nouvel auteur: "); fgets(livres[idx].auteur, 100, stdin);
    printf("Nouvelle categorie: "); fgets(livres[idx].categorie, 50, stdin);
    printf("Nouvelle annee: "); scanf("%d", &livres[idx].annee);
    printf("Nouveaux exemplaires: "); scanf("%d", &livres[idx].exemplaires);
    getchar();

    printf("\nLivre modifie avec succes!\n");
    pause_menu();
}

void admin_supprimer_livre() {
    int id;

    printf("\n**********************************************\n");
    printf("SUPPRIMER UN LIVRE\n");
    printf("**********************************************\n");

    printf("\nID du livre a supprimer: ");
    scanf("%d", &id);
    getchar();

    int idx = chercher_livre_par_id(id);
    if (idx == -1) {
        printf("Livre non trouve!\n");
        pause_menu();
        return;
    }

    for (int i = idx; i < nb_livres - 1; i++) {
        livres[i] = livres[i + 1];
    }
    nb_livres--;

    printf("\nLivre supprime avec succes!\n");
    pause_menu();
}

void admin_gestion_etudiants() {
    int choix;

    while (1) {
        printf("\n**********************************************\n");
        printf("GESTION DES ETUDIANTS\n");
        printf("**********************************************\n");

        printf("\n1. Ajouter un etudiant\n");
        printf("2. Afficher tous les etudiants\n");
        printf("3. Modifier un etudiant\n");
        printf("4. Supprimer un etudiant\n");
        printf("5. Rechercher un etudiant\n");
        printf("6. Retour\n");
        afficher_separateur();
        printf("Choisissez une option: ");
        scanf("%d", &choix);
        getchar();

        switch(choix) {
            case 1: {
                if (nb_etudiants >= MAX_ETUDIANTS) {
                    printf("Limite atteinte!\n");
                    pause_menu();
                    break;
                }

                printf("\n**********************************************\n");
                printf("AJOUTER UN ETUDIANT\n");
                printf("**********************************************\n");

                Etudiant *e = &etudiants[nb_etudiants];
                printf("\nID: "); scanf("%d", &e->id);
                getchar();
                printf("Nom: "); fgets(e->nom, 50, stdin);
                printf("Prenom: "); fgets(e->prenom, 50, stdin);
                printf("Numero d'inscription: "); fgets(e->num_inscription, 20, stdin);
                printf("Filiere: "); fgets(e->filiere, 50, stdin);
                printf("Niveau: "); scanf("%d", &e->niveau);
                getchar();
                printf("Telephone: "); fgets(e->telephone, 20, stdin);
                printf("Email: "); fgets(e->email, 50, stdin);

                nb_etudiants++;
                printf("\nEtudiant ajoute avec succes!\n");
                pause_menu();
                break;
            }
            case 2: {
                printf("\n**********************************************\n");
                printf("LISTE DE TOUS LES ETUDIANTS\n");
                printf("**********************************************\n");

                if (nb_etudiants == 0) {
                    printf("\nAucun etudiant enregistre.\n");
                } else {
                    printf("\nID  | Nom                | Prenom             | Filiere             | Niveau\n");
                    afficher_separateur();

                    for (int i = 0; i < nb_etudiants; i++) {
                        printf("%-3d | %-18s | %-18s | %-19s | %d\n",
                               etudiants[i].id,
                               etudiants[i].nom,
                               etudiants[i].prenom,
                               etudiants[i].filiere,
                               etudiants[i].niveau);
                    }
                }
                afficher_separateur();
                pause_menu();
                break;
            }
            case 3: {
                printf("ID de l'etudiant a modifier: ");
                int id;
                scanf("%d", &id);
                getchar();

                int idx = chercher_etudiant_par_id(id);
                if (idx == -1) {
                    printf("Etudiant non trouve!\n");
                } else {
                    printf("Nom: "); fgets(etudiants[idx].nom, 50, stdin);
                    printf("Prenom: "); fgets(etudiants[idx].prenom, 50, stdin);
                    printf("Etudiant modifie!\n");
                }
                pause_menu();
                break;
            }
            case 4: {
                printf("ID de l'etudiant a supprimer: ");
                int id;
                scanf("%d", &id);
                getchar();

                int idx = chercher_etudiant_par_id(id);
                if (idx == -1) {
                    printf("Etudiant non trouve!\n");
                } else {
                    for (int i = idx; i < nb_etudiants - 1; i++) {
                        etudiants[i] = etudiants[i + 1];
                    }
                    nb_etudiants--;
                    printf("Etudiant supprime!\n");
                }
                pause_menu();
                break;
            }
            case 5: {
                printf("ID de l'etudiant a rechercher: ");
                int id;
                scanf("%d", &id);
                getchar();

                int idx = chercher_etudiant_par_id(id);
                if (idx == -1) {
                    printf("Etudiant non trouve!\n");
                } else {
                    printf("\nEtudiant trouve:\n");
                    afficher_separateur();
                    printf("ID: %d\n", etudiants[idx].id);
                    printf("Nom: %s\n", etudiants[idx].nom);
                    printf("Prenom: %s\n", etudiants[idx].prenom);
                    printf("Filiere: %s\n", etudiants[idx].filiere);
                    printf("Niveau: %d\n", etudiants[idx].niveau);
                    printf("Telephone: %s\n", etudiants[idx].telephone);
                    printf("Email: %s\n", etudiants[idx].email);
                }
                pause_menu();
                break;
            }
            case 6:
                return;
        }
    }
}

void admin_gestion_enseignants() {
    int choix;

    while (1) {
        printf("\n**********************************************\n");
        printf("GESTION DES ENSEIGNANTS\n");
        printf("**********************************************\n");

        printf("\n1. Ajouter un enseignant\n");
        printf("2. Afficher tous les enseignants\n");
        printf("3. Modifier un enseignant\n");
        printf("4. Supprimer un enseignant\n");
        printf("5. Rechercher un enseignant\n");
        printf("6. Retour\n");
        afficher_separateur();
        printf("Choisissez une option: ");
        scanf("%d", &choix);
        getchar();

        switch(choix) {
            case 1: {
                if (nb_enseignants >= MAX_ENSEIGNANTS) {
                    printf("Limite atteinte!\n");
                    pause_menu();
                    break;
                }

                printf("\n**********************************************\n");
                printf("AJOUTER UN ENSEIGNANT\n");
                printf("**********************************************n");

                Enseignant *p = &enseignants[nb_enseignants];
                printf("\nID: "); scanf("%d", &p->id);
                getchar();
                printf("Nom: "); fgets(p->nom, 50, stdin);
                printf("Prenom: "); fgets(p->prenom, 50, stdin);
                printf("Departement: "); fgets(p->departement, 50, stdin);
                printf("Grade: "); fgets(p->grade, 30, stdin);
                printf("Telephone: "); fgets(p->telephone, 20, stdin);
                printf("Email: "); fgets(p->email, 50, stdin);

                nb_enseignants++;
                printf("\nEnseignant ajoute avec succes!\n");
                pause_menu();
                break;
            }
            case 2: {
                printf("\n**********************************************\n");
                printf("LISTE DE TOUS LES ENSEIGNANTS\n");
                printf("**********************************************\n");

                if (nb_enseignants == 0) {
                    printf("\nAucun enseignant enregistre.\n");
                } else {
                    printf("\nID  | Nom                | Prenom             | Departement         | Grade\n");
                    afficher_separateur();

                    for (int i = 0; i < nb_enseignants; i++) {
                        printf("%-3d | %-18s | %-18s | %-19s | %s\n",
                               enseignants[i].id,
                               enseignants[i].nom,
                               enseignants[i].prenom,
                               enseignants[i].departement,
                               enseignants[i].grade);
                    }
                }
                afficher_separateur();
                pause_menu();
                break;
            }
            case 3: {
                printf("ID de l'enseignant a modifier: ");
                int id;
                scanf("%d", &id);
                getchar();

                int idx = chercher_enseignant_par_id(id);
                if (idx == -1) {
                    printf("Enseignant non trouve!\n");
                } else {
                    printf("Nom: "); fgets(enseignants[idx].nom, 50, stdin);
                    printf("Prenom: "); fgets(enseignants[idx].prenom, 50, stdin);
                    printf("Enseignant modifie!\n");
                }
                pause_menu();
                break;
            }
            case 4: {
                printf("ID de l'enseignant a supprimer: ");
                int id;
                scanf("%d", &id);
                getchar();

                int idx = chercher_enseignant_par_id(id);
                if (idx == -1) {
                    printf("Enseignant non trouve!\n");
                } else {
                    for (int i = idx; i < nb_enseignants - 1; i++) {
                        enseignants[i] = enseignants[i + 1];
                    }
                    nb_enseignants--;
                    printf("Enseignant supprime!\n");
                }
                pause_menu();
                break;
            }
            case 5: {
                printf("ID de l'enseignant a rechercher: ");
                int id;
                scanf("%d", &id);
                getchar();

                int idx = chercher_enseignant_par_id(id);
                if (idx == -1) {
                    printf("Enseignant non trouve!\n");
                } else {
                    printf("\nEnseignant trouve:\n");
                    afficher_separateur();
                    printf("ID: %d\n", enseignants[idx].id);
                    printf("Nom: %s\n", enseignants[idx].nom);
                    printf("Prenom: %s\n", enseignants[idx].prenom);
                    printf("Departement: %s\n", enseignants[idx].departement);
                    printf("Grade: %s\n", enseignants[idx].grade);
                }
                pause_menu();
                break;
            }
            case 6:
                return;
        }
    }
}

void admin_tableau_bord() {
    printf("\n**********************************************\n");
    printf("TABLEAU DE BORD - ADMINISTRATEUR\n");
    printf("**********************************************\n");

    printf("\nSTATISTIQUES GENERALES:\n");
    afficher_separateur();
    printf("Nombre total de livres: %d\n", nb_livres);
    printf("Nombre d'etudiants: %d\n", nb_etudiants);
    printf("Nombre d'enseignants: %d\n", nb_enseignants);
    printf("Total des emprunts: %d\n", nb_emprunts);

    printf("\nLIVRES DISPONIBLES:\n");
    afficher_separateur();
    int livres_dispo = 0;
    for (int i = 0; i < nb_livres; i++) {
        if (livres[i].exemplaires > 0) {
            livres_dispo++;
            printf("- %s (%d exemplaires)\n", livres[i].titre, livres[i].exemplaires);
        }
    }
    if (livres_dispo == 0) printf("Aucun livre disponible\n");

    printf("\nEMPRUNTS EN COURS:\n");
    afficher_separateur();
    if (nb_emprunts == 0) {
        printf("Aucun emprunt en cours\n");
    } else {
        for (int i = 0; i < nb_emprunts; i++) {
            int idx_livre = chercher_livre_par_id(emprunts[i].livre_id);
            if (idx_livre != -1) {
                printf("- %s (ID utilisateur: %d)\n",
                       livres[idx_livre].titre,
                       emprunts[i].utilisateur_id);
            }
        }
    }

    afficher_separateur();
    pause_menu();
}

void menu_admin() {
    int choix;

    while (1) {
        printf("\n**********************************************\n");
        printf("MENU ADMINISTRATEUR\n");
        printf("**********************************************\n");

        printf("\n1. Gestion de la bibliotheque\n");
        printf("2. Gestion des livres\n");
        printf("3. Gestion des etudiants\n");
        printf("4. Gestion des enseignants\n");
        printf("5. Tableau de bord\n");
        printf("6. Retour au menu principal\n");
        afficher_separateur();
        printf("Choisissez une option (1-6): ");
        scanf("%d", &choix);
        getchar();

        switch(choix) {
            case 1:
                admin_gestion_biblio();
                break;
            case 2: {
                int sous_choix;
                while (1) {
                    printf("\n**********************************************\n");
                    printf("GESTION DES LIVRES\n");
                    printf("**********************************************\n");
                    printf("\n1. Ajouter un livre\n");
                    printf("2. Afficher tous les livres\n");
                    printf("3. Modifier un livre\n");
                    printf("4. Supprimer un livre\n");
                    printf("5. Retour\n");
                    afficher_separateur();
                    printf("Choisissez une option: ");
                    scanf("%d", &sous_choix);
                    getchar();

                    switch(sous_choix) {
                        case 1: admin_ajouter_livre(); break;
                        case 2: admin_afficher_livres(); break;
                        case 3: admin_modifier_livre(); break;
                        case 4: admin_supprimer_livre(); break;
                        case 5: goto sortir_livres;
                    }
                }
                sortir_livres:
                break;
            }
            case 3:
                admin_gestion_etudiants();
                break;
            case 4:
                admin_gestion_enseignants();
                break;
            case 5:
                admin_tableau_bord();
                break;
            case 6:
                return;
            default:
                printf("Option invalide!\n");
                pause_menu();
        }
    }
}

//FONCTIONS ETUDIANT

void etudiant_consulter_catalogue() {
    printf("\n**********************************************\n");
    printf("CATALOGUE DES LIVRES\n");
    printf("**********************************************\n");

    if (nb_livres == 0) {
        printf("\nAucun livre disponible.\n");
    } else {
        printf("\nID  | Titre                         | Auteur              | Exemplaires\n");
        afficher_separateur();

        for (int i = 0; i < nb_livres; i++) {
            if (livres[i].exemplaires > 0) {
                printf("%-3d | %-29s | %-19s | %d\n",
                       livres[i].id,
                       livres[i].titre,
                       livres[i].auteur,
                       livres[i].exemplaires);
            }
        }
    }
    afficher_separateur();
    pause_menu();
}

void etudiant_emprunter_livre(int id_etudiant) {
    int id_livre;

    printf("\n**********************************************\n");
    printf("EMPRUNTER UN LIVRE\n");
    printf("**********************************************\n");

    printf("\nID du livre a emprunter: ");
    scanf("%d", &id_livre);
    getchar();

    int idx = chercher_livre_par_id(id_livre);
    if (idx == -1) {
        printf("Livre non trouve!\n");
        pause_menu();
        return;
    }

    if (livres[idx].exemplaires <= 0) {
        printf("Le livre n'est pas disponible!\n");
        pause_menu();
        return;
    }

    if (nb_emprunts >= MAX_EMPRUNTS) {
        printf("Limite d'emprunts atteinte!\n");
        pause_menu();
        return;
    }

    Emprunt *emp = &emprunts[nb_emprunts];
    emp->id = nb_emprunts + 1;
    emp->livre_id = id_livre;
    emp->utilisateur_id = id_etudiant;
    emp->type_utilisateur = 'E';
    strcpy(emp->date_emprunt, "Non rempli");

    livres[idx].exemplaires--;
    nb_emprunts++;

    printf("\nLivre emprunte avec succes!\n");
    pause_menu();
}

void etudiant_retourner_livre(int id_etudiant) {
    int id_livre;

    printf("\n**********************************************\n");
    printf("RETOURNER UN LIVRE\n");
    printf("**********************************************\n");

    printf("\nID du livre a retourner: ");
    scanf("%d", &id_livre);
    getchar();

    int idx_emprunt = -1;
    for (int i = 0; i < nb_emprunts; i++) {
        if (emprunts[i].livre_id == id_livre &&
            emprunts[i].utilisateur_id == id_etudiant &&
            emprunts[i].type_utilisateur == 'E') {
            idx_emprunt = i;
            break;
        }
    }

    if (idx_emprunt == -1) {
        printf("Cet emprunt n'existe pas!\n");
        pause_menu();
        return;
    }

    int idx_livre = chercher_livre_par_id(id_livre);
    if (idx_livre != -1) {
        livres[idx_livre].exemplaires++;
    }

    for (int i = idx_emprunt; i < nb_emprunts - 1; i++) {
        emprunts[i] = emprunts[i + 1];
    }
    nb_emprunts--;

    printf("\nLivre retourne avec succes!\n");
    pause_menu();
}

void etudiant_consulter_compte(int id_etudiant) {
    printf("\n**********************************************\n");
    printf("MON COMPTE - ETUDIANT\n");
    printf("**********************************************\n");

    int idx = chercher_etudiant_par_id(id_etudiant);
    if (idx == -1) {
        printf("Profil non trouve!\n");
        pause_menu();
        return;
    }

    printf("\nMES INFORMATIONS:\n");
    afficher_separateur();
    printf("Nom: %s\n", etudiants[idx].nom);
    printf("Prenom: %s\n", etudiants[idx].prenom);
    printf("N° d'inscription: %s\n", etudiants[idx].num_inscription);
    printf("Filiere: %s\n", etudiants[idx].filiere);
    printf("Niveau: %d\n", etudiants[idx].niveau);
    printf("Telephone: %s\n", etudiants[idx].telephone);
    printf("Email: %s\n", etudiants[idx].email);

    printf("\nMES EMPRUNTS EN COURS:\n");
    afficher_separateur();

    int nb_mes_emprunts = 0;
    for (int i = 0; i < nb_emprunts; i++) {
        if (emprunts[i].utilisateur_id == id_etudiant && emprunts[i].type_utilisateur == 'E') {
            int idx_livre = chercher_livre_par_id(emprunts[i].livre_id);
            if (idx_livre != -1) {
                printf("- %s\n", livres[idx_livre].titre);
                nb_mes_emprunts++;
            }
        }
    }

    if (nb_mes_emprunts == 0) printf("Aucun emprunt en cours\n");

    afficher_separateur();
    pause_menu();
}

void menu_etudiant() {
    int id_etudiant = -1;
    int choix;

    printf("\nID de l'etudiant: ");
    scanf("%d", &id_etudiant);
    getchar();

    if (chercher_etudiant_par_id(id_etudiant) == -1) {
        printf("Etudiant non trouve! Voulez-vous vous inscrire? (1=Oui, 0=Non): ");
        int reponse;
        scanf("%d", &reponse);
        getchar();

        if (reponse == 1) {
            if (nb_etudiants >= MAX_ETUDIANTS) {
                printf("Limite atteinte!\n");
                pause_menu();
                return;
            }

            Etudiant *e = &etudiants[nb_etudiants];
            e->id = id_etudiant;
            printf("Nom: "); fgets(e->nom, 50, stdin);
            printf("Prenom: "); fgets(e->prenom, 50, stdin);
            printf("Numero d'inscription: "); fgets(e->num_inscription, 20, stdin);
            printf("Filiere: "); fgets(e->filiere, 50, stdin);
            printf("Niveau: "); scanf("%d", &e->niveau);
            getchar();
            printf("Telephone: "); fgets(e->telephone, 20, stdin);
            printf("Email: "); fgets(e->email, 50, stdin);

            nb_etudiants++;
            printf("Inscription reussie!\n");
            pause_menu();
        } else {
            return;
        }
    }

    while (1) {
        printf("\n**********************************************\n");
        printf("MENU ETUDIANT\n");
        printf("**********************************************\n");

        printf("\n1. Consulter le catalogue\n");
        printf("2. Emprunter un livre\n");
        printf("3. Retourner un livre\n");
        printf("4. Consulter mon compte\n");
        printf("5. Retour au menu principal\n");
        afficher_separateur();
        printf("Choisissez une option (1-5): ");
        scanf("%d", &choix);
        getchar();

        switch(choix) {
            case 1:
                etudiant_consulter_catalogue();
                break;
            case 2:
                etudiant_emprunter_livre(id_etudiant);
                break;
            case 3:
                etudiant_retourner_livre(id_etudiant);
                break;
            case 4:
                etudiant_consulter_compte(id_etudiant);
                break;
            case 5:
                return;
            default:
                printf("Option invalide!\n");
                pause_menu();
        }
    }
}

//FONCTIONS ENSEIGNANT
void enseignant_consulter_catalogue() {
    printf("\n**********************************************\n");
    printf("CATALOGUE DES LIVRES\n");
    printf("**********************************************\n");

    if (nb_livres == 0) {
        printf("\nAucun livre disponible.\n");
    } else {
        printf("\nID  | Titre                         | Auteur              | Exemplaires\n");
        afficher_separateur();

        for (int i = 0; i < nb_livres; i++) {
            if (livres[i].exemplaires > 0) {
                printf("%-3d | %-29s | %-19s | %d\n",
                       livres[i].id,
                       livres[i].titre,
                       livres[i].auteur,
                       livres[i].exemplaires);
            }
        }
    }
    afficher_separateur();
    pause_menu();
}

void enseignant_emprunter_livre(int id_enseignant) {
    int id_livre;
    int limite_emprunts = 5;

    int nb_emprunts_actuels = 0;
    for (int i = 0; i < nb_emprunts; i++) {
        if (emprunts[i].utilisateur_id == id_enseignant && emprunts[i].type_utilisateur == 'P') {
            nb_emprunts_actuels++;
        }
    }

    if (nb_emprunts_actuels >= limite_emprunts) {
        printf("Vous avez atteint la limite d'emprunts (%d livres)!\n", limite_emprunts);
        pause_menu();
        return;
    }

    printf("\n**********************************************\n");
    printf("EMPRUNTER UN LIVRE\n");
    printf("**********************************************\n");

    printf("\nID du livre a emprunter: ");
    scanf("%d", &id_livre);
    getchar();

    int idx = chercher_livre_par_id(id_livre);
    if (idx == -1) {
        printf("Livre non trouve!\n");
        pause_menu();
        return;
    }

    if (livres[idx].exemplaires <= 0) {
        printf("Le livre n'est pas disponible!\n");
        pause_menu();
        return;
    }

    if (nb_emprunts >= MAX_EMPRUNTS) {
        printf("Limite d'emprunts atteinte!\n");
        pause_menu();
        return;
    }

    Emprunt *emp = &emprunts[nb_emprunts];
    emp->id = nb_emprunts + 1;
    emp->livre_id = id_livre;
    emp->utilisateur_id = id_enseignant;
    emp->type_utilisateur = 'P';
    strcpy(emp->date_emprunt, "Non rempli");

    livres[idx].exemplaires--;
    nb_emprunts++;

    printf("\nLivre emprunte avec succes!\n");
    pause_menu();
}

void enseignant_retourner_livre(int id_enseignant) {
    int id_livre;

    printf("\n**********************************************\n");
    printf("RETOURNER UN LIVRE\n");
    printf("**********************************************\n");

    printf("\nID du livre a retourner: ");
    scanf("%d", &id_livre);
    getchar();

    int idx_emprunt = -1;
    for (int i = 0; i < nb_emprunts; i++) {
        if (emprunts[i].livre_id == id_livre &&
            emprunts[i].utilisateur_id == id_enseignant &&
            emprunts[i].type_utilisateur == 'P') {
            idx_emprunt = i;
            break;
        }
    }
    if (idx_emprunt == -1) {
        printf("Cet emprunt n'existe pas!\n");
        pause_menu();
        return;
    }
    int idx_livre = chercher_livre_par_id(id_livre);
    if (idx_livre != -1) {
        livres[idx_livre].exemplaires++;
    }
    for (int i = idx_emprunt; i < nb_emprunts - 1; i++) {
        emprunts[i] = emprunts[i + 1];
    }
    nb_emprunts--;

    printf("\nLivre retourne avec succes!\n");
    pause_menu();
}

void enseignant_consulter_compte(int id_enseignant) {
    printf("\n**********************************************\n");
    printf("MON COMPTE - ENSEIGNANT\n");
    printf("**********************************************\n");

    int idx = chercher_enseignant_par_id(id_enseignant);
    if (idx == -1) {
        printf("Profil non trouve!\n");
        pause_menu();
        return;
    }

    printf("\nMES INFORMATIONS:\n");
    afficher_separateur();
    printf("Nom: %s\n", enseignants[idx].nom);
    printf("Prenom: %s\n", enseignants[idx].prenom);
    printf("Departement: %s\n", enseignants[idx].departement);
    printf("Grade: %s\n", enseignants[idx].grade);
    printf("Telephone: %s\n", enseignants[idx].telephone);
    printf("Email: %s\n", enseignants[idx].email);

    printf("\nMES EMPRUNTS EN COURS:\n");
    afficher_separateur();

    int nb_mes_emprunts = 0;
    for (int i = 0; i < nb_emprunts; i++) {
        if (emprunts[i].utilisateur_id == id_enseignant && emprunts[i].type_utilisateur == 'P') {
            int idx_livre = chercher_livre_par_id(emprunts[i].livre_id);
            if (idx_livre != -1) {
                printf("- %s\n", livres[idx_livre].titre);
                nb_mes_emprunts++;
            }
        }
    }
    if (nb_mes_emprunts == 0) printf("Aucun emprunt en cours\n");

    afficher_separateur();
    pause_menu();
}
void menu_enseignant() {
    int id_enseignant = -1;
    int choix;
    printf("\nID de l'enseignant: ");
    scanf("%d", &id_enseignant);
    getchar();
    if (chercher_enseignant_par_id(id_enseignant) == -1) {
        printf("Enseignant non trouve! Voulez-vous vous inscrire? (1=Oui, 0=Non): ");
        int reponse;
        scanf("%d", &reponse);
        getchar();
        if (reponse == 1) {
            if (nb_enseignants >= MAX_ENSEIGNANTS) {
                printf("Limite atteinte!\n");
                pause_menu();
                return;
            }
            Enseignant *p = &enseignants[nb_enseignants];
            p->id = id_enseignant;
            printf("Nom: "); fgets(p->nom, 50, stdin);
            printf("Prenom: "); fgets(p->prenom, 50, stdin);
            printf("Departement: "); fgets(p->departement, 50, stdin);
            printf("Grade: "); fgets(p->grade, 30, stdin);
            printf("Telephone: "); fgets(p->telephone, 20, stdin);
            printf("Email: "); fgets(p->email, 50, stdin);

            nb_enseignants++;
            printf("Inscription reussie!\n");
            pause_menu();
        } else {
            return;
        }
    }
    while (1) {
        printf("\n**********************************************\n");
        printf("MENU ENSEIGNANT\n");
        printf("**********************************************\n");

        printf("\n1. Consulter le catalogue\n");
        printf("2. Emprunter un livre\n");
        printf("3. Retourner un livre\n");
        printf("4. Consulter mon compte\n");
        printf("5. Retour au menu principal\n");
        afficher_separateur();
        printf("Choisissez une option (1-5): ");
        scanf("%d", &choix);
        getchar();

        switch(choix) {
            case 1:
                enseignant_consulter_catalogue();
                break;
            case 2:
                enseignant_emprunter_livre(id_enseignant);
                break;
            case 3:
                enseignant_retourner_livre(id_enseignant);
                break;
            case 4:
                enseignant_consulter_compte(id_enseignant);
                break;
            case 5:
                return;
            default:
                printf("Option invalide!\n");
                pause_menu();
        }
    }
}
///main
int main() {
    int choix;
    while (1) {
        printf("\n**********************************************\n");
        printf("GESTION BIBLIOTHEQUE UNIVERSITAIRE\n");
        printf("**********************************************\n");
        printf("\n1. Administrateur\n");
        printf("2. Etudiant\n");
        printf("3. Enseignant\n");
        printf("4. Quitter\n");
        afficher_separateur();
        printf("Choisissez un role (1-4): ");
        scanf("%d", &choix);
        getchar();
        switch(choix) {
            case 1:
                menu_admin();
                break;
            case 2:
                menu_etudiant();
                break;
            case 3:
                menu_enseignant();
                break;
            case 4:
                printf("\nAu revoir!\n\n");
                return 0;
            default:
                printf("Option invalide!\n");
                pause_menu();
        }
    }
    return 0;
}
