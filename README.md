# I2C-communication
The C-code of a master and slave that communicate over I2C.
The code was written in Atmel Studio and is supposed to demonstrate the functionality of the I2C communication between two Arduino UNO/NANO.

# Master

- reads the state of a button
- Send the button state over I2C to the slave
- controls the I2C communication

# Slave

- Displays on an LCD 20x4 the state of the button: "Btn. pressed" or "Btn. not pressed"
![Schematic](https://user-images.githubusercontent.com/75970114/197552101-32ad1437-7aba-4bd2-8dca-93f09380c5e5.png)
