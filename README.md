# Project Opkomende Technologieën

<img width="2810" height="2481" alt="image" src="https://github.com/user-attachments/assets/620af287-151b-47fc-a59f-51c50e57e4c3" />


## Introductie

>### Studenten
>Arthur Verhaeghe - Student in Industrieel Ontwerpen  
>Kylian Maelstaf - Schakelstudent in Industrieel Ontwerpen

In kader van het vak Opkomende Technologieën werd gekozen om het softwarepakket zo ver als mogelijk uit te werken voor PlayClean -- het concept van [project GGO](https://github.com/RJ-917/Opruimkast).  
  
Hiermee trachten we een werkend prototype te bereiken die functioneel alle verreisten behaalt.

## Project GGO

PlayClean is een slimme speelgoedkast die kinderen op een speelse en gestructureerde manier leert opruimen en bewuster laat spelen. Veel ouders ervaren frustratie door tijdsgebrek, vermoeidheid en een overvloed aan speelgoed. Kinderen raken hierdoor snel afgeleid en spelen minder geconcentreerd, terwijl ouders geconfronteerd worden met rommel en extra stress. Bestaande opbergoplossingen focussen vooral op opslag en ondersteunen het aanleren van opruimgedrag onvoldoende. PlayClean biedt een laagdrempelig alternatief dat spel en structuur combineert.  
  
De kast werkt met een ingebouwd vergrendelingssysteem waarbij slechts één compartiment tegelijk toegankelijk is. Pas wanneer dit vak volledig is opgeruimd, wordt het volgende ontgrendeld. Deze aanpak stimuleert focus, verantwoordelijkheid en zelfstandigheid bij kinderen, zonder voortdurende tussenkomst van ouders. Dankzij de intuïtieve werking en duidelijke visuele structuur leren kinderen spelenderwijs omgaan met orde.  
  
Het ontwerp van PlayClean is gebaseerd op literatuuronderzoek, benchmarking, interviews en usertests met ouders, met aandacht voor gebruiksgemak, veiligheid en duurzaamheid. Door de educatieve en gezinsgerichte aanpak vermindert PlayClean rommel en opvoedstress en draagt het bij aan meer rust en overzicht in huis.  
  

## Uitwerking

### Lijst van gebruikte componenten

* Een ESP32 in de kast die als server functioneert, waarop alle logica staat.
  * Een batterij  
  
* Een ESP32 per bak die elk als unieke client functioneert, die naar de server luistert.
  * Een solenoïde
    * Deze staat default uitgeschakeld
    * Als de solenoïde ingeschakeld is kan de bak uit de kast gehaald worden.
  * Een end switch
    * Deze staat default ingeschakeld
    * Deze dient als input om aan te tonen dat de bak wil uitgehaald worden
  * Een load cell
    * Zal het gewicht in de bak meten
  * Een led-strip
    * Zal blauw flikkeren wanneer de ESP32 geïnitialiseerd is.
    * Zal volledig groen branden als het correcte gewicht in de bak zit.
    * Zal een percentage van de LEDs in de strip uitschakelen naarmate hoeveel gewicht tekort is in de bak.
    * Zal volledig rood branden als er teveel gewicht in de bak zit.
  * Een batterij
  

### Logica

[Zie hier](https://github.com/arthurverhaeghe/project-opkomende-technologie/blob/main/imgs/schakel%20schema.png) voor het schakel schema van de componenten.  

#### Setup

De load cell wordt bij het opstarten van de ESP32 eerst getared.  
  
Hierna zal het speelgoed in de bak geplaatst worden en zal een knop ingedrukt worden om het gewicht te bevestigen.  
  
Nu zal de LED strip van deze bak groen worden, wat aanduidt dat deze klaar is om in de kast te plaatsen.  
  

#### Gebruik

Om de communicatie te realiseren tussen de ESP32s, word BLE gebruikt.  
  
In elke bak zit een ESP32, waarvan één bak zijn ESP32 zal functioneren als server, en alle andere bakken hun ESP32s als client.  
  
De bak met de server zal alle logica regelen van wanneer een bak uit de kast gehaald mag worden. De andere bakken zullen als client luisteren naar de server.  
  
De client stuurt elke 100ms een datapakket naar de server met daarin de status van de end switch. De server verwerkt deze informatie en stuurt op zijn beurt elke 100ms een pakket terug naar elke client met daarin de systeemtoestand en het commando voor de solenoïde.  
  
Een bak mag enkel uit de kast gehaald worden als aan de volgende condities voldaan zijn:  
  
* Er is op dat moment slechts één bak waarvan de end switch contact verbroken heeft.
* Er is geen andere bak tegelijk actief (als meerdere end switches tegelijk contact verbreken, gaat het systeem in CONFLICT en wordt geen enkele solenoïde geactiveerd).
* Het gewicht in de bak is correct.
  
Als deze condities voldaan zijn, stuurt de server een commando terug naar de betreffende client, die dan de solenoïde activeert.  
  
Wanneer de end switch opnieuw contact maakt (bak terug in de kast), verdwijnt die client automatisch uit de actieve lijst en deactiveert de server het solenoïde-commando. De client zet de solenoïde dan onmiddellijk uit zodra hij het bijgewerkte pakket ontvangt.  
  
Als een client meer dan 5 seconden geen pakket stuurt, beschouwt de server die client als verloren (TIMEOUT) en wordt de solenoïde ook gedeactiveerd.  
