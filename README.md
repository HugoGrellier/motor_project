# Motor_Project_Grellier_Leconte

Grellier Hugo
Leconte Thibault

MOTOR-TP

L'Objectif du TP est de mettre en oeuvre un systeme motorisé composé de :
    - un moteur (wild thumper 74,8:1) + un train d'engrenage
    - un pont en H 
    - un codeur 
    - une carte microcontroleur (NUCLEO-F401RE equipée d'une STM32F401RE)
    - un asservissement en boucle fermée de type PID.

Les timers ont une fréquence de 84 Mhz (APB1 timer clock)

On a pu utiliser HAL_SYSTICK_Callback et SysTick_Handler sans les définir, car ils étaient déjà définis grâce à __weak.
Systick est un timer intégré dans le microprocesseur ARM Cortex M4
systick_handler est une interruption liée à ce timer
Le mot clef __weak permet de dire au compilateur que si le développeur ne définit pas une fonction ailleurs, alors est définie ici

Pilotage du pont en H et du moteur
Configuration des PWNs :
Nous avons utilsé le timer 3 pour la generation des PWNs .
Voici la fonction d'initialisation du timer 3 permettant de réaliser la PWN désirée (nous mettrons en évidence seulement les parties modifiées et intéressantes du code)
Pour plus de details : voire les codes commentés
'
/* TIM3 init function */
void MX_TIM3_Init(void)
{
  ...
'
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0; // mise a zéro du prescalaire du timer (Calcul explique ci-apres)
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP; //comptage au front montant du compteur
  htim3.Init.Period = 4000; //Valeure fixee a 4000, valeure necessaire pour respecter le 21MHz (Calcul explique ci-apres)
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
  ...

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0; //Passage a zero du signal pour déclenchement de la PWN (en slow decay)
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  //Envoie sur les channels 1 et 2 du timer 3 de la PWN (sorties du microcontroleur)
  //Ces lignes de code permettent de satisfaire la table de verite de focntionnement en slow decay du pont en H
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim3);
}
'
La valeure de reload a été fixee a 4000 a cause d'une contrainte imposee. 
En effet nous ne pouvions pas deppasser les 25kHz pour le pont de puissance.
Ayant la formule suivante : T(timer)=T(clock)(Prescalaire + 1)(reLoad+1)
Avec T(timer)=1/21kHz (fréquence étant la contrainte choisie)
    T(clock)=1/84kHz (horloge du timer)
    Prescalaire = 0
On obtient 4000.

Lecture du codeur
Nous avons utilsé le timer 2 pour le codeur.
Voici la fonction d'initialisation du timer 2 permettant de mettre le timer en mode "encoder"
Pour plus de details : voire les codes commentés
'/* TIM2 init function */
void MX_TIM2_Init(void)
{
  ...

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535; //valeur de periode (donc de reload) maximale pour compteur 16 bits
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
  ...

  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}'