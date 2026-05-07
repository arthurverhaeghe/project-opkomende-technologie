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
  * Een end switch
    * Deze staat default ingeschakeld
  * Een load cell
  * Een led-strip
  * Een batterij
  

### Logica

[Zie hier]() voor het schakel schema van de componenten  

#### Bakken

#### Kast
