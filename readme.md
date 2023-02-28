# Ecole-42-MINISHELL
Reproduire, a peu de chose pres, le comportement du shell (rien que ca!)

Liens utiles:
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_09_01

# TO DO:

-> Gestion des quotes simples et doubles ouverts : simple a faire
-> Il faudra absolument gerer les here_doc en premier : un ctrl -C dans un here_doc va stopper tous les here_doc (gestion du signal ?) un ctrl -D devra stopper l exec du seul here_doc concerne

## PIPEX 
->pipe -> fork() [ENFANT] -> dup2 -> exec
                 [PARENT] -> swap pipe -> pipe a nouveau
