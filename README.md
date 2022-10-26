# I2C-communication
The C-code of a master and slave that communicate over I2C.
The code was written in Atmel Studio and is supposed to demonstrate the functionality of the I2C communication between two Arduino UNO/NANO.

# Master

- reads the state of a button
- Send the button state over I2C to the slave
- controls the I2C communication

# Slave

- Displays on an LCD 20x4 the state of the button: "Btn. pressed" or "Btn. not pressed"

![Schematic](https://user-images.githubusercontent.com/75970114/198071869-87bfaadc-0b58-4169-99fc-0380deb23673.png)
