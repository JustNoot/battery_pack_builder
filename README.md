# Battery Pack Builder

This program will "build" your battery pack for you. Input your cell capacities in battery.txt then run the program and give it your desired configuration and tha maximum difference in mAh. For large number of cells the program may run for a long time.

In the included example files I built a 5s20p pack which took the program 10 minutes with a 800 mAh maximum delta.

In battery.txt you should:
  only input the cell capacities, 1 in each row
  input exactly as many cells as your configuration requires (can be more but later rows will be ignored)
  
In pack.txt you get:
  the number of tries it took to finish
  the biggest difference in the pack (open check.txt for more info)
  the cell capacities which should be paralelled together in every row
