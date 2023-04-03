# ComS327-CSV
### Author:
Ethan Hancock, ehancock@iastate.edu
### TA Notes: 
> 

### Description:
#### Major Changes:
 - parse.cpp & parse.h added
    - parse.cpp holds all the logic to parse the csv files

#### Methods Added
 - Within parse.cpp:
    - verifyFile()
        - Called in csv.cpp to verify that the parameter passed via command line is a valid csv file name
    - parseFile()
        - Handle checking the two places the database could be stored in, first checking /share/ then /$HOME/
        - Neither of those directories exist then "Database not found" is outputted
    - readFile()
        - Called by parseFile() if a directory is found that contains the database
        - Handles actually reading the file and nicely outputting the data.
            - Builds objects out of the data and stores them in a std::vector which could be returned for use in other code later.
