# Motor_Project_Grellier_Leconte

On peut trouver dans un robot différents systèmes d'entraînement motorisés, que ce soit pour entraîner des
roues, des liaisons prismatiques ou rotoïdes d'un bras, pour actionner un gripper, etc...

On peut considérer chacun de ces systèmes comme ayant:
- un Moteur (M)
- un pont en H (H power bridge)
- un Codeur (C)
- un train d'engrenage (Gear train)
- un corps robotique (roue, bras, ...)
- un asservissement en boucle fermée, de type PID par exemple

Le but de ce TP/projet sera de mettre en oeuvre un tel système pour être en capacité ensuite de
l'implémenter pour différents usages.