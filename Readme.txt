Malapel Florian
Dhersin Jérôme

TP2 - Système de fichier à la linux

//Exécution avec la librairie pour mac OS//

Voici les différents main exécutable: 
	- ./create_vol size
		Création d'un nouveau volume avec la taille passée en argument du programme

	- ./print_vol volume
		Affichage du volume passé en argument du programme

	- ./delete_vol volume value
		Formate le volume passé en argument du programme avec la valeur "value" puis le supprime

	- ./test_vol 
		Programme qui test la création, suppression et affichage d'un volume

	- ./dfs
		display_file_system: affiche les infos du disque (taux d'occupation, la list des blocs libres)

	- ./mknfs
		make_new_file_system : initialise le superBloc et initialise la liste des free_bloc dans le superBloc

	
	Toutes les fonctionnalités demandées jusqu’à maintenant sont fonctionnelle, nous avons aussi implémentée une fonction free_bloc_triee(unsigned int bloc) qui nous permet d’insérer les blocs à libérer dans un ordre croissant pour optimiser les accès disques.