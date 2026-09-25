# philosophers

Projet de l'école 42 Paris sur la programmation concurrente : le problème du dîner des philosophes, résolu avec des threads et des mutex.

Chaque philosophe est un thread. Il mange (deux fourchettes, une par mutex), dort, puis pense. Le programme détecte la mort d'un philosophe (famine) dans les délais impartis, sans data race ni deadlock.

## Compilation & usage

```bash
make
./philo <nb_philos> <temps_mourir> <temps_manger> <temps_dormir> [nb_repas]
```

Exemple : `./philo 5 800 200 200` — 5 philosophes, meurent après 800 ms sans manger.
