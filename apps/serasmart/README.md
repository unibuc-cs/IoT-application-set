# Sera Smart – Echipa 17
O sera inteligenta cu control de la distanta si integrare cu mqtt!
Acest proiect iti ofera posibilitatea de a seta senzori de `temperatura`, `umiditate`, `lumina`, `miscare` in propia sera si de a-i monitoriza de la distanta. Iar atunci cand valori depasesc un prag sau se doreste modificarea mediului intern se pot efectua de la distanta doua actiuni: `deschiderea usii` pentru o ventilatie mai buna sau `a geamului` pentru controlul luminii si a umiditatii.

#### Documentatia API se regaseste [aici](APIDocumentation/)


#### Proiect realizat cu:
[Python 3.7](https://www.python.org/downloads/release/python-370/)<br>
[Flask](https://flask.palletsprojects.com/en/2.0.x/)<br>
[Mosquitto](https://mosquitto.org/download/)<br>
[OpenAPI Specs](https://editor.swagger.io/)<br>
[AsyncAPI Specs](https://playground.asyncapi.io/)<br>
[Pytest](https://docs.pytest.org/en/6.2.x/)<br>
[PyYAML](https://pyyaml.org/)<br>
[SQLite](https://www.sqlite.org/docs.html)<br>

#### Membrii echipei:
[Dudau Vlad](https://github.com/vladdudau)<br>
[Gal Iulian](https://github.com/iuliangal186)<br>
[Mindrescu Albert-Codrin](https://github.com/MindrescuAlbert)<br>
[Neculae Andrei-Sorin](https://github.com/sorinNgit)<br>
[Reznicencu Sergiu](https://github.com/AntonVonDelta)<br>
[Staicu Bogdan](https://github.com/StaicuBogdan)<br>

## Instalare
Instaleaza pachetele `py -3.7 -m pip install flask pytest coverage pyyaml`

## Executia programului
Mai intai se creeaza baza de date:
- ``py -3.7 app.py init-db``
- ``python app.py init-db``

Se executa prin comenzile:
- ``py -3.7 app.py``
- ``python app.py``



## Evaluare
 - Nota finală va fi data de două elemente: 
   - 1 punct din oficiu
   - 9 puncte -> programul realizat
 - Programul trebuie să respecte următoarele cerințe (2.5p):
   - [x] Expune un Rest API HTTP – documentat folosind Open API (Swagger)
   - [x] Expune un API MQTT – documentat folosind AsyncAPI
   - [x] Aplicația să aibă minim 5 funcționalități – puteți să vă gândiți la ele ca sell points ale aplicației. Depinde de aplicația pe care v-ați propus să o faceți, dar chestii de genul o funcționalitate e scăderea, o altă funcționalitate e adunarea, nu înseamnă chiar că sunt diferite
   - [x] Tot ce faceți să se găsească într-un singur repo.
 - Pentru puncte programul trebuie să respecte următoarele cerințe:
   - [x] Toate funcționalitățile și/sau toate endpoints au unit teste asociate. +1.5p
   - [x] Documentația de analiză este up to date + 1p
   - [x] Documentația de utilizare reflectă aplicația reală + 1p
   - [x] Să prelucreze date reale (fie că accesează un alt api pentrua prelua date, fie că descărcați un set de date pe care îl dați apoi aplicației) + 1p
   - [x] Utilizarea unui tool de testare automată (gen RESTler) pentru a identifica buguri. +1.5p
   - [x] Integration tests +1p
   - [x] Coverage al testelor de 80% + 0.5p


## Testarea proiectului
In path-ul `Unit Tests` sunt definite atat unit tests cat si integration tests.

Se executa:
- `cd "Unit Tests"`
- `py -3.7 -m pytest`

Pentru coverage:
- `py -3.7 -m coverage run -m pytest`
- `py -3.7 -m coverage report`

![image](https://user-images.githubusercontent.com/25268629/152255607-d3f42968-664a-4017-8b12-00dad12a5843.png)


## AsyncAPI
[Specificația AsyncAPI](https://www.asyncapi.com/docs/specifications/v2.0.0) este un limbaj de specificații cuprinzător pentru descrierea API-urilor de mesagerie asincronă 

Instalati generatorul de AsyncAPI:
```sh
npm install -g @asyncapi/generator
```

Apoi executa::
```
cd APIDocumentation
ag asyncapi.yml https://github.com/asyncapi/html-template
```



## Document de analiză a cerințelor clientului

#### Scopul aplicației: 
*Aplicatia are ca scop modificarea serei traditionale prin automatizarea acesteia, folosindu-se de date de natura variabila pe care le preia din mediul inconjurator (lumina, temperatura, umiditate etc.). Aceasta aplicatie poate fi rulata si parametrii pot fi modificati de catre utilizator remote prin intermediul telefonului/desktopului si va oferi un feedback in timp real a conditiilor din sera.*

#### Obiectivele aplicației:
- Sera va avea ca scop maximizarea cantitatii de recolta din interiorul acesteia de-a lungul timpului.
- Aceasta va economisi resursele neregenerabile folosite si timpul persoanei care o detine/opereaza. 
- Aplicatia ar trebui sa fie usor de folosit si foarte intuitiva*.*


#### Grupul țintă
Aplicatia se adreseaza agricultorilor, dar si amatorilor pasionati de legumicultura, ce cauta sa isi automatizeze propriile culturi.

- Ca agricultor, as vrea sa pot sa accesez o serie de statistici relevante despre sera, pentru a optimiza calitatea viitoarei recolte.
- Ca agricultor, as vrea sa pot modifica parametrii din interior, precum umiditatea solului, temperatura aerului, cantitatea de lumina, pentru a influenta recolta. 
- Ca utilizator, mi-ar fi foarte util ca aplicatia sa fie foarte usor de folosit.
- Ca legumicultor amator, as dori sa pot sa ma descurc cu sera intr-un mod cat mai necostisitor.


#### Colectarea cerințelor

- prezenta unui spatiu de stocare ce retine in timp datele senzorilor si compileaza statistici pe baza lor.
- folosirea unui numar minim de senzori de temperatura, umiditate, lumina.
- accesarea unui api extern pentru preluarea datelor metereologice.
- citirea unui senzor de temperatura.
- citirea unui senzor de umiditate.
- citirea unui senzor de lumina.
- citirea unui senzor de miscare.
- actionarea de la distanta al unei usi.
- actionarea de la distanta al unui geam.
- performanta sistemului nu este critica.
- conexiunea la internet.


### Interpretarea și prioritizarea cerințelor

*1. Label-uiți cerințele funcționale / non-funcționale.* 

- prezenta unui spatiu de stocare ce retine in timp datele senzorilor si compileaza statistici pe baza lor.      **Functional**
- folosirea unui numar minim de senzori de temperatura, umiditate, lumina.  **Nonfunctional**
- accesarea unui api extern pentru preluarea datelor metereologice.  **Functional**
- citirea unui sensor de temperatura.       **Functional**
- citirea unui sensor de umiditate.            **Functional**
- citirea unui sensor de lumina.        **Functional**
- citirea unui sensor de miscare.        **Functional**
- actionarea de la distanta al unei usi.    **Functional**
- actionarea de la distanta al unui geam.     **Functional**
- performanta sistemului nu este critica.    **Nonfunctional**
- conexiunea la internet.            **Functional**
- accesarea sistemului prin HTTP  **Functional**
- implementarea serverului prin tehnologia MQTT   **Functional**



*2. Gruparea cerințelor*

###### STOCAREA DATELOR

- prezenta unui spatiu de stocare ce retine in timp datele senzorilor si compileaza statistici pe baza lor.

###### PERFORMANTA 

- folosirea unui numar minim de senzori de temperatura, umiditate, lumina, miscare.
- performanta sistemului nu este critica.

###### FUNCTIONABILITATE

- conexiunea la internet.
- compilare de statistici.

###### APIs

- accesarea unui api extern pentru preluarea datelor metereologice.

###### CITIREA SI PRELUCRAREA DATELOR

- citirea unui sensor de temperatura.
- citirea unui sensor de umiditate. 
- citirea unui sensor de lumina.        
- citirea unui sensor de miscare. 
- citirea unui api extern si compilarea temperaturii furnizate cu cea raportata de senzor.



*3. Proiectul de github creat* 

*4. Play planning poker.* 

###### Poker planning dupa dificultate:
1. prezenta unui spatiu de stocare ce retine in timp datele senzorilor si compileaza statistici pe baza lor. Functional 3 3 3 4 = 3.25
2. folosirea unui numar minim de senzori de temperatura, umiditate, lumina. Nonfunctional 1 2 1 2 = 1.50
3. accesarea unui api extern pentru preluarea datelor metereologice. Functional 2 3 2 3 = 2.50 
4. citirea unui sensor de temperatura. Functional 2 2 2 2 = 2 
5. citirea unui sensor de umiditate. Functional 2 2 2 2 = 2 
6. citirea unui sensor de lumina. Functional 2 2 2 2 = 2 
7. citirea unui sensor de miscare. Functional 2 2 2 2 = 2 
8. performanta sistemului nu este critica. Nonfunctional 1 1 1 2 = 1.25 
9. conexiunea la internet. Functional 4 2 1 3 =2.50 

###### Poker planning dupa prioritate:
1. prezenta unui spatiu de stocare ce retine in timp datele senzorilor si compileaza statistici pe baza lor. Functional 3 3 3 4 = 3.25; Prioritate= 5 5 5 5 = 5 
2. folosirea unui numar minim de senzori de temperatura, umiditate, lumina. Nonfunctional 1 2 1 2 = 1.50; Prioritate= 1 1 3 5 = 2.5 
3. accesarea unui api extern pentru preluarea datelor metereologice. Functional 2 3 2 3 = 2.50; Prioritate= 4 5 4 4 = 4.25 
4. citirea unui sensor de temperatura. Functional 2 2 2 2 = 2; Prioritate= 3 4 4 3 = 3.50
5. citirea unui sensor de umiditate. Functional 2 2 2 2 = 2; Prioritate= 3 4 4 3 = 3.50 
6. citirea unui sensor de lumina. Functional 2 2 2 2 = 2; Prioritate= 3 4 4 3 = 3.50 
7. citirea unui sensor de miscare. Functional 2 2 2 2 = 2; Prioritate= 3 4 4 3 = 3.50 
8. performanta sistemului nu este critica. Nonfunctional 1 1 1 2 = 1.25; Prioritate= 1 1 2 2 = 1.50 
9. conexiunea la internet. Functional 4 2 1 3 =2.50; Prioritate= 3 5 5 3 = 4 

*5. Plot the issues.* 
![Axa Dificultate/Prioritate](https://cdn.discordapp.com/attachments/899336393657036871/902527635400327198/Screenshot_2021-10-26_150217.png)

