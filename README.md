# Online-Shopping-System-in-C++
Introduction
This is a simple command-line-based Online Shopping System implemented in C++. It provides basic functionality for user login, registration, shopping, and transaction recording. The system differentiates between regular customers and an admin with additional privileges.

Features
User Authentication:
Users can log in with their username and password.
New users can register to create an account.
Users can recover their account using a forget password feature.

Shopping Categories:
The system offers three main shopping categories: Men's, Women's, and Kids'.
Each category further includes Eastern and Western sections (for Men and Women) and Girl's and Boy's sections (for Kids).
Shopping Cart:

Users can add items to their shopping cart.
The system supports different sizes for items, and users can select their preferred size.
Quantities are managed based on the available stock.

Discounts for Special Customers:
Different levels of customers (Silver, Golden, Diamond) are implemented, each with its discount criteria.
Discounts are applied based on the total amount of the purchase.

Transaction Recording:
After shopping, the system generates an invoice, applies discounts, and records the transaction details.
Transaction records are stored in a TransactionRecord.txt file.

Admin Panel:
Admins can log in with a separate username and password.
The admin menu includes the option to view transaction records.
