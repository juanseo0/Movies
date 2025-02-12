### Movies Project

This program uses polymorphism and factory method pattern to imitate a movie store. It will initalize the contents of the inventory from a file (data4movies.txt), the customer list from another file (data4customers.txt), and then process an arbitrary sequence of commands from a third file (data4commands.txt).

### Description
A local movie rental store wishes to automate their inventory tracking system. Currently there are three types of movies/videos (in DVD media) to be tracked:

- Comedy (denoted as ‘F’ for funny)
- Drama (denoted as ‘D’)
- Classics (denoted as ‘C’)
- Borrows and returns of items by customers are also to be tracked.

Four types of actions are desired in the system:

- Borrow (denoted as ‘B’): (stock – 1) for each item borrowed  
- Return (denoted as ‘R’): (stock + 1) for each item returned
- Inventory (denoted as ‘I’): outputs the inventory of all the items in the store
- History (denoted as ‘H’): outputs all the transactions of a customer

### Testing
Use ./create-output.sh > output.txt 2>&1 to test the program
