# CigaretteSmoker-Problem
Solutions to the Cigarette Smoker problem using semaphores and pthread in C

Consider a system with 3 smoker processes and 1 agent process. Each smoker continuously rolls a cigarette and then smokes it. 
The smoker needs three ingredients: tobacco, paper, and matches. One of the smokers has paper, another has tobacco, and the third 
has matches. The agent has an infinite supply of all three materials and (randomly) places two of the ingredients on the table each time. 
The smoker who has the remaining ingredient then makes and smokes a cigarette, signaling the agent on completion. The agent then puts out 
another two of the three ingredients, and the cycle repeats. 
