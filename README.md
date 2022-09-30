## HW 2

 - Name: Kourosh Arfania
 - Email: arfania@usc.edu

### Programming Problem Notes

 - Compiling the Code:

(1) navigate to locally stored docker folder and run an instance of the csci104 container (ch start csci104,
 ch shell csci104)

(2) once in the container, navigate to code's main directory (cd hw2/)

(3) run make amazon in the terminal 

 - Running the Code:
 ./amazon <filename.txt>
 
 (example file, database.txt, provided in file directory: ./amazon database.txt)

 - Design decisions made or other non-trivial choices of implementation:
 
 (1) for the ADD username hit_result_index, pass in the matching index displayed by the screen
 ex: to add the first hit of the prior search term to kory's cart, run ADD kory 1 (not ADD kory 0)

(2) usernames and keywords are always in lower-case to allow for case insensitive searching through
 the menu
 
(3) program outputs what products were and were not purchased from a user's cart after BUYCART, as it improves clarity and helps with testing dump()

(4) database1.txt included in the repository to show the correct functionality of dump() when QUIT is called
