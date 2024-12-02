import machine
import array as arr
from machine import Pin
from machine import UART
from micropython import const
import time

# Define pins and constants
receive_buffer = []

# Initialize UART
uart = UART(0, 9600, tx=Pin(0), rx=Pin(1))

# Interrupt handler for receiving data

while True:
    uart.write('Hi\0')  # Send a message
    while(uart.any()>0):
        receive_buffer  = uart.read()
        receive_buffer = receive_buffer.decode('utf8')
        print(f"{receive_buffer}")
        
    time.sleep(5)

