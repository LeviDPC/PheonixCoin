# PheonixCoin is awesome!

This i a crypto currency simulation I wrote for a class project. If you look at my repositories you will find the front end written by another student.

A config file called cppConfig.txt is used to input data into the program.

There are 3 opperation you can call: 1. add a user to the database, 2. add a transaction to the current unmined block 3. mine the current unmined block.

You can find examples of how to structure the cppConfig.txt file in the examples folder. It is worth noting that you can't have any coments in the config file and it has to be named exactly cppConfig.txt

At the beggining of the program the user list is loaded from users.json, the current unmined block is loaded from unminedBlock.json and the block chain is loaded from blockchain.json. If one or more of the files don't exist than blank objects will be created. At the end of the program it will create these files and output the data in ram into them.

Throught the runtime of this program it will create temp files. These are kept and not deleted because they make debugging easier but aren't important except for that.

These files are fromatted in valid JSON, that being said the program can't take input from any old json file. They have to be formated specifically. You should either use the program to manipulate the data or be very carefull when doing it by hand. That being said it handles you putting in empty values through the config file fine unless they are values for things that are designed to be required.

at hte end of it's runtime the program will create a file called results.txt The first line will be contain Success! or Failure! and the following lines will contain more information.

My thought is that the front end should let the user do the 3 things (create user, create transaction, mine) and view the 3 data sources(users, unmined blocks, and the whold blockChain)

All the basic features are implented. You can create users, transactions and when you mine the transactions the user list is updated and balances are calculated. 

More testing should be done and I still have a crap tone of clean up to do on the code but the basics are there.

hmu if you find any bugs



SHA-256 comes from picosha2. Check out the github here: https://github.com/okdshin/PicoSHA2. Picosha2 is released under the MIT Liscense which can be found in picosha2.h.
