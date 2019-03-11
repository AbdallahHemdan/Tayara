# 🍕 Tayary 
---------------------------------
## ✔ Main idea
Tayara is delivery system which manage the process of receiving
the orders and deliver it to the customer.
---------------------------------
## 📝 Project description
Our system receive a list of orders as input.
This list represents the scenario to be simulated.

For each order, the system will receive the following information:

- Arrival Time Stamp: When the order was made.
- Order Type: There are 3 types of orders: VIP orders, Frozen orders and Normal orders.

• VIP orders must be serviced first before frozen and normal orders.
• Frozen orders are the orders that needs to be delivered using motorcycles with
refrigerators (Frozen Motorcycles) to keep its temperature low.
• Normal orders are the orders that neither VIP nor Frozen.

- Order Region: the restaurant has 4 branches. Each branch is in a different region. The
Order Region indicates the region of the order and hence the branch that should deliver the
order to the customer.
- Order Distance: the distance between the restaurant and the order location (in meters).
- Order Money: the total order money the customer should pay.

At startup, the system loads (from a file) information about the available motorcycles. For
each motorcycle, the system will load the following information:
- Motorcycle Type: There are 3 types: Fast motorcycles, Frozen motorcycles and Normal
motorcycles.

• Fast motorcycles are motorcycles with higher speed level.
• Frozen motorcycles are the motorcycles that have small refrigerator to save food
in.
• Normal motorcycles are the motorcycles that neither Fast nor Frozen.

- Motorcycle Region: the branch or the region of this motorcycle (from which the motorcycle
starts its delivery and to which it returns after delivery).
- Note: The Motorcycle speed (the number of meters it can move in one timestep) is the
same for all motorcycles of the same type
