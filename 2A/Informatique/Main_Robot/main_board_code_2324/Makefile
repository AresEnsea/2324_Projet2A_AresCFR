# Ce make file lance la génération de la documentation du projet :
# % make documentation

# Les fichiers .h contiennent la description des structures et fonctions.
# Ils doivent commencer par /** @file XXX.h */ pour être pris en compte.

# Un push vers le git met à jour la documentation en ligne, disponible au lien :
# https://aresensea.github.io/PhobosMainboardFirmware2022/

documentation:
	'/Applications/Doxygen.app/Contents/Resources/doxygen' Doxygen/doxyconfig
	rm -r ./docs/
	cp -R Doxygen/html/ docs/