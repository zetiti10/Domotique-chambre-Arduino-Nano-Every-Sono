/**
 * @file main.cpp
 * @author Louis L
 * @brief Fichier principal de l'Arduino Nano Every gérant le DEL infrarouge qui contrôle la sono.
 * @version 1.0
 * @date 2023-03-07
 */

/*
 * Informations :
 * Pour allumer la sono, envoyer une impulsion de 50ms.
 * Pour diminuer le volume, envoyer une impultion de 100ms.
 * Pour augmenter le volume, envoyer une impultion de 150ms.
 */

// Ajout des bibliothèques au programmes.
#include <Arduino.h>
#include <IRremote.h>
#include <main.hpp>

// Variables globales.
int VDataValue = 0;

void setup()
{
  IrSender.begin(3);
  pinMode(PCData, INPUT_PULLUP);
}

void loop()
{
  // Vérification de l'état de la broche pour savoir si une information est reçue.
  VDataValue = digitalRead(PCData);
  if (VDataValue == 0)
  {
    // Analyse du message reçu.
    int VCounter = millis();
    while (VDataValue == 0)
    {
      VDataValue = digitalRead(PCData);
    }
    VCounter = millis() - VCounter;

    //Exécution du code en fonction du message reçu (voir plus haut).
    if (VCounter < 75 && VCounter > 25)
    {
      //Plusieurs répétitions pour être sûr que la sono permute.
      for (int i = 0; i < 5; i++)
      {
        delay(10);
        IrSender.sendNEC(0x44C1, 0x87, 3);
      }
    }

    else if (VCounter < 125)
    {
      IrSender.sendNEC(0x44C1, 0xC7, REPETITIONS_VOLUME);
    }

    else if (VCounter < 175)
    {
      IrSender.sendNEC(0x44C1, 0x47, REPETITIONS_VOLUME);
    }

    delay(500);
  }
}